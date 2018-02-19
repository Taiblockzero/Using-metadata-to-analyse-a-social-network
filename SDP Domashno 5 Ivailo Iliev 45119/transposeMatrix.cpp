#include "transposeMatrix.h"

int** transposeMatrix(int** matrix, int mWidth, int mHeight, int& resultHeight, int& resultWidth)
{
	resultHeight = mWidth;
	resultWidth = mHeight;

	int** tMatrix = new int*[mWidth]; //transposed matrix
	for (int i = 0; i < mWidth; ++i)
	{
		tMatrix[i] = new int[mHeight];
	}

	//fill up tMatrix
	for (int i = 0; i < mHeight; ++i)
	{
		for (int j = 0; j < mWidth; ++j)
		{
			tMatrix[j][i] = matrix[i][j];
		}
	}

	return tMatrix;
}