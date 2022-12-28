//stackproblem.c – lab 2 – ashley, robb

//necessary libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to create a node with data and the next pointer
struct node {
    char data;
    struct node * next;
};
struct node* top = NULL;// declaring top node

// function to display stack
void display() {
    if (top == NULL) {// check if stack is empty
        printf("\nStack Underflow\n");
    } else {
        struct node *temp = top;// create temporary node to traverse stack
        while (temp->next != NULL) {
            printf("%c", temp->data); // print character
            temp = temp->next;// update pointer
        }
        printf("%c\n\n", temp->data);// at end of stack print new line
    }
}
// function to add character to stack
void push(char value) {
    struct node *new;// creating a new node
    new = (struct node *)malloc(sizeof(struct node));
    new->data = value; // adjusting new node data pointer
    if (top == NULL) {// checking if values in stack exist
        new->next = NULL; // adding first value
    } else {
        new->next = top; // adding value to point to top
    }
    top = new; // adjust top to always be the node on top
}

int main() {
    printf("\n\nInput your characters below with each all characters on the same line."
           "\nWhen all characters have been entered, press enter\n");
    char str[80];// maximum number of values
    scanf("%[^\n]%*c", str);// reading inputs
    int length = strlen(str); //determining input string size
    for(int i= 0; i < length; i++) push(str[i]); // adding inputs to stack

    printf("Your inputted list is:\n");
    printf("%s\n", str);// original input

    printf("Your updated reversed list is:\n");
    display();// updated reversal due to stack
}