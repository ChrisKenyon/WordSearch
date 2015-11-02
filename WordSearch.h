#pragma once
#include "stdafx.h"
#include "Grid.h"
#include "WordList.h"

class WordSearch // helper class to avoid globals
{
public:
	WordSearch(Grid gameGrid, WordList sortedList);
	~WordSearch();
	void FindAndPrintWords();
private:
	WordList sortedList;
	Grid gameGrid;

	vector<string> findMatches();
	void printMatches(vector<string> matches, int rows, int cols);
};

