#include "closenessCentrality.h"

double* closenessCentrality(int** shortestPaths, int spHeightWidth, int& ccSize)
{
	ccSize = spHeightWidth;


	double* cc = new double[ccSize];
	
	for (int i = 0; i < spHeightWidth; ++i)
	{
		double sum = 0;
		for (int j = 0; j < spHeightWidth; ++j)
		{
			sum = sum + shortestPaths[i][j];
		}
		cc[i] = 1 / sum;
	}

	return cc;
}