/*
A heap is a data structure that implements the following:
	
	void insert(int key) -> insert key into heap
	bool removeMin(int &key) ->remove smallest key from heap and put this value in variable key passed as reference, return false if heap is empty

a heap is implemented with a binary tree

the binary heap tree in heap has two properties
	1. the key m the children are larger than the parents
		left->key > parent->key
		right->key > parent->key
	2. heaps are "left filled" that is all levels are full except for the last one

the height of a heap is the maximum distance from the top to the bottom children
	h=O(logn)
	2^h-1=N
	h=log2(n+1)

insert::
	1) fix heap, starting at node inserted swap it with the parent if the key in parent is larger than the key in the child
	2) continue upwards swapping until it is not necessary or we reach the root

	the number of steps in the insertion is proportional to the number of swaps that is limited by the height of the heap, 
	since height is O(logn), then the execution time for insert is O(logn)

removeMin::
	1) remove element at the top and store key in a tmp variable to return it at the end
	2) removal of root leaves a hole.  substitute the root with the rightmost element at the bottom row
	3) starting at the root compare the parent with the children and if the parent is larger than any of the children then swap parent with smallest child (compare left to right and pick smallest...)
	4) continue swapping down the heap until it is no longer necessary or reach bottom

max number of swaps will be limited by height of the tree that is O(logn) therefore, removeMin takes O(logn)

heap implementation:
	we could implement a heap using binary tree with left and right pointers 
	however it is simpler and more efficient to use an array to implement a heap

	in general you may represent a binary tree using an array in this way:
	left(i) = 2i+1
	right(i) = 2i+2
	parent(i) = (i-1)/2
*/
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "heap.h"
// #include "array-dictionary.h"

Heap::Heap(int maxSize)
{
	_maxSize = maxSize;
	_last = 0;
	_heap = (ArrayDictionaryNode*) malloc(maxSize * sizeof(ArrayDictionaryNode));
}

Heap::~Heap()
{
	delete [] _heap;
}

// int left(int i)
// {
// 	return 2i+1;
// }

// int right(int i)
// {
// 	return 2i+2;
// }

// int hparent(int i)
// {
// 	return (i-1)/2;
// }

bool
Heap::insert(ArrayDictionaryNode node)
{
	if (_last == _maxSize)
	{
		return false;
	}

	_heap[_last] = node;
	_last++;

	int child = _last - 1;
	int parent = hparent(child);

	while (child > 0 && strcmp(_heap[child].key, _heap[parent].key) < 0)
	{
		//try to swap if we haven't reached root
		// if (heap[child] < heap[parent])
		// {
			//need to swap
			ArrayDictionaryNode tmp = _heap[child];
			_heap[child] = _heap[parent];
			_heap[parent] = tmp;
			//update parent and child
			child = parent;
			parent = hparent(child);
		// }
		// else
		// {
		// 	break;
		// }
	}//while

	return true;
}

ArrayDictionaryNode 
Heap::removeMin()
{
	if(_last == 0) //heap is empty
	{
		ArrayDictionaryNode tmp;
		return tmp;
	}
	//heap isn't empty, get min key

	ArrayDictionaryNode min = _heap[0];

	//sub root w/last element
	_heap[0] = _heap[_last-1];
	_last--;

	//fix heap starting at root of the heap
	//swap parent with smallest child
	//if parent is larger than children

	int parent = 0;
	int l = left(parent);
	int r = right(parent);

	while(l < _last)
	{
		//get smallest child between l and r
		int minChild = l;
		if(r < _last && strcmp(_heap[r].key, _heap[l].key) < 0)
		{
			minChild = r;
		}

		if (strcmp(_heap[minChild].key, _heap[parent].key) < 0)
		{//need to swap min child and parent
			ArrayDictionaryNode tmp = _heap[minChild];
			_heap[minChild] = _heap[parent];
			_heap[parent] = tmp;
			//update parent
			parent = minChild;
			l = left(parent);
			r = right(parent);
		}
		else
		{
			//no need to swap, heap is ordered, done
			break;
		}
	}//while
	
	return min;
}

void
heapSort(ArrayDictionaryNode *array, int n)
{
	Heap heap(n);

	//fill heap w/numbers
	for (int i = 0; i < n; i++) //takes O(logn)
	{
		heap.insert(array[i]);
	}
	
	//put numbers back in array
	for (int i = 0; i < n; i++) //takes O(logn)
	{
		array[i] = heap.removeMin();
	}
	//array is now sorted in ascending order in O(logn)
}