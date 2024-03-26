#include "racionais.h"
#include <stdlib.h>
#include <stdio.h>

/* acrescente demais includes que voce queira ou precise */

/* Funcoes privadas restritas a este modulo.
 * Voce deve implementa-las pois serao necessarias,
 * embora elas nao precisem estar no .h */

/* retorna um numero aleatorio entre min e max, inclusive. */
int aleat (int min, int max){
    return (min + rand() % (max + 1 - min));
}

/* Maximo Divisor Comum entre a e b      */
/* calcula o mdc pelo metodo de Euclides */
/* dica: a versao recursiva eh bem elegante! */
int mdc (int a, int b){
    if ((a % b) == 0)
        return b;
    return mdc (b, a % b);
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
int mmc (int a, int b){
    int divisor = mdc (a, b);
    return ((a * b) / divisor);
}

/* Recebe um numero racional e o retorna simplifico.
 * Por exemplo, ao receber 10/8 devera retornar 5/4.
 * Se ambos numerador e denominador forem negativos, devera retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Quem chama esta funcao deve garantir que o racional r eh valido */
struct racional simplifica_r (struct racional r){
    int divisor;
	
    /*Divide numerador e denominador pelo mdc entre eles*/
    divisor = mdc (r.num, r.den);
    r.num = r.num / divisor;
    r.den = r.den / divisor;
	
    /*Se o denominador for negativo, migra sinal para numerador*/
    /*Se numerador e denominador forem negativos, transforma em positivo*/
    if (r.den < 0){
        r.num = r.num * (-1);
        r.den = r.den * (-1);
    }
    return r;
}



/* aqui voce pode definir mais funcoes internas, caso queira ou precise */

/*
 * Implemente aqui as funcoes definidas no racionais.h.
*/
