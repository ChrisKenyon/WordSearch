#include "stdafx.h"
#include "Hashtable.h"

template <typename T>
Hashtable<T>::Hashtable()
{
	table.resize(HASH_SIZE);
}

template <typename T>
Hashtable<T>::~Hashtable()
{
}

template<typename T>
void Hashtable<T>::addItem(T value)
{
	int key = hash(value);
	table[key].push_back(value);
}

template<typename T>
void Hashtable<T>::deleteItem(T value)
{
	int key = hash(value);
	int collisionSize = table[key].size();
	for (int i = 0; i < collisionSize; i++)
	{
		if (table[key][i] == value)
			table[key].erase(i);
	}
}

// hash table lookup to see if value exists
// keys are not being used in this hash table in the traditional sense, as there are no key-value pairs
// this is the only necessity is to check if a value exists
template<typename T>
bool Hashtable<T>::inList(T value)
{
	int key = hash(value);
	int collisionSize = table[key].size();
	for (int i = 0; i < collisionSize; i++)
	{
		if (table[key][i] == value)
			return true;
	}
	return false;
}

// optimization code for finding the next highest word for prefix checking
//template<typename T>
//const T Hashtable<T>::getNextHighest(T value)
//{
//	int key = hash(value);
//	int collisionSize = ValueLists[key].size();
//	if (collisionSize == 0) return T(); // return empty lookup
//
//	T nextVal;
//	for (int i = 0; i < collisionSize; i++)
//	{
//		if (ValueLists[key][i] > value)
//		{
//			if (ValueLists[key][i] < nextVal)
//				nextVal = ValueLists[key][i];
//			else nextVal = ValueLists[key][i];
//		}
//	}
//	return nextVal;
//}

// mostly for debugging, makes sure that there aren't too many collisions
template<typename T>
int Hashtable<T>::findMaxCollisions()
{
	int maxSize = 0;
	for (int i = 0; i < HASH_SIZE; i++)
	{
		maxSize = (table[i].size() > maxSize) ? table[i].size() : maxSize;
	}
	return maxSize - 1;
}

// returns index in the vector
template<typename T>
int Hashtable<T>::hash(T value)
{
	// UNNECESSARY WITHOUT STRING PREFIX CHECKING
/*	if (std::is_same<T, string>::value)
	{
		// code for optimization for finding next alphabetical word (for prefix checking)
		//int end = (value.size() <= 5 ? value.size(): 5);
		//string hashString = value.substr(0, end);

		unsigned int hashInt = 1;
		for (int i = 0; i < value.size(); i++)
		{
			// multiply by a prime
			hashInt = hashInt * 101 + hashString[i];
		}
		// mod with a prime
		return hashInt % HASH_SIZE;
	}
	else 
	{*/ 
		std::hash<T> hasher;
		return hasher(value) % HASH_SIZE;
	//}
}
