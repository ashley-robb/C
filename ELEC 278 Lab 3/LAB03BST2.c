//LAB03BST2.c – Lab 03 – Ashley, Robb
#include <stdlib.h>
#include <stdio.h>

// create node structure
typedef struct Node {
    char *pswrd; // password
    int val; // value
    struct Node *left, *right; //  child pointers (left & right)
} Node, *pn; // node , node pointer

// create the binary tree structure
typedef struct Tree {
    pn root;
} Tree, *pt;// tree tree pointer

//create a new node function
pn create_N(int value, char *pw) {
    //allocating mem for node
    pn curr = (Node *) malloc(sizeof(Node));
    // initializing
    if (curr != NULL) { //check for proper mem allocation
        curr->pswrd = pw; //set password
        curr->val = value; // set identification
        curr->left = NULL; // set left child to null
        curr->right = NULL;// set right child to null
    }
    return curr; // returning the current node
}
// create a new tree function
pt create_T(int value, char *pw) {
    Tree *tree_new = (Tree *) malloc(sizeof(Tree));// memory allocation for tree
    if (tree_new != NULL) {
        tree_new->root = create_N(value, pw); // calling previous function
    }
    return tree_new;
}
//function to add node to tree
void add(pn r, int value, char *pw) {
    if (value == r->val) {// if root id is same as new id function ends
        return;
    } else if (value > r->val) { //check if new id is larger than previous id
        if (r->right != NULL) add(r->right, value, pw); // check right pointer - recursive call function if right node not null
        else r->right = create_N(value, pw); // create new node if right child points nothing
    } else if (value < r->val) { //check if new id is smaller than previous id
        if (r->left != NULL) add(r->left, value, pw); // check left pointer - recursive function call
        else r->left = create_N(value, pw);// new node if left child points to nothing
    }
}
// function to return max value
int max(int a, int b) {
    if (a > b) {
        return a;
    }
    else return b;
}
// function to find tree height
int height(pn root) {
    int max_h;
    if (root == NULL) return -1;
    else max_h = 1 + ((height(root->right) > height(root->left)) ? height(root->right) : height(root->left));
    return max_h;
}
// print tree in order
void in(pn root) {
    if (root->left != NULL) in(root->left); //recursive call left child
    printf("%d ,", root->val);
    if (root->right != NULL) in(root->right); //recursive call right child
}
// print tree pre order
void pre(pn root) {
    printf("%d ,", root->val);
    if (root->left != NULL) pre(root->left); // recursive left node
    if (root->right != NULL) pre(root->right); //recursive right node

// print tree in post order
void post(pn root) {
    if (root->left != NULL) post(root->left); //recursive left node call
    if (root->right != NULL) post(root->right); //recursive right node call
    printf("%d ,", root->val);
}

// checks the validity of the tree
int valid(pn root) {
    int L = 0;
    int R = 0;
    //iterate through left
    if (root->left != NULL) {
        if (root->left->val > root->val) L = -1;
        else L = valid(root->left);
    }
    //iterate through right
    if (root->right != NULL) {
        else R = valid(root->right);
    }
    if (L == -1 || R == -1)
        return -1;
    else return 1;
}
//counts the number of nodes in the tree
int count(pn root) {
    int sum;
    if (root == NULL) return 0;//break if tree is empty
    sum = 1 + count(root->left) + countNodes(root->right);// recusively sums through tree
    return sum;
}
//function to find a node
pn find(pn root, int i) {
    if (root == NULL) return NULL; // break if root is null -- no tree
    if (root->val == i) return root; // found node
    else if (root->val > i) find(root->left, i);// check left with recursive
    else if (root->val < i) find(root->right, i); // check right with recursive call
}
// function to find a parent node
pn find_parent(pn root, int i) {
    if (root == NULL) return root; //if root is null tree is empty -- returns the root
    if (root->val == i) return root; // found parent
    if ((root->left == NULL) && (root->right == NULL)) return root;  //check for children
    else if (root->val > i) {
        if (root->left->val == i) return root;// check left
        else find_parent(root->left, i);// recursive left call
    } else if (root->val < i) {
        if (root->right->val == i) return root;// check right
        else find_parent(root->right, i); // recursive right call
    }
}

// function to delete a node
void delete(pn root, pn parent) {
    pn temp = root;
    if (root->left != NULL) delete(root->left, root);// check left child - delete
    if (root->right != NULL) delete(root->right, root);// check right child - delete
    if (parent->left == root) parent->left = NULL; // check parent left - set null if root
    if (parent->right == root) parent->right = NULL;// check parent right - set null if root
    free(temp);//
}

int main(void) {

    char *deletes = "DELETES.txt"; // open deletes file
    char *idents = "IDENTS.txt"; // open indents file
    char *lookups = "LOOKUPS.txt"; // open lookups file

    FILE *del = fopen(deletes, "r");// read delete file
    FILE *ide = fopen(idents, "r");// read intents file
    FILE *look = fopen(lookups, "r"); // read lookups file

    if (del == NULL) printf("ERROR - File could not open %s\n", deletes);    //gives error if delete file cannot be found
    if (ide == NULL) printf("ERROR - FIle could not open %s\n", idents);    //gives error if indents file cannot be found
    if (look == NULL) printf("ERROR - File could not open %s\n", lookups);    //gives error if lookups file cannot be found

    //traverse files to separate integers and characters
    int user;
    char *pswrd = (char *) malloc(8 * sizeof(char));
    pswrd[7] = '\0';
    // scan inputs for indents user and the password
    fscanf(ide, "%d %s", &user, pswrd);
    // call the create tree function with the inputted data
    pt tree = create_T(user, passwrd);

    while (1) {
        int id;
        char *pw = (char *) malloc(8 * sizeof(char));
        pw[7] = '\0';
        // scan inputs for indents user and the password
        if (fscanf(ide, "%d %s", &id, pw) == EOF) break;// break at the end of data
        // add to tree using add function
        add(tree->root, id, pw);
    }
    // printing outputs
    printf("BST NODES: %d\n", countNodes(tree->root)); // # of nodes
    if (valid == -1) exit(1);// exit if invalid tree

    while (1) {
        int id;
        // scanning data
        if (fscanf(del, "%d", &id) == EOF) break; // break at end of data
        pn n = find(tree->root, id); // use node finder
        pn p = find_parent(tree->root, id); // use parent node finder
        delete(n, p);// calling the delete funciton
    }
    printf("NODES AFTER DELETES: %d\n", countNodes(tree->root));
    if (valid == -1) exit(1);// exit if invalid tree
    while (1) {
        int id;
        if (fscanf(look, "%d", &id) == EOF) break;// break at end of data
        pn n = find(tree->root, identification); // use node finder function
        if (n->pswrd != NULL) printf("ID %d   PASSWORD %s\n", n->val, n->pswrd);// print id & passwords
        else printf("ID %d   PASSWORD <NOT FOUND>", n->val); // print if password cannot be found
    }
}