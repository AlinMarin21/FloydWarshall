#include "FW.h"
#include <conio.h>
#include <chrono>

int main()
{
    int no_of_nodes = 20;
    char ch;
    int node1, node2;

    FW FloydWarshall(no_of_nodes);

    FloydWarshall.initialise_matrix();

    FloydWarshall.copy_matrix();

    auto start = chrono::steady_clock::now();

    FloydWarshall.floyd_warshall();

    auto end = chrono::steady_clock::now();

    cout << "Time for FW: " << chrono::duration_cast<chrono::microseconds>(end - start).count() << " microseconds" << endl;
    cout << "Time for FW: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " milliseconds" << endl;
    cout << "Time for FW: " << chrono::duration_cast<chrono::seconds>(end - start).count() << " seconds" << endl;

    cout << "Distances Matrix: " << endl;
    FloydWarshall.display_distances_matrix();

    cout << endl << "APSP Matrix: " << endl;
    FloydWarshall.display_apsp_matrix();

    do
    {
        cout << endl << endl << "node1 = ";
        cin >> node1;
        cout << "node2 = ";
        cin >> node2;

        FloydWarshall.print_path(node1, node2);

        cout << endl << endl << "Do you want to find a path between other nodes from the graph? <y/n>";
        ch = _getch();

    } while (ch == 'y' || ch == 'Y');

    return 0;
}


