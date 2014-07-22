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

void heapSort(ArrayDictionaryNode **array, int n)
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