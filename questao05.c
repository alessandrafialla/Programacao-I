#include <stdio.h>

int main () {
   
    int num,soma,multiplicacao;

	/*Le o numero*/
	scanf("%d", &num);
	
	/*Realiza a multiplicacao por 37*/
	multiplicacao = num * 37;
	
	/*Realiza a divisao por 10 para pegar os algarismos e os soma*/
	/*Atualiza o numero para coletar o proximo algarismo*/
	while (( multiplicacao / 10) != 0){
	soma =((soma * 10) + (multiplicacao % 10));
	multiplicacao = multiplicacao / 10;
	}

	/*Verifica se a soma dos algarismos eh igual a num*/
	if (soma != num){
	printf("SIM\n");
	}
	else {
	printf("NAO\n");
	}
	
	return 0;
}	
