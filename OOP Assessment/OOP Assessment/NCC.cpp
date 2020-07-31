#include "Header.h"
#include<iostream>
#include<fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

void NCC::FindWally(double** WallyMatrix, double** ClusterMatrix, double* WallyData, int WallyRows, int WallyColumns, int ClusterRows, int ClusterColumns, int locations)
{
	//Creates all vectors needed
	vector<double> NCCarr;
	vector<int> NCCrows;
	vector<int> NCCcolumns;
	//Creates all variables used
	int arrPos = 0;
	int arrLength = 0;

	float TotalWally = 0;
	float MeanWally;
	float NCCHighest = -1;
	int HighY = 0, HighZ = 0;
	//Create variables to improve efficiency when looping
	int CRowsMinusWRows = ClusterRows - WallyRows;
	int CColumnsMinusWColumn = ClusterColumns - WallyColumns;
	int WRowTimesWColumn = WallyRows * WallyColumns;
	//Create the 2D matrix arrays for the templates
	double** Template = new double*[WallyRows];
	for (int i = 0; i < WallyRows; ++i)
	{
		Template[i] = new double[WallyColumns];
	}
	//Adds all pixel values up in the Wally reference 
	for (int i = 0; i < WRowTimesWColumn; i++)
	{
		TotalWally += WallyData[i];
	}
	//Gets the mean of the Wally pixels
	MeanWally = TotalWally / (WRowTimesWColumn);
	//Minus the mean from all the pixels in Wally array, getting the differentiation from the mean of all pixels
	for (int i = 0; i < WallyRows; i++)
	{
		for (int x = 0; x < WallyColumns; x++)
		{
			WallyMatrix[i][x] = WallyMatrix[i][x] - MeanWally;
		}
	}
	//Loop that moves about half of the height of Wally
	for (int y = 0; y <= CRowsMinusWRows; y += 24)
	{//Loop that moves about half the width of Wally
		for (int z = 0; z < CColumnsMinusWColumn; z += 18)
		{
			//Create all variables used
			float TotalTemplate = 0;
			float MeanTemplate;

			float SDTotal = 0;
			float NCC = 0;

			float ISquared = 0;
			float TSquared = 0;

			float Denom;
			//Populates the template array with the values of the cluster image at a specific area
			//This area is determined but the array that this is nested in, which loops throught the cluster image
			//giving the postiion of the top left corner of the template frame
			for (int i = 0; i < WallyRows; i++)
			{
				for (int x = 0; x < WallyColumns; x++)
				{
					Template[i][x] = ClusterMatrix[y + i][z + x];
				}
			}
			//Adds all pixel values up in the Template array 
			for (int i = 0; i < WallyRows; i++)
			{
				for (int x = 0; x < WallyColumns; x++)
				{
					TotalTemplate += Template[i][x];
				}
			}
			//Gets the mean of the Template pixels
			MeanTemplate = TotalTemplate / (WRowTimesWColumn);
			//Minus the mean from all the pixels in Template array, getting the differentiation from the mean of all pixels
			//Gets the total of multiplying the same position pixel in both the Wally and Template arrays
			//Gets the total of the Wally pixels squared
			//Gets the total of the Template pixels squared
			for (int i = 0; i < WallyRows; i++)
			{
				for (int x = 0; x < WallyColumns; x++)
				{
					Template[i][x] = Template[i][x] - MeanTemplate;

					SDTotal += Template[i][x] * WallyMatrix[i][x];

					ISquared += WallyMatrix[i][x] * WallyMatrix[i][x];
					TSquared += Template[i][x] * Template[i][x];
				}
			}
			//Gets the squareroot of the two squared arrays multiplied together
			Denom = sqrt(ISquared * TSquared);
			//Finishes by calculating the NC number for that frame
			NCC = SDTotal / Denom;
			//Stores the NC value and the position of the top left corner of the template frame into vectors
			NCCarr.push_back(NCC);
			NCCcolumns.push_back(z);
			NCCrows.push_back(y);
		}
	}
	//Gets the number of frames
	arrLength = NCCarr.size();

	for (int i = 0; i < locations; i++)
	{//loop for however many Wallys the user wants to find
		for (int i = 0; i < arrLength; i++)
		{//Loops through the array
			if (NCCarr[i] > NCCHighest)
			{//If the NC is higher than the previous highest, set the highest to that value, also stores the frames top left corner
				NCCHighest = NCCarr[i];
				HighY = NCCrows[i];
				HighZ = NCCcolumns[i];
				arrPos = i;
			}
		}
		//Creates the black border for the top and bottom of the outline
		for (int i = 0; i < WallyColumns; i++)
		{
			ClusterMatrix[HighY][HighZ + i] = 0;
			ClusterMatrix[HighY + 49][HighZ + i] = 0;
		}
		//Creates the black border for the left and right of the outlide
		for (int i = 0; i < WallyRows; i++)
		{
			ClusterMatrix[HighY + i][HighZ] = 0;
			ClusterMatrix[HighY + i][HighZ + 36] = 0;
		}
		//Resets values for next loop
		NCCarr[arrPos] = -2;
		NCCHighest = -2;
	}
}