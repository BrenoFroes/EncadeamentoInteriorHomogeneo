#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct no {
    int dado;
    struct no *prox;
} No;

/* Cria uma lista vazia */
No *criaLista() {
    No *novo = (No *)malloc(sizeof(No));
    novo->dado = 0;
    novo->prox = novo;
    return novo;
}

/* Verifica se a lista é vazia */
int vazia(No **l) {
    if ((*l)->dado == 0)
        return 1;
    else
        return 0;
}

/* Verifica se a tabela está cheia */
int cheia(No *tabela[40]){
    int flag = 1; // 1 representa tabela cheia
    for(int i = 0; i<40; i++){
        if(tabela[i]->dado == 0){
            flag = 0;
            return flag;
        }
    }
    return flag;
}

/* Insere nó com colisão */
void colisao(No **tabela, No *n){
    if(cheia(tabela) == 0){
        for(int i = 40; i>=0; i--){
            if(tabela[i]->dado == 0){
                tabela[i]->prox = n;
                tabela[i]->dado++;
                break;
            }
        }
    }else{
        printf("Overflow");
        exit(0);
    }
}

/* Insere novo nó na lista */
void insereFim(No **tabela, No **l, int valor) {
    No *novo = (No *)malloc(sizeof(No));
    novo->dado = valor;
    if (vazia(l) == 1) {
        (*l)->prox = novo;
        novo->prox = *l;
        (*l)->dado++;
    } else if ((*l)->dado == 1) {
        (*l)->prox->prox = novo;
        novo->prox = *l;
        (*l)->dado++;
        colisao(tabela, novo);
    } else {
        No *aux = *l;
        do {
            aux = aux->prox;
        } while (aux->prox != *l);
        aux->prox = novo;
        novo->prox = *l;
        (*l)->dado++;
        colisao(tabela, novo);
    }
}

/* Remove nó da lista */
void remover(No **l, int valor){
    No *aux = (*l)->prox;
    if(vazia(l) == 1){
        printf("Lista vazia\n");
    }else if((*l)->dado == 1){

        free(aux);
        (*l)->dado--;
    }else{
        No *aux = (*l)->prox;
        No *aux2 = *l;
        while(aux->prox != NULL){
            if(aux->dado == valor) break;
            aux2 = aux;
            aux = aux->prox;
        }
        if(aux->prox == NULL){
            aux2->prox = NULL;
        }else{
            aux2->prox = aux->prox;
        }
        free(aux);
        (*l)->dado--;
    }
}

/* Imprime a tabela */
void imprime(No *tabela[40]) {
    for(int i = 0; i<40; i++){
        if(i < 5){
            printf("%d - %d\n", i, tabela[i]->prox->dado);
            printf("________\n");// MF //
        }
        else{
            printf("%d\n", tabela[i]->prox->dado);
            printf("_____\n"); // MF //
        }

    }
}

/* Insere um novo numero na tabela */
void insereNumero (No *tabela[40], int n){
    int chave = n%5;
    insereFim(tabela, &tabela[chave], n);
}

/* Remove um numero da tabela */
void removeNumero(No *tabela[40], int n){
    int chave = n%5;
    remover(&tabela[chave], n);
}

int main(void) {
    No* tabela [40] ;
    int x;
    for(int i = 0; i<40; i++){
        tabela[i] = criaLista();
    }
    /* srand(time(NULL)); /* essa linha permite que a cada "run" sejam gerados números diferentes, caso queira os mesmos aleatórios sempre só deletá-la */
    for (int i=0; i<40; i++){
        insereNumero(tabela, rand ()%100);
    }
    /*insereNumero(tabela, 7);
    insereNumero(tabela, 14);
    insereNumero(tabela, 42);
    insereNumero(tabela, 32);
    insereNumero(tabela, 4);
    insereNumero(tabela, 9);
    insereNumero(tabela, 22);
    insereNumero(tabela, 12);
    insereNumero(tabela, 32);
    insereNumero(tabela, 32);
    insereNumero(tabela, 32);*/


    imprime(tabela);
    removeNumero(tabela, 11);
    imprime(tabela);
    return 0;

}

// modificado = MF //
// OBS: TODOS OS VALORES IGUAIS A 10 FORAM SUBSTITUÍDOS POR 40 //
