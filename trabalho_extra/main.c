#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

#define MAX 100

void elimina_invalidos (v, n){
    int i;

    for (i = 0; i < n; i++){
        if ( !valido_r (v[i]){
                v[i] = v[n-1];
                n--; //decrementa tamanho do vetor
                i--; // decrementa i para testar o substituto
    }
}

void imprime_racionais (v, n){
    int i;

    /* Imprime os racionais contidos no vetor*/
    for (i = 0; i < n; i++){
        imprime_r(v[i]);
        if (i < n-1)
            printf (" ");
    }
    printf ("\n");
}

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
    
    /*Imprime racionais contidos no vetor*/
    imprime_racionais (v, n);
    elimina_invalidos (v, n);
    imprime_racionais (v, n);
    return 0;
}

