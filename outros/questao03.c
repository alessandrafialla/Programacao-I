#include <stdio.h>

int main()
{
    int k,j, i,acDivisores, perfeitos; 
    
    /*Le quantos inteiros quer calcular*/
    scanf("%d", &k);

    /*Primeiro for controla numeros impressos*/
    for (i=1,  perfeitos = 0 ;( perfeitos < k); i++){
    
    	/*acumula soma de valores dos divisores*/ 
		for (j = 1 ; j < i; j++){
			if((i % j == 0))
				acDivisores = acDivisores + j;
		}

		/* Verifica se eh perfeito, contabiliza a quantidade e os imprime*/
		if (acDivisores == i){
			printf("%d ", i);
			perfeitos = perfeitos + 1;
      	}	
      	acDivisores = 0;
    }
    
    printf("\n");
    	
    return 0;
}
