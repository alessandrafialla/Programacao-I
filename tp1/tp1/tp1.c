/* Arquivo MAIN que usa o TAD racionais */

/* coloque seus includes aqui */
#include "racionais.h"
#include <stdio.h>
#include <stdlib.h>


int main (){
    int n, max, i;
   	struct racional r1, r2, rSoma, rSubtracao, rMultiplicacao, rDivisao;
    srand(0); // inicia semente randomica
	
	/*Os racionais gerados teram valores de num e den entre 0 e max*/
    scanf("%d %d", &n, &max);

    for (i = 1; i <= n; i++ ){
    	printf("%d: ", i);
    	
    	/*Sorteia e imprime r1 e r2*/
    	r1 = sorteia_r(max);
    	r2 = sorteia_r(max);
    	imprime_r (r1);
    	imprime_r (r2);
    	
    	/*Verifica se algum deles eh invalido antes de fazer operacoes*/
    	if (!valido_r(r1) | !valido_r(r2)){
    		printf ("NUMERO INVALIDO\n");
    		return 1;
    	}
    	
    	/*Realiza as operacoes entre os racionais*/
    	rSoma = soma_r (r1, r2);
    	rSubtracao = subtrai_r (r1, r2);
    	rMultiplicacao = multiplica_r (r1, r2);
    	rDivisao = divide_r (r1, r2);
    	
    	/*Se o resultado da divisao for invalido, imprime mensagem e encerra*/
    	if (!valido_r (rDivisao)){
    		printf ("DIVISAO INVALIDA\n");
    		return 1;
    	}
    	
    	/*Imprime o resultado das operacoes*/
    	imprime_r (rSoma);
    	imprime_r (rSubtracao);
    	imprime_r (rMultiplicacao);	
    	imprime_r (rDivisao);
    	printf("\n");
    }
    return 0;
}
