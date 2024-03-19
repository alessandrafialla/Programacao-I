#include "racionais.h"
#include <stdlib.h>
#include <stdio.h>
/* acrescente demais includes que voce queira ou precise */

/* 
 * Implemente aqui as funcoes definidas no racionais.h 
 * caso queira, você pode definir neste arquivo funcoes
 * adicionais que serao internas e so podem ser usadas
 * aqui.
*/

/*Gera numero aleatorio entre min e max*/
int aleat (int min, int max){
    return (min + rand() % (max + 1 - min));
}

/*Calcula mdc pelo metodo de euclides, recursivo*/
int mdc (int a, int b){
    if ((a % b) == 0)
        return b;
    return mdc (b, a % b);
}

/*Calcula MMC*/
int mmc (int a, int b){
    int divisor = mdc (a, b);
    return ((a * b) / divisor);
}

/*Simplifica racional atraves de reducao e simplifica o sinal*/
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
    	r = simplifica_r (r);
    return r;
}

/*Imprime os racionais formatando a impressao*/
void imprime_r (struct racional r){
    /*Imprime apenas zero se o numerados for nulo*/
    if (r.num == 0){
        printf("0 ");
        return;
    }
	
    /*Imprime apenas o numerador se o denominador for 1*/
    if (r.den == 1){
        printf("%d ", r.num);
    return;
    }
    
    /*Imprime 1 se o numerador = denominador*/
    if (r.num == r.den){
        printf("1 ");
        return;
    }
	
    /*Imprime mensagem se o racional for invalido*/
    if (!r.valido){
        printf("INVALIDO ");
	    return;
    }
	
    /*Imprime na formatacao padrao*/
    printf("%d/%d " , r.num, r.den);
    return;
}

/*Verifica se o racional eh valido, retorna 1 se valido e 0 se nao*/
int valido_r (struct racional r){
    return (r.den != 0);
}

/*Soma fracoes e retorna simplificada, r1 e r2 garantidamente validos*/
struct racional soma_r (struct racional r1, struct racional r2){
    struct racional soma;
    int num, den;
	
    den = mmc (r1.den, r2.den);
    num = (((den / r1.den) * r1.num) + ((den / r2.den) * r2.num));
    soma = cria_r (num, den);
	
    /*r1 e r2 sao validos, logo a soma nao pode ser invalida*/
    soma = simplifica_r (soma);
    return soma;
}

/*Subtrai duas fracoes e retorna simplificado, r1 e r2 garantidamente validos*/
struct racional subtrai_r (struct racional r1, struct racional r2){
    struct racional subtracao;
    int num, den;
	
    den = mmc (r1.den, r2.den);
    num = (((den / r1.den) * r1.num) - ((den / r2.den) * r2.num));
    subtracao = cria_r (num, den);
	
    /*r1 e r2 sao validos, logo a subtracao nao pode ser invalida*/
    subtracao = simplifica_r (subtracao);
    return subtracao;
}

/*Multiplica 2 fracoes e retorna simplificado, r1 e r2 garantidamente validos*/
struct racional multiplica_r (struct racional r1, struct racional r2){
    struct racional multiplicacao;
    int num, den;
	
    num = (r1.num * r2.num);
    den = (r1.den * r2.den);
    multiplicacao = cria_r (num, den);
	
    /*r1 e r2 sao validos, logo a multiplicacao nao pode ser invalida*/
    multiplicacao = simplifica_r (multiplicacao);
    return multiplicacao;
}

/*Divide duas fracoes e retorna simplificado se resultado for valido*/
struct racional divide_r (struct racional r1, struct racional r2){
    struct racional divisao;
    int num, den;
	
    num = (r1.num * r2.den);
    den = (r1.den * r2.num);
    divisao = cria_r (num, den);

    /*So simplifica se o recional de resultado for valido*/
    if (divisao.valido)
        divisao = simplifica_r (divisao);
    return divisao;
}
	










