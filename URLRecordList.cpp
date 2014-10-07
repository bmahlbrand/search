//
// Implement the List class
//

#include <stdio.h>
#include "URLRecordList.h"


//
// List constructor
//
URLRecordList::URLRecordList() {
    _head = NULL;
}

//
// Inserts a new element with value "val" in
// ascending order.
//
void
URLRecordList::insertSorted(int val)
{
    // fprintf(stderr, "%i\n", val);
    URLRecordListNode *node = _head;
    URLRecordListNode *tmp = newNode(val);
    URLRecordListNode *prev = _head;

    if (_head == NULL) {
        init(val);
        delete tmp;
        return;
    }

    if (val <= _head->_value) {
        prepend(val);
        delete tmp;
        return;
    }
    
    while (node->_next != NULL) {
        if (compare(tmp->_value, node->_value) < 0) {
            // tmp = newNode(val);
            prev->_next = tmp;
            tmp->_next = node;
            return;
        }
        prev = node;
        node = node->_next;
    }

    append(val);
    delete tmp;
}

URLRecordListNode *
URLRecordList::newNode(int val) {
    URLRecordListNode *newNode = new URLRecordListNode;
    newNode->_value = val;
    newNode->_next = NULL;
    return newNode;
}

int 
URLRecordList::compare(int a, int b) {
  return a - b;
}

void
URLRecordList::init(int val) {
    _head = newNode(val);
    _head->_value = val;
    _head->_next = NULL;
}

bool
URLRecordList::isEmpty() {
    if (_head == NULL) {
        return true;
    }
    return false;
}
//
// Inserts a new element with value "val" at
// the end of the list.
//
void
URLRecordList::append(int val) {
    URLRecordListNode *tmp = _head;
    // URLRecordListNode *node = new URLRecordListNode;

    while (tmp->_next != NULL) {
        tmp = tmp->_next;   
    }

    tmp->_next = newNode(val);
    // tmp->_value = val;
}

//
// Inserts a new element with value "val" at
// the beginning of the list.
//
void
URLRecordList::prepend(int val) {
    URLRecordListNode *node = newNode(val);
    
    node->_next = _head;
    _head = node;
}

// Removes an element with value "val" from List
// Returns 0 if succeeds or -1 if it fails
int 
URLRecordList::remove(int val) {   
    URLRecordListNode *node = _head;
    URLRecordListNode *prev = node;
    
    while (node != NULL) 
    {
        if (node->_value == val) 
        {
            prev->_next = node->_next;
            delete node;
            return 0;
        }

        prev = node;
        node = node->_next;
    }
    return -1;
}

// Prints The elements in the list. 
void
URLRecordList::print() {
    URLRecordListNode *node = _head;
    while (node != NULL)
    {
        fprintf(stderr, " %i,", node->_value);
        node = node->_next;
    }   

    fprintf(stderr, "\n");
}

//
// Returns 0 if "value" is in the list or -1 otherwise.
//
int
URLRecordList::lookup(int val) {
    URLRecordListNode *list = _head;

    while(list != NULL) {
        if (val == list->_value) return 0;
        list = list->_next;
    }

    return -1;
}

//
// List destructor: delete all list elements, if any.
//
URLRecordList::~URLRecordList() {
    URLRecordListNode *node = _head;
    URLRecordListNode *tmp = NULL;
    while (node != NULL) {
        tmp = node->_next;
        delete node; 
        node = tmp;
    }
}