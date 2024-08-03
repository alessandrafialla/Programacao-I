#include "mundo.h"
#include "lef.h"
#include "conjunto.h"
#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
    h.base = -1;
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
    if(b.presentes == NULL){
        printf("Erro em criar cojunto de presentes na base\n");
    }
    b.espera = fila_cria();
    if(b.espera == NULL){
        printf("Erro em criar fila de espera na base\n");
    }
    return b;
}


/* Retorna um inteiro aleatorio entre min e max*/
int aleat (int min, int max){
    return min + rand() % (max - min + 1);
}

int distancia_cartesiana( struct local_t A, struct local_t B){
    int d;
    d = pow((B.x - A.x), 2) + pow((B.y - A.y), 2);
    return sqrt(d);
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
        insere_lef(w->lef, ev);
    }

    /* Cria um evento p todas as missoes do mundo*/ 
    for(i = 0; i < w->n_missoes; i++){
        tempo = aleat(0, T_FIM_DO_MUNDO);
        ev = cria_evento(tempo, MISSAO, i, -1);
        insere_lef(w->lef, ev); 
    } 

    /* Agenda o fim do mundo */
    tempo = w->n_tam_mundo;
    ev = cria_evento(tempo, FIM, -1, -1);
    insere_lef(w->lef, ev);
}

void chega(struct mundo_t *w, int tempo, int heroi, int base){
    struct evento_t *ev;
    struct heroi_t h;
    struct base_t b;
    int presentes, lotacao, espera, fila_espera;

    h = w->herois[heroi]; /* Caminho para o heroi*/
    b = w->bases[base]; /* Caminho para a base*/

    presentes = cardinalidade_cjt(b.presentes); /* Quantos na base*/
    fila_espera = fila_tamanho(b.espera); /* Tamanho da fila*/ 
    lotacao = w->bases[base].lotacao; /* Lotacao maxima*/

    h.base = base; /* Atualiza a base do heroi*/

    /* Se a quantidade de presentes eh menor que a lotacao e fila vazia*/
    if(presentes < lotacao  && fila_vazia(b.espera))
        espera = 1;
    else {
        espera = h.paciencia > (10 * fila_espera);
    }

    if(espera == 1){
        ev = cria_evento(tempo, ESPERA, heroi, base);
        insere_lef(w->lef, ev);
        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) ESPERA\n",
                             tempo,heroi,base, presentes, lotacao);
    }
    else{
        ev = cria_evento(tempo, DESISTE, heroi, base);
        insere_lef(w->lef, ev);
        printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) DESISTE\n", tempo,heroi,base,presentes, lotacao);
    }
}

void espera(struct mundo_t *w, int tempo, int heroi, int base){
    struct evento_t *ev;

    printf("%6d: ESPERA HEROI %2d BASE %d" ,tempo, heroi, base);
    printf("(%2d)\n",fila_tamanho(w->bases[base].espera));

    enqueue(w->bases[base].espera, heroi);

    ev = cria_evento(tempo, AVISA, -1, base);
    insere_lef(w->lef, ev);
    
}

void desiste(struct mundo_t *w, int tempo, int heroi, int base){
    struct evento_t *ev;

    printf("%6d: DESISTE HEROI %2d BASE %d\n", tempo, heroi, base);

    base = aleat(0, w->n_bases-1); /*Escolhe um id de base aleatoria*/
    ev = cria_evento(tempo, VIAJA, heroi, base);
    insere_lef(w->lef, ev);
}

/* Trata a fila de espera*/
void avisa(struct mundo_t *w, int tempo, int base){
    struct evento_t *ev;
    struct base_t b;
    int lotacao, heroi, presentes;
    
    b = w->bases[base];

    lotacao = b.lotacao; /* Lotacao maxima*/
    presentes = cardinalidade_cjt(b.presentes);/* Quantos na base*/

    printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA ", tempo, base, presentes, lotacao);
    fila_imprime(b.espera);
    
    /*Enquanto a quantidade de presentes eh menor que lotação*/
    while(presentes <= lotacao && !fila_vazia(b.espera)){
        dequeue(b.espera, &heroi); /* Tira da espera*/
        insere_cjt(w->bases[base].presentes, heroi); /* Insere na Base*/
        presentes++;

        printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", tempo, base, heroi);
        
        ev = cria_evento(tempo, ENTRA, heroi, base);
        insere_lef(w->lef, ev);
    }
}

void entra(struct mundo_t *w, int tempo, int heroi, int base){
    struct evento_t *ev;
    struct base_t b;
    struct heroi_t h;
    int permanencia, presentes, lotacao;

    b = w->bases[base]; /* Caminho para a base*/
    h = w->herois[heroi]; /*Caminho para o heroi*/

    presentes = cardinalidade_cjt(b.presentes); /* Quantos presentes na base*/
    lotacao = b.lotacao; /* Lotacao max da base*/

    permanencia = 15 + (h.paciencia * aleat(1, 20));

    ev = cria_evento(tempo + permanencia, SAI, heroi, base);
    insere_lef(w->lef, ev);

    printf("%6d: ENTRA  HEROI %2d BASE %d ", tempo, heroi, base);
    printf("(%2d/%2d) SAI %6d\n",presentes, lotacao, tempo + permanencia);
}

void sai(struct mundo_t *w, int tempo, int heroi, int base){
    struct evento_t *ev;
    struct base_t b;
    int nbase;

    b = w->bases[base];
    
    retira_cjt(b.presentes, heroi); /* Retira heroi da Base*/
    nbase = aleat(0, w->n_bases-1); /* Define uma nova base*/

    /* Cria evento de viagem para nova base*/
    ev = cria_evento(tempo, VIAJA, heroi, nbase);
    insere_lef(w->lef, ev);

    ev = cria_evento(tempo, AVISA, -1, base);
    insere_lef(w->lef, ev); 

    printf("%6d: SAI    HEROI %2d BASE %d)",tempo, heroi, base);
    
    printf("(%2d/%2d)\n", cardinalidade_cjt(b.presentes), b.lotacao);
}

void viaja(struct mundo_t *w, int tempo, int heroi, int base){
    struct base_t base_atual, base_proxima;
    struct evento_t *ev;
    struct heroi_t h;
    int duracao, dist;

    h = w->herois[heroi]; /* Caminho do heroi */
    base_atual = w->bases[h.base]; /*Base atual do heroi */
    base_proxima = w->bases[base];/* Proxima base */

    /*Calcula a distancia entre elas e a duracao da viagem*/
    dist = distancia_cartesiana(base_atual.coordenadas, base_proxima.coordenadas);
    duracao = dist / h.velocidade;

    /* Cria evento de chegada para a base destino */
    ev = cria_evento(tempo + duracao, CHEGA, heroi, base);
    insere_lef(w->lef, ev);

    printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d ", tempo, heroi, h.base, base);
    printf("DIST %6d VEL %d CHEGA %6d\n", dist ,h.velocidade, tempo + duracao);

}

int missao(struct mundo_t *w, int tempo, int missao){
    struct local_t loc_missao;/*Local em que a missao ocorrera*/
    struct conjunto *requeridas, *uniao; 
    struct evento_t *ev;
    int dist[w->n_bases]; /* Vetor com as distancias de todas as bases*/
    int i, menor_valido, heroi;
    int k;

    requeridas = w->missoes[missao].habi_req;
    loc_missao = w->missoes[missao].local_missao;

    printf("%6d: MISSAO %d HAB REQ: ", tempo, missao);
    imprime_cjt(requeridas); /*Mensagem base da missao*/

    /*Insere no vetor todas as distancias das bases ate a missao*/
    for(i = 0; i < w->n_bases; i++){
        dist[i]= distancia_cartesiana(loc_missao, w->bases[i].coordenadas);
    }/*Tem que inserir ordenado ou usar fila*/

    menor_valido = -1; /* Posicao invalida */

    i = 0; /* representar o indice do vetor e a base */
    /* Enquanto tem bases para analisar procura a menor valida*/
    while (i < w->n_bases-1){

        printf("%6d: MISSAO %d BASE %d DIST %d HEROIS ", tempo, missao, i, dist[i]);
        imprime_cjt(w->bases[i].presentes);

        inicia_iterador_cjt(w->bases[i].presentes);
        while (incrementa_iterador_cjt(w->bases[i].presentes, &k)) {
            printf("%6d: MISSAO %d HAB HEROI %d: ", tempo, missao, k);
            imprime_cjt(w->herois[k].habilidades);
        }

        /* Cria um conjunto com as habiliddades dos presentes na base*/
        uniao = uniao_cjt(requeridas, w->bases[i].presentes);
        printf("%6d: MISSAO %d UNIAO HAB BASE %d: ", tempo, missao, i);
        imprime_cjt(uniao);

        /*Se o conjunto tem as habilidades e o atual eh menor que anterior*/
        if(contido_cjt(requeridas, uniao) && dist[menor_valido] > dist[i]){ /* Se esse conjunto tem todas as hab validas*/
            menor_valido = i; /* Atualiza o valor*/
        }
        i++; /* Itera para testar outra base*/
        uniao = destroi_cjt(uniao);
    }
    
    if(menor_valido == -1){ 
        printf("%6d: MISSAO IMPOSSIVEL %d IMPOSSIVEL\n", tempo, missao);
        ev = cria_evento(tempo + 24*60, MISSAO, -1,-1);
        insere_lef(w->lef, ev);
        return 0;
    } else {
        /* Se achou uma base*/
        inicia_iterador_cjt (w->bases[menor_valido].presentes); /* inicia o ptr do conjunto*/

        while(incrementa_iterador_cjt(w->bases[menor_valido].presentes, &heroi))
            (w->herois[heroi].experiencia)++; /*Incrementa o xp do heroi*/
        }
        return 1;
    }

void fim(struct mundo_t *w, int cumpridas, int agendadas){
    int i;
    float porcentagem, media;
    media = agendadas/cumpridas;
    porcentagem = cumpridas/w->n_missoes;

    for(i = 0; i < w->n_herois; i++){
        printf("HEROI  %d PAC  %d VEL %d EXP %d HABS ", i,w->herois[i].paciencia, w->herois[i].velocidade, w->herois[i].experiencia );
        if(!vazio_cjt(w->herois[i].habilidades))
            imprime_cjt(w->herois[i].habilidades);
    }
    printf("MISSOES CUMPRIDAS: %d/%d (%.2f%%)\n", cumpridas, w->n_missoes, porcentagem);
    printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.2f", agendadas, cumpridas, media );
    destroi_mundo(w);
}
    
void destroi_mundo(struct mundo_t *w){
    int heroi, base, missao;

    destroi_cjt(w->habilidades);

    /*Para cada heroi destroi conjunto de habilidades*/
    for (heroi = 0; heroi < w->n_herois; heroi++) {
        destroi_cjt(w->herois[heroi].habilidades);
    }

    /*Para cada base destroi*/
    for(base = 0; base < w->n_bases; base++){
        destroi_cjt(w->bases[base].presentes); /* conjunto dos presentes na base*/
        fila_destroi(&w->bases[base].espera); /* Fila de espera*/
    }
    
    for (missao = 0; missao < w->n_missoes; missao++) {
        destroi_cjt(w->missoes[missao].habi_req);
    }      
        destroi_lef(w->lef);

    }
