#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <omp.h>
#include <string.h>

#define INF 99999
#define THREADS 10


void initialise_matrix(int** matrix, int no_of_nodes, int no_of_edges, FILE* f);

void copy_matrix(int** copy_matrix, int** matrix, int no_of_nodes);

void matrix_to_array(int** matrix, int* array, int no_of_nodes);

void array_to_matrix(int* array, int** matrix, int no_of_nodes);

void display_matrix(int** matrix, int no_of_nodes);

void floyd_warshall_openmp(int* distances, int no_of_nodes);

void compute_path(int node1, int node2, int** matrix, int no_of_nodes);

void print_path(int node1, int node2, int** matrix, int no_of_nodes);