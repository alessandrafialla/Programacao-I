#include "racionais.h"
#include <stdio.h>
#include <stdlib.h>

/* Funcoes privadas restritas a este modulo.
 * Voce deve implementa-las pois serao necessarias,
 * embora elas nao precisem estar no .h */

/* Retorna um numero aleatorio entre min e max, inclusive. */
int aleat (long int min, long int max){
    return (min + rand () % (max + 1 - min));
}

/* Maximo Divisor Comum entre a e b.         */
/* Calcula o mdc pelo metodo de Euclides.    */
/* Dica: a versao recursiva eh bem elegante! */
long int mdc (long int a, long int b){
    if (a % b == 0)
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
    
    /* Divide o numerador e o denominador pelo mdc entre eles */
    divisor = mdc (r->num, r->den);
    r->num = r->num / divisor;
    r->den = r->den / divisor;

    /* Se o denominador for negativo migra sinal para numerador */
    /* Se numerador e denominador forem negativos, tranforma em positivo */
    if (r->den < 0) {
        r->num = r->num * (-1);
        r->den = r->den * (-1);
    }
}

/* Cria e aloca memoria para um racional, se erro retorna NULL */
/* Retorna o racional apontado na forma simplificada           */
struct racional *cria_r (long int numerador, long int denominador){
    struct racional *r;

    /*Aloca memoria e testa, se erro retorna NULL*/
    r = malloc (sizeof (struct racional));
    if (r == NULL)
        return NULL; 

    /* Inicializa com valores fornecidos e simplifica se valido*/
    r->num = numerador;
    r->den = denominador;
    if (valido_r(r))
        simplifica_r (r); 

    return r;
}

/* Libera memoria e aterra ponteiro */
void destroi_r (struct racional **r){
    free (*r);
    *r = NULL;
}

/* Retorna 1 se valido e 0 se invalido */
int valido_r (struct racional *r){
    return r->den != 0;  
}

/* Retorna o denominador de um racional */
long int denominador_r (struct racional *r){
    return r->den;
}

/* Retorna o numerador de um racional */
long int numerador_r (struct racional *r){
    return r->num;
}

/* Retorna a soma simplificada de *r1 e *r2                      */
/* Retirna NULL se alocacao deu errado                           */
struct racional *soma_r (struct racional *r1, struct racional *r2){
    long int num, den;
    struct racional *r;

    den = mmc (r1->den, r2->den);
    num = ((den / r1->den) * r1->num) + ((den / r2->den) * r2->num);

    r = cria_r (num, den); // aloca memoria e retorna simplificado, se possivel
    if (r == NULL) // cria retorna NULL se tiver erro no malloc
        return NULL;
    return r;
}

/* Retorna a subtracao simplificada dos racionais *r1 e *r2         */
struct racional *subtrai_r (struct racional *r1, struct racional *r2){
    long int num, den;
    struct racional *r;

    den = mmc (r1->den, r2->den);
    num = ((den / r1->den) * r1->num) - ((den / r2->den) * r2->num);

    r = cria_r (num, den); //aloca memoria e retorna simplificado, se possivel
    if (r == NULL) //se erro no malloc
        return NULL;
    return r;
}

/* Retorna a multiplicacao simplificada dos racionais *r1 e *r2        */
struct racional *multiplica_r (struct racional *r1, struct racional *r2){
    long int num, den;
    struct racional *r;

    num = (r1->num * r2->num);
    den = (r2->den * r2->den);

    r = cria_r (num, den); //aloca e retorna simplificado
    if (r == NULL)
        return NULL;
    return r;
}

/* Retorna a divisao simplificada dps racionais *r1 e *r2   
 * RetornA NULL se a memoria nao foi alocada corretamente
 * Retorna NULL se o resultado da divisao for invalido     */
struct racional *divide_r (struct racional *r1, struct racional *r2){
    long int num, den;
    struct racional *r;

    num = (r1->num * r2->den);
    den = (r1->den * r2->num);
    r = cria_r (num, den);
    
    /* Retorna NULL se ocorreu erro na alocacao ou se resultado eh invalido*/
    if ((r == NULL) || !valido_r(r))
        return NULL;
    return r;
}

/* Compara dois racionais usando uma fracao equivalente    
 * Retorna -1 se r1 < r2; 0 se r1 == r2 e 1 se r1 > r2   */
int compara_r (struct racional *r1, struct racional *r2){
    long int den, eq1, eq2;

    den = mmc (r1->den, r2->den);// Iguala o denominador dos dois racionais
    eq1 = ((den / r1->den) * r1->num); // Numerador equivalente de r1
    eq2 = ((den / r2->den) * r2->num); //Numerador equivalente de r2

    /* Como possuem o mesmo den, compara o numerador*/
    if (eq1 < eq2)
        return -1;
    else if (eq1 == eq2)
        return 0;
    else //eq1 > eq2
        return 1;
}

/* Imprime um numero racional */
void imprime_r (struct racional *r) {

    /* Imprime zero se o numerador for nulo */
    if (r->num == 0){
        printf("0");
        return;
    }

    /* Imprime apenas o numerador se o denominador for 1 */
    if (r->den == 1){
        printf ("%ld", r->num);
        return;
    }

    /* Imprime apenas "1" se numerador == denominador */
    if (r->num == r->den){
        printf ("1");
        return;
    }

    /* Imprime mensagem se o racional for invalido */
    if ( !valido_r(r) ){
        printf ("INVALIDO");
        return;
    }

    /* Imprime na formatacao padrao  */
    printf ("%ld/%ld" , r->num, r->den);
    return;
}

/* aqui voce pode definir mais funcoes internas, caso queira ou precise */

/* Implemente aqui as funcoes cujos prototipos estao em racionais.h */
