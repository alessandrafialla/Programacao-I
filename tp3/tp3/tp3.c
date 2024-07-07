/* Arquivo MAIN que usa o TAD racionais */

#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

/* Elimina valores invalidos substituindo pelo ultimo valor do vetor */
/* Modifica o valor de n que representa o tamanho do vetor           */
void elimina_invalidos(struct racional **v, int *n)
{
    int i;

    /* Percorre o vetor trocando o valor invalido com valor da ultima posicao*/
    for (i = 0; i < (*n); i++)
    {
        if (!valido_r(v[i]))
        {
            *v[i] = *v[(*n) - 1];
            destroi_r(&v[(*n) - 1]); // destroi e aterra a ultima pos
            (*n)--;
            i--; // decrementa i para testar o substituto
        }
    }
}

/* Imprime todos os racionais do vetor                  */
void imprime_vetor_racionais(struct racional **v, int n)
{
    int i;

    if (n < 1){
        printf("\n");
        return;
    }

    /* Imprime os racionais contidos no vetor*/
    for (i = 0; i < n; i++)
    {
        imprime_r(v[i]);
        printf(" ");
    }
    printf("\n");
}

/* Ordena o vetor                              */
void selection_sort(struct racional **v, int n)
{
    int menor, i, j;
    struct racional *aux;

    /*Considera o primeiro elemento do vetor como menor*/
    for (i = 0; i < n; i++)
    {
        menor = i;

        /*Verifica indice do menor valor do vetor*/
        for (j = i + 1; j < n; j++)
        {
            if (compara_r(v[menor], v[j]) == 1)
            {
                menor = j;
            }
        }
        /* Ordena a posicao i do vetor */
        aux = v[menor];
        v[menor] = v[i];
        v[i] = aux;
    }
}

int main()
{

    /* vetor de ponteiros para racionais */
    struct racional **v; /* equivalente a struct racional *v[] */
    struct racional *soma;
    int n, i, j, k;
    long int num, den;

    /* 0 < n < 100 */
    scanf("%d", &n);

    /* Aloca dinamicamente um vetor[n] de ponteiros para numeros racionais */
    v = (struct racional **)malloc(n * sizeof(struct racional *));

    if (v == NULL)
        return 1;

    /* Inicializa vetor com valores do teclado */
    for (i = 0; i < n; i++)
    {
        scanf("%ld %ld", &num, &den);
        v[i] = cria_r(num, den);
    }

    imprime_vetor_racionais(v, n); // imprime vetor atual
    
    elimina_invalidos(v, &n);

    imprime_vetor_racionais(v, n); // vetor sem invalidos

    selection_sort(v, n);

    imprime_vetor_racionais(v, n);

    if (n > 0){ //se nao vazio a soma inicia com primeiro valor do vetor
        soma = cria_r(numerador_r(v[0]), denominador_r(v[0]));

        /*Soma todos os elementos*/
        for (j = 1; j < n; j++)
        {
            struct racional *nova_soma;
            nova_soma = soma_r(v[j], soma);
            destroi_r(&soma);
            soma = nova_soma;
        }
    }
    else{  //se vetor estiver vazio cria soma com valor zero
        soma = cria_r(0, 0);
    }

    printf("a soma de todos os elementos eh: ");
    imprime_r(soma);
    printf("\n");

    /*Destroi elementos*/
    destroi_r(&soma);

    for (k = 0; k < n; k++)
        destroi_r(&v[k]);
    
    free(v);

    return 0;
}