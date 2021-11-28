#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct _listnode
{
	int item;
	struct _listnode *next;
} ListNode;	

typedef struct _linkedlist
{
	int size;
	ListNode *head;
} LinkedList;	

typedef struct _queue
{
	LinkedList ll;
} Queue;  

typedef struct _graph{
    int V;	// number of vertices
    int E;	// number of edges
    int **matrix; // adjacency matrix (graph)
}Graph;

int* dijkstra_matrix(Graph g, int root);
int min(Graph g, int d[], int s[]);

int peek(Queue *q);
void enqueue(Queue *q, int item);
void dequeue_spec(Queue *q, int item);
void enqueue_ordered(Queue *q, int item);
int dequeue(Queue *q);
int isEmptyQueue(Queue *q);
void removeAllItemsFromQueue(Queue *q);

void printList(LinkedList *ll);
void removeAllItems(LinkedList *ll);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
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

    g.E = 0;
    g.matrix = (int **)malloc(g.V*sizeof(int *));
    for(i=0;i<g.V;i++)
        g.matrix[i] = (int *)malloc(g.V*sizeof(int));
        
    for(i=0;i<g.V;i++)
       for(j=0;j<g.V;j++)
           g.matrix[i][j] = 0;
           
    int V1, V2, weight;       
    //* populate adjacency matrix (from user input)   
    //printf("Enter two vertices which are adjacent to each other:\n");
    while(scanf("%d %d %d",&V1,&V2, &weight)==3) // scanf returns the number of items successfully read
    {
        if(V1>0 && V1<=g.V && V2>0 && V2<=g.V)
        {
            g.matrix[V1-1][V2-1] = weight;
            g.matrix[V2-1][V1-1] = weight;
            if (weight >= max) max = weight;
            g.E++;
        }
        else
            break;
        //printf("Enter two vertices which are adjacent to each other:\n");
    }
    max = g.V*max; // ensure maximum path is covered
    //*/
    
    //* Print Adjacency List
    printf("Adjacency matrix:\n");
     printf("\t");
    for(i=0;i<g.V;i++)
        printf("%d\t", i+1);
    printf("\n\t");
    for(i=0;i<g.V;i++)
        printf("---\t");
    printf("\n");
    for(i=0;i<g.V;i++) {
        printf("%d:\t", i+1);
        for(j=0;j<g.V;j++)
            printf("%d\t", g.matrix[i][j]);
        printf("\n");
    }
    //*/
    
    struct timeval  tv1, tv2;
    gettimeofday(&tv1, NULL);

    int* d = dijkstra_matrix(g, (root-1));

    gettimeofday(&tv2, NULL);

    // print result
    printf("\n"); 
    for (int i = 0; i < g.V; i++) 
        printf("Vertex: %d \t  Dist: %d\n", i+1, d[i]); 

    printf("\nCPU Time: %f\n", (double) (tv2.tv_usec - tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
    fflush(stdout);
}

int* dijkstra_matrix(Graph g, int root) 
{ 
    int *d = malloc(sizeof(int)*g.V); // dist from root to i 
    int *s = malloc(sizeof(int)*g.V); // s[i] marks if vertex is included in shortest path tree with 1
    
    // Populate
    for (int i = 0; i < g.V; i++) {
        d[i] = max;
        s[i] = 0; 
    }
    d[root] = 0; 

    //* priority queue method (see previous commented section)
    Queue *q = malloc(sizeof(Queue));
    q->ll.head = NULL;
    q->ll.size = 0;

    enqueue(q, root);
    for (int i = 0; i < g.V; i++) { // all are max, so order does not matter
        if (i != root)
            enqueue(q, i);
    }

    int tmpSize = g.V;
    while (!isEmptyQueue(q)) {
        int tmp = dequeue(q);
        s[tmp] = 1;
        for (int j = 0; j < g.V; j++) {
            if (g.matrix[tmp][j] > 0 && (d[tmp] + g.matrix[tmp][j]) < d[j]) {
                d[j] = d[tmp] + g.matrix[tmp][j]; 
                enqueue_ordered(q, j);
            }
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
int peek(Queue *q) {
	if (!isEmptyQueue(q))
		return ((q->ll).head)->item;
}

void enqueue(Queue *q, int item) {
	insertNode(&(q->ll), q->ll.size, item);
}

void dequeue_spec(Queue *q, int item) {
printf("Calling ds!\n");
    ListNode *tmpNode = q->ll.head;
    for (int i = 0; i < q->ll.size; i++) {
        if (item == tmpNode->item) {
            removeNode(&(q->ll), i);
            return;
        }
    }
    printf("Nothing Dequeued!\n");
}

void enqueue_ordered(Queue *q, int item) {
    ListNode *tmpNode = q->ll.head;
    for (int i = 0; i < q->ll.size; i++) {
        if (item < tmpNode->item) {
            insertNode(&(q->ll), i, item);
            return;
        }
        tmpNode = tmpNode->next;
    }
	insertNode(&(q->ll), q->ll.size, item);
}

int dequeue(Queue *q) {
	int item;

	if (!isEmptyQueue(q)) {
		item = ((q->ll).head)->item;
		removeNode(&(q->ll), 0);
		return item;
	}
	return -1;
}

int isEmptyQueue(Queue *q) {
	if ((q->ll).size == 0)
		return 1;
	return 0;
}

void removeAllItemsFromQueue(Queue *q)
{
	int count, i;
	if (q == NULL)
		return;
	count = q->ll.size;

	for (i = 0; i < count; i++)
		dequeue(q);
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

int insertNode(LinkedList *ll, int index, int value){

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
