#include "trie.h"

int alpha_key(char character){
    int key = character;
    return key % 97;
}
trie *create_empty_trie(char def){
    trie *new_trie = (trie*) malloc(sizeof(trie));
    new_trie->value = def;
    new_trie->previous = NULL;
    int i;
    for(i=0;i<ALPHABET_SIZE;i++){
        new_trie->itens[i] = NULL;
    }
    new_trie->isLeaf = FALSE;
}
void insert(trie *root, char *word){
    int i, index;
    trie *current = root;
    for(i=0;i<strlen(word);i++){
        index = alpha_key(word[i]);
        if(!current->itens[index]){
            current->itens[index] = create_empty_trie(word[i]);
        }
        current->itens[index]->previous = current;
        current = current->itens[index];
    }
    current->isLeaf = TRUE;
    printf("%s foi adicionado a trie\n", word);
}
int find_letter_index(trie *trie){
    int i;
    for(i=0;i<ALPHABET_SIZE;i++){
        if(trie->itens[i] != NULL){
            return i;
        }
    }
    return -1;
}
int search(trie *root, char *str){
    int level, index;
    trie *current = root;
    char wordSuggestion[30];
    for(level=0;level<strlen(str);level++){
        index = alpha_key(str[level]);
        if(!current->itens[index]){
            printf("Nenhuma sugestao encontrada\n");
            return -1;
        }
        current = current->itens[index];
    }
    int i = 0;
    while(!current->isLeaf){
        int letter_index = find_letter_index(current);
        if(letter_index == -1){
            printf("Nenhuma sugestao encontrada\n");
            return -1;
        }
        current = current->itens[letter_index];
        wordSuggestion[i++] = current->value;
    }
    wordSuggestion[i] = '\0';
    printf("%s%s\n", str, wordSuggestion);
    return 1;
}
int hasChild(trie *letter){
    int i;
    for(i=0;i<ALPHABET_SIZE;i++){
        if(letter->itens[i] != NULL){
            return TRUE;
        }
    }
    return FALSE;
}
int remove_from_trie(trie* root, char* word) {
    int level;
    int index;
    trie* current = root;
    for (level = 0; word[level] != '\0'; ++level){
        index = alpha_key(word[level]);
        if (!current->itens[index]){
            printf("Palavra nao existe na trie.\n");
            return -1;
        }
        current = current->itens[index];
    }
    if (!current->isLeaf){
        printf("Palavra nao existe na trie.\n");
        return -1;
    }
    current->isLeaf = FALSE;
    while (current->previous != NULL){
        if (!hasChild(current) && !current->isLeaf){
            int index = alpha_key(current->value);
            current = current->previous;
            if (current->itens[index]){
                free(current->itens[index]);
                current->itens[index] = NULL;
            }
        }
        else{
            current = current->previous;
        }
    }
    return 1;
}