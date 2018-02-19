#include "createMatrix.h"
#include <fstream>
#include <iostream>
using namespace std;

int** createMatrix(char* filePath, int& mWidth, int& mHeight)
{
	ifstream csvFile(filePath);

	//get matrix width
	//matrix width is the same as the amount of ',' in a line
	mWidth = 0; //matrix width
	char c = 'a'; //== 'a' so that it has a value different than '\n' for the first check
	while (c != '\n')
	{
		csvFile.get(c);
		if (c == ',')
			++mWidth;
	}


	//get matrix height
	mHeight = 0;

	//check if there is a newline before end of file
	bool thereIsNewline = false; //is there a newline before end of file
	csvFile.seekg(-1, ios::end);
	csvFile.get(c);
	if (c == '\n')
		thereIsNewline = true;

	//matrix height is amount of newlines - 1 (if there is a newline before end of file) 
	//or amount of newlines (if there isn't a newline before end of file) 
	if (csvFile.eof())
		csvFile.clear();
	csvFile.seekg(0); //go to start of file

	int newlines = 0; //amount of newlines
	while (csvFile)
	{
		csvFile.get(c);
		if (c == '\n')
			++newlines;
	}

	if (thereIsNewline)
		mHeight = newlines - 1;
	else
		mHeight = newlines;


	//create empty matrix
	int** matrix = new int*[mHeight];
	for (int i = 0; i < mHeight; ++i)
	{
		matrix[i] = new int[mWidth];
	}

	//fill up empty matrix
	csvFile.clear();
	csvFile.seekg(0); //go to start of file
	
	
	c = 'a'; //so that char c != '\n'
	while (c != '\n') //skip first line
		csvFile.get(c);

	for (int i = 0; i < mHeight; ++i)
	{
		//skip name
		c = 'a'; //so that char c isn't leftover = ','
		while (c != ',')
			csvFile.get(c);

		csvFile.unget(); //go before the first ',' in the line

		for (int j = 0; j < mWidth; ++j)
		{
			csvFile.get(c); //skip ','
			csvFile.get(c);
			matrix[i][j] = c - '0';
		}
	}


	csvFile.close();

	//result
	return matrix;
}