//
// Created by mohamedessam on 11/2/18.
//
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

//columns and rows input
int RA, CA, RB, CB;

//2D Arrays
int **A, **B, **C;

//output file
FILE *output;

//2 global variable to check the correctness of thread operation
int count_rowMulti = 0;
int count_elementMulti = 0;

//struct to hold value of row and column for element multiplication
struct index {
    int row; /* row */
    int colum; /* column */
};



void read_matrix() {
    FILE *file = fopen("/home/mohamedessam/CLionProjects/untitled1/input", "r");
    if (!file) {printf("file not found");}
    //inputs for Matrix 1
    fscanf(file, "%d", &RA);
    fscanf(file, "%d", &CA);
    printf("%d\t%d\n", RA, CA);
    A = malloc(RA * sizeof(int *));
    for (int i = 0; i < RA; i++) {
        A[i] = malloc(CA * sizeof(int));
        for (int j = 0; j < CA; j++)
            fscanf(file, "%d", &A[i][j]);
    }

    for (int i = 0; i < RA; i++) {
        for (int j = 0; j < CA; j++)
            printf("%d ", A[i][j]);
        printf("\n");
    }
    //inputs for Matrix 2
    fscanf(file, "%d", &RB);
    fscanf(file, "%d", &CB);
    printf("%d\t%d\n", RB, CB);
    B = malloc(RB * sizeof(int *));
    for (int i = 0; i < RB; i++) {
        B[i] = malloc(CB * sizeof(int));
        for (int j = 0; j < CB; j++)
            fscanf(file, "%d", &B[i][j]);
    }

    for (int i = 0; i < RB; i++) {
        for (int j = 0; j < CB; j++)
            printf("%d ", B[i][j]);
        printf("\n");
    }

    C = malloc(RA * sizeof(int *));
    for (int i = 0; i < RA; i++)
        C[i] = malloc(CB * sizeof(int));

    fclose(file);
}


void *multi_row(void *arg) {
    count_rowMulti++;
    int *rowNumber = (int *) arg;
    int i = rowNumber;

    for (int j = 0; j < CB; j++)
        for (int k = 0; k < CA; k++)
            C[i][j] += A[i][k] * B[k][j];
}

void row_thread() {
    output = fopen("/home/mohamedessam/CLionProjects/untitled1/output", "a");
    count_rowMulti = 0;
    read_matrix();
    //for calculate time
    clock_t begin = clock();
    pthread_t pthread[RA];
    int *rowNumber = 0;
    for (int i = 0; i < RA; i++) {
        pthread_create(&pthread[i], NULL, multi_row, (void *) (rowNumber));
        int i = rowNumber;
        i++;
        rowNumber = i;
    }
    // joining and waiting for all threads to complete
    for (int i = 0; i < RA; i++)
        pthread_join(pthread[i], NULL);

    printf("row_Multipication_Counter=%d times\n", count_rowMulti);

    fprintf(output, "output array method 1\n");
    printf("output array \n");
    for (int i = 0; i < RA; i++) {
        for (int j = 0; j < CB; j++) {
            printf("%d ", C[i][j]);
            fprintf(output, "%d ", C[i][j]);
        }
        fprintf(output, "\n");
        printf("\n");
    }
    clock_t end = clock();
    printf("Time taken:%lfsec\n", (double) (end - begin) / CLOCKS_PER_SEC);
    fprintf(output, "element_Multipication_Counter=%d times\n", count_rowMulti);
    fprintf(output, "Time taken:%lfsec\n", (double) (end - begin) / CLOCKS_PER_SEC);

}

void *multi_element(void *arg) {
    count_elementMulti++;
    struct index *data = arg; // the structure that holds our data
    int sum = 0; //the counter and sum

    //Row multiplied by column
    for (int i = 0; i < CA; i++) {
        sum += A[data->row][i] * B[i][data->colum];
    }
    //assign the sum to its coordinate
    C[data->row][data->colum] = sum;
}

void element_thread() {
    output = fopen("/home/mohamedessam/CLionProjects/untitled1/output", "a");
    read_matrix();
    // for calculate time
    clock_t begin = clock();
    pthread_t pthread;
    for (int i = 0; i < RA; i++) {
        for (int j = 0; j < CA; ++j) {
            //to save row and columns for each thread
            struct index *data = (struct index *) malloc(sizeof(struct index));
            data->row = i;
            data->colum = j;

            pthread_create(&pthread, NULL, multi_element, data);

            // joining and waiting for all threads to complete
            pthread_join(pthread, NULL);

        }
    }
    printf("element_Multipication_Counter=%d times\n", count_elementMulti);
    fprintf(output, "output array method 2\n");
    printf("output array \n");
    for (int i = 0; i < RA; i++) {
        for (int j = 0; j < CB; j++) {
            printf("%d ", C[i][j]);
            fprintf(output, "%d ", C[i][j]);
        }
        printf("\n");
        fprintf(output, "\n");
    }
    clock_t end = clock();
    printf("Time taken:%lfsec\n", (double) (end - begin) / CLOCKS_PER_SEC);
    fprintf(output, "element_Multiplication_Counter=%d times\n", count_elementMulti);
    fprintf(output, "Time taken:%lfsec\n", (double) (end - begin) / CLOCKS_PER_SEC);
}

