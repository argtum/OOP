#include "pch.h"
#include <array>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>

using namespace std;

enum class Status
{
	Ok,
	WrongArgumentCount,
	InvalidInputFile,
	WrongInputData,
	CanNotInvertMatrix
};

const unsigned int ARGUMENT_COUNT = 2;
const unsigned int MATRIX_SIZE = 3;

using Matrix = array<array<double, MATRIX_SIZE + 1>, MATRIX_SIZE + 1>;

void printError(Status error)
{
	if (error == Status::WrongArgumentCount)
	{
		cout << "Invalid arguments count\n"
			 << "Usage: invert.exe <matrix file>\n";
	}
	else if (error == Status::InvalidInputFile)
	{
		cout << "Invalid input file\n"
			 << "Can't open input files\n";
	}
	else if (error == Status::WrongInputData)
	{
		cout << "Invalid input data\n"
			 << "Program works with 3x3 matrix\n";
	}
	else if (error == Status::CanNotInvertMatrix)
	{
		cout << "Invalid matrix\n"
			 << "Discriminant is 0. This matrix cannot be inverted\n";
	}
}

void readMatrix(string fileName, Matrix& matrix, Status& status)
{
	ifstream inputFile(fileName);
	string line;
	int row = 0;
	int col;

	if (!inputFile.is_open())
	{
		status = Status::InvalidInputFile;
	}
	else
	{
		while (getline(inputFile, line) && status == Status::Ok)
		{
			col = 0;

			if (row < MATRIX_SIZE)
			{
				stringstream stringIterator(line);
				
				while (!stringIterator.eof())
				{
					stringIterator >> matrix[row][col];
					col++;
				}

				if (col != MATRIX_SIZE)
				{
					status = Status::WrongInputData;
				}
			}

			row++;
		}

		if (row != MATRIX_SIZE)
		{
			status = Status::WrongInputData;
		}
	}
}

void checkArgumentNumber(int argc, Status& status)
{
	if (argc != ARGUMENT_COUNT)
	{
		status = Status::WrongArgumentCount;
	}
}

void PrintMatrix(const Matrix& resultMatrix)
{
	for (int row = 0; row < MATRIX_SIZE; row++)
	{
		for (int col = 0; col < MATRIX_SIZE; col++)
		{
			cout.width(10);
			cout.setf(ios::left);
			cout << fixed << setprecision(3) << resultMatrix[row][col];
		}
		cout << endl;
	}
}
/*
bool isDeterminantNotNull(Matrix& matrix)
{
	return matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0] + matrix[0][2] * matrix[1][0] * matrix[2][1] - matrix[0][2] * matrix[1][1] * matrix[2][0] - matrix[0][0] * matrix[1][2] * matrix[2][1] - matrix[0][1] * matrix[1][0] * matrix[2][2] != 0;
}

void invertMatrix(Matrix& inputMatrix, Matrix& resultMatrix, Status& status)
{
	if (isDeterminantNotNull(inputMatrix))
	{

	}
	else
	{
		status = Status::CanNotInvertMatrix;
	}
}
*/
int main(int argc, char* argv[])
{
	Status status = Status::Ok;
	Matrix inputMatrix;//, resultMatrix;

	checkArgumentNumber(argc, status);

	if (status == Status::Ok)
	{
		readMatrix(argv[1], inputMatrix, status);
	}

	if (status == Status::Ok)
	{
		//invertMatrix(inputMatrix, resultMatrix, status);
	}

	if (status == Status::Ok)
	{
		PrintMatrix(inputMatrix);
	}
	else
	{
		printError(status);
	}

	return 0;
}
