
// Implementation of a dictionary using an array and sequential search
// The array will be dynamically resized if necessary

#include <stdlib.h>
#include <string.h>

#include "array-dictionary.h"

// Constructor
ArrayDictionary::ArrayDictionary() {
	maxNumber = 2;
	currentNumber = 0;
	// array = new ArrayDictionaryNode[maxNumber];
	array = (ArrayDictionaryNode*) malloc(maxNumber * sizeof(ArrayDictionaryNode));
}

// Add a record to the dictionary. Returns false if key already exists
bool
ArrayDictionary::addRecord( KeyType key, DataType record ) {	
	for (int i = 0; i < currentNumber; i++) {
		if (strcmp(array[i].key, key) == 0)
		{
			array[i].data = record;
			return false;
		}
	}

	if (currentNumber == maxNumber)	{
		resize();
	}

	array[currentNumber].key = strdup(key);
	array[currentNumber].data = record;
	currentNumber++;
	
	return true;
}

void
ArrayDictionary::resize()
{
	maxNumber = maxNumber * 2;
	array = (ArrayDictionaryNode*)realloc(array, maxNumber * sizeof(ArrayDictionaryNode));
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
ArrayDictionary::findRecord( KeyType key)
{
	int i = 0;
	while (i < currentNumber)
	{
		if (strcmp(array[i].key, key) == 0)
		{
			return array[i].data;
		}

		i++;
	}

	return NULL;
}

// Removes one element from the table
bool
ArrayDictionary::removeElement(KeyType key)
{
	for (int i = 0; i < currentNumber; i++)
	{
		if (strcmp(array[i].key, key) == 0)
		{
			// delete array[i].key;
			// delete array[i].data;
			
			for (; i < currentNumber; i++)
			{
				array[i] = array[i + 1];
			}

			currentNumber--;

			return true;
		}
	}

	return false;
}

// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType *
ArrayDictionary::keys(int *n)
{
	KeyType *keys = new KeyType[maxNumber];
	
	for (int i = 0; i < maxNumber; i++) 
	{
		keys[i] = array[i].key;
	}

	*n = currentNumber;

	return keys;
}
