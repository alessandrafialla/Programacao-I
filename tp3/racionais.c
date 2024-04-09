#include "racionais.h"
#include <stdio.h>
#include <stdlib.h>

/* Funcoes privadas restritas a este modulo.
 * Voce deve implementa-las pois serao necessarias,
 * embora elas nao precisem estar no .h */

/* retorna um numero aleatorio entre min e max, inclusive. */
int aleat (long int min, long int max){
    return (min + rand () % (max + a - min));
}

/* Maximo Divisor Comum entre a e b.         */
/* Calcula o mdc pelo metodo de Euclides.    */
/* Dica: a versao recursiva eh bem elegante! */
long int mdc (long int a, long int b){
    if ((a % b) == 0)
        return b;
    return mdc (b, a % b);
}

/* Minimo Multiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b)        */
long int mmc (long int a, long int b){
    return ( a * b) / mdc (a, b);
}

/* Recebe um numero racional e o retorna simplificado no parametro *r.
   Quem chama esta funcao deve garantir que *r seja valido e nao NULL. */
void simplifica_r (struct racional *r){
    int divisor;

    divisor = mdc (r->num, r->den);
    r->num = r->num / divisor;
    r->den = r->den / divisor;

    if (r->den < 0) {
        r->num = r->num * (-1);
        r->den = r->den * (-1);
    }
}

/* Testar se aloca da forma certa se devolve o endereco */
/* Depois de usar testar se eh NULL, prob de alocacao*/
struct racional *cria_r (long int numerador, long int denominador){
    struct racional *r;

    r = malloc (sizeof (struct racional));
    r->num = numerador;
    r->den = denominador;

    return r;
}

/*Testar*/
void destroi_r (struct racional **r){
    free (*r);
    *r = NULL;
}

/* aqui voce pode definir mais funcoes internas, caso queira ou precise */

/* Implemente aqui as funcoes cujos prototipos estao em racionais.h */
