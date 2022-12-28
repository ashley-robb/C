// // LAB4_AVL.c – Lab 04 – Ashley, Robb
//
// Code for ELEC278 Lab 4.  Some code has already been implemented.
// You will develop your own code - look for the comments that say:
// "Your code goes here";
//


/* --README--------------------------------------------------------------------
Source code used for teaching purposes in course:
ELEC278, Queen's University, Kingston, Fall semester 2022.
This code is provided without warranty of any kind. It is the responsibility
of the user to determine the correctness and the usefulness of this code for
any purpose.

All rights reserved. This code is intended for students registered in the
course and the semester listed above.

See LICENCE.MD for restrictions on the use of this code.
---------------------------------------------------------------------------- */


#include <stdio.h>
#include "/Users/ashleyrobb/CLionProjects/LAB04/bintree.h"
#include "/Users/ashleyrobb/CLionProjects/LAB04/bintree.c"

#include "/Users/ashleyrobb/CLionProjects/LAB04/avl.h"
/*
void printTree(Node* root)
// Print representation of tree. We make an assumption, because tree nodes
// actually have pointer to data, not actual data.  So assume that it is a
// pointer to an integer.
{
	printf("{");		// Tree starts with an opening curly bracket
	// then value of root node
	printf("(%d,%d)", root->key, *(int*) root->value);
						// need to cast void pointer actual data type
	printf(",");		// children come next

	// left child. If NULL it will just print two empty braces,
	// otherwise it prints whole left tree.
	if (root->leftChild) {
		printTree(root->leftChild);
	} else
		printf("{}");
	// separate left child from right child
	printf(",");
	// right child. If NULL it will just print two empty braces,
	// otherwise it prints whole right tree.
	if (root->rightChild) {
		printTree(root->rightChild);
	} else
		printf("{}");
	printf("}");	// Tree ends with closing curly bracket
}//printTree()

//=============================================================================
// ALTERNATE IMPLEMENTATION OF PRINTTREE - FOR YOUR REVIEW.
//    YOU MAY IGNORE THIS.

void printTree2(Node* root)
// Print representation of tree. We make an assumption, because tree nodes
// actually have pointer to data, not actual data.  So assume that it is a
// pointer to an integer.
{
	if (root == NULL)	{
		// printing an empty tree
		printf("{}");
	} else	{
		// printing non-empty tree
		printf("{");		// Tree starts with an opening curly bracket
		// then value of root node
		printf("(%ld,%d)", (long) root->key, *(int*) root->value);
							// need to cast void pointer actual data type
		printf(",");		// children come next

		// left child.
		printTree(root->leftChild);
		// separate left child from right child
		printf(",");
		// right child.
		printTree(root->rightChild);
		printf("}");	// Tree ends with closing curly bracket
		}
}//printTree2()
//=============================================================================
*/
int maxint(int a, int b)	{ return (a>=b) ? a : b; }


void insertAVL (Key k, void *v, Tree *t)
// Add new data item to tree.  Use two data components - key and actual data -
// to create new node and insert node in appropriate place.
{
	// Check for mistakes, including verification of tree type
	if ((t == NULL) || (t->tt != AVL))	return;
	//printf("Insert %d into AVL\n", k);
	// Check if tree empty - if so, insert first node
	if (t->root == NULL) {
		Node *n = initNode(k, v);
		n->height = 0;
		t->root = n;
	} else	{
		t->root = insertNodeAVL(k, v, t->root);
		}
	return;
}//insert()


Node* rotateRight(Node* root)
// Rotate to right.  Returns new root pointer.
{
	printf("Rotate Right\n");
//---Your code goes here
//---<SNIP>---
    if (root != NULL){
        Node* l = root->leftChild;
        Node* L_R = l->rightChild;
        root->leftChild = L_R;
        l->rightChild = root;
        root->height = calcHeight(root);
        l->height = calcHeight(l);
        return l;
    }

//---</SNIP>---
	return root;
}//rotateRight()


Node* rotateLeft(Node* root)
// Rotate to left.  Returns new root pointer.
{
	printf("Rotate Left\n");
//---Your code goes here
//---<SNIP>---

    if (root != NULL)	{
        Node* r = root->rightChild;
        Node* R_L = r->leftChild;
        root->rightChild = R_L;
        r->leftChild = root;

        root->height = calcHeight(root);
        r->height = calcHeight(r);
        return r;
    }
//---</SNIP>---
	return root;
}//rotateLeft()


int getBalanceFactor(Node* root)
// Get balance factor - difference between left height and right height
{
	int	hr = -1, hl = -1;		// Default values
//---Your code goes here
//---<SNIP>---
    hl = (root->leftChild) ? root->leftChild->height : -1;
    hr = (root->rightChild) ? root->rightChild->height : -1;
//---</SNIP>---
	return hl - hr;
}//getBalanceFactor()


int calcHeight(Node* root)
// Calculate height of this node by adding 1 to maximum of left, right
// child height.
{
	int hrl = -1, hll = -1;		// Default values

//---Your code goes here
//---Code has to compute hrl - height of right subtree - and compute
//---hll - height of left subtree. In last line, 1 is added to the maximum
//---of hll and hrl and that value is returned.
//---<SNIP>---
    if (root->leftChild  != NULL) {
        hll = root->leftChild->height;
    }
    if (root->rightChild != NULL){
        hrl = root->rightChild->height;
    }
//---</SNIP>---
	return maxint(hrl, hll) + 1;
}//calcHeight();


Node* rebalance(Node* root)
// Check balance factor to see if balancing required (bf > 1 or bf < -1).
// If balancing required, perform necessary rotations.
{
	int bf = getBalanceFactor(root);
//---Your code goes here
//---<SNIP>---

    if (bf > 1) { // left
        int bfl = getBalanceFactor(root->leftChild);
        if (bfl >= 0) { //left
            printf("Node %d is unbalanced.", root->key);
            printf("Left of Left");
            return rotateRight(root);
        } else if (bfl < 0) { // right
            printf("Node %d is unbalanced.", root->key);
            printf("Right of Left");
            root->leftChild = rotateLeft(root->leftChild);
            return rotateRight(root);
        }
    } else if (bf < -1) { //right
        int bfr = getBalanceFactor(root->rightChild);
        if (bfr >= 0) { //left
            printf("Node %d is unbalanced.", root->key);
            printf("Left of Right");
            root->rightChild = rotateRight(root->rightChild);
            return rotateLeft(root);
        } else if (bfr < 0) { // right
            printf("Node %d is unbalanced", root->key);
            printf("Right of Right");
            return rotateLeft(root);
        }
    }
//---</SNIP>---
	return root;
}//rebalance()

// I added this function to match output formatting
void insert_print(int l){
    printf("Inserting %d\n", l);
}

void delete_print(int l){
    printf("Deleting %d\n", l);
}

Node* insertNodeAVL(Key k, void *v, Node *root)
// Build new node and insert into (non-empty) tree. Check if insertion has
// created imbalance and rebalance if necessary.
{
	if (root==NULL) {
		Node *n = initNode(k, v);
		n->height = 0;
        insert_print(k);
		return n;
		}
	if (k < root->key) {
		root->leftChild = insertNodeAVL(k, v, root->leftChild);
		root->height = calcHeight(root);
	} else if (k > root->key) {
		root->rightChild = insertNodeAVL(k, v, root->rightChild);
		root->height = calcHeight(root);
		}
	// Note - ignored equal case - should not occur.
	return rebalance(root);
}//insertNode()


void inOrderT(Node* root)
// In order traversal of tree displaying contents
{
	if (root) {
		inOrderT(root->leftChild);
		printf("%d(h=%d,bf=%d) - ", root->key, root->height,getBalanceFactor(root));
		inOrderT(root->rightChild);
		}
}//inOrderT()


//------------------------------------------------------------------------------------------------------------------
Node* findParentHelper (Key k, Node* root)
// Help find parent of node with key == k. Parameter root is node with
// at least one child (see findParent()).
{
    if (root->leftChild)	{ //left subtree- check for match
        if (k == root->leftChild->key)	return root; // stop search if match
        else if (k < root->key) // keep looking
            return findParentHelper(k, root->leftChild); // recursive call
    }
    if (root->rightChild) { // check right subtree
        if (k == root->rightChild->key) return root; // stop if we find match
    }
    if (k < root->key) return findParentHelper(k, root->leftChild); // recursive left
    else return findParentHelper(k, root->rightChild); // recursive right
}//findparenthelper()




Node *findParent(Key k, Node *root)
//
{
    // Deal with special special cases which could only happen for root
    // of whole tree
    if (root == NULL)	return root;
    // real root doesn't have parent so we make it parent of itself
    if (root->key == k)	return root;
    // root has no children
    if ((root->leftChild == NULL) && (root->rightChild == NULL))
        return NULL;

    // Deal with cases where root has at least one child
    return findParentHelper(k, root);
}//findParent()



void delete (Node *p, Node *n)
// Delete node pointed to by n.
// Parameters:
//	n	- points to node to be deleted
//	p	- points to parent of node to be deleted.
{
    // Deletion has 3 cases - no subtrees, only left or right subtree, or both
    // left and right subtrees.
    Node *deleteNode = n;		// Save copy of pointer to node to delete.

    if (n->leftChild != NULL) {	// there is left child
        p = n;
        n = n->leftChild;  // pointing leftchild
        while (n->rightChild) { // finding the furthest right child of the left side
            p = n;
            n = n->rightChild; // pointing rightchild
        }
        deleteNode->key = n->key; // setting node key
        deleteNode->value = n->value; // setting node value
        delete(p,n); // recursive function call

    } else if (n->rightChild) {	// there is a right child
        p = n;
        n = n->rightChild;
        while(n->leftChild) {// finding the furthest right child of the left side
            p = n;
            n = n->leftChild;
        }
        // overwrite deleteNode (key,value) with (key,value) of leftmost child of right subtree
        deleteNode->key = n->key; // override and set node key
        deleteNode->value = n->value; // override and set node value
        delete(p,n);

    } else	{	// no children
        if (p != NULL) { // if not null then there is a parent
            if (p->leftChild == n) p->leftChild = NULL; // check for left delete
            else if (p->rightChild == n) p->rightChild = NULL; // check for right delete
        }
        free(n);
    }

}

Node* deleteNodeAVL(Key k, void *v, Node *root)
// deletes node from AVL
{
    if (root==NULL) return root;

    delete(findParent(k,root), find(k, root));
    return rebalance(root);
}//deletenodeavl()