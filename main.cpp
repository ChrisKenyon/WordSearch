// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "WordList.h"
#include "Grid.h"
#include "WordSearch.h"

int main()
{
	try {
		// Set to false for using original wordlist and binary search
		// but make sure that debugWithHashAndBinary is false in the WordList.cpp checkValidity
		bool UseHashTable = true;

		// clear the output file (output for persisting words found)
		ofstream out("Output.txt", std::ofstream::out | std::ofstream::trunc);
		out.close();

		WordList dictionary(UseHashTable);
		dictionary.Sort(WordList::HEAP);

		// Uncomment for the list to be printed
		//cout << dictionary;

		Grid g1("puzzle1_size10");
		Grid g2("puzzle2_size20");
		Grid g3("puzzle3_size50");
		Grid g4("puzzle4_size100");
		Grid g5("puzzle5_size500");
		Grid g6("puzzle6_size1000");
		
		WordSearch ws1(g1, dictionary);
		WordSearch ws2(g2, dictionary);
		WordSearch ws3(g3, dictionary);
		WordSearch ws4(g4, dictionary);
		WordSearch ws5(g5, dictionary);
		WordSearch ws6(g6, dictionary);

		ws1.FindAndPrintWords();
		ws2.FindAndPrintWords();
		ws3.FindAndPrintWords();
		ws4.FindAndPrintWords();
		ws5.FindAndPrintWords();
		ws6.FindAndPrintWords();
	}
	catch (exception ex)
	{
		cout << ex.what();
	}
	
	int x;
	cin >> x;
    return 0;
}

