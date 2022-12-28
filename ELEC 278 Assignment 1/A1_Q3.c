//Q3.c – Assignment 1 – ashley, robb
// including relevent libraries
#include <stdio.h>
#include <stdlib.h>

// Structure to create a node with data and the next pointer
struct node {
    int data;
    struct node * next;
};
// declaring nodes for queue and stack
struct node * front = NULL;
struct node * rear = NULL;
struct node* top = NULL;

// Enqueue() operation on a queue
void enqueue(int value) {
    struct node * ptr; // create pointer node
    ptr = (struct node * ) malloc(sizeof(struct node));
    // adjust pointer node pointers
    ptr -> data = value;
    ptr -> next = NULL;
    if ((front == NULL) && (rear == NULL)) {// check if its first entry in queue
        // if it is first entry front and rear are equal to each other and the node we just created
        front = rear = ptr;
    } else {
        // if its not the first node we adjust pointer accordingly
        rear -> next = ptr;
        rear = ptr;
    }
}

// Dequeue() operation on a queue
int dequeue() {
    if (front == NULL) { // check if list even exists
        printf("\nUnderflow\n");
        return -1;
    } else {
        // save data from front node
        int temp_data = front -> data;
        // adjust pointer
        front = front -> next;
        return temp_data;
    }
}

// Display all elements of the queue
void display() {
    struct node * temp; // temporary node used to traverse list
    if ((front == NULL) && (rear == NULL)) { // checking if queue exists
        printf("\nQueue is Empty\n");
    } else {
        printf("["); // printing for start of list
        temp = front; // temporary node starts at front and traverses to back
        while (temp) {
            if (temp->next == NULL){
                printf("%d]\n\n", temp -> data);// special print case for last value
            }
            else {
                printf("%d, ", temp->data); // printing data
            }
            temp = temp -> next; // updating pointer to continue moving through list
        }
    }
}

// used to determine the length of a list
int size() {
    int count = 0; // starting count
    if(front == NULL) return count; // returning 0 if no list
    struct node *temp; // using node to traverse through list
    temp = front; // start at front
    while (temp) {
        count = count +1; // update count
        if (temp ->next == NULL) return count; // returning count if end of list is reached
        temp = temp->next;// adjusting pointer to move through list
    }
}


// function used to push value into stack
void push(int new)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node)); // node creation

    if (temp == NULL) { // checking for successful node creation
        printf("Stack overflow n");
        getchar();
        exit(0);
    }
    // adjusting pointers and top to accommodate for new node
    temp-> data = new;
    temp->next = top;
    top = temp;
}

// Function to pop an item from stack
int pop()
{
    int result;

    // If stack is empty then error
    if (top == NULL) {
        printf("Stack overflow n");
        getchar();
        exit(0);
    }
    else {// finding top data and adjusting pointer
        result= top-> data;
        top = top->next;
        return result;
    }
}

int main() {

    printf("\n\nInput your Queue below inside of the opening square bracket.\n"
           "When you have finished adding all values, close the brackets and press enter\n");
    int quit = 0; // used for while loop
    // variable declaration
    char action;
    int val;
    printf("["); // start of input
    scanf(" %d", &val);// scanning first value
    enqueue(val); // adding first value to queue
    while (quit == 0) { // after first value we use comma to signify another value being added and ] for end of input
        scanf(" %c", &action);
        switch (action) {
            case',': // adding value to queue
                scanf(" %d", &val);
                enqueue(val);
                break;
            case']': // end of queue
                printf("End of Queue\n");
                quit = 1;
                break;
            default: // unaccepted input
                printf("ERROR:\n"
                       "you entered %c, the accepted inputs are values in your "
                       "queue and commas to separate them\n", action);
                return 0;
        }
    }
    printf("Your inputted list:\n"); // show inputted list
    display();

    printf("how many elements would you like to reverse the order of at the start? (this is k):\n");
    int k;
    scanf("%d", &k); // determine how many elements to reverse
    printf("reversing the first k = %d elements...\n", k);

    int input_size = size(); // determine list size
    if(k>input_size) {
        printf("ERROR: list is too short to reverse %f elements", k);
        return 0;
    }
    for(int i = 1; i<= k; i++) push(dequeue());// dequeue the first k values and push them into a stack

    for(int j = 1; j <= k; j++) enqueue(pop()); // pop these values from the stack and add them to end of queue

    for(int p = 1; p <= input_size - k; p++) enqueue(dequeue()); // remove the values at the front of the queue and add them to the back

    printf("\nyour updated list:\n");
    // shoe updated list
    display();

}