#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// define node structure
struct node {
    int num;
    struct node *left, *right;
};
// function to create new node
struct node* newNode(int item)
{
    struct node* temp
            = (struct node*)malloc(sizeof(struct node));
    temp->num = item;
    temp->left = temp->right = NULL;
    return temp;
}
// necessary function for breadth first printing
void level(struct node* root, int row) {
    if (root == NULL) return;
    if (row == 0) {
        printf("%d, ", root->num);
    }
    else {
        level(root->left, row - 1);
        level(root->right, row - 1);
    }

}

// returns higher value
int max(int a, int b) { return (a >= b) ? a : b; }
//determines tree height
int height(struct node* node)
{
    if (node == NULL)
        return 0;
    return 1 + max(height(node->left), height(node->right));
}

void breadthFirstTraversal(struct node* root) {
    int h = height(root);
    for (int i = 0; i < h; i++) {
        level(root, i);
    }
}
// inserts node to BST
struct node* insert(struct node* node, int num)
{
    if (node == NULL)
        return newNode(num);
    if (num < node->num)
        node->left = insert(node->left, num);
    else if (num > node->num)
        node->right = insert(node->right, num);
    else if(num == node-> num){
        if (node->right == NULL) node->right = insert(node->right, num);
        else if (node->left == NULL) node->left = insert(node->left, num);
        else insert(node->right, num);

    }
    return node;
}

// merging two trees
struct node* merge(struct node* first_root, struct node* second_root)
{
    if(first_root == NULL){
        return second_root;
    }
    else if(second_root == NULL){
        return first_root;
    }
    else{
        insert(first_root, second_root->num);
        if(second_root->left != NULL){
            merge(first_root, second_root->left);
        }
        if(second_root->right != NULL){
            merge(first_root, second_root->right);
        }
        if(second_root->left == NULL && second_root-> right == NULL){
            return first_root;
        }
    }
}

int main()
{
    printf("\n----------QUESTION 2----------\n");

    printf("ALL VALUES ARE HARD CODED WITH EXAMPLE INPUTS, INPUTS CAN BE ACCEPTED IF SECTIONS ARE UNCOMMENTED :)\n");
    /*
    printf("how many values are in your first tree?\n");
    int numvals1;
    scanf("%d", &numvals1);

    printf("\n num vals = %d", numvals1);

    int temp;
    struct node *root_1 = NULL;
    printf("\n\nInput your values below when prompted, press enter to add the value\n");
    int i = 0;
    while (i < numvals1) {
        if (i == 0) {
            printf("enter your first value below\n");
            scanf("%d", &temp);
            root_1 = insert(root_1, temp);
            i = i + 1;
        } else if (i + 1 == numvals1) {
            printf("enter your last value below\n");
            scanf("%d", &temp);
            insert(root_1, temp);
            i = i + 1;
        } else {
            printf("enter your next value below\n");
            scanf("%d", &temp);
            insert(root_1, temp);
            i = i + 1;
        }
    }
    printf("Your first tree printed in order is: ");
    inorder(root_1);
    */
    struct node *root_1 = NULL;
    root_1 = insert(root_1, 3);
    insert(root_1, 5);
    insert(root_1, 2);
    insert(root_1, 1);
    printf("Your first tree printed in breadth first order is: \n");
    breadthFirstTraversal(root_1);

    // // // // // // // // // // // // //

    /*
    printf("how many values are in your second tree?\n");
    int numvals2;
    scanf("%d", &numvals2);

    printf("\n num vals = %d", numvals2);

    struct node *root_2 = NULL;
    printf("\n\nInput your values below when prompted, press enter to add the value\n");
    i = 0;
    while (i < numvals2) {
        if (i == 0) {
            printf("enter your first value below\n");
            scanf("%d", &temp);
            root_2 = insert(root_2, temp);
            i = i + 1;
        } else if (i + 1 == numvals2) {
            printf("enter your last value below\n");
            scanf("%d", &temp);
            insert(root_2, temp);
            i = i + 1;
        } else {
            printf("enter your next value below\n");
            scanf("%d", &temp);
            insert(root_2, temp);
            i = i + 1;
        }
    }
    printf("Your second tree printed in order is: ");
    inorder(root_2);

    */

    struct node *root_2 = NULL;
    root_2 = insert(root_2, 7);
    insert(root_2, 1);
    insert(root_2, 2);
    insert(root_2, 9);
    insert(root_2, 4);
    printf("Y\n\nour second tree printed in breadth first order is: \n");
    breadthFirstTraversal(root_2);

    printf("\n\nMerging these 2 trees using the new merge function and printing it in breadth first order gives: \n");

    merge(root_1, root_2);
    breadthFirstTraversal(root_1);
    return 0;
}