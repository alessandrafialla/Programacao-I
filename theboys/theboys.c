#include <stdio.h>
#include <stdlib.h>
#include "fila.h"
#include "lef.h"
#include "mundo.h"
#include "conjunto.h"

/* demais includes */

/* funcoes que voce ache necessarias aqui */
void imprime_herois(struct mundo_t w){
    int i;
    for(i = 0; i < N_HEROIS; i++){
        printf("%d ", w.herois[i].id);
        printf("%d ", w.herois[i].experiencia);
        printf("%d ", w.herois[i].paciencia);
        printf("%d \n", w.herois[i].velocidade);
        imprime_cjt(w.herois[i].habilidades);
        printf("\n\n");
    }
}

void verifica_missoes(struct mundo_t w) {
    struct nodo_lef_t *atual = w.lef->primeiro;
    int count = 0;

    while (atual != NULL) {
        if (atual->evento->tipo == MISSAO) {
            count++;
        }
        atual = atual->prox;
    }
    printf("Total de missões do tipo MISSAO na LEF: %d\n", count);
}

int main (){
    struct mundo_t w; 
    /*
    struct evento_t *ev; *//*
    int agendadas, cumpridas; *//* contabilizar missoes*/
    /*int relogio;*/
    int i; 
    
    /* declaracoes de variaveis aqui */

    srand (0); /* use zero, nao faca com time (0) */

    w = cria_mundo();
    
    verifica_missoes(w);
    
    for (i = 0; i < N_MISSOES; i++)
        printf("%d\n", w.missoes[i].id);

    imprime_lef(w.lef);
    return 1;
}
