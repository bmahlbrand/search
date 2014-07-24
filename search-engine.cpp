
#include <string.h>
#include "search-engine.h"

SearchEngine::SearchEngine( int port, DictionaryType dictionaryType): MiniHTTPD(port)
{
	Dictionary * dict = NULL;
	
	// Create dictionary of the indicated type
	if (dictionaryType == ArrayDictionaryType) 
	{
		dict = new ArrayDictionary();
	}
	else if(dictionaryType == HashDictionaryType)  
	{
		dict = new HashDictionary();
	}
	else if (dictionaryType == AVLDictionaryType) 
	{
	 	// dict = new AVLDictionary();
	}
	else if (dictionaryType == BinarySearchDictionaryType) 
	{
		dict = new BinarySearchDictionary();
	}

	// Populate dictionary and sort it if necessary
	if (dictionaryType == BinarySearchDictionaryType)
	{

	}

}

int 
SearchEngine::wordCount(const char *urlString)
{
	int count = 1;

	while (*urlString != '\0')
	{
		
		if (*urlString == '+') 
		{
			count++;
		}

		urlString++;
	}

	return count;
}

void
SearchEngine::dispatch( FILE * fout, const char * documentRequested)
{
	if (strcmp(documentRequested, "/") == 0) 
	{
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
	} 
	else if (strcmp(documentRequested, "/index.html") == 0)
	{
		FILE *fp;
	    char line[100000];
	    size_t len = 0;
	    char read;
	    fp = fopen("index.html", "r");
	    // fprintf(fout, "did\n");
	    if (fp == NULL){
	    	fprintf(stderr, "%s\n", "failed");
	    	return;
	    }
	    char c;
	    while(1)
	    {
      		c = fgetc(fp);
      		if( feof(fp) )
      		{
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
	else if (strncmp(documentRequested, "/bootstrap", 10) == 0)
	{
		FILE *fp;

	    fp = fopen(documentRequested+1, "r");
	    // fprintf(fout, "did\n");
	    if (fp == NULL){
	    	fprintf(stderr, "%s\n", "failed");
	    	return;
	    }
	    
	    char c;
	    while(1)
	    {
      		c = fgetc(fp);
      		if( feof(fp) )
      		{
          		break ;
      		}
      		fprintf(fout,"%c", c);
   		}

	    if (ferror(fp)) {

	        /* handle error */
	    }
	    fclose(fp);
	    return;	
	}
	else if (strncmp(documentRequested, "/jumbotron.css", 14) == 0)
	{
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
	    while(1)
	    {
      		c = fgetc(fp);
      		if( feof(fp) )
      		{
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
	else if (strncmp(documentRequested, "/search?word=", 13) == 0)
	{
		fprintf(stderr, "%s\n", "did it");
		documentRequested = documentRequested + 13;
		// while (*documentRequested != '=')
		// {
		// 	documentRequested++;
		// }

		int wc = wordCount(documentRequested);
		fprintf(stderr, "%i\n", wc);
		char *words[256] = {NULL};
		// for (int i = 0; i < wc; i++)
		// {
		// 	words[i] = NULL;
		// }
		
		int newWords = 0;
		char wordBuffer[256] = {'\0'};
		int bufferCount = 0;
		
		while (newWords < wc)
		{
			if (*documentRequested == '+' || *documentRequested == '\0')
			{
				wordBuffer[bufferCount] = '\0';
				bufferCount = 0;
				words[newWords] = strdup(wordBuffer);
				memset(wordBuffer, '\0', 256);
				newWords++;
				documentRequested++;
			} 
			else 
			{
				wordBuffer[bufferCount] = *documentRequested;
				bufferCount++;
				documentRequested++;
			}
		}

		for (int i = 0; i < newWords; i++)
		{
			fprintf(stderr, "%s\n", words[i]);
		}
	}



	// Here the URLs printed are hardwired
	
	const int nurls=2;

	const char * words = "data structures";

	char * urls[] = {
		"http://www.cs.purdue.edu",
		"http://www.cs.purdue.edu/homes/cs251"
	};
	
	char * description[] = {
		"Computer Science Department. Purdue University.",
		"CS251 Data Structures"
	};

	fprintf( stderr, "Search for words: \"%s\"\n", words);

	fprintf( fout, "<TITLE>Search Results</TITLE>\r\n");
	fprintf( fout, "<H1> <Center><em>Boiler Search</em></H1>\n");
	fprintf( fout, "<H2> Search Results for \"%s\"</center></H2>\n", words );

	for ( int i = 0; i < nurls; i++ ) {
		fprintf( fout, "<h3>%d. <a href=\"%s\">%s</a><h3>\n", i+1, urls[i], urls[i] );
		fprintf( fout, "<blockquote>%s<p></blockquote>\n", description[i] );
	}

	// Add search form at the end
	fprintf(fout, "<HR><H2>\n");
	fprintf(fout, "<FORM ACTION=\"search\">\n");
	fprintf(fout, "Search:\n");
	fprintf(fout, "<INPUT TYPE=\"text\" NAME=\"word\" MAXLENGTH=\"80\"><P>\n");
	fprintf(fout, "</H2>\n");
	fprintf(fout, "</FORM>\n");
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
	}
	else if (!strcmp(dictType, "hash")) {
		dictionaryType = HashDictionaryType;
	}
	else if (!strcmp(dictType, "avl")) {
		dictionaryType = AVLDictionaryType;
	}
	else if (!strcmp(dictType, "bsearch")) {
		dictionaryType = BinarySearchDictionaryType;
	}
	else {
		printUsage();
		return 0;
	}
	
	SearchEngine httpd(port, dictionaryType);
	
	httpd.run();

	return 0;
}
