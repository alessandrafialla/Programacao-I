#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

#define MAX 100

/* Elimina valores invalidos substituindo pelo ultimo valor do vetor */
/* Modifica o tamanho de n                                           */
void elimina_invalidos (struct racional *v, int *n){
    int i;
    
    for (i = 0; i < (*n); i++){
        if ( !valido_r (v[i]) ){
                v[i] = v[(*n)-1]; //troca com o ultimo valor
                (*n)--; 
                i--; // decrementa i para testar o substituto
        }
    }
}

/* Imprime todos os racionais do vetor */
void imprime_vetor_racionais (struct racional *v, int n){
    int i;

    /* Imprime os racionais contidos no vetor*/
    for (i = 0; i < n; i++){
        imprime_r(v[i]);
        if (i < n-1) // nao imprime o espaco no ultimo elemento
            printf (" ");
    }
    printf ("\n");
}

/*Funcao principal*/
int main(){
    int n, i;
    int num, den;
    struct racional v[MAX];
    
    /* 0 < n < 100*/
    scanf("%d", &n);

    /* Carrega os n racionais para dentro do vetor*/
    for (i = 0; i < n; i++){
        scanf ("%d %d", &num, &den);
        v[i] = cria_r (num, den);
    }
    
    /*Imprime racionais contidos no vetor, elimina invalidos e imprime novamente*/
    imprime_vetor_racionais (v, n);
    elimina_invalidos (v, &n);
    imprime_vetor_racionais (v, n);

    return 0;
}

