#pragma once
#include "stdafx.h"
#include <vector>

using namespace std;

template <typename T>
class Heap
{
public:
	Heap();
	~Heap();

	void InitializeMaxHeap(vector<T>& list);
	void InitializeMinHeap(vector<T>& list);
	void Heapsort(vector<T> & copyOutVector);
private:
	vector<T> heap;

	int parent(int idx) const;
	int left(int idx) const;
	int right(int idx) const;
	const T & getItem(int idx) const;

	void maxHeapify(int i, int bottom);
	void buildMaxHeap();

	void minHeapify(int i, int heapSize);
	void buildMinHeap();

};
