#include "FloydWarshall.h"

void initialise_matrix(int** matrix, int no_of_nodes, int no_of_edges, FILE* f)
{
	int node1, node2, cost;

	for (int i = 1; i <= no_of_nodes; i++)
	{
		for (int j = 1; j <= no_of_nodes; j++)
		{
			if (i == j)
			{
				matrix[i][j] = 0;
			}
			else
			{
				matrix[i][j] = INF;

			}
		}
	}
	for (int i = 1; i <= no_of_edges; i++) 
	{
		fscanf(f, "%d%d%d\n", &node1, &node2, &cost);
		matrix[node1][node2] = cost;
	}
}

void display_matrix(int** matrix, int no_of_nodes)
{
	for (int i = 1; i <= no_of_nodes; i++)
	{
		for (int j = 1; j <= no_of_nodes; j++)
		{
			if (matrix[i][j] == INF)
			{
				printf("   -");
			}
			else
			{
				printf("%4d", matrix[i][j]);
			}
		}
		printf("\n");
	}
}

void copy_matrix(int** copy_matrix, int** matrix, int no_of_nodes)
{
	for (int i = 1; i <= no_of_nodes; i++)
	{
		for (int j = 1; j <= no_of_nodes; j++)
		{
			copy_matrix[i][j] = matrix[i][j];
		}
	}
}

void floyd_warshall_openmp(int* distances, int no_of_nodes)
{
	int* k_row = (int*)malloc(no_of_nodes * sizeof(int));
	int new_cost;

#pragma omp parallel num_threads(THREADS) private(k) shared(distances, k_row)
		for (int k = 0; k < no_of_nodes; k++)
		{
#pragma omp master
			memcpy(k_row, distances + (k * no_of_nodes), no_of_nodes * sizeof(int));

#pragma omp parallel for private(i, j) schedule(dynamic)
			for (int i = 0; i < no_of_nodes; i++)
			{
				for (int j = 0; j < no_of_nodes; j++)
				{
					new_cost = distances[i * no_of_nodes + k] + k_row[j];
					if (new_cost < distances[i * no_of_nodes + j])
					{
						distances[i * no_of_nodes + j] = new_cost;
					}
				}
			}
		}
}

void compute_path(int node1, int node2, int** matrix, int no_of_nodes)
{
	int ok = 0, k = 1;

	while (k <= no_of_nodes && !ok)
	{
		if (node1 != k && node2 != k)
			if (matrix[node1][node2] == matrix[node1][k] + matrix[k][node2])
			{
				compute_path(node1, k, matrix, no_of_nodes);
				compute_path(k, node2, matrix, no_of_nodes);
				ok = 1;
			}
		k++;
	}
	if (!ok)
	{
		printf(" - %d", node2);
	}
}

void print_path(int node1, int node2, int** matrix, int no_of_nodes)
{
	if (matrix[node1][node2] < INF)
	{
		printf("\nThe path from %d to %d has the weight %d", node1, node2, matrix[node1][node2]);
		printf("\nThe minimum cost path is: %d", node1);
		compute_path(node1, node2, matrix, no_of_nodes);
	}
	else
	{
		printf("\nThere is no path between %d to %d", node1, node2);
	}
}

void matrix_to_array(int** matrix, int* array, int no_of_nodes)
{
	int k = 0;

	for (int i = 1; i <= no_of_nodes; i++)
	{
		for (int j = 1; j <= no_of_nodes; j++)
		{
			array[k] = matrix[i][j];
			k++;
		}
	}
}

void array_to_matrix(int* array, int** matrix, int no_of_nodes)
{
	int k = 0;
	for (int i = 1; i <= no_of_nodes; i++)
	{
		for (int j = 1; j <= no_of_nodes; j++)
		{
			matrix[i][j] = array[k];
			k++;
		}
	}
}