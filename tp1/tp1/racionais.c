#include "racionais.h"
/* acrescente demais includes que voce queira ou precise */

/* 
 * Implemente aqui as funcoes definidas no racionais.h 
 * caso queira, você pode definir neste arquivo funcoes
 * adicionais que serao internas e so podem ser usadas
 * aqui.
*/

int aleat (int min, int max){
    return (min + rand() % max + 1 - min));
}

int mmc (int a, int b){
    int mdc = mdc (a, b);
    return ((a * b) / mdc);
}

int mdc (int a, int b){
}

int valido_r (struct racional r){
    return (r.den != 0);
}

struct racional sorteia_r (int n){
    struct racional r;  
    int num = aleat (0, n);
    int den = aleat (0, n);
    r = cria_r (num, den);
    return simplifica_r (r);
}

struct racional cria_r (int num, int den){
    struct racional r;
    r.num = num;
    r.den = den;
    r.valido = valido_r (r);
    return r;
}
