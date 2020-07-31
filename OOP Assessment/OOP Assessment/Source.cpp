#include "Header.h"
#include<iostream>
#include<fstream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;


int main()
{
	int locations;
	bool answer = false;

	while (answer == false)
	{
		cout << "Welcome to Where's Wally! \nHow many Locations do you want to find? (0 gives the base image)" << endl; //Lets user choose N-many Wallys to find
		cin >> locations;
		if(locations >= 0 && locations <= 1650)
		{
			cout << "Finding " << locations << " location(s)" << endl;
			answer = true;
		}
		else
		{
			cout << "You have entered an invalid input, Please select a whole number between 0 and 1650 included!" << endl;
		}
	}
	
	//Creates all the accessors for the classes
	BaseImage *Wally = new RefImage(49, 36);
	BaseImage *Cluster = new LargeImage(768, 1024);

	ReadFile *wally = new ReadFile();
	ReadFile *cluster = new ReadFile();

	Matrix *wallyMatrix = new Matrix();
	Matrix *clusterMatrix = new Matrix();

	NCC *WheresWally = new NCC();

	//Creates the 1D and 2D arrays
	double* WallyData = new double[Wally->Rows() * Wally->Columns()];
	double* ClusterData = new double[Cluster->Rows() * Cluster->Columns()];

	double** WallyMatrix = new double*[Wally->Rows()];
	for (int i = 0; i < Wally->Rows(); ++i)
	{
		WallyMatrix[i] = new double[Wally->Columns()];
	}

	double** ClusterMatrix = new double*[Cluster->Rows()];
	for (int i = 0; i < Cluster->Rows(); ++i)
	{
		ClusterMatrix[i] = new double[Cluster->Columns()];
	}

	//Calls for the .txt files to be put into 1D Arrays
	ClusterData = cluster->read_text("Cluttered_scene.txt", Cluster->Rows(), Cluster->Columns());
	WallyData = wally->read_text("Wally_grey.txt", Wally->Rows(), Wally->Columns());
	//Calls for the 1D arrays to be tured into 2D arrays or matricies
	clusterMatrix->CreateMatrix(ClusterData, ClusterMatrix, Cluster->Rows(), Cluster->Columns());
	wallyMatrix->CreateMatrix(WallyData, WallyMatrix, Wally->Rows(), Wally->Columns());
	//Calls the NNS function to find Wally, and outlines him
	WheresWally->FindWally(WallyMatrix, ClusterMatrix, WallyData, Wally->Rows(), Wally->Columns(), Cluster->Rows(), Cluster->Columns(), locations);
	//Calls the function that turns the newly changed 2D arry back into a 1D array 
	clusterMatrix->ReverseMatrix(ClusterData, ClusterMatrix, Cluster->Rows(), Cluster->Columns());
	//Calls the function to turn the 1D array into a .PMG file
	cluster->write_pgm("cluster.pgm", ClusterData, Cluster->Rows(), Cluster->Columns(), 255);
	//Deletes all class accessors
	delete Wally;
	delete Cluster;
	delete wally;
	delete cluster;
	delete wallyMatrix;
	delete clusterMatrix;
	delete WheresWally;

	cout << endl << "FINISHED";
	cin.get();
	cin.get();

	return 0;
}