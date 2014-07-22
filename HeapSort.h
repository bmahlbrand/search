//HeapSort

//sorting algorithm that uses heaps
//given an array of unsorted numbers
	//+create a heap
	//+for each num in array
		//heap.insert(array[i]);
//O(nlogn) - runtime of insert
	//+empty array
	//+for each num in heap i
//O(nlogn) - runtime of rmeoveMin
		//heap.removeMin(array[i]);
		//array[i] = min;
		// i++;
	//you will get a sorted array in O(nlogn)

// #include "heap.h"

void heapSort(ArrayDictionaryNode **a, int n);