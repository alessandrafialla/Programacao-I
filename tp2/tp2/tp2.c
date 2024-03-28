/* Arquivo MAIN que usa o TAD racionais */

#include "racionais.h"
#include <stdio.h>
#include <stdlib.h>

int main (){
    int n, max, i;
    struct racional r1, r2, resultado;
    struct racional *r3 = &resultado;

    srand (0); /* Inicia semente randomica */

    scanf ("%d %d", &n, &max);

    /* n eh a quantidade de racionais que seram sorteados */
    for (i = 1; i <= n; i++) {
        printf ("%d: ", i);

        /* Sorteia r1 e r2 */
        r1 = sorteia_r (n); // numerador e denominador devem estar entre -n e n
        r2 = sorteia_r (n);
        
        /*Imprime*/
        imprime_r (r1);
        printf (" ");
        imprime_r (r2);
        printf (" ");
        
        /* Verifica se sao validos antes das operacoes */
        if (!valido_r (r1) || !valido_r (r2)){
            printf ("NUMERO INVALIDO\n");
            return 1;
        }

        soma_r (r1, r2, r3);
        imprime_r (*r3);
        printf (" ");

        subtrai_r (r1, r2, r3);
        imprime_r (*r3);
        printf (" ");

        multiplica_r (r1, r2, r3);
        imprime_r (*r3);
        printf (" ");
        
        /*Realiza a divisao e testa se resultado eh valido*/
        divide_r (r1, r2, r3);
        if (!valido_r (*r3)){
            printf ("DIVISAO INVALIDA");
            return 1;
        }

        imprime_r (*r3);
        printf (" \n");
    }

    return 0;
}
