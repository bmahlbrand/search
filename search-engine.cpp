
#include <string.h>
#include "search-engine.h"
#include <time.h>
#include <unistd.h>
#define WORDSIZE 256


FILE *
openFile(char *fn) {
    FILE *f = fopen(fn, "r");
    return f;
}

bool 
closeFile(FILE *f) {
	if (fclose(f) == 0)
		return true;
	return false;
}

char *
getLine(FILE *f) {
	char str[2196];
	memset(str, '\0', 2196);
	return fgets(str, 2196, f);
}

bool 
wordIndexing(Dictionary *dict, const char *line) {

	char *word = (char*)calloc(sizeof(char), WORDSIZE);
	char *key = NULL;
	URLRecordList *l = new URLRecordList();
	int i = 0;
	bool wordSet = false;

	while (*line != '\0') {
		if (wordSet == false && (*line == ' ')) {
			word[i] = '\0';
			wordSet = true;
			key = strdup(word);
			memset(word, '\0', WORDSIZE);
			i = 0;
		} else if (wordSet == false) {
			word[i] = *line;
			i++;
		} else if (wordSet == true && (*line == ' ' || *line == '\n')) {
			word[i] = '\0';
			if (word[0] != '\0') {
				int tmp = atoi(word);
				// fprintf(stderr, "%s %d\n", word, strlen(word));
				l->insertSorted(tmp);
				memset(word, '\0', WORDSIZE);
				i = 0;	
			}
			
		} else if (wordSet == true) {
			word[i] = *line;
			i++;
		}

		*line++;
	}

	// if (key != NULL && word[0] != '\0') {
	// 	fprintf(stderr, "%s", word);
	// 	l->insertSorted(atoi(word));
	// }

	if (!l->isEmpty()) {
		// fprintf(stderr, "%s of %s", key, "teh ListNode indexed");
		// l->print();
		// fprintf(stderr,"\n");
		dict->addRecord(key, l);
	}
	return true;
}

bool 
addWordsToDictionary(Dictionary *dict) {
	FILE *f = openFile("word.txt");
	char str[2196];
	if (!f) {
		return false;
	}
	// return fgets(str, 256, f);
	while (fgets(str, 2196, f) != NULL) {
		// fprintf(stderr, "%s\n", str);
		wordIndexing(dict, str);
		memset(str, '\0', 2196);
	}

	closeFile(f);
	return true;
}

void
SearchEngine::resize() {
	_maxSize *= 2;
	_urlArray = (URLRecord**)realloc(_urlArray, _maxSize * sizeof(URLRecord*));
}

void removeNL(char *str) {
    int len = strlen(str) -1;
    if (str[len] == '\n')
        str[len] = '\0';
}

void SearchEngine::buildURLs() {
	FILE *f = openFile("url.txt");
	char c = '\0';
	enum {URL, DESCRIPTION, SET} state;
	state = URL;
	char desc[501];
	char url[501];
	
	int urlCount = 0;
	int descCount = 0;
	memset(url, '\0', 501);
	memset(desc, '\0', 501);
	bool flag = false;

	while ((c = fgetc(f)) != EOF) {
		switch(state) {
			case URL: {
				// while (c != '\n') {
					// 
					if (flag == false) {
						if (c == ' ') {
							flag = true;
						}
						continue;
					}

					if (flag == true && urlCount < 500 && c != ' ') {
						url[urlCount] = c;
						urlCount++;
					} else if (flag == true) {
						urlCount = 0;
						flag = false;
						state = DESCRIPTION;
						break;
					}
				// }
				if (c == '\n'){
					state = DESCRIPTION;
					urlCount = 0;
					flag = false;
					continue;
					// fgetc(f);
					break;	
				}
				break;
			}
			case DESCRIPTION: {
				// while (c != '\n') {
					

				if (descCount < 500) {
					desc[descCount] = c;
					descCount++;
				} else {
					state = URL;
					descCount = 0;
					break;
				}
			// }
				if (c == '\n') {
					state = SET;
					descCount = 0;
					continue;
					// fgetc(f);
					break;						
				}
				break;
			}

			case SET: {
				URLRecord *record = new URLRecord();
				record->_url = strdup(url);
				record->_description = strdup(desc);
				_urlArray[_currentURL] = record;
				memset(url, '\0', 501);
				memset(desc, '\0', 501);
				_currentURL++;	
				if (_currentURL == _maxSize) {
					resize();
				}

				state = URL;
				break;
			}
		}
			
	}


	closeFile(f);
}

// void 
// SearchEngine::buildURLs() {

// 	FILE *f = openFile("url.txt");
// 	read(f);
// 	char desc[501];
// 	char url[501];
	
// 	int urlCount = 0;
// 	memset(url, '\0', 501);
// 	memset(desc, '\0', 501);
	
// 	// while (1) {
// 	// 	// fgets(url, 501, f);
// 	// 	bool flag = false;
// 	// 	char c = '\0';
// 	// 	if (urlCount != 0)
// 	// 		fgetc(f);
// 	// 	while ((c = fgetc(f)) != '\n') {
// 	// 		if (flag == false) {
// 	// 			if (c == ' ') flag = true;
// 	// 			continue;
// 	// 		}
// 	// 		if (urlCount < 500) {
// 	// 			url[urlCount] = c;
// 	// 			urlCount++;
// 	// 		} else {
// 	// 			urlCount = 0;
// 	// 			break;
// 	// 		}
// 	// 	}


// 	// 	fgets(desc, 501, f);
// 	// 	removeNL(desc);

// 	// 	if (url == NULL || desc == NULL || desc[0] == '\0' || url[0] == '\0')
// 	// 		break;
// 	// 	// fprintf(stderr, "%s\n%s\n", url, desc);
// 	// 	URLRecord *record = new URLRecord();
// 	// 	record->_url = strdup(url);
// 	// 	record->_description = strdup(desc);
// 	// 	_urlArray[_currentURL] = record;
// 	// 	memset(url, '\0', 501);
// 	// 	memset(desc, '\0', 501);
// 	// 	_currentURL++;
		
// 	// 	if (_currentURL == _maxSize) {
// 	// 		resize();
// 	// 	}
// 	// }

// 	closeFile(f);
// }

void
SearchEngine::printURLs() {
	fprintf(stderr, "%s", "...._urlArray....");

	for (int i = 0; _urlArray[i] != NULL; i++) {
		fprintf(stderr, "%s @ %i %s", _urlArray[i]->_url, i, _urlArray[i]->_description);
	}

	fprintf(stderr, "%s", ".................");
}

SearchEngine::SearchEngine( int port, DictionaryType dictionaryType): MiniHTTPD(port) {
	Dictionary * dict = NULL;
	_currentURL = 0;
	searches = 0;
	avg_time = 0;
	_maxSize = 2;

	_urlArray = (URLRecord**)calloc(_maxSize, sizeof(URLRecord*));
	// Create dictionary of the indicated type
	if (dictionaryType == ArrayDictionaryType) {
		dict = new ArrayDictionary();
		dictionaryTypeEnum = ArrayDictionaryType;
	} else if(dictionaryType == HashDictionaryType) {
		dict = new HashDictionary();
		dictionaryTypeEnum = HashDictionaryType;
	} else if (dictionaryType == AVLDictionaryType) {
	 	dict = new AVLDictionary();
	 	dictionaryTypeEnum = AVLDictionaryType;
	} else if (dictionaryType == BinarySearchDictionaryType) {
		dict = new BinarySearchDictionary();
		dictionaryTypeEnum = BinarySearchDictionaryType;
	}

	buildURLs();
	// Populate dictionary and 
	addWordsToDictionary(dict);
	
	_wordToURLList = dict;
	// printURLs();

	//sort it if necessary
	// if (dictionaryType == BinarySearchDictionaryType)
	// {
	// 	// dict->sort();
	// }

}

bool 
isIntersect(int val, URLRecordList *l) {
	if (l->lookup(val) == 0) {
		return true;
	} else {
		return false;
	}
}

URLRecordList *
getIntersect(URLRecordList *l1, URLRecordList *l2) {
	URLRecordList *intersection = new URLRecordList();
	URLRecordListNode *tmp = l1->_head;

	while (tmp != NULL) {
		int val = tmp->_value;

		if (l2->lookup(val) == 0) {
			intersection->insertSorted(val);
		}

		tmp = tmp->_next;
	}

	return intersection;
}

URLRecordList *
SearchEngine::buildResultSet(char **words) {
	URLRecordList *tmpList = NULL;
	URLRecordList *resultSet = new URLRecordList();
	int i = 0;
	
	if (words[1] == NULL) 
		return (URLRecordList*)_wordToURLList->findRecord(words[i]);
	// { //only 1 word
		
		// if (strcmp(words[0], "it") == 0)
		// 	tmpList->print();
		// return tmpList;
	// }

	while (words[i] != NULL) { //while still words to check
		tmpList = (URLRecordList*)_wordToURLList->findRecord(words[i]);	//get url list from key

		if (i == 0) {
			++i;
			resultSet = tmpList;
			continue;
		} else {

			if (tmpList != NULL) { //traverse url list and add intersection to resultset
			
			resultSet = getIntersect(resultSet, tmpList);

			// ListNode *tmp = tmpList->_head;
			// // tmpList->print();

			// while (tmp != NULL) {
			// 	int val = tmp->_value;
			// 	if (resultSet->lookup(val) == 0) { //if in prev resultSet AND this tmp list from the key, add to secondary
			// 		fprintf(stderr, "%d\n", val);
			// 		// secondaryResultSet->insertSorted(val);
			// 	} else {
			// 		resultSet->remove(val);
			// 	}
			// 	// fprintf(stderr, "%d\n", tmp->_value);
			// 	tmp = tmp->_next;
			// }

			// resultSet = secondaryResultSet; //set new results to the old
			// secondaryResultSet = new List(); //new result set
			}	
		}
		++i;
	}

	return resultSet;
}

DataType
SearchEngine::query(char *query) {
	// fprintf(stderr, "%s\n", "querying");
	// const char *f = "found";
	// const char *n = "nothing";
	DataType record = _wordToURLList->findRecord(query);
	if (record == NULL) {
		return NULL;
	}

	return record;
}
// bool
// SearchEngine::parseFilesToDictionary(Dictionary * dict) {

// }

int 
SearchEngine::wordCount(const char *urlString) {
	int count = 1;

	while (*urlString != '\0') {
		if (*urlString == '+') {
			count++;
		}
		
		urlString++;
	}

	return count;
}

void
SearchEngine::dispatch( FILE * fout, const char * documentRequested) {

	clock_t timetaken;
	timetaken = clock();
	searches++;
	if (strcmp(documentRequested, "/") == 0) {
		// Send initial form
		fprintf(fout, "<TITLE>CS251 Search</TITLE>\r\n");
		fprintf(fout, "<CENTER><H1><em>Boiler Search</em></H1>\n");
		fprintf(fout, "<H2>\n");
		fprintf(fout, "<FORM ACTION=\"search\">\n");
		fprintf(fout, "Search:\n");
		fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
		fprintf(fout, "</H2>\n");
		fprintf(fout, "</FORM></CENTER>\n");
		return;

	} else if (strcmp(documentRequested, "/index.html") == 0) {
		FILE *fp;
	    char line[100000];
	    size_t len = 0;
	    char read;
	    fp = fopen("index.html", "r");
	    // fprintf(fout, "did\n");
	    if (fp == NULL) {
	    	fprintf(stderr, "%s\n", "failed");
	    	return;
	    }
	    char c;
	    while(1) {
      		c = fgetc(fp);
      		if(feof(fp)) {
          		break;
      		}
      		fprintf(fout,"%c", c);
   		}
	    // if (fgets(line, 100000, fp) != NULL)
	    // {
	    //     // printf("Retrieved line of length %zu :\n", read);
	    //     fprintf(stderr,"%s", line);
	    // }
		   //  fprintf(stderr, "%s\n","bawls" );

	    
	    if (ferror(fp)) {

	        /* handle error */
	    }
	    // delete line;
	    fclose(fp);
	    return;
	} else if (strncmp(documentRequested, "/bootstrap", 10) == 0) {

		FILE *fp;

	    fp = fopen(documentRequested+1, "r");
	    // fprintf(fout, "did\n");
	    if (fp == NULL){
	    	fprintf(stderr, "%s\n", "failed");
	    	return;
	    }
	    
	    char c;
	    while(1) {
      		c = fgetc(fp);
      		if(feof(fp)) {
          		break ;
      		}
      		fprintf(fout,"%c", c);
   		}

	    if (ferror(fp)) {

	        /* handle error */
	    }
	    fclose(fp);
	    return;	
	} else if (strncmp(documentRequested, "/jumbotron.css", 14) == 0) {
		FILE *fp;
	    // char line[10000000];
	    // size_t len = 0;
	    // char read;
	    fp = fopen(documentRequested+1, "r");
	    // fprintf(fout, "did\n");
	    if (fp == NULL){
	    	fprintf(stderr, "%s\n", "failed");
	    	return;
	    }
	    char c;
	    while(1) {
      		c = fgetc(fp);
      		if(feof(fp)) {
          		break ;
      		}
      		fprintf(fout,"%c", c);
   		}
	    // if (fgets(line, 100000, fp) != NULL)
	    // {
	    //     // printf("Retrieved line of length %zu :\n", read);
	    //     fprintf(stderr,"%s", line);
	    // }
		   //  fprintf(stderr, "%s\n","bawls" );

	    
	    if (ferror(fp)) {

	        /* handle error */
	    }
	    // delete line;
	    fclose(fp);
	    return;	
	}
	// TODO: The words to search in "documentRequested" are in the form
	// /search?word=a+b+c
	//
	// You need to separate the words before search
	// Search the words in the dictionary and find the URLs that
	// are common for al the words. Then print the URLs and descriptions
	// in HTML. Make the output look nicer.
	else if (strncmp(documentRequested, "/search?word=", 13) == 0) {

		// fprintf(stderr, "%s\n", "did it");
		documentRequested = documentRequested + 13;

		int wc = wordCount(documentRequested);
		char *words[256] = {'\0'};
		
		int newWords = 0;
		char wordBuffer[256] = {'\0'};
		int bufferCount = 0;
		
		while (newWords < wc) {
			if (*documentRequested == '+' || *documentRequested == '\0') {
				wordBuffer[bufferCount] = '\0';
				bufferCount = 0;
				words[newWords] = strdup(wordBuffer);
				memset(wordBuffer, '\0', 256);
				newWords++;
				documentRequested++;
			} else {
				wordBuffer[bufferCount] = *documentRequested;
				bufferCount++;
				documentRequested++;
			}
		}

		fprintf(fout, "<TITLE>Search Results</TITLE>\r\n");
		fprintf(fout, "<H1> <Center><em>Boiler Search</em></H1>\n");
		
		fprintf(fout, "<H2> Search Results for");
		
		for (int i = 0; i < wc; i++) {
			fprintf(fout, " \"%s\"", words[i]);
		}
		
		fprintf(fout, "</center></H2>\n");
		
		URLRecordList * results = buildResultSet(words);
		URLRecordListNode *head = NULL;
		// if (results != NULL)
		// 	results->print();
		if (results != NULL) {
			head = results->_head;
			for (int i = 0; head != NULL; i++) {

				// DataType tmp = NULL;
				// tmp = query(words[i]);
				// _urlArray[tmp]
				// if (tmp == NULL)
					// tmp = "bawl";

				fprintf( fout, "<h3>%d. <a href = \"%s\">%s</a></h3>\n%s",
				head->_value, 
				_urlArray[head->_value]->_url, 
				_urlArray[head->_value]->_url, 
				_urlArray[head->_value]->_description);
			// 	fprintf( fout, "<blockquote>%s<p></blockquote>\n", description[i] );
				head = head->_next;
			}
		} else {
			fprintf(fout, "<h3>%s</h3>", "no results found");
		}
		
		// printf("end: %f\n", time_end.tv_nsec);
		// fprintf(stderr, "%f\n", ((double)timetaken)/CLOCKS_PER_SEC);
		// Add search form at the end
		fprintf(fout, "<HR><H2>\n");
		fprintf(fout, "<FORM ACTION=\"search\">\n");
		fprintf(fout, "Search:\n");
		fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
		fprintf(fout, "</H2>\n");
		fprintf(fout, "</FORM>\n");

		timetaken = clock() - timetaken;
		// clock_t final = ;
		// fprintf(fout, "<h3>");
		double final = ((double)timetaken)/CLOCKS_PER_SEC;
		if (searches != 1) {
			avg_time = (avg_time + final)/((double)2);
		} else {
			avg_time = (avg_time + final);
		}

		char *dictType = NULL;
		if (dictionaryTypeEnum == ArrayDictionaryType) {
			dictType = "Array Dictionary";
		} else if(dictionaryTypeEnum == HashDictionaryType) {
			dictType = "Hash Dictionary";
		} else if (dictionaryTypeEnum == AVLDictionaryType) {
		 	dictType = "AVL Tree Dictionary";
		} else if (dictionaryTypeEnum == BinarySearchDictionaryType) {
			dictType = "Binary Search Dictionary";
		}
		fprintf(fout, "results retrieved in %f seconds, running average is %f seconds", final, avg_time);
		// fprintf(fout, "<h3>\n");

	}
}

void
printUsage()
{
	const char * usage =
		"Usage: search-engine port (array | hash | avl | bsearch)\n"
		"  It starts a search engine at this port using the\n"
		"  data structure indicated. Port has to be larger than 1024.\n";

	fprintf(stderr, usage);
}

int main(int argc, char ** argv)
{
	if (argc < 3) {
		printUsage();
		return 1;
	}

	// Get port
	int port;
	sscanf( argv[1], "%d", &port);

	// Get DictionaryType
	const char * dictType = argv[2];
	DictionaryType dictionaryType;

	if (!strcmp(dictType, "array")) {
		dictionaryType = ArrayDictionaryType;
	} else if (!strcmp(dictType, "hash")) {
		dictionaryType = HashDictionaryType;
	} else if (!strcmp(dictType, "avl")) {
		dictionaryType = AVLDictionaryType;
	} else if (!strcmp(dictType, "bsearch")) {
		dictionaryType = BinarySearchDictionaryType;
	} else {
		printUsage();
		return 0;
	}
	
	SearchEngine httpd(port, dictionaryType);
	
	httpd.run();

	return 0;
}
