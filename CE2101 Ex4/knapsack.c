#include <stdio.h>
#include <stdlib.h>

static inline int max(int a, int b) {
    if (a > b)
        return a;
    else 
        return b;
}

int uknapsack(int* w, int* p, int C, int n)  
{  
    printf("-- UNBOUNDED KNAPSACK --\n");
    int profit[C];
    for (int i=0; i <= C; i++) profit[i] = 0;

    for (int r = 1; r <= C; r++) {  
        for (int c = 1; c <= n; c++) {
            if (w[c-1] <= r)
                profit[r] = max(profit[r], profit[r-w[c-1]] + p[c-1]);
        }
    }

    printf("Cap\tProfit\n");
    for (int r = 0; r <= C; r++) {
        printf("%d:\t%d\n", r, profit[r]);
    }
    printf("\n");
}

int knapsack(int* w, int* p, int C, int n)  
{  
    printf("-- REGULAR KNAPSACK --\n");
    int *profit[C];
    for (int i=0; i <= C; i++)
         profit[i] = (int *)malloc(n+1 * sizeof(int));

    for (int c = 0; c <= n; c++) profit[0][c] = 0;  
    for (int r = 0; r <= C; r++) profit[r][0] = 0;  

    for (int r = 1; r <= C; r++) {  
        for (int c = 1; c <= n; c++) {
            profit[r][c] = profit[r][c-1]; 
            if (w[c-1] <= r)
                profit[r][c] = max(profit[r][c], profit[r-w[c-1]][c-1] + p[c-1]);
        }
    }

    printf("\t");
    for (int c = 0; c <= n; c++) printf("%d\t", c);
    printf("\n");
    for (int c = 0; c <= n+1; c++) printf("--\t");

    for (int r = 0; r <= C; r++) {  
        printf("\n%d: \t", r);
        for (int c = 0; c <= n; c++) {
            printf("%d\t", profit[r][c]);
        }
    }
    printf("\n\n");
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
    uknapsack(weight, profit, C, n);
    return 0;
}

