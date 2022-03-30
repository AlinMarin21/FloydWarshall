#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define INF 99999

void initialise_matrix(int** matrix, int no_of_nodes);

void copy_matrix(int** copy_matrix, int** matrix, int no_of_nodes);

void display_matrix(int** matrix, int no_of_nodes);

void floyd_warshall(int** matrix, int no_of_nodes);

void compute_path(int node1, int node2, int** matrix, int no_of_nodes);

void print_path(int node1, int node2, int** matrix, int no_of_nodes);