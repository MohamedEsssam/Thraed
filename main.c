//
// Created by mohamedessam on 11/2/18.
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <pthread.h>

FILE *output;

//function to read and scan Matrix input from file
void read_matrix();

//function to read and scan Merge sort input from file
void read_merge();

//function multiply 2 Matrices
void *multi_row(void *arg);

// Thread function that call function multiply ana calculate running time per sec
void row_thread();

//function multiply 2 Matrices
void *multi_element(void *arg);

// Thread function that call function multiply ana calculate running time per sec
void element_thread();

void merge(int ,int ,int );

void *merge_sort(void *n);

void merge_thread();

//main to run
void main() {
    row_thread();
    element_thread();
    merge_thread();
    fclose(output);

}
