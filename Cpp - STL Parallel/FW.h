#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <iomanip>
#include <string>
#include <conio.h>
#include <chrono>
#include <algorithm>
#include <execution>
#include <functional>

using namespace std;

#define INF 99999

class FW
{
private:
	int mNoOfNodes;
	int mNoOfEdges;
	int** mMatrix;
	int** mCopyMatrix;
	vector<int> mPath;
	vector<int> mKVector;
	void floyd_warshall_foreach_k(int k);
public:
	FW(int no_of_nodes, int no_of_edges);
	void initialise_matrix(ifstream& graphInit);
	void display_apsp_matrix();
	void display_distances_matrix();
	void copy_matrix();
	void floyd_warshall_stlparallel();
	void compute_path(int node1, int node2);
	void print_path(int node1, int node2);
	~FW();
};