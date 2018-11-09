#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct no {
    int dado;
    struct no *prox;
} No;

No *criaLista(){
    No *novo = (No *) malloc(sizeof (No));
    novo->prox = NULL;
    novo->dado = 0;
    return novo;
}

int vazia(No *tabela[40], int chave) {
    if (tabela[chave]->dado == 0 || tabela[chave]->dado == -1 ) return 1;
    else return 0;
}

int cheiaTabela(No *tabela[40]){
    int flag = 1;
    for (int i=0; i<40; i++){
        if (tabela[i]->dado == 0 || tabela[i]->dado == -1) {
            flag = 0;
        }
    }
    return flag;
}

int vaziaTabela(No *tabela[40]){
    int flag = 1;
    for (int i=0; i<40; i++){
        if(tabela[i]->dado  !=  0 && tabela[i]->dado != -1){
            flag = 0;
        }
    }
    return flag;
}

void colisao (No *tabela[40], int chave, No *n){
    No *aux = tabela[chave];
    while(aux->prox != NULL){
        if (aux->prox->dado == 0 || aux->prox->dado == 1){
            aux->prox = n;
            if(aux->prox->prox != NULL){
                n->prox = aux->prox->prox;
            }
        }
        aux = aux->prox;
    }
    if(aux->prox == NULL){
        aux->prox = n;
    }
    if(cheiaTabela(tabela) == 0){
        for(int i = 40; i>0; i--){
            if (tabela[i]->dado == 0 || tabela[i]->dado == -1){
                tabela[i] = n;
                return;
            }
        }
    }
    else {
        printf("____________________ \n");
        printf ("OVERFLOW \n\n");
        return;
    }
}

void inserir (No *tabela[40], int valor) {
    No *novo = (No *) malloc (sizeof (No));
    novo->dado = valor;
    novo->prox = NULL;
    int chave = valor%5;
    if (vazia(tabela, chave)  ==  0){
        if (cheiaTabela(tabela) == 1) {
            printf("____________________ \n");
            printf ("OVERFLOW\n\n");
            exit(0);
        }
        else{
            colisao(tabela, chave, novo);
        }
    }
    else{
        tabela[chave] = novo;

    }
}
int busca(No *tabela[40], int valor){
    int flag = 0;
    for(int i =0; i<40;i++){
        if(tabela[i]->dado == valor)
            flag = 1;
        int x = i;
    }
    return flag;
}

void remover (No *tabela[40], int valor){
    if (vaziaTabela(tabela) == 1){
        printf("____________________ \n");
        printf("UNDERFLOW \n\n");
    }
    else{
        if(busca(tabela, valor) == 0){
            printf("____________________ \n");
            printf("VALOR NÃO ENCONTRADO \n\n");
        }
        else{
            int chave = valor%5;
            No *aux = tabela[chave]->prox;
            No *aux2 = tabela[chave];
            if (aux2->dado == valor){
                aux2->dado = -1;
            }
            while (aux != NULL){
                if(aux->dado == valor){
                    aux->dado = -1;
                }
                aux2 = aux;
                aux = aux->prox;
            }
        }
    }
}

void imprimir (No *tabela[40]){
    printf("________________________ \n");
    printf("LISTA INTERIOR HOMOGÊNEA: \n \n");
    for(int i = 0; i < 40; i++){
        if(tabela[i]->dado == 0) printf ("[%d]-> CASA VAZIA\n", i);
        if(tabela[i]->dado == -1) printf ("[%d]-> CASA LIBERADA\n", i);
        else if(tabela[i]->dado != 0)printf ("[%d]-> %d\n", i, tabela[i]->dado);
    }
}
void imprimirLista(No *l, int i){
    printf("\nLISTA DA CASA %d\n",i);
    printf("__________________\n \n");
    No *aux = l;
    int cont = 0;
    while(aux != NULL){
        if(aux->dado == -1)
            printf("aux->dado: CASA LIBERADA\n");
        if(aux->dado == 0)
            printf("aux->dado: CASA VAZIA\n");
        else if(aux->dado != -1){
            printf("aux->dado: %d\n", aux->dado);
        }
        aux = aux->prox;
        cont++;
    }
    printf("Quantidade de itens nessa lista: %d\n", cont);
}


int main(void) {
    No *tabela [40];
    for(int i = 0; i<40; i++){
        tabela[i] = criaLista();
    }
    for (int i = 0; i<40;i++){
        inserir(tabela, rand() %100);
    }
    imprimir(tabela);
    int n, b;
    printf("Diga um valor para remoção: ");
    scanf("%d", &n);
    remover(tabela, n);
    printf("Diga um valor para busca: ");
    scanf("%d", &b);
    if (busca(tabela, b) == 1){
        printf("___________________ \n");
        printf("VALOR %d ENCONTRADO\n \n", b);
    }
    else{
        printf("______________________________\n");
        printf("VALOR NÃO ENCONTRADO NA TABELA\n\n");
    }

    imprimir(tabela);
    for (int i = 0; i<5; i++){
        imprimirLista(tabela[i], i);
    }
    return 0;
}