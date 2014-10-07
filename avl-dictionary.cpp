
// Implementation of a dictionary using an AVL tree
// AVL Trees are balanced binary trees 

#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>

#include "avl-dictionary.h"

bool debug = false;

// Constructor
AVLDictionary::AVLDictionary() {
	root = NULL;
	nElements = 0;
}

// Add a record to the dictionary. Returns false if key already exists
bool
AVLDictionary::addRecord( KeyType key, DataType data) {
	if ( debug) {
		printf("------------------------------------\n");
		printf("addRecord(\"%s\",%d)\n",  key, (int)data);
		printf("---------- Before -----------------\n");
		printNode("", root, 0);
	}

	//find node with that key, if any
	//overwrite data if found
	AVLNode *current = root;
	AVLNode *prev = NULL;

	while (current != NULL)	{
		prev = current;
		if (strcmp(key, current->key) == 0) {
		// key == current->key) //
			//found, overwrite data
			current->data = data;
			return false;
		} else if (strcmp(key, current->key) > 0) {
		// (key - current->key > 0)
		//key is in right subtree
			current = current->right;
		} else {	//key is in left subtree
			current = current->left;
		}
	} //did not find key in tree, and prev points to parent node where new node will be inserted
	
	AVLNode *newNode = new AVLNode();
	newNode->key = strdup(key); //use strdup if key is const char*
	newNode->data = data; 
	newNode->height = 1;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = prev;

	if (prev == NULL) {	//tree is empty, assign to root
		root = newNode;
		nElements++;
		return true;
	}

	if (strcmp(key, prev->key) > 0) {	//attach to right
		prev->right = newNode;
	} else {
		prev->left = newNode;
	}
	
	//adjust heights of above subtrees, path from inserted node to root
	AVLNode *m = newNode->parent;

	while (m != NULL) {//go up
		//get maxHeight of left and right children
		int maxHeight = 0;

		if (m->left != NULL) {
			maxHeight = m->left->height;
		}

		if (m->right != NULL && maxHeight < m->right->height) {
			maxHeight = m->right->height;
		}
		//update height of m
		m->height = 1 + maxHeight;
		m = m->parent;
	}

	//at this point, the newnode is in place and height has been adjusted for correctness, 
	//however, may not fulfill AVL tree conditions, because of potential height differences 
	//in subtrees (ie difference in height of left and right > 1)
	//restructure beginning at inserted node

	//Find node to insert into 
	//Node does not exist. Create it.
	//Height might not be valid anymore.
	//We need to restructure .

	if ( debug) {
		printf("---------- Before Restructure -----------------\n");
		printNode("", root, 0);
	}
	
	// Call restructure
	restructure(newNode);

	if (debug) {
		checkRecursive(root);
		
		printf("---------- After Restructure -----------------\n");
		printNode("", root, 0);
	}

	nElements++;
	return true;
}

void
AVLDictionary::restructure(AVLNode * node) {
	//Balance starting at n 
	//Go upwards until root is found

	/* go up and look for subtree imbalances, starting at node
	go up from n, find "z" that is the first parent where the
	difference in height of the children, is larger than 1 */
	AVLNode *z = node;

	while (z != NULL) {//while not root
		//find parent of unbalanced tree
		int hleft = 0; //height of left child
		
		if (z->left != NULL) {
			hleft = z->left->height;
		}

		int hright = 0; //height of right child

		if (z->right != NULL) {
			hright = z->right->height;
		}

		int hdiff = hleft - hright;

		if (hdiff < 0) { //absolute value
			hdiff = -hdiff;
		}

		//recompute height of z just in case it was modified w/a restructure previously

		if (hleft > hright)	{
			z->height = 1 + hleft;
		} else {
			z->height = 1 + hright;
		}

		//test if z is the parent of an unbalanced substree
		if (hdiff <= 1)	{
			//z is parent of balanced subtree...skip it, by going up
			z = z->parent;
			continue;
		}

		//at this point, z is parent of unbalanced subtree
		//find y: the child of z with largest height

		AVLNode *y = NULL;
		int maxHeight = 0;

		if (z->left != NULL) {
			y = z->left;
			maxHeight = y->height;
		}

		if (z->right != NULL && z->right->height > maxHeight) {
			y = z->right;
			maxHeight = y->height;
		}

		assert(y != NULL); //debugging, if algorithm correct, this will never be false

		//find x: x is the child of y with largest height

		AVLNode *x = NULL;

		maxHeight = 0;

		if (y->left != NULL) {
			x = y->left;
			maxHeight = x->height;
		}

		if (y->right != NULL && y->right->height > maxHeight) {
			x = y->right;
			maxHeight = x->height;
		}

		assert(x != NULL);

		/*
		4 cases:
		-----1
		smallest: a,z
		largest: c,x
		mid: b,y
		-----2
		smallest: a,z
		largest: b,x
		mid: c,y
		-----3
		smallest: a,x
		largest: c,z
		mid: b,y
		-----4
		smallest: a, y
		largest: c,z
		mid: b,x
		*/

		AVLNode *t0, *t1, *t2, *t3;
		AVLNode *a, *b, *c;

		if (z->right == y) {//case 1 or 2
			if (y->right == x) {//case 1
				a = z;
				b = y;
				c = x;
				t0 = a->left;
				t1 = b->left;
				t2 = c->left;
				t3 = c->right;
			} else {//case 2
				a = z;
				b = x;
				c = y;
				t0 = a->left;
				t1 = b->left;
				t2 = b->right;
				t3 = c->right;
			}
		} else { //case 3 or case 4
			if (y->left == x) { //case 3
				a = x;
				b = y;
				c = z;
				t0 = a->left;
				t1 = a->right;
				t2 = b->right;
				t3 = c->right;
			} else {//case 4
				a = y;
				b = x;
				c = z;
				t0 = a->left;
				t1 = b->left;
				t2 = b->right;
				t3 = c->right;
			}
		}
			
		AVLNode *p = z->parent;
		if (p == NULL) {
			//z is parent, then set b to root
			root = b;
		} else {	
			//z was not at root, attach b either in the left or right of p depending where z was
			if (p->left == z) {
				//z was at the left, so attach b at left
				p->left = b;
			} else {
				p->right = b;
			}
		}

		//make a,b,c subtree

		b->parent = p;
		b->left = a;
		b->right = c;
		
		a->parent = b;
		a->left = t0;
		a->right = t1;
		
		c->parent = b;
		c->left = t2;
		c->right = t3;

		//connect to parents of t0,t1,t2,t3
		if (t0 != NULL)	{
			t0->parent = a;
		}
		
		if (t1 != NULL)	{
			t1->parent = a;
		}
		
		if (t2 != NULL)	{
			t2->parent = c;
		}

		if (t3 != NULL) {
			t3->parent = c;
		}

		//now fix heights of a,b,c

		maxHeight = 0;

		if (a->left != NULL) {
			maxHeight = a->left->height;
		}

		if (a->right != NULL && maxHeight < a->right->height) {
			maxHeight = a->right->height;
		}

		a->height = maxHeight + 1;

		maxHeight = 0;

		if (c->left != NULL) {
			maxHeight = c->left->height;
		}

		if (c->right != NULL && maxHeight < c->right->height) {//in class shows maxh> c->right->height
			maxHeight = c->right->height;
		}

		c->height = maxHeight + 1;

		maxHeight = 0;

		if (b->left != NULL) {
			maxHeight = b->left->height;
		}

		if (b->right != NULL && maxHeight < b->right->height) {
			maxHeight = b->right->height;
		}

		b->height = maxHeight + 1;

		//at this point a,b,c subtree is constructed and attached to parent, a,b,c have correct height
		//proceed constructing up to the tree
		z = p;
	}//while
} //you will need to call restructure in insert and remove

AVLNode *
AVLDictionary::findNode(KeyType key) {
	AVLNode *current = root;
	
	while (current != NULL)	{
		if (strcmp(current->key, key) == 0) {
			return current;
		} else if (strcmp(current->key, key) > 0)	{
			current = current->left;
		} else {
			current = current->right;
		}
	}

	return NULL;
}
// Find a key in the dictionary and return corresponding record or NULL
DataType
AVLDictionary::findRecord( KeyType key) {
	AVLNode *current = root;
	// AVLNode *current = (AVLNode*)findNode(key);
	
	// if (current == NULL)
	// 	return NULL;
	// else
	while (current != NULL)	{
		if (strcmp(current->key, key) == 0) {
			return current->data;
		} else if (strcmp(current->key, key) > 0) {
			current = current->left;
		} else {
			current = current->right;
		}
	}

	return NULL;
}

// int getDepth(AVLNode *t) {
// 	int depth= 0;
// 	if (t == NULL) {
// 		return depth-1;
// 	} else {
// 		if(getDepth(t->left) > getDepth(t->right)) {
// 			depth = getDepth(t->left);
// 		} else {
// 			depth = getDepth(t->right);
// 		}
// 		return depth + 1;
// 	}
// }
// Let node X be the node with the value we need to delete, and let node Y be a node in the tree we need to find to take node X's place, and let node Z be the actual node we take out of the tree.

// Steps to consider when deleting a node in an AVL tree are the following:

// If node X is a leaf or has only one child, skip to step 5. (node Z will be node X)
// Otherwise, determine node Y by finding the largest node in node X's left sub tree (in-order predecessor) or the smallest in its right sub tree (in-order successor).
// Replace node X with node Y (remember, tree structure doesn't change here, only the values). In this step, node X is essentially deleted when its internal values were overwritten with node Y's.
// Choose node Z to be the old node Y.
// Attach node Z's subtree to its parent (if it has a subtree). If node Z's parent is null, update root. (node Z is currently root)
// Delete node Z.
// Retrace the path back up the tree (starting with node Z's parent) to the root, adjusting the balance factors as needed.
// As with all binary trees, a node's in-order successor is the left-most child of its right subtree, and a node's in-order predecessor is the right-most child of its left subtree. 
// In either case, this node will have zero or one children. Delete it according to one of the two simpler cases above.
// Removes one element from the dictionary
bool
AVLDictionary::removeElement(KeyType key)
{
	if (debug) {
		printf("------------------------------------\n");
		printf("removeElement(\"%s\")\n",  key);
		printf("---------- Before -----------------\n");
		printNode("", root, 0);
	}

	//need to subsitute root with node that comes immediately before or after
	// AVLNode *current = (AVLNode*)findNode(key);
	AVLNode *current = root;
	while (current != NULL)	{
		if (strcmp(current->key, key) == 0) {
			break;
		} else if (strcmp(current->key, key) > 0) {
			current = current->left;
		} else {
			current = current->right;
		}
	}
	
	if (current == NULL) {
		return false;
	}

	AVLNode *parent = NULL;
	if (current != root) {
		parent = current->parent;
	} else { //is root
		current->left = current->right->parent;
	}
	// if(current == parent->right) {
 //        parent->right = current->right;
	// } else {
 //        parent->left = current->right;
	// }

	if (current->left == NULL && current->right == NULL) { //no children, just delete?
		if (current == parent->right) {
			parent->right = NULL;
		} else {
			parent->left = NULL;
		}
		
		delete current;
		restructure(parent);
	} else if (current->left == NULL) {
		if (current == parent->right) {
			parent->right = NULL;
			parent->right = current->right;
			parent->right->height = current->right->height;
			delete current;
			current = NULL;
			restructure(parent);
		} else {
			parent->left = NULL;
			parent->left = current->right;
			parent->left->height = current->right->height;
			restructure(parent);
			delete current;
			current = NULL;
		}
    	// restructure(current->right);
	} else if (current->right == NULL) {
		if (current == parent->right) {
			parent->right = NULL;
			parent->right = current->left;
			parent->right->height = current->left->height;
			// current = current->right;
			restructure(parent);
			delete current;
			current = NULL;
			
		} else {
			parent->left = NULL;
			parent->left = current->left;
			parent->left->height = current->left->height;
			restructure(parent);
			delete current;
			current = NULL;
			
			// current = current->right;
		}
		// delete current;
		// restructure(parent);
		// parent->left = current->right;
		// current = current->right;
		
		// restructure(current);
		// restructure(current->left);
	} else { //is internal
		AVLNode *preorder = current->left;

		while (preorder->right != NULL) {
			preorder = preorder->right;
		}

		current->key = preorder->key;
		current->data = preorder->data;
		
		current = preorder;

		if (current->left == NULL) {
			if (current->parent->right == current) {
				current->parent->right = current->right;
			} else {
				current->parent->left = current->right;
			}
		} else {
			if (current->parent->right == current) {
				current->parent->right = current->left;
			} else {
				current->parent->left = current->left;
			}
		}

		restructure(current->parent);
		delete current;
	}
	
	if (debug) {
		printf("---------- After -----------------\n");
		printNode("", root, 0);

		checkRecursive(root);
	}
	
	return true;
}

// Returns all the elements in the table as an array of strings.
// *n is the size of the table and it is returned by reference
KeyType *
AVLDictionary::keys(int * n)
{
	KeyType * a = (KeyType *) malloc(nElements * sizeof(KeyType));
	*n = 0;
	addKeysRecursive(root, a, n);

	return a;
}

// Add keys recursively
void
AVLDictionary::addKeysRecursive(AVLNode * node, KeyType * a, int * n) {
	if (node==NULL) {
		return;
	}
	
	
	a[*n] = node->key;
	(*n)++;
	addKeysRecursive(node->left, a, n);
	addKeysRecursive(node->right, a, n);
}