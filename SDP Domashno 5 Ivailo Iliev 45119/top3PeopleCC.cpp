#include "top3PeopleCC.h"
#include <iostream>
#include <fstream>
using namespace std;

void top3PeopleCC(double* cc, int ccSize, char* fileName)
{
	if (ccSize < 3)
	{
		cout << "There must be atleast 3 people for top3PeopleCC() to work! ERROR!\n";
		return;
	}


	int mostCenI = 0; //index of most central person
	int mostCenI2; //second most
	int mostCenI3;

	//Checking the first three indexes to be in order
	if (cc[0] < cc[1])
	{
		mostCenI = 1;
		mostCenI2 = 0;
	}
	else
		mostCenI2 = 1;

	if (cc[mostCenI2] < cc[2])
	{
		if (cc[mostCenI] < cc[2])
		{
			mostCenI3 = mostCenI2;
			mostCenI2 = mostCenI;
			mostCenI = 2;
		}
		else
		{
			mostCenI3 = mostCenI2;
			mostCenI2 = 2;
		}
	}
	else
		mostCenI3 = 2;


	//Now to check the rest of the array
	for (int i = 3; i < ccSize; ++i)
	{
		if (cc[i] > cc[mostCenI3])
		{
			if (cc[i] > cc[mostCenI2])
			{
				if (cc[i] > cc[mostCenI])
				{
					mostCenI3 = mostCenI2;
					mostCenI2 = mostCenI;
					mostCenI = i;
				}
				else
				{
					mostCenI3 = mostCenI2;
					mostCenI2 = i;
				}
			}
			else
				mostCenI3 = i;
		}
	}


	//Now that we have the indexes of the three most central people we check for their names in the file
	ifstream csvFile(fileName);
	char c = 'a'; //== 'a' so that it has a value different than '\n' for the first check

	
	char** top3CPNames = new char*[3]; //top3CentralPeopleNames
	int cnt = 0;

	bool mostCenIfound = false;
	bool mostCenI2found = false;
	bool mostCenI3found = false;


	int mostCenPersonI; //index (in top3Names) of the name of the most central person
	int mostCenPersonI2; //same but for the name of the second-most central person
	int mostCenPersonI3;

	while (c != '\n') //Skip first row
		csvFile.get(c);

	for (int i = 0; i < ccSize; ++i)
	{
		if (i == mostCenI || i == mostCenI2 || i == mostCenI3)
		{
			if (i == mostCenI)
			{
				mostCenIfound = true;
				mostCenPersonI = cnt;
			}
			else if (i == mostCenI2)
			{
				mostCenI2found = true;
				mostCenPersonI2 = cnt;
			}
			else if (i == mostCenI3)
			{
				mostCenI3found = true;
				mostCenPersonI3 = cnt;
			}

			int nameLen = 0;
			while (c != ',')
			{
				csvFile.get(c);
				++nameLen;
			}
			--nameLen; //because when it gets ',' it will also ++nameLen

			top3CPNames[cnt] = new char[nameLen + 1];
			for (int j = 0; j < nameLen + 1; ++j) //get back to beginning of name
				csvFile.unget();

			csvFile.get(top3CPNames[cnt], nameLen + 1, ',');

			++cnt;


			if (mostCenIfound == true && mostCenI2found == true && mostCenI3found == true)
				break;


			//skip the rest of the line, we only needed the name from this line
			c = 'a'; //so that it isn't a leftover '\n' from before
			while (c != '\n')
				csvFile.get(c);
		}

		else
		{
			//skip line
			c = 'a'; //so that it isn't a leftover '\n' from before
			while (c != '\n')
				csvFile.get(c);
		}
	}


	csvFile.close();


	std::cout << "The most central person is " << top3CPNames[mostCenPersonI]
		<< " who has Closeness Centrality " << cc[mostCenI] << "\n";

	std::cout << "The second-most central person is " << top3CPNames[mostCenPersonI2]
		<< " who has Closeness Centrality " << cc[mostCenI2] << "\n";

	std::cout << "The third-most central person is " << top3CPNames[mostCenPersonI3]
		<< " who has Closeness Centrality " << cc[mostCenI3] << "\n";


	
	
	for (int i = 0; i < 3; ++i)
		delete[] top3CPNames[i];
	delete[] top3CPNames;
}