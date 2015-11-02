#pragma once
#include "stdafx.h"
#include <vector>
#include "heap.cpp"
#include "Hashtable.cpp"

class WordList
{
public:
	enum Validity { NOT_POSSIBLE, POSSIBLE_PREFIX, MATCH};
	enum SortType { INSERTION, QUICK, MERGE, HEAP };
	
	WordList(bool useHashTable);
	~WordList();
	void Sort(SortType type);
	
	// compares a lookup string to the list of real words and returns
	// a Validity value to provide information about what was found
	Validity CheckWordValidity(string lookup);

	int getLargestWordLength();

	// print list
	friend ostream &operator<<(ostream &cstr, const WordList &c);
private:
	vector<string> words;
	Hashtable<string> wordsTable;
	bool useHashTable;
	int largestWordLength;
	// read from file method
	void initializeListFromFile();

	// sorting algos
	void insertionSort();
	void quickSort(vector<string>& arr, const int left, const int right);
	int partition(vector<string>& arr, const int left, const int right);
	void mergeSort(vector<string>& subWordList);
	void merge(vector<string> &words, vector<string> &sub1, vector<string> &sub2);

	// search algos
	string binarySearch(const string lookup) const;
	bool checkIfPrefix(string &word, string &prefix);

	// find largest word length
	void findLargestWord();
};

