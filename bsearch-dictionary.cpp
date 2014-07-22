
// Implementation of a dictionary using an array and binary search
// It will inherit from the ArrayDictionary

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "bsearch-dictionary.h"
#include "heap.h"
// #include "HeapSort.cpp"
// Constructor
BinarySearchDictionary::BinarySearchDictionary()
{
	sorted = false;
  	maxNumber = 2;
	currentNumber = 0;
	array = (ArrayDictionaryNode*) malloc(maxNumber * sizeof(ArrayDictionaryNode));
}

bool
BinarySearchDictionary::addRecord( KeyType key, DataType record) {
	sorted = false;
	return ArrayDictionary::addRecord(key, record);
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
BinarySearchDictionary::findRecord( KeyType key)
{
	if (!sorted) {
		sort();
		sorted = true;
	}

  	int start = 0;
    int end = currentNumber - 1;

    while(end > start) {
    
        int mid = (start + end) / 2;
        int result = strcmp(key, array[mid].key);
       
        if(result == 0) {
            return array[mid].data;
        }
        else if(result < 0) {
            end = mid - 1;
        }
        else {
            start = mid+1;
        }
    }

    return NULL;
}


// Sort array using heap sort
void
BinarySearchDictionary::sort()
{
	printf("Before\n");
	for (int i = 0; i < currentNumber; i++) {
		printf("%s\n", array[i].key);
	}
    
    heapSort(array, currentNumber);
        // Add your code here

	printf("After\n");
	for (int i = 0; i < currentNumber; i++) {
		printf("%s\n", array[i].key);
	}
}

bool 
BinarySearchDictionary::removeElement(KeyType key)
{
    return ArrayDictionary::removeElement(key);
}

KeyType * 
BinarySearchDictionary::keys(int * n)
{
    return ArrayDictionary::keys(n);
}