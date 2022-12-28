// Robb, Ashley 20203465
// ELEC 278 Assignment 3 Question 2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// defining node structure
typedef struct node {
    int val, key;
    struct node* prev;
    struct node* next;
}Node, * LL;

// liked list structure
typedef struct {
    LL hold;
    LL* next;
}hash_table;

// cache hash structure
typedef struct {
    int limit, size;
    hash_table* table;
    LL head, tail;
}fast_cache;

// mapping the function
hash_table* map(hash_table* table, int key, int max) {
    int i = key % max;
    return &table[i];
}

//inserting node at head of structure
void insert_at_head(LL head, LL here){
    LL first = head->next;
    if (here->next == NULL && here->prev == NULL){ // locating the head

        here->prev = head;
        here->next = head->next;

        head->next->prev = here;
        head->next = here;
    }
    else if (first != here){ //updating structure

        here->next->prev = here->prev;
        here->prev->next = here->next;

        here->next = first;
        here->prev = head;

        head->next = here;
        first->prev = here;
    }
}


fast_cache* Cache(int max) {
    // determining sizes of  structures
    int hash_size = sizeof(hash_table);
    int fast_size = sizeof(fast_cache);
    int node_size = sizeof(Node);
    //setting the structure
    fast_cache* item = (fast_cache*)malloc(fast_size);
    item->size = 0;
    item->limit = max;
    item->table = (hash_table*)malloc(max * hash_size);
    // allocating head and tail memory
    item->tail = (LL)malloc(node_size);
    item->head = (LL)malloc(node_size);
    // assigning head and tail next and prev
    item->tail->prev = item->head;
    item->head->next = item->tail;
    // node previous to head and after tail are null
    item->head->prev = NULL;
    item->tail->next = NULL;
    //copying values
    memset(item->table, 0, max * hash_size);
    return item;
}

int Get(fast_cache* item, int key) { // function to GET an item from the cache
    hash_table* i = map(item->table, key, item->limit);
    if (i->next == NULL) { // check for valid node creation
        return -1;
    }
    i = i->next; // traverse through list
    while (i->hold->key != key && i->next != NULL) {
        i = i->next;
    }
    if (i->hold->key == key){ // return desired value
        insert_at_head(item->head, i->hold);
        return i->hold->val;
    }
    return -1;
}

void Put(fast_cache* item, int key, int value) { // add or PUT a value in the cache
    hash_table *i = map(item->table, key, item->limit); // implementing new hash
    if (Get(item, key) == -1) // check for proper definition
    {
        if (item->size >= item->limit) // traverse item within limit
        {
            LL rear = item->tail->prev->prev;
            LL temp1 = rear->next;

            rear->next = item->tail;
            item->tail->prev = rear;

            hash_table *temp2 = map(item->table, temp1->key, item->limit);
            hash_table *temp_helper = temp2;
            temp2 = temp2->next;

            while (temp2->hold->key != temp1->key) { // check for temp1 temp2 overlap
                temp_helper = temp2;
                temp2 = temp2->next;
            }
            temp_helper->next = temp2->next; // adjust and free temp vals
            temp2->hold = NULL;
            temp2->next = NULL;
            free(temp2);

            hash_table *i2 = (hash_table *) malloc(sizeof(hash_table)); // define new i
            i2->next = i->next;
            i->next = i2;
            i2->hold = temp1;
            temp1->key = key;
            temp1->val = value;
            insert_at_head(item->head, temp1);
        } else {
            hash_table *insert = (hash_table *) malloc(sizeof(hash_table)); // node creation
            insert->hold = (LL) malloc(sizeof(Node)); // memory allocation
            // pointer assignments
            insert->next = i->next;
            i->next = insert;
            insert->hold->prev = NULL;
            insert->hold->next = NULL;
            insert->hold->val = value;
            insert->hold->key = key;
            insert_at_head(item->head, insert->hold);
            (item->size)++;
        }
    } else {
        item->head->next->val = value; // pointer adjust
    }
}// put

void results(int j){ // function to print results as their value or (not found)
    if (j == -1)
        printf("\n(not found)");
    else printf("\n%d",j);
}


void main() { // calling put and calling get within results for printing
    printf("ROBB ASHLEY\nELEC 278 FALL 22\nASSIGNMENT 3: QUESTION 2\n\n");

    fast_cache* cache = Cache(2);
    Put(cache, 1, 10);
    Put(cache, 2, 20);
    results(Get(cache, 1));
    Put(cache, 3, 30);
    results(Get(cache, 2));
    Put(cache, 4, 40);
    results(Get(cache, 1));
    results(Get(cache, 3));
    results(Get(cache, 4));
    Put(cache, 5, 50);
    printf("\n");
}
