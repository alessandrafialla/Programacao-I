#include <stdio.h>

int main () {

    int n,fatorial;
    
	/*Le o n!*/
	scanf("%d" , &n);

	/*Calcula o fatorial de n*/
	for (fatorial = 1  ; n > 0 ; n-- ){
		fatorial = fatorial*n;
	}

	/*Imprime o fatorial*/
	printf("%d\n", fatorial);
	
	return 0;
}
