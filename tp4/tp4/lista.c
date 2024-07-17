#include "lista.h"
#include <stdlib.h>

struct lista *lista_cria()
{
    struct lista *l = (struct lista *)malloc(sizeof(struct lista));

    if (l == NULL)
        return NULL;

    /* Inicializa os nodos e tamanho com NULL*/
    l->ini = NULL;
    l->ptr = NULL;
    l->tamanho = 0;

    return l;
}

void lista_destroi(struct lista **lista)
{
    struct nodo *aux, *temp;

    /* Se a lista for vazia */
    if (*lista == NULL)
        return;

    aux = (*lista)->ini;

    /* Percorre a lista e libera cada nodo */
    while (aux != NULL)
    {
        temp = aux;
        aux = aux->prox;
        free(temp);
    }

    /* Libera a estrutura da lista */
    free(*lista);
    *lista = NULL;
}

int lista_insere_inicio(struct lista *lista, int chave)
{
    struct nodo *novo;

    novo = (struct nodo *)malloc(sizeof(struct nodo));

    if (novo == NULL)
        return 0;

    novo->chave = chave;

    if (lista_vazia(lista))
        novo->prox = NULL;
    else {
        novo->prox = lista->ini;
    }
    lista->ini = novo;
    (lista->tamanho)++;
    return 1;
}

int lista_insere_fim(struct lista *lista, int chave)
{
    struct nodo *novo;
    struct nodo *aux;

    /* Se a lista estiver vazia insere no inicio*/
    if (lista_vazia(lista))
    {
        lista_insere_inicio(lista, chave);
        return 1;
    }

    novo = (struct nodo *)malloc(sizeof(struct nodo));

    if (novo == NULL)
        return 0;

    novo->chave = chave;
    novo->prox = NULL;

    aux = lista->ini; 
    while (aux->prox != NULL) /* Percorre ate chegar no ultimo atual*/
        aux = aux->prox;

    aux->prox = novo; 
    (lista->tamanho)++;
    return 1;
}

int lista_insere_ordenado(struct lista *lista, int chave)
{
    struct nodo *novo, *aux;

    /* Se a lista estiver vazia insere no inicio*/
    if (lista_vazia(lista))
        return lista_insere_inicio(lista, chave);

    novo = (struct nodo *)malloc(sizeof(struct nodo));

    if (novo == NULL)
        return 0;

    /* Se o novo elemento deve ser inserido antes do primeiro elemento*/
    if (lista->ini->chave >= chave)
    {
        novo->chave = chave;
        novo->prox = lista->ini;
        lista->ini = novo;
        return 1;
    }

    aux = lista->ini;

    /* Encontra a posição correta para inserir o novo nodo*/
    while (aux->prox != NULL && aux->prox->chave <= chave)
    {
        aux = aux->prox;
    }

    novo->chave = chave;
    novo->prox = aux->prox;
    aux->prox = novo;
    return 1;
}

int lista_remove_inicio(struct lista *lista, int *chave)
{
    struct nodo *aux;

    if (lista_vazia(lista))
        return 0;
    
    *chave = lista->ini->chave;
    aux = lista->ini->prox; /* salva o segundo elemento da lista*/
    free(lista->ini);
    lista->ini = aux;
    (lista->tamanho)--;
    return 1;
}

int lista_remove_fim(struct lista *lista, int *chave)
{
    struct nodo *aux;

    if (lista_vazia(lista))
        return 0;

    /* Se a lista tiver apenas 1 elemento*/
    if (lista->ini->prox == NULL)
    {
        *chave = lista->ini->chave;
        free(lista->ini);
        lista->ini = NULL;
        return 1;
    }

    aux = lista->ini;

    while (aux->prox->prox != NULL) /* Percorre ate achar o ultimo*/
        aux = aux->prox;

    *chave = aux->prox->chave;
    free(aux->prox);
    aux->prox = NULL;
    (lista->tamanho)--;
    return 1;
}

int lista_remove_ordenado(struct lista *lista, int chave)
{
    struct nodo *aux, *anterior;

    if (lista_vazia(lista))
        return 0;

    aux = lista->ini;

    /* Se o primeiro elemento eh o desejado*/
    if (aux->chave == chave)
    {
        lista->ini = aux->prox;
        free(aux);
        lista->tamanho--;
        return 1;
    }

    /* Procura o elemento */
    while (aux != NULL && aux->chave != chave)
    {
        anterior = aux;
        aux = aux->prox;
    }

    anterior->prox = aux->prox;
    free(aux);
    lista->tamanho--;

    return 1;
}

int lista_vazia(struct lista *lista)
{
    return (lista->ini == NULL);
}

int lista_tamanho(struct lista *lista)
{
    return lista->tamanho;
}

int lista_pertence(struct lista *lista, int chave)
{
    struct nodo *aux;

    if ((lista_vazia(lista)))
        return 0;

    aux = lista->ini;

    /* Percorre ate chegar ao fim da lista ou achar o elemento*/
    while (aux->chave != chave && aux->prox != NULL)
        aux = aux->prox;

    /* Retorna 1 se encontrou e 0 se chegou ao fim sem encontrar*/
    return (aux->chave == chave);
}

void lista_inicia_iterador(struct lista *lista)
{
    lista->ptr = lista->ini;
}

int lista_incrementa_iterador(struct lista *lista, int *chave)
{
    if (lista->ptr == NULL) /* Lista vazia*/
        return 0;

    *chave = lista->ptr->chave;
    lista->ptr = lista->ptr->prox;
    return 1;
}
