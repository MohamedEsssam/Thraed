//
// Created by mohamedessam on 11/19/18.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

int  N;

//2D Arrays
int *M;

FILE *output;

struct  pos {
    int low;
    int high;
};

void read_merge(){
    FILE *file = fopen("/home/mohamedessam/CLionProjects/untitled1/input1", "r");
    if (!file) {printf("file not found");}
    //inputs for merge sort
    fscanf(file, "%d", &N);
    printf("%d\n", N);
    M=malloc(N * sizeof(int));
    for (int i = 0; i < N; i++ )
        fscanf(file, "%d",&M[i]);

    fclose(file);
    for (int i = 0; i <N ; ++i)printf("%d ",M[i]);
    printf("\n");
}

void merge(int l, int m, int h){
    int *left = malloc((m-l+1)*sizeof(int));
    int *right = malloc((h-m)*sizeof(int));

    // n1 is size of left part and n2 is size
    // of right part
    int n1 = m-l+1, n2 = h-m, i, j;

    // storing values in left part
    for (i = 0; i < n1; i++)
        left[i] = M[i + l];

    // storing values in right part
    for (i = 0; i < n2; i++)
        right[i] = M[i+m+ 1];

    int k = l;
    i = j = 0;

    // merge left and right in ascending order
    while (i < n1 && j < n2) {
        if (left[i] <= right[j])
            M[k++] = left[i++];
        else
            M[k++] = right[j++];
    }

    // insert remaining values from left
    while (i < n1) {
        M[k++] = left[i++];
    }

    // insert remaining values from right
    while (j < n2) {
        M[k++] = right[j++];
    }
}

void *merge_sort(void *n){
    struct pos *data = n;
    struct pos n1 , n2;
    pthread_t pthread , pthread1;
    int mid = (data->low+data->high)/2;
    n1.low=data->low;
    n1.high=mid;
    n2.low=mid +1;
    n2.high=data->high;
    if (data->low<data->high){
        pthread_create(&pthread,NULL,merge_sort,&n1);
        pthread_create(&pthread1,NULL,merge_sort,&n2);
        pthread_join(pthread,NULL);
        pthread_join(pthread1,NULL);
        merge(data->low,mid,data->high);

    }
}

void merge_thread(){
    output = fopen("/home/mohamedessam/CLionProjects/untitled1/output", "a");
    read_merge();
    clock_t begin = clock();
    pthread_t pthread;
    struct pos *data = (struct pos *) malloc(sizeof(struct pos));
    data->low=0;
    data->high=N-1;
    pthread_create(&pthread,NULL,merge_sort,data);
    pthread_join(pthread,NULL);
    fprintf(output,"sorted array\n");
    printf("Sorted Array : ");
    for (int j = 0; j < N; ++j) {
        printf("%d ", M[j]);
        fprintf(output, "%d ", M[j]);
    }
    fprintf(output,"\n");
    printf("\n");
    clock_t end = clock();
    printf("Time taken:%lfsec\n", (double) (end - begin) / CLOCKS_PER_SEC);
    fprintf(output, "Time taken:%lfsec\n", (double) (end - begin) / CLOCKS_PER_SEC);
}