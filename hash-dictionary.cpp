
// Implementation of a dictionary using a hash table

#include <stdlib.h>
#include <string.h>
#include "hash-dictionary.h"

HashDictionary::HashDictionary()
{
	nElements = 0;
	for (int i = 0; i < MaxBuckets; i++) {
	  	_buckets[i] = NULL;
	}
}

int
HashDictionary::hash(KeyType key) {
  int h = 0;
  int len = strlen(key);
  for (int i = 0; i < len; i++) {
		h += (i + 1) * key[i];
  }
  return h % MaxBuckets;
}

// Add a record to the dictionary. Returns false if key already exists
bool
HashDictionary::addRecord( KeyType key, DataType data)
{
	int h = hash(key);
	HashNode *current = _buckets[h];
	while (current != NULL)
	{
		if (strcmp(current->_key, key) == 0)
		{
			current->_data = data;
			return false;
	    }

		current = current->_next;
	}

	HashNode *new_entry = new HashNode();
	new_entry->_next = _buckets[h];
	new_entry->_key = strdup(key);
	new_entry->_data = data;
	new_entry->_next = _buckets[h];
	_buckets[h] = new_entry;
	nElements++;

	return true;
}

// Find a key in the dictionary and return corresponding record or NULL
DataType
HashDictionary::findRecord( KeyType key)
{
	int h = hash(key);
	HashNode *current = _buckets[h];

	if (current == NULL)
	{
		return NULL;
	}

	while (current != NULL)
	{
		if (strcmp(current->_key, key) == 0)
		{
			// printf("%i\n", *((int*)data));
			return current;
		}

		current = current->_next;
	}
	return NULL;
}

// Removes one element from the table
bool
HashDictionary::removeElement(KeyType key)
{
	int h = hash(key);
	HashNode *current = _buckets[h];
	HashNode *prev = NULL;
	while (current != NULL)
	{
	    if (strcmp(current->_key, key) == 0)
	    {
		    if (prev != NULL) 
		    {
		    	prev->_next = current->_next;   
		    }
		    else
		    {
		    	_buckets[h] = current->_next;
		    }
	    	//entry contains key, substitute data
	      
	    	delete current;
	    	// current->_data = data;
	    	return true;
	    }

	    prev = current;
	    current = current->_next;
	}
	nElements--;
	return false;
}

// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType *
HashDictionary::keys(int * n)
{
	KeyType * a = (KeyType *) malloc(nElements * sizeof(KeyType));

	*n = nElements;
	int i = 0;
	for (int h = 0; h < MaxBuckets; h++) {
		HashNode * n = _buckets[h];
		while (n!=NULL) {
			a[i] = n->_key;
			i++;
			n = n->_next;
		}
	}
	*n = nElements;
	return a;
}