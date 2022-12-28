//Q1.c – Assignment 1 – ashley, robb

//including necessary libraries
#include <stdio.h>
#include <stdlib.h>

// creating node structure for doubly linked list
struct node {
    int num;
    struct node * next;
    struct node * prev;
} *head, *tail, *head2, *tail2;// pointer for head and tail of each list


// function used to creat and insert a node at the end of a doubly linked list
void create(int n)// input is length of list
{
    int num, i; // declare variables
    struct node *new; // create node

    if(n >= 1)// making sure list is not empty
    {
        head = (struct node *)malloc(sizeof(struct node));// creating the head node

        if(head != NULL)// checking that creation worked
        {
            printf("input data values, with each value on a separate line\n");
            scanf("%d", &num);//scanning for input
            // adjusting pointers for new value and pointers that point to new value
            head->num = num;
            head->next = NULL;
            head -> prev = NULL;
            tail = head;// only for first input

            // putting data for rest of the nodes
            for(i=2; i<=n; i++)
            {
                new = (struct node *)malloc(sizeof(struct node));
                if(new != NULL)
                {
                    scanf("%d", &num);// scanning data
                    //updating relevant pointers
                    new->num = num;
                    new->next = NULL;
                    new -> prev = tail;
                    tail->next = new;
                    tail = new;
                }
                else//checking for issue
                {
                    printf("ERROR: memory allocation");
                    break;
                }
            }
        }
        else printf("ERROR: memory allocation");
    }else printf("ERROR you cannot have a list of length 0");
}

// function used to display doubly linked list 1
void display()
{
    int size = 0; // used to determine the number of values in the list
    if(head == NULL)//checking that list exists
    {
        printf(" No data found in the List yet.");
    }
    else
    {
        struct node * temp;//creating temporary node to traverse through list
        temp = head;
        printf("\n\nYour list:\n");

        while(temp != NULL) // while loop used to traverse list
        {
            if (temp->next == NULL)
                {
                    printf("%d", temp->num);// printing last value without a comma after it
                    size++; // updating length of list
                    temp = temp->next;// moving to the next node
                }
            else {
                printf("%d, ", temp->num); //printing current value with a comma to separate it from next value
                size++; // updating list length
                temp = temp->next; // current pointer moves to the next node
                }
        }
        free(temp);// freeing memory
    }
}
//insert first function for Q1 B
void insert_first(int val)
{
    // declaring new node
    struct node *new;
    new = (struct node *)malloc(sizeof(struct node));
    if(new == NULL) { // checking node creation worked
        printf("ERROR: please review inputs and try again");
    }
    else { // adjusting relevant pointers to insert node at front of list
        new->next = head;
        new->num = val;
        new -> prev = NULL;
        head = new;
    }
}

// delete first function for Q1 C
void delete_first(char choice)
{
    if(choice == 'y' || choice == 'Y'){ // confirming that we want to delete the first node
        printf("this means YES, you are deleting the first node");
        // updating pointers
        head = head -> next;
        head -> prev = NULL;
    }
    else if((choice == 'n') || (choice == 'N')){ // not deleting nodes
        printf("this means NO, you are not deleting the first node");
    }
    else{ // input other than y/n
        printf("\nERROR: the choice you entered in not valid");
    }
}

//insert position for Q1 D
void insert_pos(int pos, int data)
{
    // creating new node
    struct node *new;
    new = (struct node *)malloc(sizeof(struct node));
    if(new == NULL) {// checking for node creation issues
        printf("ERROR: please review inputs and try again");
    }
    else {
        if (pos == 1) {// special case for inserting node at front
            new->num = data;
            new->next = head;
            new->prev = NULL;
            head = new;
        }
        else {
            int i=1;
            struct node *temp;// using a temporary node to determine where we need to enter our value
            temp = head;
            while (i < pos && temp != NULL) {// travelling through the list
                temp = temp->next; // update node pointers along the way
                i++;
            }
            if (i < (pos)) { // issue if list is shorter than position
                printf("\nERROR: the position you have selected is outside of the list range\n");
            }
            else if (temp == NULL) { // special case for end of list
                new->num = data;
                new->next = NULL;
                tail ->next = new;
                new->prev = tail;
                tail = new;
            } else {// adding value in middle of list
                new->num = data;
                new->next = temp;
                new->prev = temp->prev;
                temp->prev->next = new;
                temp->prev = new;
            }

        }
    }
}


void create2(int m){ // used for creating a separate doubly linked list
    {
        int num, i; // declaring variables
        struct node *new; //creating node

        if(m >= 1) // checking list length
        {
            head2 = (struct node *)malloc(sizeof(struct node));

            if(head2 != NULL) // checking for successful node creation
            {
                printf("input data values, with each value on a separate line\n");
                scanf("%d", &num);// reading inputs
                // adjusting pointers for first node
                head2->num = num;
                head2->next = NULL;
                head2 -> prev = NULL;
                tail2 = head2;

                // putting data for rest of the nodes
                for(i=2; i<=m; i++) // repeating for length of list
                {
                    new = (struct node *)malloc(sizeof(struct node));
                    if(new != NULL)
                    {
                        scanf("%d", &num); // scanning values
                        // updating relevant pointers
                        new->num = num;
                        new->next = NULL;
                        new -> prev = tail2;
                        tail2->next = new;
                        tail2 = new;
                    }
                    else printf("ERROR: memory allocation"); // checking for issues
                }
            }
            else printf("ERROR: memory allocation");
        }
    }
}

// display function for second doubly linked list
void display2()
{
    int size2 = 0; // counter variable
    if(head2 == NULL) // checking that list exists
    {
        printf(" No data found in the List yet.");
    }
    else
    {
        //using a temporary list to traverse through data
        struct node * temp;
        temp = head2;
        printf("\n\nYour second list:\n");

        while(temp != NULL)// using a while loop for moving through list
        {
            if (temp->next == NULL) // special case for last value
            {
                printf("%d", temp->num);// doesnt print comma after last value
                size2++; // updating list length
                temp = temp->next;// adjusting pointer
            }
            else {
                printf("%d, ", temp->num);// printing value
                size2++; // adjusting length counter
                temp = temp->next; // current pointer moves to the next node
            }
        }
        free(temp); // freeing memory space
    }
}

// function to merge and sort lists
void merge(int m) { // inputting size of new list
    head2 = NULL; // declaring new head and tail
    tail2 = NULL;
    create2(m); // creating the list
    printf("great! now we have 2 lists, they are:\n");
    display();
    display2();
    //putting the lists together
    tail->next = head2; // pointing the end of list one to the start of list two merging them into one list
    head2->prev = tail;

    // using two temporary nodes to compare values
    struct node *temp = NULL;
    struct node *next_temp = NULL;
    int data_holder; // bookmarks data
    if (head == NULL) { // checking that list is not empty
        printf("ERROR: cannot sort empty list");
        return;
    } else
        for (temp = head; temp->next != NULL; temp = temp->next) // creating a loop to traverse the list
            for (next_temp = temp->next; next_temp != NULL; next_temp = next_temp->next) { // nested for loop to traverse the list again to ensure all values are correctly sorted
                if (temp->num > next_temp->num) { // adjusting values order if necessary
                    // updating relevant pointers
                    data_holder = temp->num;
                    temp->num = next_temp->num;
                    next_temp->num = data_holder;
                }
            }
    printf("\n\ncombining these lists together, and sorting them into ascending order gives:");
    display();
}

int main()
{   printf("\n---------------Q1 PART A:---------------\n\n");
    printf("Let's create a doubly linked list!\n");

    int n;
    printf("How many nodes (data values) are in the list?: ");
    scanf(" %d", &n); // length of list
    head = NULL;
    tail = NULL;
    create(n);
    display();

    printf("\n\n---------------Q1 PART B:---------------\n\n");
    printf("for part b, we must add a value to the front of the list\n");
    printf("Enter the data value you would like to add the the start of the list:  ");
    int val;
    scanf(" %d", &val); // value being added to start of list
    insert_first(val); // calling the function to add value at front
    display();

    printf("\n\n---------------Q1 PART C:---------------\n\n");
    printf("for part c, we are asked to delete the first value of the list\n");
    printf("would you like to proceed and delete the first value? (y/n):  ");
    char choice;
    scanf(" %c" ,&choice);
    printf("you entered: %c, ", choice);
    delete_first(choice); // calling the function to delete first node, if y, node deleted, if n node not deleted
    display();

    printf("\n\n---------------Q1 PART D:---------------\n\n");
    printf("for part d, we are asked to add a value at a given position in the list\n");
    printf("To select a position to insert the new data:\n"
           "Enter 1, to have the new data be at the front of the list\n"
           "Enter 2, to have the new data be the second value in the list\netc...\n");
    int pos, data;
    printf("Enter your position value here:  ");
    scanf(" %d", &pos); // determining where to add new node
    if(pos < 1){
        printf("ERROR: position must be greater than 0 and less than the length of the list");
    }
    printf("\nEnter the data value you would like to add into position %d:  ", pos);
    scanf(" %d", &data);//value being entered
    printf("You have chosen to insert %d into position %d of the list",data,pos);
    insert_pos(pos, data); // calling insert function
    display();


    printf("\n---------------Q1 PART E:---------------\n\n");
    printf("Let's merge our doubly linked list with a new doubly linked list!\n");

    int m;
    printf("How many nodes (data values) are in the NEW list?: ");
    scanf(" %d", &m); // determining length of new list
    merge(m); // calling the merge function to create, merge, sort and print lists
    return 0;
}