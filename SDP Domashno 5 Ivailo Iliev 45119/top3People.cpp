#include "top3People.h"
#include <iostream>
#include <fstream>

void top3People(int** product, int pHeight, int pWidth, char* fileName, char pOrG)
{
	if (pHeight < 3)
	{
		std::cout << "There are less than 3 people for the top3people() function! ERROR!\n";
	}



	int* pCon = new int[pHeight]; //array consisting of connections to how many other people each person has
	for (int i = 0, con; i < pHeight; ++i)
	{
		con = 0; //amount of connections
		for (int j = 0; j < pWidth; ++j)
		{
			if (product[i][j] > 0)
				++con;
		}
		pCon[i] = con - 1; //- 1 because a person will always have a connection with himself
	}


	int mostConI = 0; //index of person with connections to most people
	int mostConI2; //second most
	int mostConI3;

	//Checking the first three indexes to be in order
	if (pCon[0] < pCon[1])
	{
		mostConI = 1;
		mostConI2 = 0;
	}
	else
		mostConI2 = 1;

	if (pCon[mostConI2] < pCon[2])
	{
		if (pCon[mostConI] < pCon[2])
		{
			mostConI3 = mostConI2;
			mostConI2 = mostConI;
			mostConI = 2;
		}
		else
		{
			mostConI3 = mostConI2;
			mostConI2 = 2;
		}
	}
	else
		mostConI3 = 2;

	//Now to check the rest of the array
	for (int i = 3; i < pHeight; ++i)
	{
		if (pCon[i] > pCon[mostConI3])
		{
			if (pCon[i] > pCon[mostConI2])
			{
				if (pCon[i] > pCon[mostConI])
				{
					mostConI3 = mostConI2;
					mostConI2 = mostConI;
					mostConI = i;
				}
				else
				{
					mostConI3 = mostConI2;
					mostConI2 = i;
				}
			}
			else
				mostConI3 = i;
		}
	}


	//Now that we have the indexes of the three people with connections to most other people,
	//we check for their names in the file
	//If they are groups then we check for their names also
	std::ifstream csvFile(fileName);
	char c = 'a'; //== 'a' so that it has a value different than '\n' for the first check
	
	

	char** top3Names = new char*[3];
	int cnt = 0;

	bool mostConIfound = false;
	bool mostConI2found = false;
	bool mostConI3found = false;


	int mostConPersonI; //index (in top3Names) of the name of the person with connections to the most people
	int mostConPersonI2; //same but for the name of the person with second most connections
	int mostConPersonI3;


	//If they are people
	if (pOrG == 'p')
	{

		while (c != '\n') //Skip first row
			csvFile.get(c);

		for (int i = 0; i < pHeight; ++i)
		{
			if (i == mostConI || i == mostConI2 || i == mostConI3)
			{
				if (i == mostConI)
				{
					mostConIfound = true;
					mostConPersonI = cnt;
				}
				else if (i == mostConI2)
				{
					mostConI2found = true;
					mostConPersonI2 = cnt;
				}
				else if (i == mostConI3)
				{
					mostConI3found = true;
					mostConPersonI3 = cnt;
				}

				int nameLen = 0;
				while (c != ',')
				{
					csvFile.get(c);
					++nameLen;
				}
				--nameLen; //because when it gets ',' it will also ++nameLen

				top3Names[cnt] = new char[nameLen + 1];
				for (int j = 0; j < nameLen + 1; ++j) //get back to beginning of name
					csvFile.unget();

				csvFile.get(top3Names[cnt], nameLen + 1, ',');

				++cnt;


				if (mostConIfound == true && mostConI2found == true && mostConI3found == true)
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
	}

	//If they are groups
	else
	{
		for (int i = 0; i < pHeight; ++i)
		{
			csvFile.get(c); //get the ','
			if (i == mostConI || i == mostConI2 || i == mostConI3)
			{
				if (i == mostConI)
				{
					mostConIfound = true;
					mostConPersonI = cnt;
				}

				else if (i == mostConI2)
				{
					mostConI2found = true;
					mostConPersonI2 = cnt;
				}

				else if (i == mostConI3)
				{
					mostConI3found = true;
					mostConPersonI3 = cnt;
				}

				int nameLen = 0;
				c = 'a';
				while (c != ',')
				{
					csvFile.get(c);
					++nameLen;
				}
				--nameLen; //because when it gets ',' it will also ++nameLen

				top3Names[cnt] = new char[nameLen + 1];
				for (int j = 0; j < nameLen + 1; ++j) //get back to beginning of name
					csvFile.unget();

				csvFile.get(top3Names[cnt], nameLen + 1, ',');

				++cnt;


				if (mostConIfound == true && mostConI2found == true && mostConI3found == true)
					break;
			}

			else
			{
				//skip group name
				c = 'a';
				while (c != ',')
					csvFile.get(c);
				csvFile.unget(); //ungets the ','
			}
		}
	}

	csvFile.close();

	
	if (pOrG == 'p' || pOrG == 'P')
	{
		std::cout << "The person with connections to the most people is " << top3Names[mostConPersonI] 
			      << " who has connections to " << pCon[mostConI] << " people.\n";

		std::cout << "The person with connections to the second-most people is " << top3Names[mostConPersonI2] 
			<< " who has connections to " << pCon[mostConI2] << " people.\n";

		std::cout << "The person with connections to the third-most people is " << top3Names[mostConPersonI3] 
				  << " who has connections to " << pCon[mostConI3] << " people.\n";
	}

	else if (pOrG == 'g' || pOrG == 'G')
	{
		std::cout << "The group with connections to the most groups is " << top3Names[mostConPersonI]
			<< " which has connections to " << pCon[mostConI] << " groups.\n";

		std::cout << "The group with connections to the second-most groups is " << top3Names[mostConPersonI2]
			<< " which has connections to " << pCon[mostConI2] << " groups.\n";

		std::cout << "The group with connections to the third-most groups is " << top3Names[mostConPersonI3]
			<< " which has connections to " << pCon[mostConI3] << " groups.\n";
	}



	delete[] pCon;

	for (int i = 0; i < 3; ++i)
		delete[] top3Names[i];
	delete[] top3Names;
}