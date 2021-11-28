#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct _listnode
{
	int item;
    int weight;
	struct _listnode *next;
} ListNode;	// You should not change the definition of ListNode

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;	// You should not change the definition of LinkedList

typedef struct _graph{
    int V;	// number of vertices
    int E;	// number of edges
    LinkedList **list; // adjacency list (graph)
}Graph;

typedef struct _heap{
	int capacity;
	int *pos;
	int size;
	ListNode **array;
}Heap;

int* dijkstra_list(Graph g, int root);
int min(Graph g, int d[], int s[]);

ListNode* newHeapNode(int item, int weight);
Heap* newHeap(int cap);
void swapHeapNode(ListNode** a, ListNode** b);
void minHeapify(Heap* minHeap, int index);
ListNode* extractMin(Heap* minHeap);
void decreaseKey(Heap* minHeap, int v, int weight);
int isInMinHeap(Heap *minHeap, int v);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value, int weight);
void insert_ordered(LinkedList *ll, int item, int weight);
int removeNode(LinkedList *ll, int index);

static int comp = 0;
static int swap = 0;
static int max = 0;

int main()
{

    // create adjacency matrix
    Graph g;
    int i,j;

    //printf("Enter the number of vertices:\n");
    scanf("%d",&g.V);

    int root;
    scanf("%d",&root);
    scanf("%*c");
    
    // create adjacency list
    g.E = 0;
    g.list = (LinkedList **)malloc(g.V*sizeof(LinkedList*));
    LinkedList *tmpList;
    for (int i = 0; i < g.V; i++) {
        tmpList = malloc(sizeof(LinkedList));
        g.list[i] = tmpList;
        g.list[i]->size = 0;
        g.list[i]->head = NULL;
    }

    int V1, V2, weight;       
    //* populate adjacency list (from user input)   
    //printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d %d",&V1,&V2, &weight)==3) // scanf returns the number of items successfully read
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            insert_ordered(g.list[V1-1], V2-1, weight);
            insert_ordered(g.list[V2-1], V1-1, weight);
            if (weight >= max) max = weight;
            g.E++;
        }
        else
            break;
        //printf("Enter two vertices which are adjacent to each other:\n");
    }
    max = g.V*max; // ensure maximum path is covered

	//* Print Adjacency List
	printf("Adjacency List [Adjacent Vertex / Weight]\n");
	for (int i = 0; i < g.V; i++) {
        ListNode *tmpNode = g.list[i]->head;
		printf("List %d:", i+1);
        while (tmpNode != NULL) {
            printf(" --> [%d / %d]", (tmpNode->item + 1), tmpNode->weight);
			tmpNode = tmpNode->next;
		}
		printf("\n");
    }
	//*/

	struct timeval  tv1, tv2;
    gettimeofday(&tv1, NULL);

    int *d = dijkstra_list(g, (root-1));

	gettimeofday(&tv2, NULL);

	// print the calculated shortest dists
    printf("\n"); 
    for (int i = 0; i < g.V; i++) 
        printf("Vertex: %d \t  Dist: %d\n", i+1, d[i]); 

    for (int i = 0; i < g.V; i++) {
        ListNode *tmpNode;
        while (g.list[i]->size > 0) {
            tmpNode = g.list[i]->head;
            //printf("Freeing vertex %d from list %d --> weight %d\n", (tmpNode->item + 1), i+1, tmpNode->weight);
            removeNode(g.list[i], 0);
        }
		//printf("freeing %d\n", i+1);
        free(g.list[i]);
    }

	printf("\nCPU Time: %f\n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
	fflush(stdout);
}


int* dijkstra_list(Graph g, int root) 
{ 

    // dist values used to pick minimum weight edge in cut
    int *d = malloc(sizeof(int) * g.V);     
 
    // minHeap represents set E
    Heap* minHeap = newHeap(g.V);
 
    // Initialize min heap with all vertices. dist value of all vertices 
    for (int i = 0; i < g.V; i++)
    {
        d[i] = max;
        minHeap->array[i] = newHeapNode(i, d[i]);
        minHeap->pos[i] = i;
    }
 
    // Make d value of root vertex as 0 so that it is extracted first
    minHeap->array[root] = newHeapNode(root, d[root]);
    minHeap->pos[root] = root;
    d[root] = 0;
    decreaseKey(minHeap, root, d[root]);
 
    // Initially size of min heap is equal to V
    minHeap->size = g.V;
 
    // In the followin loop, min heap contains all node whose shortest dist is not yet finalized.
    while (minHeap->size != 0)
    {
        // Extract the vertex with minimum dist value
        ListNode* minHeapNode = extractMin(minHeap);
       
        // Store the extracted vertex number
        int u = minHeapNode->item; 
 
        // Traverse through all adjacent vertices of u (the extracted vertex) and update their dist values
        ListNode* tmpNode = g.list[u]->head; 
        while (tmpNode != NULL)
        {
            int v = tmpNode->item;
 
            // If shortest dist to v is not finalized yet, and dist to v
            // through u is less than its previously calculated dist
            if (isInMinHeap(minHeap, v) == 1 && tmpNode->weight + d[u] < d[v])
            {
                d[v] = d[u] + tmpNode->weight;

                // update dist value in min heap also
                decreaseKey(minHeap, v, d[v]);
            }
            tmpNode = tmpNode->next;
        }
    }

	return d;
} 

int min(Graph g, int d[], int s[]) 
{ 
    // Initialize min value 
    int min = max, min_index; 
  
    for (int v = 0; v < g.V; v++) 
        if (s[v] == 0 && d[v] <= min) 
            min = d[v], min_index = v; 
  
    return min_index; 
} 

//////////////////////////////////////////////////////////////////////////////////

ListNode* newHeapNode(int item, int weight) {
	ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
	newNode->item = item;
	newNode->weight = weight;
	newNode->next = NULL;

	return newNode;
}

Heap* newHeap(int cap) {
	Heap *newH = (Heap*)malloc(sizeof(Heap));
	newH->pos = (int *)malloc(sizeof(int)*cap);
	newH->capacity = cap;
	newH->size = 0;
	newH->array = (ListNode**)malloc(sizeof(ListNode*) * cap);

	return newH;
}

void swapHeapNode(ListNode** a, ListNode** b) {
    ListNode *t = *a;
    *a = *b;
    *b = t;
}

void minHeapify(Heap* minHeap, int index) {
    int smallest, left, right;
    smallest = index;
    left = 2 * index + 1;
    right = 2 * index + 2;
 
    if (left < minHeap->size &&
        minHeap->array[left]->weight < 
         minHeap->array[smallest]->weight )
      smallest = left;
 
    if (right < minHeap->size &&
        minHeap->array[right]->weight <
         minHeap->array[smallest]->weight )
      smallest = right;
 
    if (smallest != index)
    {
        // The nodes to be swapped in min heap
        ListNode *smallestNode = minHeap->array[smallest];
        ListNode *indexNode = minHeap->array[index];
 
        // Swap positions
        minHeap->pos[smallestNode->item] = index;
        minHeap->pos[indexNode->item] = smallest;
 
        // Swap nodes
        swapHeapNode(&minHeap->array[smallest], &minHeap->array[index]);
 
        minHeapify(minHeap, smallest);
    }
}

// Standard function to extract minimum node from heap
ListNode* extractMin(Heap* minHeap) {
    if (minHeap->size == 0)
        return NULL;
 
    // Store the root node
    ListNode* root = minHeap->array[0];
 
    // Replace root node with last node
    ListNode* lastNode =  minHeap->array[minHeap->size - 1];
    minHeap->array[0] = lastNode;
 
    // Update position of last node
    minHeap->pos[root->item] = minHeap->size-1;
    minHeap->pos[lastNode->item] = 0;
 
    // Reduce heap size and heapify root
    --minHeap->size;
    minHeapify(minHeap, 0);
 
    return root;
}
 
// Function to decreasy d value of a given vertex v. This function
// uses pos[] of min heap to get the current index of node in min heap
void decreaseKey(Heap* minHeap, int v, int weight) {
    // Get the index of v in  heap array
    int i = minHeap->pos[v];
 
    // Get the node and update its d value
    minHeap->array[i]->weight = weight;
 
    // Travel up while the complete tree is not heapified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->weight < minHeap->array[(i - 1) / 2]->weight)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->item] = (i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->item] = i;
        swapHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);
 
        // move to parent index
        i = (i - 1) / 2;
    }
}
 
// A utility function to check if a given vertex 'v' is in min heap or not
int isInMinHeap(Heap *minHeap, int v) {
    if (minHeap->pos[v] < minHeap->size)
		return 1;

    return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void insert_ordered(LinkedList *ll, int item, int weight) {
    ListNode *tmpNode = ll->head;
    for (int i = 0; i < ll->size; i++) {
        if (item < tmpNode->item) {
            insertNode(ll, i, item, weight);
            return;
        }
		tmpNode = tmpNode->next;
    }
	insertNode(ll, ll->size, item, weight);
}

void printList(LinkedList *ll){

	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;
	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}


void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}


ListNode * findNode(LinkedList *ll, int index){

	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value, int weight){

	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size + 1)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		if (ll->head == NULL)
		{
			exit(0);
		}
		ll->head->item = value;
        ll->head->weight = weight;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		if (pre->next == NULL)
		{
			exit(0);
		}
		pre->next->item = value;
        pre->next->weight = weight;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}


int removeNode(LinkedList *ll, int index){

	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;
		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}