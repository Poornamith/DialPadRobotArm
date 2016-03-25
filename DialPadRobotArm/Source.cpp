/*
===================================================================================
Program for DialPad Robot Arm
===================================================================================
* based on the Recursive algorithm which is available in Wikipedia written in .java
https://en.wikipedia.org/wiki/Maze_solving_algorithm
* This Maze solving algorithm can only solve shortest paths for co-ordinates on a single COLUMN.
i.e. both starting and ending points should be in one single ROW.
* The priority is given row-wise, not column wise
if you want vice-versa change the rows and columns and some minor tweaks for the recursiveSolve() function
===================================================================================
(copywrite) © Poornamith
the PAH inv
created: 24-03-2016
revised: 25-03-2016
www.poornamith.azurewebsites.net
===================================================================================
*/


#include <iostream>
#include <conio.h>
#include <math.h>

using namespace std;

//grid co-ordinates
const unsigned short gridR = 4, gridC = 3;

//mobile Number
int mobileNo = 0;

// Dialpad keys accessibility
short maze[gridR][gridC] = {
	{ 1,1,1 },
	{ 1,1,1 },
	{ 1,1,1 },
	{ 1,1,1 }
};


bool wasHere[gridR][gridC] = { 0 };
bool correctPath[gridR][gridC] = { 0 };		// The solution to the maze
short startR = 3, startC = 1;		// Starting R and C values of maze
short endR = 3, endC = 1;		// Ending R and C values of maze


								//fn prototypes for solving Maze
void solveMaze();
bool recursiveSolve(int row, int col);
void getNumber();
void digitLocation(int digit);

//display purpose ONLY
void showArr(bool _arr[gridR][gridC]);

int digit;

void main()
{
	//solveMaze();
	while (mobileNo == 0)
	{
		getNumber();
	}

	int digits[10] = { 0 };
	int i = 9;

	while (mobileNo > 0)
	{
		digit = mobileNo % 10;
		mobileNo /= 10;
		// << digit << endl;

		digits[i--] = digit;
	}

	cout << endl;

	for (int i = 1; i < 10; i++)
	{
		//cout << digits[i] << endl;
		digitLocation(digits[i]);
	}

	//digitLocation(7);

	getch();
}

void solveMaze()
{

	bool pathFound = recursiveSolve(startR, startC);

	if (pathFound)
	{
		cout << "shortest possible path: ";
		//display the path generated
		showArr(correctPath);
	}
	else
		cout << "No solutions to the Maze!.";

	//getch();
}

bool recursiveSolve(int row, int col) {

	if (row == endR && col == endC)
	{
		correctPath[row][col] = true;
		return true; // If you reached the end
	}

	if (maze[row][col] == 2 || wasHere[row][col])
		return false;

	// If you are on a wall or already were here
	wasHere[row][col] = true;

	if (row != gridR - 1) // Checks if not on bottom edge
		if (recursiveSolve(row + 1, col))
		{
			// Recalls method one to the bottom
			correctPath[row][col] = true;
			return true;
		}

	if (col != 0)  // Checks if not on left edge
		if (recursiveSolve(row, col - 1))
		{
			// Recalls method one to the left
			correctPath[row][col] = true;
			return true;
		}

	if (row != 0) // Checks if not on top edge
		if (recursiveSolve(row - 1, col))
		{
			// Recalls method one to the top
			correctPath[row][col] = true; // Sets that path value to true;
			return true;
		}


	if (col != gridC - 1) // Checks if not on right edge
		if (recursiveSolve(row, col + 1))
		{
			// Recalls method one to the right
			correctPath[row][col] = true;
			return true;
		}
	return false;
}

//display the array
void showArr(bool _arr[gridR][gridC])
{
	cout << endl << endl << digit << endl;

	for (int i = 0; i < gridR; i++)
	{
		for (int j = 0; j < gridC; j++)
		{
			cout << _arr[i][j] << " ";
		}
		cout << endl;
	}


	//array clear
	for (int i = 0; i < gridR; i++)
	{
		for (int j = 0; j < gridC; j++)
		{
			correctPath[i][j] = false;
			wasHere[i][j] = false;
		}
	}
}

void getNumber()
{
	//start:

	cout << "Enter the mobile Number: ";
	cin >> mobileNo;
	cin.clear(); while (cin.get() != '\n') {} //Loop to clear all the stored values in cin (if not when the user enters an invalid entry like a string, the switch statement is repeated infinitely)
											  //cout << mobileNo;
	return;
}

void digitLocation(int digit)
{
	//get the current location
	startR = endR;
	startC = endC;

	switch (digit)
	{
	case 0: endR = 3; endC = 1; break;
	case 1: endR = 2; endC = 0; break;
	case 2: endR = 2; endC = 1; break;
	case 3: endR = 2; endC = 2; break;
	case 4: endR = 1; endC = 0; break;
	case 5: endR = 1; endC = 1; break;
	case 6: endR = 1; endC = 2; break;
	case 7: endR = 0; endC = 0; break;
	case 8: endR = 0; endC = 1; break;
	case 9: endR = 0; endC = 2; break;
	}

	solveMaze();
}