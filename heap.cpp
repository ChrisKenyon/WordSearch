#include "stdafx.h"
#include "heap.h"

// PUBLIC 

template<typename T>
Heap<T>::Heap()
{
}

template<typename T>
Heap<T>::~Heap()
{
}

template<typename T>
void Heap<T>::InitializeMaxHeap(vector<T> &list)
{
	for (int i = 0; i < list.size(); i++)
		heap.push_back(list[i]);

	buildMaxHeap();
}

template<typename T>
void Heap<T>::InitializeMinHeap(vector<T> &list)
{
	for (int i = 0; i < list.size(); i++)
		heap.push_back(list[i]);
	buildMinHeap();
}

template<typename T>
void Heap<T>::Heapsort(vector<T>& copyOutVector)
{
	int heapSize = heap.size();
	buildMaxHeap();

	for (int i = heap.size() - 1; i > 0; i--)
	{
		swap(heap[0], heap[i]);
		heapSize--;

		maxHeapify(0, heapSize);
	}

	copyOutVector = heap;
}

// PRIVATE

// INDEXES & GET
template<typename T>
int Heap<T>::parent(int idx) const
{
	return (idx + 1) / 2 - 1;
}

template<typename T>
int Heap<T>::left(int idx) const
{
	return 2 * (idx + 1) - 1;
}

template<typename T>
int Heap<T>::right(int idx) const
{
	return 2 * (idx + 1);
}

template<typename T>
const T & Heap<T>::getItem(int idx) const
{
	if (idx > heap.size() - 1 || idx < 0)
		throw new indexRangeException();
	return heap[idx];
}

// MAX HEAP
// maxHeapify puts the root in the right position with recursive swaps
template<typename T>
void Heap<T>::maxHeapify(int root, int bottom)
{
	bottom--;
	int leftChild = left(root);
	int rightChild = right(root);
	int largerChild;

	if (leftChild <= bottom)
	{
		if (leftChild == bottom)
			largerChild = leftChild;
		else
		{
			// get the larger one 
			if (heap[leftChild] > heap[rightChild]) // there will be no ==, this is for unique key word dictionary
				largerChild = leftChild;
			else largerChild = rightChild;
		}
		if (heap[root] < heap[largerChild])
		{
			swap(heap[root], heap[largerChild]);
			maxHeapify(largerChild, bottom);
		}
	}
}

// build max heap iterates through the heap placing the nodes in the right spots
// you can start at half the heap size because the lower half will not have children by definition
template<typename T>
void Heap<T>::buildMaxHeap()
{
	int heapSize = heap.size();
	for (int i = (heap.size() + 1) / 2; i >= 0; i--)
		maxHeapify(i, heapSize);
}

// MIN HEAP
template<typename T>
void Heap<T>::minHeapify(int root, int bottom)
{
	bottom--;
	int leftChild = left(root);
	int rightChild = right(root);
	int smallerChild;

	if (leftChild <= bottom)
	{
		if (leftChild == bottom)
			smallerChild = leftChild;
		else
		{
			// get the smaller one 
			if (heap[leftChild] < heap[rightChild]) // there will be no ==, this is for unique key word dictionary
				smallerChild = leftChild;
			else smallerChild = rightChild;
		}
		if (heap[root] > heap[smallerChild])
		{
			swap(heap[root], heap[smallerChild]);
			minHeapify(smallerChild, bottom);
		}
	}
}

template<typename T>
void Heap<T>::buildMinHeap()
{
	int heapSize = heap.size();
	for (int i = (heap.size() + 1) / 2; i >= 0; i--)
		minHeapify(i, heapSize);
}