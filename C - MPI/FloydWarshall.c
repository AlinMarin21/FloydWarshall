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

void floyd_warshall_mpi(int* local_array, int no_of_nodes, int rank, int numtasks, MPI_Comm comm)
{
	int* k_row = (int*)malloc(no_of_nodes * sizeof(int));
	int root;
	int new_cost;

	for (int k = 0; k < no_of_nodes; k++)
	{
		root = k / (no_of_nodes / numtasks);
		if (rank == root)
		{
			copy_matrix_row(local_array, no_of_nodes, numtasks, k_row, k);
		}
		MPI_Bcast(k_row, no_of_nodes, MPI_INT, root, comm);
		for (int i = 0; i < no_of_nodes / numtasks; i++)
		{
			for (int j = 0; j < no_of_nodes; j++)
			{
				new_cost = local_array[i * no_of_nodes + k] + k_row[j];
				if (new_cost < local_array[i * no_of_nodes + j])
				{
					local_array[i * no_of_nodes + j] = new_cost;
				}
			}
		}
	}
	
	free(k_row);
}

void copy_matrix_row(int* local_array, int no_of_nodes, int numtasks, int* copy, int copy_length)
{
	int k = copy_length % (no_of_nodes / numtasks);

	for (int j = 0; j < no_of_nodes; j++)
	{
		copy[j] = local_array[k * no_of_nodes + j];
	}
}