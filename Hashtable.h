#pragma once
#include"stdafx.h"
#include<vector>

template <typename T>
class Hashtable
{
public:
	Hashtable();
	~Hashtable();
	void addItem(T value);
	void deleteItem(T value);
	bool inList(T value);
	//const T getNextHighest(T value);
	int findMaxCollisions();
private:
	// first prime number over 90k, around the num of words, but higher
	// allows few collisions and good spreading
	const int HASH_SIZE = 90001; 
	vector<vector<T>> table;
	int hash(T value);
};

