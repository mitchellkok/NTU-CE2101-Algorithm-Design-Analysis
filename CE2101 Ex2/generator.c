#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main()
{
    srand(time(0)+getpid());

    int size, edges, mult, root, v1, v2, weight;
    
    //printf("Enter the number of vertices:\n");
    scanf("%d",&size);

    //printf("Enter the vertex multiplier for edges\n");
    scanf("%d",&mult);

    //printf("Enter the root\n");
    scanf("%d",&root);

    int **matrix = (int **)malloc(size*sizeof(int *));
    for(int i = 0; i < size; i++)
        matrix[i] = (int *)malloc(size*sizeof(int));

    for(int i = 0; i < size; i++)
       for(int j = 0; j < size; j++) {
           matrix[i][j] = 0;
       }

    edges = (int)(size*3);

    int i = edges, check = 0;
    while (i > 0 || check == 0) {
        
        do {
            v1 = 1 + (rand() % size);
            v2 = 1 + (rand() % size);
        } while (v2 == v1 || matrix[v1-1][v2-1] != 0);

        weight = 1 + (rand() % (size/3)); //more manageable weights
        matrix[v1-1][v2-2] = weight;
        matrix[v2-1][v1-2] = weight;

        for(int j = 0; j < size; j++) {
            if (matrix[root-1][j] != 0) check = 1;
        }

        printf("%d %d %d\n", v1, v2, weight);
        i--;
    }


}