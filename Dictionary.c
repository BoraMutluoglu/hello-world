//Bora Mutluoglu | bmutluog | 1564633 | cs12b | March 17, 2018 |
//Dictionary.c using a hash table implementation instead of the ADT
//or BST implementation
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>
#include"Dictionary.h"

// NodeObj
const int tablesize = 180;
int items = 0;
struct NodeObj{
    char* key;
    char* value;
    struct NodeObj* next;
} NodeObj;

// Node

// newNode()
// constructor of the Node type
struct NodeObj* newNode(char* k, char* v) {
    struct NodeObj* N = calloc(1,sizeof(NodeObj));
    N->key = calloc(strlen(k)+1, sizeof(char));
    N->value = calloc(strlen(v)+1, sizeof(char));
    N->key = k;
    N->value = v;
    N->next = NULL;
    return(N);
}

// freeNode()
// destructor for the Node type
void freeNode(struct NodeObj** pN){
    if( pN!=NULL && *pN!=NULL ){
        free((*pN)->key);
        free((*pN)->value);
        free(*pN);
        *pN = NULL;
    }
}

// DictionaryObj
struct DictionaryObj{
    struct NodeObj* root;
    struct NodeObj* table[tablesize];
    int numPairs;
} DictionaryObj;
typedef struct DictionaryObj* Dictionary;


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
void freeDictionary(Dictionary* pD){
    if(pD!=NULL && *pD!=NULL ){
        if( !isEmpty(*pD) ) makeEmpty(*pD);
        //free(*pD->table);
        free(*pD);
        *pD = NULL;
    }
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
    int a = pre_hash(key);
     a = a%(tablesize);
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
    while(D->table[hashkey]!= NULL)
    {
        if(D->table[hashkey]->key == k)
            return D->table[hashkey];
        if(D->table[hashkey]->next == NULL)
            break;
        D->table[hashkey] = D->table[hashkey]->next;
    }
    return NULL;
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
    if(items == 0)
        return NULL;
    //if the Dictionary is NULL throw an error
    if( D==NULL ){
        fprintf(stderr, "Dictionary Error: calling lookup() on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    //initialize N the key to be found so the corresponding value can be found
    struct NodeObj* N = find(D, k);
    if (N == NULL){
        return NULL;
    }else{
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
    if (lookup(D, k) != NULL){
        fprintf(stderr, "Dictionary Error: cannot insert duplicate keys\n");
        exit(EXIT_FAILURE);
    }
    //intialize a new Node object if current node is empty
    struct NodeObj* N = newNode(k, v);
    D->numPairs++;
    items = D->numPairs;
    int hashIndex = hash(k);
    while(D->table[hashIndex] != NULL)
    {
        D->table[hashIndex] = D->table[hashIndex]->next;
    }
    D->table[hashIndex] = N;
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
    free(&D->table[hash(k)]);
    D->numPairs--;
    items--;
}

// makeEmpty()
// re-sets D to the empty state.
// pre: none
void makeEmpty(Dictionary D){
    //setting top/bot to NULL and items to zero empties the Dictionary
    int counter = 0;
    while(&(D->table[counter]) != NULL && counter < D->numPairs){
        struct NodeObj* N;
        *N = *D->table[counter];
        D->table[counter]=N->next;
        freeNode(&N);
        N = NULL;
        counter++;
    }
    D->numPairs = 0;
    
}

void printDictionary(FILE* out, Dictionary D){
    if(D==NULL){
        fprintf(stderr, "Dictionary Error: printDictionary() called on NULL Dictionary reference\n");
        exit(EXIT_FAILURE);
    }
    for(int i =0; i< tablesize; i++){
        while(D->table[i] != NULL){
            fprintf(out, "%s %s \n" , D->table[i]->key, D->table[i]->value);
            D->table[i] = D->table[i]->next;
        }
    }
}

