/* Estado Inicial */
#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS  N_HABILIDADES * 5
#define N_BASES N_HEROIS / 6
#define N_MISSOES  T_FIM_DO_MUNDO / 100


/* Codigo dos Eventos */
#define CHEGA 1
#define ESPERA 2
#define DESISTE 3
#define AVISA 4
#define ENTRA 5
#define SAI 6
#define VIAJA 7
#define MISSAO 8
#define FIM 9

/* Estrutura das Entidades */

/* Estrutura do Heroi */
struct heroi_t {
    int id;
    struct conjunto *habilidades; /* Conjunto de habilidades do heroi */
    int paciencia; 
    int velocidade;
    int experiencia;
    int base; /* id da base que se encontra atualmente */
};

/* Estrutura Auxiliar de local */
struct local_t {
    int x;
    int y;
};
/* Estrutura da Base */
struct base_t {
    int id;
    int lotacao;
    struct conjunto *presentes; /* lista com os presentes na base */
    struct fila *espera;        /* fila de espera da base */
    struct local_t coordenadas; /* localizacao da base no mundo */
};

/* Estrutura da Missao */
struct missao_t {
    int id;                    /* Inteiro que Identifica a Missao*/
    struct conjunto *habi_req; /* Lista das Habilidades Requeridas pela Missao*/
    struct local_t local_missao;
};

/* Estrutura do Mundo */
struct mundo_t {
    int n_herois; 
    struct heroi_t herois[N_HEROIS];
    int n_bases;
    struct base_t bases[N_BASES];
    int n_missoes;  /* Numero Total de Missoes a Cumprir*/
    struct missao_t missoes[N_MISSOES]; /* Vetor com todas as missoes*/
    int n_habilidades;      /* Numero de Habilidades Distintas Possiveis*/
    struct conjunto *habilidades;   /*Todas as habilidades distintas*/
    int n_tam_mundo;       /*Coordenadas Maximas do Plano Cartesiano*/
    int relogio;     /*Inteiro para representar tempo atual no mundo*/
    struct lef_t *lef;   /* Lista dos eventos futuros*/
};

/* Gera numero aleatorio entre min e max */
int aleat (int min, int max);

/* Calcula a distancia cartesiana entre dois pontos */
int distancia_cartesiana( struct local_t A, struct local_t B);

/* Calcula a distancia de uma base */
int base_proxima_valida(struct mundo_t *w, int base);

/* Cria o mundo e suas entidades  */
struct mundo_t cria_mundo();
struct heroi_t cria_heroi(struct mundo_t *w, int id);
struct missao_t cria_missao(struct mundo_t *w, int id);
struct base_t cria_base (struct mundo_t *w, int id);
void eventos_iniciais(struct mundo_t *w);
void destroi_mundo(struct mundo_t *w);

/* Eventos da simulacao */
void chega(struct mundo_t *w, int tempo, int heroi, int base);
void espera(struct mundo_t *w, int tempo, int heroi, int base);
void desiste(struct mundo_t *w, int tempo, int heroi, int base);
void viaja(struct mundo_t *w, int tempo, int heroi, int base);
int missao(struct mundo_t *w,int tempo, int missao);
void sai(struct mundo_t *w, int tempo, int heroi, int base);
void entra(struct mundo_t *w, int tempo, int heroi, int base);
void avisa(struct mundo_t *w, int tempo, int base);
void fim(struct mundo_t *w, int cumpridas, int agendadas);