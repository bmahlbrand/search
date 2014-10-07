
all: search-engine test-dict test-avl

# Build Search engine
search-engine: search-engine.o minihttpd.o array-dictionary.o \
	hash-dictionary.o  bsearch-dictionary.o heap.o avl-dictionary.o avl-dictionary2.o
	g++ -g -o search-engine search-engine.o minihttpd.o \
		  array-dictionary.o hash-dictionary.o  \
		  bsearch-dictionary.o heap.o avl-dictionary.o avl-dictionary2.o URLRecordList.cpp -lnsl -Wno-deprecated -Wno-write-strings -m32 -lrt

test-dict: test-dict.cpp array-dictionary.o hash-dictionary.o bsearch-dictionary.o heap.o
	g++ -g -o test-dict test-dict.cpp array-dictionary.o hash-dictionary.o bsearch-dictionary.o avl-dictionary.cpp avl-dictionary2.cpp heap.o -Wno-write-strings -m32

test-avl: test-avl.cpp avl-dictionary.o avl-dictionary2.o
	g++ -g -o test-avl test-avl.cpp avl-dictionary.o avl-dictionary2.o  -Wno-deprecated -Wno-write-strings -m32

search-engine.o: search-engine.h search-engine.cpp
	g++ -g -c search-engine.cpp -m32  -Wno-deprecated -Wno-write-strings

test-arraydict: test-dict.cpp array-dictionary.o
	g++ -g -o test-dict test-dict.cpp array-dictionary.cpp bsearch-dictionary.cpp  -Wno-deprecated -Wno-write-strings -m32

# HTTP Server
minihttpd.o: minihttpd.cpp minihttpd.h
	g++ -g -c minihttpd.cpp -m32  -Wno-deprecated

# Build dictionaries
array-dictionary.o: array-dictionary.h array-dictionary.cpp
	g++ -g -c array-dictionary.cpp -m32  -Wno-deprecated

hash-dictionary.o: hash-dictionary.h hash-dictionary.cpp
	g++ -g -c hash-dictionary.cpp -m32  -Wno-deprecated -Wno-write-strings

heap.o: heap.h heap.cpp
	g++ -g -c heap.cpp -m32 

bsearch-dictionary.o: bsearch-dictionary.h bsearch-dictionary.cpp 
	g++ -g -c bsearch-dictionary.cpp -m32  -Wno-deprecated -Wno-write-strings

avl-dictionary.o: avl-dictionary.h avl-dictionary.cpp
	g++ -g -c avl-dictionary.cpp -m32  -Wno-deprecated -Wno-write-strings

avl-dictionary2.o: avl-dictionary.h avl-dictionary2.cpp
	g++ -g -c avl-dictionary2.cpp -m32  -Wno-deprecated -Wno-write-strings



# Used only for testing minihttpd independently
minihttpd: minihttpd.h minihttpd.cpp
	g++ -g -o minihttpd -DSTANDALONE minihttpd.cpp -lnsl -m32

clean:
	rm -f *.o minihttpd search-engine test-avl test-dict core
