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
    struct mundo_t mundo;
    struct evento_t *evento; 
    int agendadas, cumpridas;  /*contabilizar missoes*/
    int fim_simulacao;
    /* declaracoes de variaveis aqui */

    srand (0); /* use zero, nao faca com time (0) */
    agendadas = 0;
    cumpridas = 0;
    mundo = cria_mundo();
    
   /* imprime_lef(mundo.lef); */ /*
    
    printf("Teste 1:\n");
    chega(&mundo, 100, 0, 0);

    printf("Teste 2: ESPERA\n");
    espera(&mundo, 100, 0, 0);

    printf("Teste 2: Avisa\n");
    avisa(&mundo, 100, 0);
   
   printf("Teste ENTRA\n");
    entra(&mundo, 100, 0, 0);

    printf("Teste SAI\n");
    sai(&mundo, 211, 0, 0); */
    /* prox eh viaja*/
    
    fim_simulacao = 0;
    while (!fim_simulacao && (evento = retira_lef(mundo.lef)) != NULL) {
        mundo.relogio = evento->tempo;
        switch (evento->tipo) {
            case CHEGA:
                chega(&mundo, evento->tempo, evento->dado1, evento->dado2);
                break; 
            case ESPERA:
                espera(&mundo, evento->tempo, evento->dado1, evento->dado2);
                break; 
            case DESISTE:
                desiste(&mundo, evento->tempo, evento->dado1, evento->dado2);
                break;
            case VIAJA:
                viaja(&mundo, evento->tempo, evento->dado1, evento->dado2);
                break;
            case MISSAO:
                if(missao(&mundo, evento->tempo, evento->dado1))
                    cumpridas++;
                else
                    agendadas++;
                break; 
            case AVISA:
                avisa(&mundo, evento->tempo, evento->dado2);
                break;
            case ENTRA:
                entra(&mundo, evento->tempo, evento->dado1, evento->dado2);
                break;
            case SAI: 
                sai(&mundo, evento->tempo, evento->dado1, evento->dado2);
                break;
            case FIM:
                fim(&mundo, cumpridas, agendadas);
                fim_simulacao = 1;
                break;;        
        }
            destroi_evento(evento);
    } /*
    destroi_mundo(&mundo);*/
    return 1;
    }
