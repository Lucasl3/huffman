#include "trie.h"
int main(){
    trie *trie = create_empty_trie('*');
    char str[50];
    int option;
    while(1){
        printf("[1] Adicionar palavra\n[2] Procurar sugestao \n[3] Apagar palavra \n[4] Sair \n");
        scanf("%d", &option);
        if(option == 1){
            printf("Digite a palavra a ser inserida: ");
            scanf("%s", str);
            insert(trie, str);
            printf("\n");
        } else if(option == 2){
            printf("Digite o prefixo ou palavra a ser procurada: ");
            scanf("%s", str);
            search(trie, str);
            printf("\n");
        } else if(option == 3){
            printf("Digite a palavra a ser apagada: ");
            scanf("%s", str);
            remove_from_trie(trie, str);
            printf("\n");
        } else{
            printf("Encerrando...\n");
            return 0;
        }
    }
}