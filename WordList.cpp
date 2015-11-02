#include "stdafx.h"
#include "WordList.h"
#include <fstream>

WordList::WordList(bool useHashTable) :
	useHashTable(useHashTable)
{
	initializeListFromFile();
	if (useHashTable)
	{
		cout << "Hashing..." << endl;
		for (int i = 0; i < words.size(); i++)
		{
			wordsTable.addItem(words[i]);
		}
		findLargestWord();
	}
	if (wordsTable.findMaxCollisions() > 10)
		throw new programmingErrorException();
}

WordList::~WordList()
{
}

// sorts and clocks the execution time
void WordList::Sort(SortType type)
{
	cout << "Sorting..." << endl;
	clock_t startTime = clock();

	switch (type)
	{
	case INSERTION: insertionSort(); break;
	case QUICK: quickSort(words, 0, words.size() - 1); break;
	case MERGE: mergeSort(words); break;
	case HEAP:
		Heap<string> heap;
		heap.InitializeMaxHeap(words);
		heap.Heapsort(words);
		break; 
	}

	clock_t execTime = clock() - startTime;

	ofstream outputFile("Output.txt", ofstream::app); 
	cout << endl << "Execution time for Sort(): " << (float)execTime / CLOCKS_PER_SEC << " seconds" << endl;
	outputFile << endl << "Execution time for Sort(): " << (float)execTime / CLOCKS_PER_SEC << " seconds" << endl;
	outputFile.close();
}

// return of NOT_POSSIBLE means that there is no possible words that could
// match the word fragment as the beginning of the word
// return of POSSIBLE_PREFIX means that there is no direct match, but there is a word
// that contains the string as its beginning
// return of MATCH means the word was found in the dictionary
WordList::Validity WordList::CheckWordValidity(string lookup)
{
	bool debugWithHashAndBinary = false; // set to true for hash&binary together optimization - must set UseHashTable to true
	if (debugWithHashAndBinary && !useHashTable)
		throw new programmingErrorException();

	if (lookup.size() < 5)
		return NOT_POSSIBLE;

	// the kluge solution for my program for the hash table look ups is to always return match or possible prefix
	// so that every 5-22 length character is checked from the grid. This is for non optimized
	if (useHashTable)
	{
		if (wordsTable.inList(lookup))
			return MATCH;
		else if (!debugWithHashAndBinary) // if false then use a combination of hash and binary searches
			return POSSIBLE_PREFIX;
		//wordToCheck = wordsTable.getNextHighest(lookup); // attempted optimization on the hash table lookup for prefixes (doesn't speed it up more than binary but is faster than full 5-22 iteration)
	}

	// binary search

	string wordToCheck = binarySearch(lookup);

	// shouldn't be true if using the hash & binary.
	// Added the !debugWithHashAndBinary to quickly move on to checking prefix
	// rather than compare string as && will check the lhs then return false
	if (!debugWithHashAndBinary && wordToCheck == lookup) 
	{
		if (useHashTable) throw new programmingErrorException();
		else return MATCH;
	}
	else if (checkIfPrefix(wordToCheck, lookup))
	{
		return POSSIBLE_PREFIX;
	}
	else return NOT_POSSIBLE;

}

int WordList::getLargestWordLength()
{
	if (largestWordLength == 0)
		findLargestWord();
	return largestWordLength;
}

void WordList::findLargestWord()
{
	for (int i = 0; i < words.size(); i++)
		largestWordLength = words[i].size() > largestWordLength ? words[i].size() : largestWordLength;
}

// read the list from the file
void WordList::initializeListFromFile()
{
	ifstream wordListFile ("wordlist.txt");
	for (string line; getline(wordListFile, line); )
	{
		words.push_back(line);
	}
	wordListFile.close();
}

// slow insertion sort (represents the natural human way of sorting)
void WordList::insertionSort()
{
	int length = words.size();
	int x = 0;
	for (int i = 0; i < length; i++)
	{
		x = i;
		while (x > 0 && words[x] < words[x - 1])
		{
			swap(words[x], words[x - 1]);
			x--;
		}
	}
}

// recursive quick sort
void WordList::quickSort(vector<string> &subWordList, const int left, const int right)
{
	int partVal = partition(subWordList, left, right);
	if (left < partVal - 1)
	{
		quickSort(subWordList, left, partVal - 1);
	}
	if (partVal + 1 < right)
	{
		quickSort(subWordList, partVal + 1, right);
	}
}

// swaps all values less than the value of the middle index of the subWordList
// to the left and those greater to the right, then returns a pivot index
int WordList::partition(vector<string> &subWordList, const int left, const int right)
{
	const int middle = (left + right) / 2;
	string pivot = subWordList[middle];
	swap(subWordList[middle], subWordList[left]);
	int first = left + 1;
	int last = right;
	while (first <= last)
	{
		while (first <= last && subWordList[first] <= pivot)
		{
			first++;
		}
		while (first <= last && subWordList[last] > pivot)
		{
			last--;
		}

		if (first < last)
		{
			swap(subWordList[first], subWordList[last]);
		}
	}
	swap(subWordList[first - 1], subWordList[left]);
	return first - 1;
}

void WordList::mergeSort(vector<string> &subWordList)
// recursive merge sort
{
	if (subWordList.size() > 1)
	{
		vector<string> sub1(subWordList.begin(), subWordList.begin() + subWordList.size() / 2);
		mergeSort(sub1);
		vector<string> sub2(subWordList.begin() + subWordList.size() / 2, subWordList.end());
		mergeSort(sub2);
		merge(subWordList, sub1, sub2);
	}
}

void WordList::merge(vector<string>& words, vector<string>& sub1, vector<string>& sub2)
// merge function for mergeSort - adds to the words list from two sublists
{
	words.clear();
	int x = 0, y = 0;
	// iterate while x has not reached the end of sub1 and y hasn't for sub2
	while (x < sub1.size() || y < sub2.size()) 
	{
		if (x != sub1.size() && (y == sub2.size() || sub1[x] <= sub2[y]))
		{
			words.push_back(sub1[x]);
			x++;
		}
		else if (y != sub2.size() && (x == sub1.size() || sub1[x] > sub2[y]))
		{
			words.push_back(sub2[y]);
			y++;
		}
	}
}

string WordList::binarySearch(const string lookup) const
// specialized binary search for this project
// returns the closest word to the lookup (greater than or equal to)
{
	int left, middle, right;

	left = 0;
	right = words.size();
	while (left < right) {
		middle = (left + right) / 2;
		if (words[middle] == lookup)
			return words[middle];
		if (words[middle] > lookup) {
			right = middle - 1;
		}
		else if (words[middle] < lookup) {
			left = middle + 1;
		}
		else break;
		if (left < 0)
			return words[0];
	}
	if (right >= words.size())
		return words[words.size() - 1];
	else if (lookup > words[right])
		return words[right + 1];
	else return words[right];
}

bool WordList::checkIfPrefix(string &word, string &prefix)
// while the string found may not be a word, it may be the 
// beginning of another word, so 'true' indicates to keep searching
{
	if (word.size() < prefix.size())
		return false;
	for (int i = 0; i < prefix.size(); i++)
	{
		if (word[i] != prefix[i])
			return false;
	}
	return true;
}

ostream & operator<<(ostream & cstr, const WordList & wl)
// overload operator for printing the list
{
	int num = wl.words.size();
	for (int i = 0; i < num; i++)
		cstr << wl.words[i] << endl;
	return cstr;
}