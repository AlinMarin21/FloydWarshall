#include "FW.h"

FW::FW(int no_of_nodes, int no_of_edges)
{
	mNoOfNodes = no_of_nodes;
	mNoOfEdges = no_of_edges;

	mMatrix = new int* [mNoOfNodes + 1];

	for (int i = 0; i <= mNoOfNodes; i++)
	{
		mMatrix[i] = new int[mNoOfNodes + 1];
	}

	mCopyMatrix = new int* [mNoOfNodes + 1];

	for (int i = 0; i <= mNoOfNodes; i++)
	{
		mCopyMatrix[i] = new int[mNoOfNodes + 1];
	}
}

void FW::initialise_matrix(ifstream& graphInit)
{
	int node1, node2, cost;

	for (int i = 1; i <= mNoOfNodes; i++)
	{
		for (int j = 1; j <= mNoOfNodes; j++)
		{
			if (i == j)
			{
				mMatrix[i][j] = 0;
			}
			else
			{

				mMatrix[i][j] = INF;
			}
		}
	}

	for (int i = 1; i <= mNoOfEdges; i++)
	{
		graphInit >> node1 >> node2 >> cost;

		mMatrix[node1][node2] = cost;
	}
}

void FW::display_apsp_matrix() 
{
	for (int i = 1; i <= mNoOfNodes; i++)
	{
		for (int j = 1; j <= mNoOfNodes; j++)
		{
			if (mMatrix[i][j] == INF)
			{
				cout << "   -";
			}
			else
			{
				cout << setfill(' ') << setw(4) << mMatrix[i][j];
			}
		}
		cout << endl;
	}
}

void FW::display_distances_matrix()
{
	for (int i = 1; i <= mNoOfNodes; i++)
	{
		for (int j = 1; j <= mNoOfNodes; j++)
		{
			if (mCopyMatrix[i][j] == INF)
			{
				cout << "   -";
			}
			else
			{
				cout << setfill(' ') << setw(4) << mCopyMatrix[i][j];
			}
		}
		cout << endl;
	}
}

void FW::copy_matrix()
{
	for (int i = 1; i <= mNoOfNodes; i++)
	{
		for (int j = 1; j <= mNoOfNodes; j++)
		{
			mCopyMatrix[i][j] = mMatrix[i][j];
		}
	}
}

void FW::floyd_warshall()
{
	for (int k = 1; k <= mNoOfNodes; k++)
	{
		for (int i = 1; i <= mNoOfNodes; i++)
		{
			for (int j = 1; j <= mNoOfNodes; j++)
			{
				if (mMatrix[i][j] > mMatrix[i][k] + mMatrix[k][j])
				{
					mMatrix[i][j] = mMatrix[i][k] + mMatrix[k][j];
				}
			}
		}
	}
}

void FW::compute_path(int node1, int node2)
{
	int ok = 0;
	int k = 1;


	while (k <= mNoOfNodes && !ok)
	{
		if (node1 != k && node2 != k)
		{
			if (mMatrix[node1][node2] == mMatrix[node1][k] + mMatrix[k][node2])
			{
				compute_path(node1, k);
				compute_path(k, node2);
				ok = 1;
			}
		}
		k++;
	}
	if (!ok)
	{
		mPath.push_back(node2);
	}
}

void FW::print_path(int node1, int node2)
{
	mPath.clear();

	if (mMatrix[node1][node2] < INF)
	{
		mPath.push_back(node1);
		compute_path(node1, node2);

		cout << endl << "The path from node " << node1 << " to " << node2 << " has the weight " << mMatrix[node1][node2] << endl;
		cout << "The minimum cost path is: " << mPath[0];

		for (int i = 1; i < mPath.size(); i++)
		{
			cout << " - " << mPath[i];
		}
	}
	else
	{
		cout << "There is no path between node " << node1 << " and " << node2;
	}
}

FW::~FW()
{
	for (int i = 0; i <= mNoOfNodes; i++)
	{
		delete[] mMatrix[i];
	}
	delete[] mMatrix;

	for (int i = 0; i <= mNoOfNodes; i++)
	{
		delete[] mCopyMatrix[i];
	}
	delete[] mCopyMatrix;
}