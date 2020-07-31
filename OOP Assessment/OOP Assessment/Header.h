#pragma once
#include <iostream>
#include <string>

using namespace std; 

//Base image class and parent class to the other image classes
class BaseImage
{
private:
	int rows;
	int columns;
public:
	BaseImage() {};	//Default initialiser
	BaseImage(int Rows, int Columns)	//Specific initialiser
	{
		rows = Rows;
		columns = Columns;
	}
	virtual int Rows() { return rows; };	//Virtual so it can be overiden in the child classes
	virtual int Columns() { return columns; };	//Virtual so it can be overiden in the child classes
	virtual ~BaseImage() { cout << "BASE IMAGE DESTRUCTOR" << endl; };	//Destructor
};
class LargeImage : public BaseImage
{
private:
	int rows;
	int columns;
public:
	LargeImage(int Rows, int Columns)	//Specific initialiser
	{
		rows = Rows;
		columns = Columns;
	};
	virtual int Rows() { return rows; };
	virtual int Columns() { return columns; };
	~LargeImage() { cout << "LARGE IMAGE DESTRUCTOR" << endl; };	//Destructor
};
class RefImage : public BaseImage
{
private:
	int rows;
	int columns;
public:
	RefImage(int Rows, int Columns)	//Specific initialiser
	{
		rows = Rows;
		columns = Columns;
	};
	virtual int Rows() { return rows; };
	virtual int Columns() { return columns; };
	~RefImage() { cout << "REF IMAGE DESTRUCTOR" << endl; };	//Destructor
};


class ReadFile
{
public:
	ReadFile() {};	//Default initialiser
	double* read_text(const char* fileName, int sizeR, int sizeC);
	void write_pgm(const char* filename, double* data, int sizeR, int sizeC, int Q);
	~ReadFile() { cout << "READ FILE DESTRUCTOR" << endl; }; //Destructor
};

class Matrix
{
public:
	Matrix() {};	//Default initialiser
	void CreateMatrix(double* arr, double** matrix, int sizeR, int sizeC);
	void ReverseMatrix(double* ClusterData, double** ClusterMatrix, int ClusterRows, int ClusterColumns);
	~Matrix() { cout << "MATRIX DESTRUCTOR" << endl; }; //Destructor
};

class NCC
{
public:
	NCC() {};	//Default initialiser
	void FindWally(double** WallyMatrix, double** ClusterMatrix, double* WallyData, int WallyRows, int WallyColumns, int ClusterRows, int ClusterColumns, int locations);
	~NCC() { cout << "NCC DESTRUCTOR" << endl; };	//Destructor
};