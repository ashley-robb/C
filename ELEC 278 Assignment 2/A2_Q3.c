#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#define bool int
//create node structure
struct node {
    int data;
    struct node* left;
    struct node* right;
};

//function to create node with integer data value
struct node* newNode(int data)
{
    struct node* node = (struct node*)malloc(sizeof(struct node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;

    return (node);
}

// insert a node into a tree by calling the root (unbalanced)
struct node* insert_BST(struct node* node, int num)
{
    if (node == NULL)
        return newNode(num);
    if (num < node->data)
        node->left = insert_BST(node->left, num);
    else if (num > node->data)
        node->right = insert_BST(node->right, num);
    else if(num == node-> data){
        if (node->right == NULL) node->right = insert_BST(node->right, num);
        else if (node->left == NULL) node->left = insert_BST(node->left, num);
        else insert_BST(node->right, num);
    }
    return node;
}

//returns the larger integer of 2 inputs
int max(int a, int b) { return (a >= b) ? a : b; }

// function to determine the height of a tree
int height(struct node* node)
{
    if (node == NULL)
        return 0;
    return 1 + max(height(node->left), height(node->right));
}

// function to check if the tree in balanced
const char*  isBalanced(struct node* root)
{
    int left_height;
    int right_height;
    if (root == NULL) {
        return "TRUE";
    }
    left_height = height(root->left);
    right_height = height(root->right);
    if (abs(left_height - right_height) <= 1 && isBalanced(root->left) && isBalanced(root->right)) return "TRUE";
    return "FALSE";
}

// function to print tree in order
void inorder(struct node* root)
{
    if (root != NULL) {
        inorder(root->left);
        printf("%d\n",root->data);
        inorder(root->right);
    }
}

// function to print tree pre order
void preorder(struct node* root)
{
    if (root != NULL){
    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
    }
}

// function to rotate BST to AVL tree
struct node* Rotation(struct node* root){
    if(isBalanced(root) == "FALSE"){
        struct node *new_root;
        if (height(root->right) > (height(root->left))) {
            //left rotation
            new_root = root->right;
            root -> right = new_root ->left;
            new_root->left = root;
            Rotation(new_root);
        }
        else {
            //right rotation
            new_root = root->left;
            new_root -> left = root ->left ->left;
            root -> left = new_root ->right;
            new_root->right = root;
            Rotation(new_root);
        }
        return new_root;
    }
    else return root;
}

int main()
{
    printf("\n----------QUESTION 3----------\n");
    // declaring the inputs of the tree in the example
    struct node* root = newNode(12);
    insert_BST(root,8);
    insert_BST(root,18);
    insert_BST(root,5);
    insert_BST(root,9);
    insert_BST(root,17);
    insert_BST(root,2);
    insert_BST(root,4);

    //printing and outputs
    printf("\nInitial tree pre order:\n");
    preorder(root);
    printf("\nbalanced: %s\n",(isBalanced(root)));
    printf("\nRotated tree pre order:\n");
    preorder(Rotation(root));
    printf("\nbalanced: %s\n",(isBalanced(Rotation(root))));
    return 0;
}
