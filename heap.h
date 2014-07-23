//heap.h
#include "array-dictionary.h"

class Heap {
	int _maxSize;
	ArrayDictionaryNode *_heap;
	int _last;

public:
	Heap(int maxSize);
	
	inline int left(int p) 
	{
    	return 2*p+1;
    }

    inline int right(int p) 
    {
    	return 2*p+2;
    }

    inline int hparent(int c) 
    {
    	return (c-1)/2;
    }

	bool insert(ArrayDictionaryNode node);
	ArrayDictionaryNode removeMin();

	~Heap();
};

void heapSort(ArrayDictionaryNode *a, int n);