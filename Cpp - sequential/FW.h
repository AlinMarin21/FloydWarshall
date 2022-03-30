#include <iostream>
#include <vector>
#include <time.h>
#include <iomanip>

using namespace std;

#define INF 99999

class FW
{
private:
	int mNoOfNodes;
	int** mMatrix;
	int** mCopyMatrix;
	vector<int> mPath;
public:
	FW(int no_of_nodes);
	void initialise_matrix();
	void display_apsp_matrix();
	void display_distances_matrix();
	void copy_matrix();
	void floyd_warshall();
	void compute_path(int node1, int node2);
	void print_path(int node1, int node2);
	~FW();
};