#include <stdio.h>

//sequencia de fibonacci

int main () {
    int numero,penultimo, ultimo, proxNum, impressos;

	/*Le o a quantidade de numeros que seram impressos*/
	scanf("%d", &numero);
    
	/*Inicializa as variaveis com os primeiros 2 numeros da sequencia*/    
	ultimo = 1;
	penultimo = 0;

	/*Se numero for == 1 imprime apenas o primeiro da sequencia*/
	if (numero == 1)
		printf("%d", penultimo);
	else {
		printf("%d %d ", penultimo, ultimo);
		
		/*Verifica a quantidade de numeros ja impressos e calcula o prox da sequencia*/
		for (impressos = 2; impressos < numero; impressos++){
	        	proxNum = penultimo + ultimo;
	        	penultimo = ultimo;
	        	ultimo = proxNum;
	        	printf("%d ", proxNum);    
		}
	}
    	printf("\n");
    	
	return 0;    
}
