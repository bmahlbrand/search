#include <stdlib.h>
#include <stdio.h>

PrefixTrie::PrefixTrie() {
	_root = new rootNode();
	_root->_set = calloc(26, sizeof(char));
}

PrefixTrie::~PrefixTrie() {
	
}

trieNode *
PrefixTrie::newNode(const char *key) {
	trieNode * node = new trieNode();

	if (!node)
		return node;

	Key *new_key = new Key();
	new_key->_str = key;
	node->_next = NULL;
	node->_key = new_key;
	node->_children = NULL;

	return node;
}

trieNode *
PrefixTrie::getRoot() {
	return _root;
}

bool 
PrefixTrie::add(const char *str) {

	return true;
}

bool 
PrefixTrie::remove(const char *str) {
	return true;
}

bool 
PrefixTrie::isMember(const char *str) {
	return true;
}
