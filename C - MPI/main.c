#include "FloydWarshall.h"

int main(int argc, char* argv[])
{
	int no_of_nodes, no_of_edges;
	int rank, numtasks;
	int** distances;
	int** copy;
	int* dist_array;
	int* local_array;

	double times[NPROC];

	double start, end, elapsed_time, total_time = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

	if (rank == 0)
	{
		FILE* f;
		f = fopen("input1.txt", "rt");
		if (f)
			printf("The file has been successfuly opened! ");
		else
			printf("Error opening file! ");

		printf("\n");
		fscanf(f, "%d", &no_of_nodes);
		fscanf(f, "%d\n", &no_of_edges);

		MPI_Bcast(&no_of_nodes, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(&no_of_edges, 1, MPI_INT, 0, MPI_COMM_WORLD);

		dist_array = (int*)malloc((no_of_nodes * no_of_nodes) * sizeof(int));
		local_array = (int*)malloc((no_of_nodes * no_of_nodes / numtasks) * sizeof(int));

		distances = (int**)malloc((no_of_nodes + 1) * sizeof(int*));
		for (int i = 0; i <= no_of_nodes; i++)
		{
			distances[i] = (int*)malloc((no_of_nodes + 1) * sizeof(int));
		}

		copy = (int**)malloc((no_of_nodes + 1) * sizeof(int*));
		for (int i = 0; i <= no_of_nodes; i++)
		{
			copy[i] = (int*)malloc((no_of_nodes + 1) * sizeof(int));
		}

		printf("\nNo of nodes = %d, no of vertices = %d\n", no_of_nodes, no_of_edges);

		initialise_matrix(distances, no_of_nodes, no_of_edges, f);
		copy_matrix(copy, distances, no_of_nodes);

		matrix_to_array(distances, dist_array, no_of_nodes);


		MPI_Scatter(dist_array, no_of_nodes * no_of_nodes / numtasks, MPI_INT, local_array, no_of_nodes * no_of_nodes / numtasks, MPI_INT, 0, MPI_COMM_WORLD);
		free(dist_array);

		MPI_Barrier(MPI_COMM_WORLD);

		start = MPI_Wtime();

		floyd_warshall_mpi(local_array, no_of_nodes, rank, numtasks, MPI_COMM_WORLD);

		end = MPI_Wtime();

		elapsed_time = (double)(end - start);

		MPI_Gather(&elapsed_time, 1, MPI_DOUBLE, times, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		dist_array = (int*)malloc((no_of_nodes * no_of_nodes) * sizeof(int));
		
		MPI_Gather(local_array, no_of_nodes * no_of_nodes / numtasks, MPI_INT, dist_array, no_of_nodes * no_of_nodes / numtasks, MPI_INT, 0, MPI_COMM_WORLD);

		array_to_matrix(dist_array, distances, no_of_nodes);

		for (int i = 0; i < NPROC; i++)
		{
			printf("\nrank %d -> time %f s", i, times[i]);
			//total_time += times[i];
		}

		//printf("\n\nTime for FW using %d processes: %f milliseconds\n", NPROC, total_time * 1000);
		//printf("\nTime for FW using %d processes: %f seconds\n", NPROC, total_time);

		printf("\nDistances matrix:\n");
		display_matrix(copy, no_of_nodes);

		printf("\nAPSP matrix:\n");
		display_matrix(distances, no_of_nodes);

		free(local_array);
		free(dist_array);

		for (int i = 0; i <= no_of_nodes; i++)
		{
			free(distances[i]);
		}

		free(distances);
		for (int i = 0; i <= no_of_nodes; i++)
		{
			free(copy[i]);
		}
		free(copy);
	}
	else
	{
		MPI_Bcast(&no_of_nodes, 1, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(&no_of_edges, 1, MPI_INT, 0, MPI_COMM_WORLD);

		dist_array = NULL;
		local_array = (int*)malloc((no_of_nodes * no_of_nodes / numtasks) * sizeof(int));

		MPI_Scatter(dist_array, no_of_nodes * no_of_nodes / numtasks, MPI_INT, local_array, no_of_nodes * no_of_nodes / numtasks, MPI_INT, 0, MPI_COMM_WORLD);

		MPI_Barrier(MPI_COMM_WORLD);

		start = MPI_Wtime();

		floyd_warshall_mpi(local_array, no_of_nodes, rank, numtasks, MPI_COMM_WORLD);

		end = MPI_Wtime();

		elapsed_time = (double)(end - start);

		MPI_Gather(&elapsed_time, 1, MPI_DOUBLE, times, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

		MPI_Gather(local_array, no_of_nodes * no_of_nodes / numtasks, MPI_INT, dist_array, no_of_nodes * no_of_nodes / numtasks, MPI_INT, 0, MPI_COMM_WORLD);

		free(local_array);
	}

	MPI_Finalize();
	return 0;
}