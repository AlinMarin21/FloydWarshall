#include "FloydWarshall.h"
#include <conio.h>


int main()
{
	int no_of_nodes = 20;

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

	initialise_matrix(distances, no_of_nodes);

	copy_matrix(copy, distances, no_of_nodes);

	double time_FW_millis = 0.0;
	double time_FW_s = 0.0;

	clock_t start = clock();

	floyd_warshall(distances, no_of_nodes);

	clock_t end = clock();

	time_FW_millis += (double)(end - start) / (CLOCKS_PER_SEC / 1000);
	time_FW_s += (double)(end - start) / CLOCKS_PER_SEC;

	printf("Time for FW: %lf milliseconds", time_FW_millis);
	printf("\nTime for FW: %lf seconds", time_FW_s);

	printf("\nDistances matrix:\n");
	display_matrix(copy, no_of_nodes);

	printf("\nAPSP matrix:\n");
	display_matrix(distances, no_of_nodes);

	do
	{
		printf("\nnode1 = ");
		scanf("%d", &node1);

		printf("node2 = ");
		scanf("%d", &node2);

		print_path(node1, node2, distances, no_of_nodes);

		printf("\n\nDo you want to find a path between other nodes from the graph? <y/n>");
		ch = _getch();
	} while (ch == 'y' || ch == 'Y');

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