#include "Header.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>

using namespace std;

//Turns 1D array into 2D array
//Fingures out how many rows you have gone down in the 2D and compensates for that when finding the correct value in the 1D
void Matrix::CreateMatrix(double* arr, double** matrix, int sizeR, int sizeC)
{
	for (int i = 0; i < sizeR; i++)
	{
		for (int x = 0; x < sizeC; x++)
		{
			matrix[i][x] = arr[(i*sizeC) + x];
		}
	}
}

//Turns 2D array into 1D array
//Does the exact reverse of the CreateMatrix function
void Matrix::ReverseMatrix(double* ClusterData, double** ClusterMatrix, int ClusterRows, int ClusterColumns)
{
	for (int i = 0; i < ClusterRows; i++)
	{
		for (int x = 0; x < ClusterColumns; x++)
		{
			ClusterData[(i*ClusterColumns) + x] = ClusterMatrix[i][x];
		}
	}
}