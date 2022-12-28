// LAB4_MAINB.c – Lab 04 – Ashley, Robb
//
// *** DO NOT EDIT THIS CODE ***
//
// See instructions in the lab handout.  You will be adding code
// to avl.c.  This code is intended to verify that your code works.
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
#include <time.h>

#include "/Users/ashleyrobb/CLionProjects/LAB04/bintree.h"
#include "/Users/ashleyrobb/CLionProjects/LAB04/bintree.c"

#include "/Users/ashleyrobb/CLionProjects/LAB04/avl.h"
#include "/Users/ashleyrobb/CLionProjects/LAB04/avl.c"

#include "/Users/ashleyrobb/CLionProjects/LAB04/bst.h"
#include "/Users/ashleyrobb/CLionProjects/LAB04/bst.c"



void panic(char *msg, char *fname)
// Function to display error message on stderr and exit program.
// First parameter is error message; second is optional, and if present,
// is supplemental information.
{
	fprintf (stderr, "ERROR: %s %s\n",
			msg==NULL ? "Unknown!" : msg,
			fname==NULL ? "" : fname);
	fprintf (stderr, "       Program terminating\n");
	exit (-1);
}// panic()



// Functions that are generic to either a BST or an AVL tree. Where two
// tree types differ is in their insert and delete functions.
// routines.
/*
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
*/



pTree initTree (TreeType trtype)
// Allocate memory for a tree descriptor. As noted in the header file, a tree
// descriptor could be much more elaborate, but this is sufficient for our
// purposes.
// Function allocates memory for Tree structure, then initializes root pointer
// to NULL. Pointer returned from this function is used to identify tree in
// subsequent tree operations.
{
	pTree t = (pTree) malloc(sizeof(Tree));
	if (t != NULL)	{
		t->root = NULL;
		t->tt = trtype;		// record tree type
		}
	return t;
}//initTree()


pNode find (Key k, pNode root)
// Function locates node with key value equal to parameter k. Parameter root
// holds pointer to root node of tree. Function returns immediately if either
// root pointer is null, or node that root points to has key value being
// looked for.  If neither of those conditions is true, then the
// function calls itself with pointer to root of either left or right
// subtree.
{
#if 0
	printf ("FIND CALLED\n");
	if (root != NULL)	{
		printf ("Checking %d while looking for %d\n", root->key, k);
	} else	{
		printf ("Root is NULL\n");
		}
#endif
	// termination conditions - either true, search is ended
	if ((root == NULL) || (root->key == k))	return root;
	// search continues.  Since this is a search tree, we know that
	// every key in the right subtree is bigger than the key in the tree's
	// root, and every key in the left subtree is smaller than the key in
	// the tree's root.  That allows us to choose the appropriate subtree
	// to search.
	if (k > root->key)
		// Key value sought is larger than current node key, so search right
		// subtree
		return find(k,root->rightChild);
	else
		// Key value sought is smaller than current node key (equal case
		// was handled as termination condition in first line), so
		// search left subtree
		return find(k,root->leftChild);
#if 0
	// slightly obscure way of doing if-then-else above. It is left to the
	// reader to decide which is the better code
	return find (k, (k > root->key) ? root->rightChild : root->leftChild);
#endif
}// find()


struct node* BST_find(struct node *root, int val){
    if (root == NULL || root->num == val) return root;
    if(val < root->num) BST_find(root->left, val);
    else BST_find(root->right, val);
}

int main(int argc, char *argv[])
{
	int		v1 = 1;
	char	*fname;			// name of input file
	FILE	*finn;			// used to input data file
	int		i, j, readcount;
	int		lastkeys[10], lastkeyindex;
	Tree	*t_avl;			// pointer to AVL tree descriptor
	Tree	*t_bst;			// pointer to BST tree descriptor
	int		gabby = 1;		// flag whether we should generate lots of output
	int		defaultdata;
	int		count;			// count number of insertions
	pNode	foundnode;
    struct node* bst_root = NULL;
    clock_t	start, end, deltaBST, deltaAVL;
    clock_t	start_bst, end_bst;

	fprintf (stderr, "Compare BST and AVL Trees.\n");
	// set up descriptor to be used for AVL tree
	t_avl = initTree(AVL);
	if (t_avl == NULL)	{
		panic ("Failed to initialize AVL tree descriptor.", NULL);
		}
	// set up descriptor to be used for BST tree
	//t_bst = initTree(BST);
	//if (t_bst == NULL)	{
	//	panic ("Failed to initialize BST tree descriptor.", NULL);
	//	}
	if (argc == 2)	{
		// Looks like user has specified an input file on command line. Assume
		// there is lots of data and output should be small.
		fname = argv [1];
		gabby = 0;
		defaultdata = 0;
	} else	{
		// use default input file
		fname = "/Users/ashleyrobb/CLionProjects/LAB04/avl_data_A.txt";
		defaultdata = 1;
		}
	fprintf (stderr, " -- Using input file: %s\n", fname);
	finn = fopen (fname, "r");
	if (finn == NULL)	{
		// something wrong - could not open file
		panic ( "Cannot open file:", fname);
		}
	// Insert each data value from file, and after inserting, output some
	// information about what the tree looks like. For the first part of
	// the lab, you just want to use the default input file.
	lastkeyindex = 0;

    struct node {
        int num;
        struct node *left, *right;
    };

	//struct node* bst_root = (struct node*)malloc(sizeof(struct node));

	for (count=0;;count++)	{
		// Read value from file
		readcount = fscanf (finn, "%d", &i);
		// Failure to read or negative number means end of list
		if ((readcount < 1) || (i < 0))	break;
		// Insert value into AVL tree (Note we're using a fake data value
		insertAVL(i, NULL, t_avl);
		if (gabby)	{
			printf("Inorder: ");
			inOrderT(t_avl->root);
			printf("\n-------\n");
		} else	{
			// This is the terse output when a large file is being read
			printf ("%7d: %11d\n", count, i);
			}

		// Your code to populate BST goes here
		//---<SNIP>---
        insert_BST(i,bst_root);
		//---</SNIP>---
	
		// keep track of last keys inserted
		lastkeys [lastkeyindex] = i;
		if (++lastkeyindex > 9)	lastkeyindex = 0;
		}
	// Close file
	fclose (finn);


	printf("\n\n\n\n----------TIMING TEST:----------\n\n\n\n");



	// Note we have last key inserted. We are going to use this to test
	// lookup performance
	if (defaultdata != NULL)	{
	    printf("test");
		// Your code to test BST goes here
		//---<SNIP>---
        start = clock();
        for (i=0; i<1000000; i++)	{
            for (j=0; j<10; j++)	{
                foundnode = BST_find(bst_root,lastkeys[j]);
                if (foundnode == NULL)	{
                    fprintf (stderr, "ERROR: BST Could not find %d iteration %d\n", lastkeys[j], i);
                    return -1;
                }//endif
            }//endfor
        }//endfor
        end = clock();
        printf("BST Elapsed time: %.2f seconds (%d ticks)\n",
               (end - start) / (double)(CLOCKS_PER_SEC), (end-start));
		//---</SNIP>---

		start = clock();
		for (i=0; i<1000000; i++)	{
			for (j=0; j<10; j++)	{
				foundnode = find (lastkeys[j], t_avl->root);
				if (foundnode == NULL)	{
					fprintf (stderr, "ERROR: AVL Could not find %d iteration %d\n",
							lastkeys[j], i);
					return -1;
					}//endif
				}//endfor
			}//endfor
		end = clock();
		printf("AVL Elapsed time: %.2f seconds (%d ticks)\n",
				(end - start) / (double)(CLOCKS_PER_SEC), (end-start));
		}//endif check timing

	return 0;




/*
 *
 *
 * I got these results but I've since changed my code and now its giving me an error :( I unfortunately
 * can't figure out what changed but I have to submit the lab now
When running a test case with 10000 input values, the following results were obtained:
    testBST Elapsed time: 37.02 seconds (37021782 ticks)
    AVL Elapsed time: 0.30 seconds (303504 ticks)
this shows that AVL is way way way faster !


Results of test with 500 inputs:
testBST Elapsed time: 18.43 seconds (18433670 ticks)
AVL Elapsed time: 0.28 seconds (276017 ticks)


Results of test with 100 inputs:
testBST Elapsed time: 3.75 seconds (3749272 ticks)
AVL Elapsed time: 0.21 seconds (208231 ticks)


Results of test with 20 inputs:
testBST Elapsed time: 0.66 seconds (655883 ticks)
AVL Elapsed time: 0.12 seconds (121507 ticks)

We can see that the time change grows exponentially with the length of the list
*/


}//main()
