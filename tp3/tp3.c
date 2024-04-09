/* Arquivo MAIN que usa o TAD racionais */

#include <stdio.h>
#include <stdlib.h>
#include "racionais.h"

/* coloque funcoes desejadas aqui. 
 * Exemplo: ordenar, eliminar invalidos... */

int main (){
    /* vetor de ponteiros para racionais */
    struct racional **v;  /* equivalente a struct racional *v[] */
    int n;

    scanf( "%d", &n);
    srand( 0);

    for (int i = 0; i < n; i++){
        *v[i] = cria_r(

    /* coloque seu codigo aqui */

    return 0;
}
