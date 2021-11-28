#include <stdio.h>
#include <stdlib.h>

static inline int max(int a, int b) {
    if (a > b)
        return a;
    else 
        return b;
}

int knapsack(int* w, int* p, int C, int n)  
{  
    int profit[C];  // create array of profits, to store max profit for given capacity
    for (int i=0; i <= C; i++) profit[i] = 0;

    for (int r = 1; r <= C; r++) {      //  iterate through remaining capacity, from 1 to C
        for (int c = 0; c < n; c++) {   //  iterate through item number, from 0 to n-1
            if (w[c] <= r)
                // if weight of item is less than remaining capacity, store the largest profit
                profit[r] = max(profit[r], profit[r-w[c]] + p[c]);
        }
    }

    printf("Cap\tProfit\n");
    for (int r = 0; r <= C; r++) {
        printf("%d:\t%d\n", r, profit[r]);
    }
}

int main()
{
    int C = 14, n = 3;

    int * weight = (int *)malloc(n * sizeof(int));
    weight[0] = 4;
    weight[1] = 6;
    weight[2] = 8;

    int * profit = (int *)malloc(n * sizeof(int));
    profit[0] = 7;
    profit[1] = 6;
    profit[2] = 9;

    knapsack(weight, profit, C, n);
    return 0;
}

