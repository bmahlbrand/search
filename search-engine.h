#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include "List.h"
#include "URLRecordList.h"
#include "minihttpd.h"
#include "dictionary.h"
#include "array-dictionary.h"
#include "avl-dictionary.h"
#include "bsearch-dictionary.h"
#include "hash-dictionary.h"
// Types of dictionaries used
enum DictionaryType {
	ArrayDictionaryType,
	HashDictionaryType,
	AVLDictionaryType,
	BinarySearchDictionaryType
};

// struct timespec {
// 	time_t   sec;         seconds 
// 	long     ns;       /* nanoseconds */
// };
// Stores a URL and the first 100 words
struct URLRecord {
  char * _url;          // URL of the document.
  char * _description;  // First 100 words of the document without tags
};

// Inherits from MiniHTTPD
class SearchEngine : public MiniHTTPD {
	double avg_time;
	int searches;
	Dictionary * _wordToURLList;
	URLRecord **_urlArray;
	int _maxSize;
	int _currentURL;
	DictionaryType dictionaryTypeEnum;
	// Add any other member variables you need
 public:


 	void buildURLs();
 	void resize();
 	void printURLs();
	// Constructor for SearchEngine
	SearchEngine( int port, DictionaryType dictionaryType);

	// Called when a request arrives
	void dispatch( FILE * out, const char * requestLine );
	URLRecordList *buildResultSet(char**words);
	DataType query(char *query);
	int wordCount(const char *urlString);
	bool parseFilesToDictionary();
};