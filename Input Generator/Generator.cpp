
// Generator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <ctime>

using namespace std;

int main()
{
    int no_of_nodes = 10000;
    int no_of_edges = 23000;

    int** matrix = (int**)malloc((no_of_nodes + 1) * sizeof(int*));
    for (int i = 0; i <= no_of_nodes; i++)
    {
        matrix[i] = (int*)malloc((no_of_nodes + 1) * sizeof(int));
    }

    int node1, node2;

    ofstream MyFile;
    MyFile.open("input23.txt");

    MyFile << no_of_nodes << " " << no_of_edges << endl;

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
                matrix[i][j] = -1;
            }
        }
    }

    srand((unsigned)time(NULL));

    for (int i = 1; i <= no_of_edges; i++)
    {
        node1 = rand() % no_of_nodes + 1;
        node2 = rand() % no_of_nodes + 1;

        while (matrix[node1][node2] != -1)
        {
            node1 = rand() % no_of_nodes + 1;
            node2 = rand() % no_of_nodes + 1;
        }

        matrix[node1][node2] = rand() % 500 + 1;

        MyFile << node1 << " " << node2 << " " << matrix[node1][node2] << endl;
    }

    MyFile.close();

    for (int i = 0; i <= no_of_nodes; i++)
    {
        free(matrix[i]);
    }

    free(matrix);

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
