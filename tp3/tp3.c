/* Arquivo MAIN que usa o TAD racionais */

#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

/* coloque funcoes desejadas aqui. 
 * Exemplo: ordenar, eliminar invalidos... */

/* Elimina valores invalidos substituindo pelo ultimo valor do vetor */
/* Modifica o valor de n que representa o tamanho do vetor           */
void elimina_invalidos (struct racional **v, int *n){
    int i;
   
    /* Percorre o vetor trocando o valor invalido com valor da ultima posicao*/
    for (i = 0; i < (*n); i++){
        if ( !valido_r (v[i]) ){
                v[i] = v[(*n)-1];
                destroi_r (&*v[(*n)-1]); //destroi e aterra a ultima pos
                (*n)--; 
                i--; // decrementa i para testar o substituto
        }
    }
}

/* Imprime todos os racionais do vetor */
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


int main (){

    /* vetor de ponteiros para racionais */
    struct racional **v;  /* equivalente a struct racional *v[] */
    int n, i;
    long int num, den;
    
    srand(0);

    /* 0 < n < 100 */
    scanf( "%d", &n);

    /*Aloca dinamicamente um vetor[n] de ponteiros para numeros racionais*/
    v = malloc ( n * sizeof(struct racional *)); 
    
    if (v == NULL)
        return 1;

    /*Inicializa vetor com valores do teclado*/
    for (i = 0; i < n; i++){
        scanf("%ld %ld", &num, &den);
        v[i] = cria_r (num, den);
    }

    imprime_vetor_racionais(v, n);
    elimina_invalidos (v, &n);
    imprime_vetor_racionais(v, n);
    return 0;
}
