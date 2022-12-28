// Created by Ashley Robb on 2022-12-06.
//
// QUICKSORT
//
// Implements simple quicksort algorithm.

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
//ADD 1:
#include <stdio.h>
#include <stdlib.h>
#include "L5_INSTSORT.c"
extern int verbose;
extern long unsigned int swaps;
extern void swap (int *a, int g, int h); //for the swap function in utilitycode.c
extern void	printarray (char *msg, int *a, int min, int max, int numperline);
#define	MAXINDEX	19
//END OF ADD 1

void printarrowatposition (int posn)
// Prints a V - a down arrow - where the pivot value will be
{
    int	i;
    for (i=0; i<posn; i++)		printf ("     ");
    printf ("   V\n");
}//printarrowatposition()



int partition (int  *a,  int left, int right)
// Using locations a[left..right], partition fragment by picking a[left] as
// separator value, then working through bottom and top halves of the array,
// arranging - by swapping values if necessary - that all values smaller than
// the separator value are in the bottom part and all values larger are in
// the top part.
{
    int	ll, rr, pivotval;
    ll = left+1;
    rr = right;
    // choose pivot to be leftmost location
    pivotval = a[left];
    if (verbose)
        //printf ("Partition around value in position %d - %d\n", left, a[left]);
        while (ll < rr)	{
            // if one on left less than pivot, leave it alone
            if(a[ll] <= pivotval)	{ ll++; continue;}
            // if one on right greater than pivot, leave it
            if(a[rr] > pivotval)	{ rr--; continue;}
            // both left and right on wrong side - swap them
            swap(a, ll, rr);
        }//endwhile
    // we stop when rr and ll collide. Place pivot value such that everything
    // to left is less and everything to right is same or greater.
    if (a[ll] < pivotval)	{
        swap(a, ll, left);
    } else	{
        swap(a, --ll, left);
    }
    return ll;
}//partition()

/*
int insertionsort (int *a, int min, int max)
// Work through array of numbers, placing each one in the correct place. Note
// that insertion sort differs from bubblesort in that with insertion sort, one
// value is moved to its relative place. In bubble sort, the largest value is
// found as the checking keeps choosing the larger of two values to keep
// moving.
{
    int		i, j;
    int		rslt = -1;

    // Check for errors
    if (a == NULL || (min > max))	{
        error ("insertionsort() called with invalid parameters");
    } else	{
        // initialize swaps so we know how many exchanges take place
        swaps = 0;

        // Outer for loop works through values from min to max. Effectively,
        // we start by making the data in position relative 0 a sorted array containing
        // one element, then adding the rest of the array, one by one, to the
        // sorted part
        for (i = min; i <=max; i++) {
            // Now, i indicates which new element in the array is going to be
            // inserted into its correct position. At the end of each loop, one
            // more value is moved, and all of the bottom is ordered.
            for (j = i; j > min && (a[j - 1] > a[j]); j--) {
                swap(a, j, j - 1);
            }//endfor
        }//endfor
        rslt = swaps;
    }//endif
    return rslt;
}//insertionsort()
*/

int quicksort (int *a,  int left, int right)
{
    if (verbose)
        //printf ("\nQuicksort: left = %d   right = %d\n", left, right);
        if (left < right)    {
            int  pivotndx = partition (a, left, right);
            //if (verbose)	{
            //printf ("    Completed partition, pivot at: %d\n", pivotndx);
            //printarrowatposition (pivotndx);
            //printarray (NULL, a, 0, MAXINDEX, 1000);
            //}
            quicksort (a, left, pivotndx-1);
            quicksort (a, pivotndx+1, right);
        }
    //ADD 2
        else if (left < right){

            insertionSort(a, left, right);
        }
        //END ADD 2
    return swaps;
}//quicksort()

