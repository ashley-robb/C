// readnumsv6.c – Lab 01 – ASHLEY, ROBB
#include <stdio.h>
#include <stdlib.h> // added to code to allow for free() function in 
                    // delete_node command to save memory

// Handy manifests
#define	EXIT_OK		0
#define	EXIT_ERROR	0


// Defining a node in our linked list 
struct node {
	struct node	*pnextnode;
	int			datavalue;
	};

// Global pointers - so they can be used by all functions. One points
// to the first element in the linked list, the other points to the last
// element in the linked list.
struct node	*phead = NULL;
struct node *pback = NULL;

//This function creates a new node and
// initializes the data and next pointer fields.
struct node *pnew_node (int d)
// function returns pointer to the new node if everything worked, 
//or it returns NULL if malloc() was unable to get memory.

{
	// declaring a local node pointer, with initialization
	struct node	*pn = (struct node *) malloc (sizeof (struct node));

	// If we actually got memory, use it
	if (pn != NULL)	{ 
		// filling in the structure
		pn->datavalue = d;
		pn->pnextnode = NULL;	// guarantees that it has unmistakeable value
		}
	// pn pointing to a filled-in structure or pn equal to NULL
	// if malloc() failed. Regardless return pn.
	return pn;
} //pnew_node()
	


int insert_data_at_front (int d)
// Insert new data value at the start of the linked list
{
	struct node	*pn = pnew_node (d);

	//check for successful node creation
	if (pn == NULL)	return -1;
    
    //The new node takes the place at the head of the list and 
    // the current head node gets pointed to by the new head
    // the original list is the same and pointed to by the new head
    
	pn->pnextnode = phead;
	phead = pn;
	// checking if this node is the first node to be added, in this case
    //we must update the last pointer as well
	if (pback == NULL)	pback = pn;
	return 0;
}//end of insert_data_at_front()


int insert_data_at_end (int d)
// Insert new item of data at end of linked list.
{
    //create new node with inputted data value 
	struct node	*pn = pnew_node (d);

	// check for successful node creation 
	if (pn == NULL)	return -1;

	// New node goes to end of list. If the list is empty,
	// we will need to update both the head and back pointers
	if (pback == NULL)	{
		pback = pn;
		phead = pn;
	} else	{
		// if there are already nodes in the list, we need to
        // Add the new one after the current last one
		pback->pnextnode = pn;
		// make the back pointer point to the new one
		pback = pn;
		}
	return 0;
}//end of insert_data_at_end()

int delete_data (int d)
// delete a data value in the list 
{   // check to make sure there is data within the list
    if (phead == NULL) {
        printf ("ERROR: list is empty, you must add values before you can delete any\n");
    return 0;
    }
    // set the present node equal to head to allow us to cycle through 
    struct node	*pn = phead;
    // special case if the first value is equal to the data value we're deleting 
    // check if the head has the assigned value update the head pointer to point to the next node if so
    if (phead -> datavalue == d) {
        phead = phead -> pnextnode; //update the head pointer to point to the next node
        free(pn); // remove the deleted value from memory
        return 0;
    }
    // for cases where the head is not the data value we are looking for, 
    // we need to create a pointer to store the previous nodes info 
    else {
        struct node* plastnode = NULL;
        while (pn != NULL && pn-> datavalue != d) { // cycle through values until we find the targetted val
            plastnode = pn; // update node pointers along the way
            pn = pn -> pnextnode;
        }
    if (pn == NULL){ // if we reach the end of the list, the value we are searching for is not in the list, error
        printf("ERROR: no value that matches input, no data has been deleted\n");
        return 0;
    }
    else { // if we reach our value, we adjust pointers and remove value from memory
        plastnode -> pnextnode = pn -> pnextnode;
        free(pn);
        return 0;
    }
}
}

void print_linked_list (void)
// printing data contents of our linked list
{
	struct node	*ptemp;		// temporary pointer used to traverse list
	int			count;		// count how many printed on one line
	if (phead == NULL)	{
		printf ("<EMPTY LIST>\n");
		return;
		}
	// List has some real data to be printed. We will point ptemp at
	// the first node in the list and print the data. If the list continues, 
	// we move ptemp to point to the next node and keep
	// doing this until there are no more nodes to look at.
	ptemp = phead;
	count = 0;				// 0 on line so far
	while (ptemp != NULL)	{
		printf ("%4d", ptemp->datavalue);
		if (ptemp->pnextnode != NULL)	{
			printf ("->");
			count++;			// one more on the line
			// check if getting close to right edge - if so, move to start of
			// next line and reset count.
			if (count > 12)	{
				putchar ('\n');
				count = 0;
				}
		} else	{
			putchar ('\n');
			}
		ptemp = ptemp->pnextnode;
		}
	// all done
	return;
} // print_linked_list()
	

void main (void)
{
	char	ch;
	int		d;
	int		going;

	printf ("On each line, enter letter F, B, or D, followed by a space and\n");
	printf ("a number. F means the number is placed at the front of the\n");
	printf ("list, B means the number is placed at the back, and D means the\n");
    printf ("first occurance of the value is deleted from the list.\n");
	printf ("To end your input, enter letter Q and any number.\n");

	going = 1;
	while (going)	{
		// very specific format !!
		scanf ("%c", &ch);			// get the letter in the first position
		scanf ("%d", &d);			// get the number after that
		while (getchar() != '\n');	// skip all up to and including newline
		printf ("Received %c %d\n", ch, d);
		switch (ch)	{
		case 'Q':
		case 'q':
			going = 0;		// Q or q means end of input
			break;
		case 'F':
		case 'f':
			insert_data_at_front (d);
			break;
        case 'D':
		case 'd':
			delete_data (d);
			break;
		case 'B':
		case 'b':
			insert_data_at_end (d);
			break;
		default:
			fprintf (stderr, "ERROR: Invalid command --%c--\n", ch);
			break;
			}//endswitch
		}//endwhile

	// User has entered all they wanted to
	print_linked_list ();

	printf ("====END====\n");
}//main()