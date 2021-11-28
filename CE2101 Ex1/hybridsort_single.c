#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

void sortSelect(int arr[], int size, int thresh);
void insertion(int arr[], int n, int m);
void hybridsort(int arr[], int n, int m);
void mergesort(int arr[], int n, int m);
void merge(int arr[], int n, int m, int mid);

static int comp = 0;
static int swap = 0;
static int thresh;

int main () {
    /*/
    int thresh = 10;
    int arr[] = { 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    int size = sizeof(arr) / sizeof(arr[0]);
    //*/
    
    //*
    int size;
    //printf("Enter the threshold size:\n");
    scanf("%d", &thresh);
    
    //printf("Enter the array size:\n");
    scanf("%d", &size);
    int *arr0 = malloc(sizeof(int)*size);
    for (int i = 0; i < size; i++)
        arr0[i] = 0;
        
    int input = 0;
    for (int i = 0; i < size; i++) {
        //printf("Enter numbers to add:\n");
	scanf("%d", &input);
	arr0[i] = input;
    }
    
    int *arr = malloc(sizeof(int)*size);
    for (int i = 0; i < size; i++)
        arr[i] = arr0[i];
    //*/

    //*
    printf("\nThe given array is: ");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
    //*/
 
    struct timeval  tv1, tv2;
    gettimeofday(&tv1, NULL);
    
    sortSelect(arr, 0, size - 1);

    gettimeofday(&tv2, NULL);
    
    //*
    printf("\nThe sorted array is: ");
    for (int i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
    //*/
    
    printf("\nHYBRID SINGLE: comp, swap, thresh, size, cpu_time\n");
    printf("HYBRID SINGLE: %d, %d, %d, %d, %f\n", comp, swap, thresh, size, (double) (tv2.tv_usec - 		tv1.tv_usec) / 1000000 + (double) (tv2.tv_sec - tv1.tv_sec));
    
    free(arr0);
    free(arr);
    return 0;
}

void sortSelect(int arr[], int n, int m) {
    if (thresh == -1) {
    	//printf("\nRunning merge sort: %d, %d, %d\n", thresh, n ,m);
    	mergesort(arr, n, m);
    }
    else if (m - n > thresh) {
	//printf("\nRunning hybrid sort: %d, %d, %d\n", thresh, n ,m);
	hybridsort(arr, n, m);
    }
    else {
        //printf("\nRunning insertion sort: %d, %d, %d\n", thresh, n ,m);
    	insertion(arr, n, m);
    }
}

void insertion(int arr[], int n, int m) {
    for (int i = n + 1; i <= m; i++)
    {
        int tmp = arr[i];
        int j = i;
        
        comp++;
        while ((j > n) && (arr[j - 1] > tmp))
        {
            if (j - 1 != n) comp++; //don't count if swapped to arr[n] (0th pos)
            swap++; //key comparison & swap
            arr[j] = arr[j - 1];
            j--; 
        }
    
        arr[j] = tmp;
    }
}

//*
void hybridsort(int arr[], int n, int m) {
    if (n < m) {
    	//comp++;
    	int mid = (m + n) / 2;
    	
    	sortSelect(arr, n, mid);
	sortSelect(arr, mid + 1, m);
	
	merge(arr, n, m, mid);
    }
}

void mergesort(int arr[], int n, int m) {
    if (n < m) {
    	//comp++;
    	int mid = (m + n) / 2;
	
	mergesort(arr, n, mid);
	mergesort(arr, mid + 1, m);
	
	merge(arr, n, m, mid);
    }
}
//*/
//*
void merge(int arr[], int n, int m, int mid) {
    int max1 = mid - n + 1;
    int max2 = m - mid;

    int *tmp1 = malloc(sizeof(int)*max1);
    int *tmp2 = malloc(sizeof(int)*max2);

    for (int i = 0; i < max1; i++) {
        tmp1[i] = arr[n + i];
    }
    for (int i = 0; i < max2; i++) {
        tmp2[i] = arr[1 + mid + i];
    }
    
    int a = 0;  //index for tmp1
    int b = 0;  //index for tmp2
    int c = n;

    while (a < max1 && b < max2) {
        //key comparisons
        comp ++; // comparison in conditional block
        if (tmp1[a] <= tmp2[b]) {
            arr[c] = tmp1[a];
            a++;
        }
        else {
            arr[c] = tmp2[b];
            b++;
        }
        c++;
    }

    while (a < max1) {
        arr[c] = tmp1[a];
        a++;
        c++;
    }

    while (b < max2) {
        arr[c] = tmp2[b];
        b++;
        c++;
    }

    free(tmp1); free(tmp2);
}
//*/
