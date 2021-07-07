//Bora Mutluoglu | bmutluog | 1564633 | cs12b | March 17, 2018 |
//Dictionary.c using a hash table implementation instead of the ADT
//or BST implementation
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Dictionary.h"

//const int TABLESIZE = 180;
// for you need a constant here and based on what I saw 'const' doesnt mean that it is a C 'constant'
// https://stackoverflow.com/questions/2308194/shall-i-prefer-constants-over-defines/2308364#2308364
// I set the tablesize to 3 so we can test chaining
#define TABLESIZE 3

// TODO you should define the structs in the header file so they are easy to use later
// NodeObj
struct NodeObj{
    char* key;
    char* value;
    struct NodeObj* next;
    struct NodeObj* prev;
} NodeObj;

// Node

// newNode()
// constructor of the Node type
struct NodeObj* newNode(char* k, char* v) {
    struct NodeObj* N = (struct NodeObj*) calloc(1,sizeof(NodeObj));
//    N->key = calloc(strlen(k)+1, sizeof(char));
//    N->value = calloc(strlen(v)+1, sizeof(char));
//    this memory was already allocated with the calloc call
    N->key = k;
    N->value = v;
    return(N);
}

// freeNode()
// destructor for the Node type
int freeNode(struct NodeObj* pN){
    int n_nodes = 0;
    if(pN != NULL){
        struct NodeObj* next_node = pN->next;
        free(pN);
        n_nodes++;
        while (next_node != NULL){
            struct NodeObj* next_next = next_node->next;
            free(next_node);
            n_nodes++;
            next_node = next_next;
        }
    }
    return n_nodes;
}



// DictionaryObj
struct DictionaryObj{
    struct NodeObj* root;
    struct NodeObj* table[TABLESIZE];
    int numPairs;
} DictionaryObj;


// public functions -----------------------------------------------------------

// newDictionary()
// constructor for the Dictionary type
Dictionary newDictionary(void){
    Dictionary D = calloc(1, sizeof(DictionaryObj)); //allocate mem of size 1 dict
    D->root = D->table[0];
    D->numPairs = 0;
    return D;
}

// freeDictionary()
// destructor for the Dictionary type
//void freeDictionary(Dictionary pD){
//    if(pD!=NULL){
//        if( !isEmpty(pD) ) makeEmpty(*pD);
//        //free(*pD->table);
//        free(*pD);
//        *pD = NULL;
//    }
//}

void freeDictionary(Dictionary pD){
    if(pD!=NULL){
        if( !isEmpty(pD) ){
            makeEmpty(pD);
        }
        free(pD);
    }
}

// makeEmpty()
// re-sets D to the empty state.
// pre: none
void makeEmpty(Dictionary D){
    //setting top/bot to NULL and items to zero empties the Dictionary
    int counter = 0;
    int num_elements = 0;
    while(num_elements < D->numPairs){
        if (D->table[counter] != NULL){

            int nodes_deconstructed = freeNode(D->table[counter]);
            D->table[counter] = NULL;
            num_elements += nodes_deconstructed;
        }
        counter++;
    }
    D->numPairs = 0;

}


// rotate_left()
// rotate the bits in an unsigned int
unsigned int rotate_left(unsigned int value, int shift) {
    int sizeInBits = 8 * sizeof(unsigned int);
    shift = shift & (sizeInBits - 1);  // remainder of shift on division by sizeInBits
    if ( shift == 0 )
    return value;
    else
    return (value << shift) | (value >> (sizeInBits - shift)); // perform rotation
}

// pre_hash()
// turn a string into an unsigned int
unsigned int pre_hash(char* input) {  // input points to first char in string
    unsigned int result = 0xBAE86554;  // = 10111010111010000110010101010100
    while (*input) {                   // while *input is not '\0' (not end of string)
        result ^= *input++;                // result = result ^ *input (current char alters result)
        // input++  (go to next char)
        result = rotate_left(result, 5);   // rotate result by fixed amount
    }
    return result;  // result is now a random looking bit pattern depending on input string
}

// hash()
// turns a string into an int in the range 0 to tableSize-1
int hash(char* key){
//   This also needs to be unsigned because you are converting an unsigned int to int so it could become negative
    unsigned int a = pre_hash(key);
    a = a%(TABLESIZE);
    return a;
}
// isEmpty()
// returns 1 (true) if S is empty, 0 (false) otherwise
// pre: none
int isEmpty(Dictionary D){
    //if the Dictionary is NULL throw the error
    if( D==NULL ){
        fprintf(stderr,
                "Dictionary Error: calling isEmpty() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    //if the number of items in the Dictionary is zero return true else return
    //false
    if(D->numPairs==0){
        return 1;
    }
    return 0;
}


// find()
// returns a reference to the Node at position index in this Hash Dictionary
struct NodeObj* find(Dictionary D, char* k){
    //while N does not equal null continue through the dictionary until the wanted key is found
    int hashkey = hash(k);
    if(D->table[hashkey] == NULL)
        return NULL;
    if(D->table[hashkey]->key == k)
        return D->table[hashkey];
    if(D->table[hashkey]->next == NULL)
        return NULL;
    else {
        struct NodeObj* node = D->table[hashkey]->next;

        while(node != NULL)
        {
            if(node->key == k)
                return node;
            if(node->next == NULL)
                return NULL;
            else{
                node = node->next;
            }
        }
        return NULL;

    }
}

// size()
// returns the number of (key, value) pairs in D
// pre: none
int size(Dictionary D){
    if( D == NULL){
        fprintf(stderr, "Dictionary Error: calling size() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    return D->numPairs;
}

// lookup()
// returns the value v such that (k, v) is in D, or returns NULL if no
// such value v exists.
// pre: none
char* lookup(Dictionary D, char* k){
    //if the Dictionary is NULL throw an error
    if( D == NULL ){
        fprintf(stderr, "Dictionary Error: calling lookup() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    if(D->numPairs == 0)
        return NULL;

    //initialize N the key to be found so the corresponding value can be found
    struct NodeObj* N = find(D, k);
    if (N == NULL){
        return NULL;
    } else{
        return N->value;
    }
}

// insert()
// inserts new (key,value) pair into D
// pre: lookup(D, k)==NULL
void insert(Dictionary D, char* k, char* v){
    //@TODO: check if either pointer is null (empty)
    //int kWords = sizeof(k) / sizeof(k[0]);
    //int vWords = sizeof(v) / sizeof(v[0]);
    if(D == NULL){
        fprintf(stderr, "Dictionary Error: cannot call insert on a NULL Dictionary");
        exit(EXIT_FAILURE);
    }
    //intialize a new Node object if current node is empty
    struct NodeObj* N = newNode(k, v);
    D->numPairs++;
    int hashIndex = hash(k);

    struct NodeObj* node = D->table[hashIndex];
    if (node != NULL){
        for (int i =0; i< D->numPairs; i++)
        {
            if(node->key == k){
                // this should never happen
                fprintf(stderr, "Dictionary Error: cannot insert duplicate keys\n");
                exit(EXIT_FAILURE);
            }
            if(node->next == NULL){
                node->next=N;
                N->prev=node;
                break;
            }
            else{
                struct NodeObj* node2 = node->next;
                node = node2;
            }
        }

    } else {
        D->table[hashIndex] = N;
    }
}

// delete()
// deletes pair with the key k
// pre: lookup(D, k)!=NULL
void delete(Dictionary D, char* k){
    //if the key is not found in the Dictionary then exit
    if (lookup(D,k)==NULL){
        fprintf(stderr, "Dictionary error: cannot delete non-existent key\n");
        exit(EXIT_FAILURE);
    }
    //if the current key in the dictionary does not match the key we are looking
    //for, move on.
//    Find node, delete after reconnecting nodes
//    recreate connection between linked list
//    this is pretty hacky and there should be functions for all these linked list operations
    struct NodeObj* node = find(D, k);
    if (node->next != NULL || node->prev != NULL){
        struct NodeObj* prev_node = node->prev;
        struct NodeObj* next_node = node->next;

        if (prev_node != NULL){
            if (next_node != NULL) {
                prev_node->next = node->next;
                node->next->prev = prev_node;
            } else {
                prev_node->next = NULL;
            }
        } else {
            D->table[hash(k)] = next_node;
        }
    } else {
        D->table[hash(k)] = NULL;
    }
    free(node);
    D->numPairs--;
}

// makeEmpty()
// re-sets D to the empty state.
// pre: none
//void makeEmpty(Dictionary D){
//    //setting top/bot to NULL and items to zero empties the Dictionary
//    int counter = 0;
//    while(&(D->table[counter]) != NULL && counter < D->numPairs){
//        struct NodeObj* N;
//        *N = *D->table[counter];
//        freeNode(N);
//        N = NULL;
//        counter++;
//    }
//    D->numPairs = 0;
//
//}

void printDictionary(FILE* out, Dictionary D){
    if(D==NULL){
        fprintf(stderr, "Dictionary Error: printDictionary() called on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    for(int i =0; i< TABLESIZE; i++){
//        BORA: you were reassigning each value during that while loop so basically you assign values to NULL
        if (D->table[i] != NULL){
            fprintf(out, "%s %s \n" , D->table[i]->key, D->table[i]->value);
            struct NodeObj* node = D->table[i]->next;
//            check the chained dictionary
            while (node != NULL) {
                fprintf(out, "%s %s \n" , node->key, node->value);
                struct NodeObj* node2 = node->next;
                node = node2;
            }
        }
    }
}


