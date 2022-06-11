#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <iomanip>
#include <thread>
#include <mutex>
#include <string>
#include <conio.h>
#include <chrono>

using namespace std;

#define INF 99999

#define NTHREADS 10

class FW
{
private:
	int mNoOfNodes;
	int mNoOfEdges;
	int** mMatrix;
	int** mCopyMatrix;
	vector<int> mPath;
	mutex mtx;
	vector<thread> mThreads;
	void floyd_warshall(int start_row);
public:
	FW(int no_of_nodes, int no_of_edges);
	void initialise_matrix(ifstream& graphInit);
	void display_apsp_matrix();
	void display_distances_matrix();
	void copy_matrix();
	void floyd_warshall_threads();
	void compute_path(int node1, int node2);
	void print_path(int node1, int node2);
	~FW();
};