//Bora Mutluoglu | bmutluog | 1564633 | cs12b | March 17, 2018 |
//Dictionary.c using a hash table implementation instead of the ADT
//or BST implementation
#include<stdio.h>
#include"Dictionary.h"



int main(int argc, char *argv[]) {
    Dictionary mydict = newDictionary();
    int empty = isEmpty(mydict);
    fprintf(stderr, "size = %d\n", size(mydict));
    if (empty){
        fprintf(stderr, "Dictionary is empty!\n");
    } else {
        fprintf(stderr, "Dictionary is NOT empty!\n");
    }

    char *hey = "Hey";
    insert(mydict, hey, "It Works!");
    fprintf(stderr, "size =%d\n", size(mydict));
    int empty2 = isEmpty(mydict);
    if (empty2){
        fprintf(stderr, "Dictionary is empty!\n");
    } else {
        fprintf(stderr, "Dictionary is NOT empty!\n");
    }

    find(mydict, "as");
    lookup(mydict, "as");
    insert(mydict, "as", "thing");
    printDictionary(stderr, mydict);

    insert(mydict, "a", "thing");
    insert(mydict, "another", "thing");

    delete(mydict, "a");

    char *itworks = lookup(mydict, hey);
    fprintf(stderr, "%s\n", itworks);

    freeDictionary(mydict);

//    struct NodeObj *mynode = newNode("a", "b");
//    free(mynode);
    return  0;
}
