//Q2.c – Assignment 1 – ashley, robb

// necessary libraries
#include <stdio.h>
#include <stdlib.h>

//node structure
struct node {
    char bracket;
    struct node* next;
};

//declaring function that are written out below main
void push(struct node** top, char new);
int pop(struct node** top);

// match function determines if the corresponding opening and closing brackets match
int match(char open, char close)
{
    // if the open and close do match, the function returns 1
    if (open == '(' && close == ')')
        return 1;
    else if (open == '{' && close == '}')
        return 1;
    else if (open == '[' && close == ']')
        return 1;
    else // if they dont match it returns zero
        return 0;
}

// function to check if opening and closing brackets
int balance(char list[])
{
    int i = 0;
    struct node* stack = NULL; // node used for stacking characters
    // traversing through the list
    while (list[i]) {
        // if the bracket is an opening bracket we add it to the stack
        if (list[i] == '{' || list[i] == '(' || list[i] == '[') push(&stack, list[i]);
        // If the bracket is a closing bracket we refer to the stack
        if (list[i] == '}' || list[i] == ')'|| list[i] == ']') {
            // if the stack is empty we know our input cannot be balanced
            if (stack == NULL)
                return 0;
            // if the stack is not empty we pop the top value and call our match function to check if they are balanced
            else if (!match(pop(&stack), list[i]))
                return 0; // return zero if they do not match
        }
        i++; // move to next bracket
    }
    if (stack == NULL) // now we have to check if all openeing brackets were popped from stack and balanced with the appropriate closing bracket
        return 1; // return 1 if balanced
    else
        return 0; // return 0 if not balanced
}

// push bracket into stack
void push(struct node** top, char new)
{
    // create node
    struct node* temp = (struct node*)malloc(sizeof(struct node));

    if (temp == NULL) { // check for proper node creation
        printf("Stack overflow n");
        getchar();
        exit(0);
    }
    // add pracket to node and adjust pointer accordingly
    temp->bracket = new;
    temp->next = (*top);
    (*top) = temp;
}

// pop bracket from stack
int pop(struct node** top)
{
    char result; // variable for popped value
    struct node* temp; // node creation

    if (*top == NULL) { // check for proper node creation
        printf("Stack overflow n");
        getchar();
        exit(0);
    }
    else {
        // adjust pointers
        temp = *top;
        result= temp-> bracket;
        *top = temp->next;
        // free memory allocation
        free(temp);
        // return popped value
        return result;
    }
}

int main()
{
    char input[100]; // max input is 100
    printf("input your string on the line below:\n");
    scanf(" %s", *&input); //reading brackets string

    // using the balance function to determine if the function is balanced or not
    // and outputting appropriate response
    if (balance(input)) {
        printf("Balanced \n");
        return 1;
    }
    else {
        printf("Not Balanced \n");
        return 0;
    }
}


