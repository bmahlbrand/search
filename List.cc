//
// Implement the List class
//

#include <stdio.h>
#include "List.h"


//
// List constructor
//
List::List() {
    _head = NULL;
}

//
// Inserts a new element with value "val" in
// ascending order.
//
void
List::insertSorted(int val)
{
    // fprintf(stderr, "%i\n", val);
    ListNode *node = _head;
    ListNode *tmp = newNode(val);
    ListNode *prev = _head;

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

ListNode *
List::newNode(int val) {
    ListNode *newNode = new ListNode;
    newNode->_value = val;
    newNode->_next = NULL;
    return newNode;
}

int 
List::compare(int a, int b) {
  return a - b;
}

void
List::init(int val) {
    _head = newNode(val);
    _head->_value = val;
    _head->_next = NULL;
}

bool
List::isEmpty() {
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
List::append(int val) {
    ListNode *tmp = _head;
    // List *node = new List;

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
List::prepend(int val) {
    ListNode *node = newNode(val);
    
    node->_next = _head;
    _head = node;
}

// Removes an element with value "val" from List
// Returns 0 if succeeds or -1 if it fails
int 
List::remove(int val) {   
    ListNode *node = _head;
    ListNode *prev = node;
    
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
List::print() {
    ListNode *node = _head;
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
List::lookup(int val) {
    ListNode *list = _head;

    while(list != NULL) {
        if (val == list->_value) return 0;
        list = list->_next;
    }

    return -1;
}

//
// List destructor: delete all list elements, if any.
//
List::~List() {
    ListNode *node = _head;
    ListNode *tmp = NULL;
    while (node != NULL) {
        tmp = node->_next;
        delete node; 
        node = tmp;
    }
}