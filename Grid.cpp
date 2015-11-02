#include "stdafx.h"
#include "Grid.h"

Grid::Grid(string file)
{
	initializeMatrix(file);
}


Grid::~Grid()
{
}

int Grid::GetRowCount()
{
	return rows;
}

int Grid::GetColumnCount()
{
	return cols;
}

// I did this assignment early and followed the directions of the assignment prompt,
// so my search uses the same diagonal it is in and doesn't use the same char twice
string Grid::GetStringFromGrid(int row, int col, Directions dir, int numberOfChars, const int largestWordSize)
{
	if (numberOfChars > largestWordSize)
		throw new argumentException();
	const int initRow = row;
	const int initCol = col;
	int r = row;
	int c = col;

	// no words in the list are longer than the longest word, just initialize every char array with this so we have a buffer
	char *arr = new char[largestWordSize + 5]; 
	
	arr[0] = matrix[r][c];
	
	int i;
	for (i = 1; i < numberOfChars; i++)
	{
		switch (dir)
		{ 
		// need to handle edge of the matrix cases differently for each direction
		// if both col and row == 0 then either case will handle it correctly
		case UP_LEFT:
			// No words can be created in the corners
			if ((initRow == 0 && initCol == cols - 1) || (initRow == rows - 1 && initCol == 0))
				goto END;
			if (c == 0)
			{
				c = (cols - 1) - r;
				r = rows - 1;
			}
			else if (r == 0)
			{
				r = (rows - 1) - c;
				c = cols - 1;
			}
			else c-- & r--; // non-edge case
			break;
		case UP:
			if (r == 0)
				r = rows - 1;
			else r--;
			break;
		case UP_RIGHT:
			// No words can be created in the corners
			if ((initRow == 0 && initCol == 0) || (initRow == rows - 1 && initCol == cols - 1))
				goto END;
			if (c == cols - 1)
			{
				c = r;
				r = rows - 1;
			}
			else if (r == 0)
			{
				r = c;
				c = 0;
			}
			else c++ & r--;
			break;
		case RIGHT:
			if (c == cols - 1)
				c = 0;
			else c++;
			break;
		case DOWN_RIGHT:
			// No words can be created in the corners
			if ((initRow == 0 && initCol == cols -1) || (initRow == rows - 1 && initCol == 0))
				goto END;
			if (c == cols - 1)
			{
				c = (cols - 1) - r;
				r = 0;
			}
			else if (r == rows - 1)
			{
				r = (rows - 1) - c;
				c = 0;
			}
			else r++ & c++;
			break;
		case DOWN:
			if (r == rows - 1)
				r = 0;
			else r++;
			break;
		case DOWN_LEFT:
			// No words can be created in the corners
			if ((initRow == 0 && initCol == 0) || (initRow == rows - 1 && initCol == cols - 1))
				goto END;
			if (c == 0)
			{
				c = r;
				r = 0;
			}
			else if (r == rows - 1)
			{
				r = c;
				c = cols - 1;
			}
			else r++ & c--;
			break;
		case LEFT:
			if (c == 0)
				c = cols - 1;
			else c--;
			break;
		}
		if (c >= cols || r >= rows)
			throw new indexRangeException();
		else if (c != initCol || r != initRow) // check that it doesn't loop back
			arr[i] = matrix[r][c];
		else
		{
			arr[0] = '\0'; // return an empty string
			goto END;
		}
	}
	END:
	arr[i] = '\0';
	string retString = string(arr);
	delete[] arr;
	return retString;
}

// file read to create matrix
void Grid::initializeMatrix(string file)
{
	ifstream puzzle(file);
	puzzle >> cols >> rows;
	for (int row = 0; row < rows; row++)
	{
		vector<char> newRow(cols);
		matrix.push_back(newRow);
		for (int col = 0; col < cols; col++)
		{
			puzzle >> matrix[row][col];
		}
	}
	puzzle.close();
}
