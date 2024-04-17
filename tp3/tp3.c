/* Arquivo MAIN que usa o TAD racionais */

#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"


/* Elimina valores invalidos substituindo pelo ultimo valor do vetor */
/* Modifica o valor de n que representa o tamanho do vetor           */
void elimina_invalidos (struct racional **v, int *n){
    int i;
   
    /* Percorre o vetor trocando o valor invalido com valor da ultima posicao*/
    for (i = 0; i < (*n); i++){
        if ( !valido_r (v[i]) ){
            *v[i] = *v[(*n)-1];
            destroi_r (&v[(*n)-1]); //destroi e aterra a ultima pos
            (*n)--; 
            i--; // decrementa i para testar o substituto
        }
    }
}

/* Imprime todos os racionais do vetor                  */
void imprime_vetor_racionais (struct racional **v, int n){
    int i;

    /* Imprime os racionais contidos no vetor*/
    for (i = 0; i < n; i++){
        imprime_r(v[i]);
        if (i < n-1) // nao imprime o espaco no ultimo elemento
            printf (" ");
        }
        printf ("\n");
    }

/* Ordena o vetor   */
void selection_sort (struct racional **v, int n){
    int menor, i;
    struct racional *aux;

    /*Considera o primeiro elemento do vetor como menor*/
    for(i = 0; i < n -1; i++){
        menor = i;

        /*Verifica indice do menor valor do vetor*/
        for (i = 1; i < n - 1; i++){
            if (compara_r(v[menor], v[i])  == 1){
                menor = i;
            }
         }
        /* Ordena a posicao i do vetor */
            aux = v[menor];
            v[menor] = v[i];
            v[i] = aux;
    }
}

/*int menor_indice (struct racional **v, n){
    if (n<= 1){
        return 0;
    }}*/
/*
void ordena_vetor(struct racional **v, int n){
    int menor, i;
    struct racional *aux;

*/

int main (){

    /* vetor de ponteiros para racionais */
    struct racional **v;  /* equivalente a struct racional *v[] */
    struct racional *soma;
    int n, i, j;
    long int num, den;  

    /* 0 < n < 100 */
    scanf("%d", &n);

    /* Aloca dinamicamente um vetor[n] de ponteiros para numeros racionais */
    v = malloc ( n * sizeof(struct racional *)); 
    
    if (v == NULL)
        return 1;

    /* Inicializa vetor com valores do teclado */
    for (i = 0; i < n; i++){
        scanf("%ld %ld", &num, &den);
        v[i] = cria_r (num, den);
    }

    imprime_vetor_racionais(v, n); //imprime vetor atual

    /*Elimina os valores invalidos e imprime*/
    elimina_invalidos (v, &n);
    imprime_vetor_racionais(v, n);

    /*Ordena vetor e imprime*/
    selection_sort(v, n);
    imprime_vetor_racionais(v, n);
    
    
    //soma = cria_r (0, 0); //aloca memoria para a soma e inicializa com 0

    if (n > 0){
        soma = v[0];

        for (j = 1; j < n; j++){
            soma = soma_r (v[j], soma);
        }
    }
    printf("a soma de todos os elementos eh: ");
    imprime_r(soma);
    printf("\n");
    destroi_r(&soma);


   /* printf("#####   TESTE DAS OPERACOES    #####\n");
    printf(" COMPARA \n");

    if (n > 1) {
    imprime_r(v[0]);
    printf(" ");
    imprime_r(v[1]);
    printf(" ");
    int compara = compara_r (v[0], v[1]);
    printf("%d\n", compara);
    }
    else printf ("vetor com n < 1\n");
    
    printf("\n");
    printf("\n");
    printf("SOMA\n");
    if(n > 1){
    struct racional *soma = soma_r (v[0], v[1]);
    imprime_r(soma);
    printf("\n");
    }
    
    */
    /*if (n <= 1)
        destroi_r(&soma);
    else {
        for (i = 0; i < n; i++)
            destroi_r(&v[i]);

        destroi_r(&soma);
    }
    free(v); */
    for (i = 0; i < n; i++){
            destroi_r(&v[i]);
        }
   /* if (n > 1)
        destroi_r(&soma);*/

    free(v);

    return 0;
}
