//queueproblem.c – lab 2 – ashley, robb
//necessary libraries
#include <stdio.h>
#include <stdlib.h>

// Structure to create a node with data and the next pointer
struct node {
    int data;
    struct node * next;
};
// creating front and rear for all 4 queue we have to add values to
struct node * front0 = NULL;
struct node * rear0 = NULL;
struct node * front1 = NULL;
struct node * rear1 = NULL;
struct node * front2 = NULL;
struct node * rear2 = NULL;
struct node * front3 = NULL;
struct node * rear3 = NULL;

// Enqueue() operation to add value to queue
void enqueue(struct node **front, struct node **rear, int value) {
    // creating pointer node and adjusting pointers
    struct node * ptr;
    ptr = (struct node * ) malloc(sizeof(struct node));
    ptr -> data = value;
    ptr -> next = NULL;
    if (((*front) == NULL) && ((*rear) == NULL)) { // checking if queue is empty
        (*front) = (*rear) = ptr;
    } else { // adding adjusting pointer and node
        (*rear) -> next = ptr;
        (*rear) = ptr;
    }
}

// Display all elements of the queue
void display(struct node **front ) {
    struct node * temp; // temporary node to traverse through list
    int count = 0;// also counting length of list to print 12 vals per line
    if ((*front) == NULL){ // check that list exists
        printf("\nNo entries fit this description\n");
    } else {
        temp = (*front); // setting temporary node to front to traverse list
        while (temp) {
            count = count + 1; // updating count
            if (temp->next == NULL){
                printf("%5d\n\n", temp -> data);// printing last value for next node null
            }
            else {
                printf("%5d,", temp->data);// printing values
            }
            if (count % 12 == 0)printf("\n");// putting vals on a new line once there are 12 values on current line
            temp = temp -> next;// updating pointer
        }
    }
}
int main() {

    printf("\n\nInput your values below inside of the opening square bracket.\n"
           "When you have finished adding all values, close the brackets and press enter\n");
    int val; // input value declaration
    int going = 1;// used for while loop
    int mod; // modulus value
    while(going==1) {
        scanf("%d", &val);
        if (val >= 0) { // if positive
            mod = val % 4;
            // add to appropriate queue
            if(mod == 0)enqueue(&front0, &rear0, val);
            else if(mod == 1)enqueue(&front1, &rear1, val);
            else if(mod == 2)enqueue(&front2, &rear2, val);
            else if(mod == 3)enqueue(&front3, &rear3, val);
            else{
                printf("ERROR: issue with input"); // check for issue
                return 0;
            }
        }
        else break; // break when value entered is negative
    }
    // display lists
    printf("The values entered with modulo 4 value = 0:\n");
    display(&front0);
    printf("The values entered with modulo 4 value = 1:\n");
    display(&front1);
    printf("The values entered with modulo 4 value = 2:\n");
    display(&front2);
    printf("The values entered with modulo 4 value = 3:\n");
    display(&front3);
}

