#ifndef trie_h
#define trie_h
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALPHABET_SIZE 26
#define FALSE 0
#define TRUE 1

typedef struct trie trie;
struct trie{
    char value;
    trie *itens[ALPHABET_SIZE];
    trie *previous;
    int isLeaf;
};

int alpha_key(char character);

trie *create_empty_trie(char father);

void insert(trie *root, char *word);

int find_letter_index(trie *trie);

int search(trie *root, char *str);

int hasChild(trie *letter);

int remove_from_trie(trie *root, char *word);

#endif