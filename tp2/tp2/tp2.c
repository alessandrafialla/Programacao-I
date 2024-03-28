/* Arquivo MAIN que usa o TAD racionais */

#include "racionais.h"
#include <stdio.h>
#include <stdlib.h>

int main (){
    int n, max, i;
    struct racional r1, r2, rSoma, rSubtracao, rMultiplicacao, rDivisao;

    srand (0); /* Inicia semente randomica */

    scanf ("%d %d", &n, &max);

    /* n eh a quantidade de racionais que seram sorteados */
    for (i = 1; i <= n; i++) {
        printf ("%d: ", i);

        /* Sorteia r1 e r2 */
        r1 = sorteia_r (max); // numerador e denominador devem estar entre -max e max
        r2 = sorteia_r (max);
        
        /* Imprime r1 e r2*/
        imprime_r (r1);
        printf (" ");
        imprime_r (r2);
        printf (" ");
        
        /* Verifica se sao validos antes das operacoes */
        if (!valido_r (r1) || !valido_r (r2)){
            printf ("NUMERO INVALIDO\n");
            return 1;
        }
        
        /* Realiza as operacoes*/
        soma_r (r1, r2, &rSoma);
        subtrai_r (r1, r2, &rSubtracao);
        multiplica_r (r1, r2, &rMultiplicacao);
        
        /* Realiza a divisao e testa se resultado eh valido*/
        //divide_r (r1, r2, &rDivisao);
        if ( !divide_r (r1, r2, &rDivisao) ){
            printf ("DIVISAO INVALIDA\n");
            return 1;
        }

        /* Imprime os resultados das operacoes*/
        imprime_r (rSoma);
        printf (" ");
        imprime_r (rSubtracao);
        printf (" ");
        imprime_r (rMultiplicacao);
        printf (" ");
        imprime_r (rDivisao);
        printf (" \n");
    }

    return 0;
}
