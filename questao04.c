#include <stdio.h>

int main (){

	int penultimo, ultimo, somaLidos, qtdLidos;
	
	/*inicializacao das variaveis*/
	somaLidos = 0;
	qtdLidos = 0;
	penultimo = 0;
	
	/*le um numero da sequencia ate ser  dobro ou a metade do anterior*/
	while (1){
	
	
	scanf("%d", &ultimo);
	
	somaLidos = somaLidos + ultimo;
	qtdLidos++;
	
	/*Condicao do dobro, se verdadeira imprime e encerra o loop*/
	if (ultimo == penultimo * 2){
		printf("%d %d %d %d\n", qtdLidos, somaLidos, penultimo, ultimo);
		return 0;
	}
	
	/*Condicao da metade, se verdadeira imprime e encerra o loop*/
	if (ultimo == penultimo / 2){
		printf("%d %d %d %d\n", qtdLidos, somaLidos, penultimo, ultimo);
		return 0;
	}
	
	/*Se nao caiu em nenhuma condicao de return,
	 o penultimo recebe ultimo para ler o proximo*/
	penultimo = ultimo;
	
	}
		
	return 0;
}
	
	
