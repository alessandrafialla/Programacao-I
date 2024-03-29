#include "racionais.h"
#include <stdio.h>
#include <stdlib.h>


/* Retorna um numero aleatorio entre min e max, inclusive. */
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

    /* Divide numerador e denominador pelo mdc entre eles */
    divisor = mdc (r->num, r->den);
    r->num = r->num / divisor;
    r->den = r->den / divisor;
	
    /* Se o denominador for negativo, migra sinal para numerador */
    /* Se numerador e denominador forem negativos, transforma em positivo */
    if (r->den < 0){
        r->num = r->num * (-1);
        r->den = r->den * (-1);
    }
}

/* Carrega dados da geracao aleatoria para o racional e carrega campo valido */
struct racional cria_r (int num, int den){
    struct racional r;

    r.num = num;
    r.den = den;
    r.valido = valido_r (r);
    return r;
}

/* Sorteia um numero racional e se for valido simplifica */
struct racional sorteia_r (int n){
    struct racional r;

    int num = aleat (-n, n); //num e den devem ter valores entre -n e n
    int den = aleat (-n, n);
    r = cria_r (num, den);    //cria o racional e carrega campo valido
    
    /*Verifica se o racional eh valido antes de simplificar */
    if (r.valido)
    	simplifica_r (&r); 
    return r;
}

/* Retorna o numerador de um racional */
int numerador_r (struct racional r){
    return r.num;
}

/* Retorna o denominador de um racional */
int denominador_r (struct racional r){
    return r.den;
}

/* Verifica se o racional eh valido, retorna 1 se valido e 0 se nao */
int valido_r (struct racional r){
    return (r.den != 0);
}

/* Retorna a soma simplificada entre r1 e r2 no parametro r3 */
void soma_r (struct racional r1, struct racional r2, struct racional *r3){
    int num, den;

    den = mmc (r1.den, r2.den); 
    num = (((den / r1.den) * (r1.num) + ((den / r2.den) * r2.num)));
    *r3 = cria_r (num, den); // Cria o racional e carrega campo valido
    simplifica_r (r3); 
}

/* Retorna a subtracao simplificada entre dois racionais no parametro r3 */
void subtrai_r (struct racional r1, struct racional r2, struct racional *r3){
    int num, den;

    den = mmc (r1.den, r2.den);
    num = (((den / r1.den) * r1.num) - ((den / r2.den) * r2.num));
    *r3 = cria_r (num, den); // Cria o racional e carrega campo valido
    simplifica_r (r3);
}

/* Retorna a multiplicacao simplificada de dois racionais no paramtro r3 */
void multiplica_r (struct racional r1, struct racional r2, struct racional *r3){
    int num, den;

    num = (r1.num * r2.num); 
    den = (r1.den * r2.den);
    *r3 = cria_r (num, den); // Cria o racional e carrega campo valido
    simplifica_r (r3);
}

/* Realiza a divisao entre dois racionais e retorna no parametro r3 */
/* Retorna 1 se o resultado eh valido e 0 se nao */
int divide_r (struct racional r1, struct racional r2, struct racional *r3){
    int num, den;
    
    /* Realiza a multiplicacao cruzada e cria racional de resultado */
    num = (r1.num * r2.den);  
    den = (r1.den * r2.num);
    *r3 = cria_r (num, den); 
    
    /* Simplifica se o racional resultante da divisao for valido */
    if (r3->valido){
        simplifica_r (r3);
        return 1;
    }
    return 0;
}

/* Compara dois racionais utilizando uma fracao equivalente */
/* Retorna -1 se r1 < r2; 0 se r1 == r2; 1 se r1 > r2 */
int compara_r (struct racional r1, struct racional r2){
    int den, eq1, eq2;

    den = mmc (r1.den, r2.den);
    eq1 = ((den/ r1.den) * r1.num); //Numerador equivalente de r1
    eq2 = ((den/r2.den) * r2.num); //Numerador equivalente de r2
    
    /* Como o denominador foi igualado, compara o numerador */
    if (eq1 < eq2)
        return -1;
    else if (eq1 == eq2)
        return 0;
    else   //caso eq1 > eq2
        return 1;
}

/* Imprime um numero racional */
void imprime_r (struct racional r) {

    /* Imprime zero se o numerador for nulo */
    if (r.num == 0){
        printf("0");
        return;
    }

    /* Imprime apenas o numerador se o denominador for 1 */
    if (r.den == 1){
        printf ("%d", r.num);
        return;
    }

    /* Imprime apenas "1" se numerador == denominador */
    if (r.num == r.den){
        printf ("1");
        return;
    }

    /* Imprime mensagem se o racional for invalido */
    if (!r.valido){
        printf ("INVALIDO");
        return;
    }

    /* Imprime na formatacao padrao  */
    printf ("%d/%d" , r.num, r.den);
    return;
}
