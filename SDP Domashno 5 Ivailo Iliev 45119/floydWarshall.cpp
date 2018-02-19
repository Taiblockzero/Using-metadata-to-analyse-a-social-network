#include "floydWarshall.h"
const int INFINITY = 1000000000;

int** floydWarshall(int** product, int& pHeight, int& spHeightWidth)
{
	spHeightWidth = pHeight;


	int** shortestPaths = new int*[spHeightWidth];
	for (int i = 0; i < spHeightWidth; ++i)
	{
		shortestPaths[i] = new int[spHeightWidth];
		for (int j = 0; j < spHeightWidth; ++j)
			shortestPaths[i][j] = INFINITY;
	}


	for (int i = 0; i < spHeightWidth; ++i)
		shortestPaths[i][i] = 0;


	for (int i = 0; i < spHeightWidth; ++i)
	{
		for (int j = 0; j < spHeightWidth; ++j)
		{
			if (i != j && product[i][j] > 0)
				shortestPaths[i][j] = 1;
		}
	}



	for (int k = 0; k < spHeightWidth; ++k)
	{
		for (int i = 0; i < spHeightWidth; ++i)
		{
			for (int j = 0; j < spHeightWidth; ++j)
			{
				if (shortestPaths[i][j] >(shortestPaths[i][k] + shortestPaths[k][j]))
					shortestPaths[i][j] = shortestPaths[i][k] + shortestPaths[k][j];
			}
		}
	}
	return shortestPaths;
}