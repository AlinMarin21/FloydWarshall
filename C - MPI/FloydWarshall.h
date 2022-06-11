#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#include "mpi.h"

#define INF 99999
#define ROOT 0
#define NPROC 10

void initialise_matrix(int** matrix, int no_of_nodes, int no_of_edges, FILE* f);

void matrix_to_array(int** matrix, int* array, int no_of_nodes);

void array_to_matrix(int* array, int** matrix, int no_of_nodes);

void copy_matrix(int** copy_matrix, int** matrix, int no_of_nodes);

void display_matrix(int** matrix, int no_of_nodes);

void floyd_warshall_mpi(int* local_array, int no_of_nodes, int rank, int numtasks, MPI_Comm comm);

void copy_matrix_row(int* local_array, int no_of_nodes, int numtasks, int* copy, int copy_length);


