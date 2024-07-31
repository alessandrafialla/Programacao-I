#include "mundo.h"
#include "lef.h"
#include "conjunto.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>

/* Cria o mundo e inicializa todas as entidades*/
struct mundo_t cria_mundo( ){
    struct mundo_t w;
    int i;

    /* Inicializa dados imutaveis*/
    w.n_herois = N_HEROIS;
    w.n_habilidades = N_HABILIDADES;
    w.n_bases = N_BASES;
    w.n_missoes = N_MISSOES;
    w.n_tam_mundo = T_FIM_DO_MUNDO;

    w.relogio = T_INICIO; /*Inicia tempo inicio do mundo */
    
    /* Cria e inicializa as habilidades distintas do mundo */
    w.habilidades = cria_cjt(w.n_habilidades);
    for(i = 0; i < w.n_habilidades; i++)
        insere_cjt(w.habilidades, i);
    

    /* Cria e inicializa os Herois */
    for(i = 0; i < w.n_herois; i++)
        w.herois[i] = cria_heroi (w, i);
    
   
    /* Cria e inicializa as Missoes */
    for(i = 0; i < w.n_missoes; i++){
        w.missoes[i]= cria_missao(w, i);
        printf("Missao %d criada\n", i);
    }
    

    /* Cria e inicaliza as Bases */
    for(i = 0; i < w.n_bases; i++){
        w.bases[i] = cria_base (w, i);
    }

    w.lef = cria_lef();
    eventos_iniciais(&w);
    return w;
}

/* Retorna um heroi inicializado*/
struct heroi_t cria_heroi(struct mundo_t w, int id){
    struct heroi_t h;

    h.id = id;
    h.experiencia = 0;
    h.paciencia = aleat (0, 100);
    h.velocidade = aleat (50, 5000);
    h.habilidades = cria_subcjt_cjt(w.habilidades, aleat(1, 3));
    return h;
}

/* Retorna uma struct de missao inicializada*/
struct missao_t cria_missao(struct mundo_t w, int id){
    struct missao_t m;

    m.id = id; 
    m.habi_req = cria_subcjt_cjt(w.habilidades, aleat(6, 10));

    /*Escolhe aleatoriamente um local para a missao ocorrer*/
    m.local_missao.x = aleat(0, w.n_tam_mundo);
    m.local_missao.y = aleat(0, w.n_tam_mundo);
    return m;
}

struct base_t cria_base (struct mundo_t w, int id){
    struct base_t b;

    b.id = id;

    /* Define coordenadas aleatorias para localizacao da base*/
    b.coordenadas.x = aleat(0, w.n_tam_mundo);
    b.coordenadas.y = aleat(0, w.n_tam_mundo);

    b.lotacao = aleat(3, 10);
    b.presentes = cria_cjt(b.lotacao);
    b.espera = fila_cria();
    return b;
}


/* Retorna um inteiro aleatorio entre min e max*/
int aleat (int min, int max){
    return min + rand() % (max - min + 1);
}

/* Cria os eventos iniciais e insere na lef*/
void eventos_iniciais(struct mundo_t *w){
    int i, tempo, base;
    struct evento_t *ev;

    /* Cria um evento chega para cada heroi*/
    for(i = 0; i < w->n_herois; i++){
        base = aleat(0, w->n_bases-1);
        tempo = aleat(0, 4320);
        ev = cria_evento(tempo, CHEGA, i, base);
        if(ev != NULL){
            insere_lef(w->lef, ev);
        }
        
    }

    /* Cria um evento p todas as missoes do mundo*/
    for(i = 0; i < w->n_missoes; i++){
        tempo = aleat(0, T_FIM_DO_MUNDO);
        ev = cria_evento(tempo, MISSAO, -1, -1);
        if(ev != NULL)
            insere_lef(w->lef, ev);
    }

    imprime_lef(w->lef);

    /* Agenda o fim do mundo */
    tempo = w->n_tam_mundo;
    ev = cria_evento(tempo, FIM, -1, -1);

    if(ev != NULL){
            insere_lef(w->lef, ev);
    }
}

void chega(struct mundo_t *w, int tempo, int heroi, int base){
    int presentes, lotacao, espera, fila_espera;
    struct evento_t *ev;

    w->herois[heroi].base = base; /* Atualiza a base do heroi*/
    
    fila_espera = fila_tamanho(w->bases[base].espera); /* Tamanho da fila*/
    presentes = cardinalidade_cjt(w->bases[base].presentes); /* Quantos na base*/
    lotacao = w->bases[base].lotacao; /* Lotacao maxima*/

    /* Se a quantidade de presentes eh menor que a lotacao e fila vazia*/
    if(presentes < lotacao  && fila_vazia(w->bases[base].espera))
        espera = 1;
    else {
        espera = w->herois[heroi].paciencia > (10 * fila_espera);
    }
    if(espera == 1){
        ev = cria_evento(tempo, ESPERA, heroi, base);
        insere_lef(w->lef, ev);
    }
    else{
        ev = cria_evento(tempo, DESISTE, heroi, base);
        insere_lef(w->lef, ev);
    }
}

void espera(struct mundo_t *w, int tempo, int heroi, int base){
    struct evento_t *ev;

    enqueue(w->bases[base].espera, heroi);
    ev = cria_evento(tempo, AVISA, -1, base);
    if(ev != NULL)
        insere_lef(w->lef, ev);

}

void desiste(struct mundo_t *w, int tempo, int heroi, int base){
    struct evento_t *ev;

    base = aleat(0, w->n_bases-1); /*Escolhe um id de base aleatoria*/
    ev = cria_evento(tempo, VIAJA, heroi, base);
    if(ev != NULL)
        insere_lef(w->lef, ev);
}

/* Trata a fila de espera*/
void avisa(struct mundo_t *w, int tempo, int base){
    struct evento_t *ev;
    int presentes, lotacao, heroi;

    presentes = cardinalidade_cjt(w->bases[base].presentes); /* Quantos na base*/
    lotacao = w->bases[base].lotacao; /* Lotacao maxima*/
    while(presentes < lotacao){
        dequeue(w->bases[base].espera, &heroi); /*tira da espera*/
        insere_cjt(w->bases[base].presentes, heroi);
        ev = cria_evento(tempo, ENTRA, heroi, base);
        if(ev != NULL)
            insere_lef(w->lef, ev);
    }
}

void entra(struct mundo_t *w, int tempo, int heroi, int base){
    struct evento_t *ev;
    int permanencia;

    permanencia = 15 + (w->herois[heroi].paciencia * aleat(1, 20));
    ev = cria_evento(tempo + permanencia, SAI, heroi, base);
    if(ev != NULL)
        insere_lef(w->lef, ev);
}
