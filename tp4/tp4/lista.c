#include "lista.h"
#include <stdlib.h>
/* coloque demais includes aqui */

struct lista *lista_cria (){

    struct lista *l = (struct lista *) malloc(sizeof(struct lista));

    if (l == NULL)
        return NULL;
    
    /*Inicializa os nodos e tamanho com NULL*/
    l->ini = NULL;
    l->ptr =NULL;
    l->tamanho = 0;

    return l;
}
/*
void lista_destroi (struct lista **lista){
}
*/
int lista_insere_inicio (struct lista *lista, int chave){
    struct nodo *novo;

    novo = (struct nodo *) malloc(sizeof(struct nodo));

    if(novo == NULL)
        return 0;

    novo->chave = chave;

    if(lista_vazia(lista)){
        novo->prox = NULL;
        lista->ini = novo;
        lista->ptr = NULL;
        lista->tamanho = 1;
    }
    else {
        novo->prox = lista->ini;
        lista->ini = novo;
        (lista->tamanho)++;
    }
    return 1;
}
/*
int lista_insere_fim (struct lista *lista, int chave){
}

int lista_insere_ordenado (struct lista *lista, int chave){
}
*/
int lista_remove_inicio (struct lista *lista, int *chave){
    struct nodo *n;

    if (lista_vazia(lista)){
        return 0;
    }
    else {
        *chave = lista->ini->chave;
        n = lista->ini->prox; /*salva o segundo elemento da lista*/
        free(lista->ini);
        lista->ini = n;
    }
    return 1;
}

/*
int lista_remove_fim (struct lista *lista, int *chave){
}

int lista_remove_ordenado (struct lista *lista, int chave){
}
*/
int lista_vazia (struct lista *lista){
    return (lista->ini == NULL);
}
/*
int lista_tamanho (struct lista *lista){
    return lista->tamanho;
}

int lista_pertence (struct lista *lista, int chave){
}
*/

void lista_inicia_iterador (struct lista *lista){
    lista->ptr = lista->ini;
}

int lista_incrementa_iterador (struct lista *lista, int *chave){
    if(lista->ptr == NULL)
        return 0;
    else {
        *chave = lista->ptr->chave;
        lista->ptr = lista->ptr->prox;
    }
    return 1;
}