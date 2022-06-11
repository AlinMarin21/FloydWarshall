#include "FloydWarshall.h"

int main()
{
	int no_of_nodes, no_of_edges;

	FILE* f;
	f = fopen("input2.txt", "rt");
	if (f)
		printf("The file has been successfuly opened! ");
	else
		printf("Error opening file! ");

	printf("\n");
	fscanf(f, "%d", &no_of_nodes);
	fscanf(f, "%d\n", &no_of_edges);

	int** distances = (int**)malloc((no_of_nodes + 1) * sizeof(int*));
	for (int i = 0; i <= no_of_nodes; i++)
	{
		distances[i] = (int*)malloc((no_of_nodes + 1) * sizeof(int));
	}

	int** copy = (int**)malloc((no_of_nodes + 1) * sizeof(int*));
	for (int i = 0; i <= no_of_nodes; i++)
	{
		copy[i] = (int*)malloc((no_of_nodes + 1) * sizeof(int));
	}

	int ch, node1, node2;

	initialise_matrix(distances, no_of_nodes, no_of_edges, f);

	fclose(f);

	copy_matrix(copy, distances, no_of_nodes);

	int* distances_array = (int*)malloc((no_of_nodes * no_of_nodes) * sizeof(int));

	matrix_to_array(distances, distances_array, no_of_nodes);

	double time_FW_millis = 0.0;
	double time_FW_s = 0.0;

	clock_t start = clock();

	floyd_warshall_openmp(distances_array, no_of_nodes);

	clock_t end = clock();

	time_FW_millis += (double)(end - start) / (CLOCKS_PER_SEC / 1000);
	time_FW_s += (double)(end - start) / CLOCKS_PER_SEC;

	printf("\nNo of nodes = %d, no of vertices = %d\n", no_of_nodes, no_of_edges);

	printf("\nTime for FW: %lf milliseconds", time_FW_millis);
	printf("\nTime for FW: %lf seconds\n", time_FW_s);

	array_to_matrix(distances_array, distances, no_of_nodes);

	printf("\nDistances matrix:\n");
	display_matrix(copy, no_of_nodes);

	printf("\nAPSP matrix:\n");
	display_matrix(distances, no_of_nodes);

	/*do
	{
		printf("\nnode1 = ");
		scanf("%d", &node1);

		printf("node2 = ");
		scanf("%d", &node2);

		print_path(node1, node2, distances, no_of_nodes);

		printf("\n\nDo you want to find a path between other nodes from the graph? <y/n>");
		ch = _getch();
	} while (ch == 'y' || ch == 'Y');*/

	free(distances_array);

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

	return 0;
}

