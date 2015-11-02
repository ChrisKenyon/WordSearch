#include "stdafx.h"
#include "WordSearch.h"
#include <fstream>

WordSearch::WordSearch(Grid gameGrid, WordList sortedList) :
	sortedList(sortedList), gameGrid(gameGrid)
{
}

WordSearch::~WordSearch()
{
}

void WordSearch::FindAndPrintWords()
{
	vector<string> matches = findMatches();
	printMatches(matches, gameGrid.GetRowCount(), gameGrid.GetColumnCount());
}

// iterates through each character in the grid in each direction starting at 5 characters
// then checks against the dictionary to see if it is possible, not possible, or the start
// of a word that is in the list
// the kluge solution for the hash table look ups is to always return match or possible prefix
// so that every 5-22 length character is checked from the grid
vector<string> WordSearch::findMatches()
{
	clock_t startTime = clock();
	int maxChars = sortedList.getLargestWordLength();

	vector<string> matches;
	for (int row = 0; row < gameGrid.GetRowCount(); row++)
	{
		for (int col = 0; col < gameGrid.GetColumnCount(); col++)
		{
			for (int direction = Grid::UP_LEFT; direction <= Grid::LEFT; direction++)
			{
				int numberChars = 5;
				while (true)
				{
					if (numberChars > maxChars)
						goto NEXT_DIRECTION;

					// grab potential string from the grid
					string word = gameGrid.GetStringFromGrid(row, col, (Grid::Directions)direction, numberChars, maxChars);
					WordList::Validity val = sortedList.CheckWordValidity(word);
					switch (val)
					{
					case WordList::Validity::NOT_POSSIBLE:
						goto NEXT_DIRECTION;
						break;
					case WordList::Validity::POSSIBLE_PREFIX:
						numberChars++;
						break;
					case WordList::Validity::MATCH:
						matches.push_back(word); // while we may have found a word, we may want to check if there is a bigger word, we'll add it anyway though
						numberChars++; // increase chars rather than go to next direction
						break;
					}
				}
			NEXT_DIRECTION:
				continue;
			}
		}
	}
	clock_t execTime = clock() - startTime;
	ofstream outputFile("Output.txt", ofstream::app);
	cout << endl << "Execution time for findMatches(): " << (float)execTime / CLOCKS_PER_SEC << " seconds" << endl;
	outputFile << endl << "Execution time for findMatches(): " << (float)execTime / CLOCKS_PER_SEC << " seconds" << endl;
	outputFile.close();
	return matches;
}

// prints the vector with the count of matches
void WordSearch::printMatches(vector<string> matches, int rows, int cols)
{
	ofstream outputFile("Output.txt", ofstream::app); // not necessary, but I outputted so that I could post words on piazza for the class
	
	cout << "The "<< matches.size() << " words in the " << rows << " by " << cols << " grid are:" << endl;
	outputFile << endl << "The " << matches.size() << " words in the " << rows << " by " << cols << " grid are:" << endl;

	for (int i = 0; i < matches.size(); i++)
	{
		outputFile << matches[i] << endl;
		cout << matches[i] << endl;
	}
	outputFile.close();
}

