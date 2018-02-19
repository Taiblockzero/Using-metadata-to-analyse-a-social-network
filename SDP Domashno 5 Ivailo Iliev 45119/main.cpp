#include "createMatrix.h"
#include "transposeMatrix.h"
#include "multiplyMatrices.h"
#include "top3People.h"
#include "floydWarshall.h"
#include "closenessCentrality.h"
#include "top3PeopleCC.h"
using namespace std;

int main(int argc, char** argv)
{
	//PEOPLE TO PEOPLE

	int mWidth, mHeight;

	//creates a matrix in the form of a 2D array from a .csv file whose values are 0 and 1, 
	//also calculates width and height of the matrix and puts them in mWidth and mHeight
	int** matrix = createMatrix(argv[1], mWidth, mHeight); 

	int tmWidth, tmHeight; //transposed matrix height and width
	//creates a transposed matrix in the form of a 2D array from an input 2D array matrix
	int** tMatrix = transposeMatrix(matrix, mWidth, mHeight, tmHeight, tmWidth); 

	int productWidth, productHeight;
	//matrix multiplication of two 2D arrays
	int** product = multiplyMatrices(matrix, tMatrix, mWidth, mHeight, tmWidth, tmHeight, productHeight, productWidth); 

	//cout the 3 people with the most connections to other people
	//if the last argument in the function gets 'p' it will be for people, and 'g' for groups (this change affects ONLY THE 
	//COUT PORTION OF THE FUNCTION, so it can be used for tables of anything)
	//this function should be used only if there are 3 or more people in the matrix
	top3People(product, productHeight, productWidth, argv[1], 'p');

	//now for top 3 groups groups we just change the places of matrix and tMatrix
	int product2Height;
	int product2Width;
	int** product2 = multiplyMatrices(tMatrix, matrix, tmWidth, tmHeight, mWidth, mHeight, product2Height, product2Width);
	
	top3People(product2, product2Height, product2Width, argv[1], 'g');
	
	

	//Calculating closeness centrality using the Floyd-Warshall algorithm
	int spHeightWidth; //shortest paths array height and width(height and width together because it will be a nxn matrix)
	int** shortestPaths = floydWarshall(product, productHeight, spHeightWidth);

	int ccSize; //closeness centrality array size
	double* cc = closenessCentrality(shortestPaths, spHeightWidth, ccSize);


	//cout the names of the 3 most central people (based on closeness centrality)
	top3PeopleCC(cc, ccSize, argv[1]);




	for (int i = 0; i < mHeight; ++i)
		delete[] matrix[i];
	delete[] matrix;

	for (int i = 0; i < tmHeight; ++i)
		delete[] tMatrix[i];
	delete[] tMatrix;

	for (int i = 0; i < productHeight; ++i)
		delete[] product[i];
	delete[] product;

	for (int i = 0; i < spHeightWidth; ++i)
		delete[] shortestPaths[i];
	delete[] shortestPaths;

	delete[] cc;
}