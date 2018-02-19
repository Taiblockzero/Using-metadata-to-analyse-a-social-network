#include "multiplyMatrices.h"
#include <iostream>

int** multiplyMatrices(int** matrix1, int** matrix2, int m1Width, int m1Height, int m2Width, int m2Height, int& resultHeight,
	                   int& resultWidth)
{
	if (m1Width != m2Height)
		std::cout << "Can't multiply these matrices because width of m1 is different than height of m2\n";

	resultHeight = m1Height;
	resultWidth = m2Width;

	int** product = new int*[m1Height];
	for (int i = 0; i < m1Height; ++i)
	{
		product[i] = new int[m2Width];
	}

	for (int i = 0; i < m1Height; ++i)
	{
		for (int j = 0; j < m2Width; ++j)
		{
			int sum = 0;
			for (int k = 0, l = 0; k < m1Width; ++k, ++l)
			{
				sum = sum + matrix1[i][k] * matrix2[l][j];
			}

			product[i][j] = sum;
		}
	}

	return product;
}