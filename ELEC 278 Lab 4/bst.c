//LAB4_BST.c – Lab 04 – Ashley, Robb
// 
// Code for ELEC278 Lab 4. Bare bones BST code used to do time comparisons.
// You may recognize this as a cut from the Lab 03 solution.


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



#include <stdlib.h>
#include <stdio.h>
#include "bst.h"


// Your code goes here - addition so that insert to a BST can be done by passing
// a pTree parameter, not a pNode parameter. (See AVL code for a suggestion.)
//---<SNIP>---

pNode initNode (Key k, void *v)
// Allocate memory for new node and initialize fields.
// Returns pointer to node created, or NULL if no memory.
{
    pNode n = (pNode) malloc(sizeof(Node));
    if (n != NULL)	{
        n->key = k;
        n->value = v;
        n->leftChild = NULL;
        n->rightChild = NULL;
        n->height = -1;
    }
    return n;
}//initNode()

//---</SNIP>---

struct node {
    int num;
    struct node *left, *right;
};

struct node* newNode(int item)
{
    struct node* temp
            = (struct node*)malloc(sizeof(struct node));
    temp->num = item;
    temp->left = temp->right = NULL;
    return temp;
}
struct node* insert_BST(int k, struct node* node)
// Function inserts new node into tree, with key k and value pointed to
// by v. Parameter root points to root node of tree.  Note that this code
// rejects an attempt to insert a duplicate key.
{
    if (node == NULL)
        return newNode(k);
    if (k < node->num)
        node->left = insert_BST(node->left, k);
    else if (k > node->num)
        node->right = insert_BST(node->right, k);
    else if(k == node-> num){
        if (node->right == NULL) node->right = insert_BST(node->right, k);
        else if (node->left == NULL) node->left = insert_BST(node->left, k);
        else insert_BST(node->right, k);
    }
    return node;
}