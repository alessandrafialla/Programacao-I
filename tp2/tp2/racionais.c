#include "racionais.h"
#include <stdio.h>
#include <stdlib.h>

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

/* Recebe um numero racional e o retorna simplificado.
 * Por exemplo, ao receber 10/8 devera retornar 5/4.
 * Se ambos numerador e denominador forem negativos, devera retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Quem chama esta funcao deve garantir que o racional r eh valido */
void simplifica_r (struct racional *r){
    int divisor;

    /*Divide numerador e denominador pelo mdc entre eles*/
    divisor = mdc (r->num, r->den);
    r->num = r->num / divisor;
    r->den = r->den / divisor;
	
    /*Se o denominador for negativo, migra sinal para numerador*/
    /*Se numerador e denominador forem negativos, transforma em positivo*/
    if (r->den < 0){
        r->num = r->num * (-1);
        r->den = r->den * (-1);
    }
}

/*Carrega dados da geracao aleatoria para o racional e verifica se eh valido*/
struct racional cria_r (int num, int den){
    struct racional r;
    r.num = num;
    r.den = den;
    r.valido = valido_r (r);
    return r;
}

/*Sorteia um numero racional e se for valido simplifica*/
struct racional sorteia_r (int n){
    struct racional r;  
    int num = aleat (0, n);
    int den = aleat (0, n);
    r = cria_r (num, den);//cria o racional e verifica se eh valido
    
    /*Verifica se o racional eh valido antes de simplificar*/
    if (r.valido)
    	r = simplifica_r (&r); /*simplifica agora recebe um ponteiro, mudei para passar o endereço de r*/
    return r;
}

/*Retorna o numerador de um racional*/
int numerador_r (struct racional r){
    return r.num;
}

/*Retorna o denominador de um racional*/
int denominador_r (struct racional r){
    return r.den;
}

/*Verifica se o racional eh valido, retorna 1 se valido e 0 se nao*/
int valido_r (struct racional r){
    return (r.den != 0);
}

/* aqui voce pode definir mais funcoes internas, caso queira ou precise */

/*
 * Implemente aqui as funcoes definidas no racionais.h.
*/
