#pragma once
#include <vector>
class Grid
{
public:
	Grid(string file);
	~Grid();
	int GetRowCount();
	int GetColumnCount();

	enum Directions { UP_LEFT, UP, UP_RIGHT, RIGHT, DOWN_RIGHT, DOWN, DOWN_LEFT, LEFT};
	
	// searches the grid starting at a matrix position and
	// creating a string of [numberOfChars] length in the direction [dir]
	string GetStringFromGrid(int row, int col, Directions dir, int numberOfChars, const int largestWordSize);

private:
	vector<vector<char>> matrix;
	// cols and rows are the dimensions of the grid
	int cols, rows;
	// string file name is necessary in constructor/initialization
	void initializeMatrix(string file);
};

