#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// defining tree structure
typedef struct trnode	TreeNode, *pTreeNode;

// defining node structure
struct trnode	{
    char		*pletter;
    TreeNode	*leftChild;
    TreeNode	*rightChild;
};
// determining the size of the node for memory
#define SZ_TRNODE	(sizeof (TreeNode))

// creating a node for the tree
TreeNode *CreateNode (char letter)
{
        TreeNode	*pn = NULL;
        pn = (TreeNode *) malloc (SZ_TRNODE);
        pn->pletter = letter;
        pn->leftChild = NULL;
        pn->rightChild = NULL;
    return pn;
}

//defining tree structure
typedef struct tree {
    TreeNode *root;
} Tree;
// creating my tree
Tree mytree = {NULL};

// printing post order function
void print_postorder (TreeNode *pn)
{
    if (pn == NULL)	return;
    print_postorder (pn->leftChild);
    print_postorder (pn->rightChild);
    printf (" %c\n", pn->pletter);
}


int main (int argc, char *argv[], char *environ[])
{
    printf("\n----------QUESTION 1----------\n");
    // creating the tree
    mytree.root = CreateNode('A');
    mytree.root-> leftChild = CreateNode('B');
    mytree.root-> leftChild->leftChild = CreateNode('D');
    mytree.root-> leftChild ->leftChild -> leftChild= CreateNode('H');
    mytree.root-> leftChild ->leftChild -> rightChild= CreateNode('I');
    mytree.root-> leftChild -> rightChild= CreateNode('E');
    mytree.root-> leftChild -> rightChild -> leftChild= CreateNode('J');
    mytree.root-> rightChild = CreateNode('C');
    mytree.root-> rightChild ->leftChild = CreateNode('F');
    mytree.root-> rightChild -> rightChild = CreateNode('G');
    mytree.root-> rightChild -> rightChild -> leftChild = CreateNode('K');

    // printing in post order with my function
    printf ("Postorder Traversal\n");
    print_postorder(mytree.root);
    return 0;
}




