#include <stdio.h>
#include <stdlib.h>
#include "entidades.h"
#include "fprio.h"
#include "mundo.h"
#include "conjunto.h"
#include "fila.h"
#include "lista.h"

// herois
heroi_t *cria_heroi (int id)
{
    heroi_t *h;

    h = malloc(sizeof(struct heroi_t));
    if (!h)
        return NULL;

    h->id_heroi = id;
    h->base_id = -1;
    h->experiencia = 0;
    h->paciencia = rand() % (100 - 0 + 1) + 0;
    h->velocidad = rand() % (5000 - 50 + 1) + 50;
    h->morto = false;

    // habilidades
    int qtd_hab_heroi = rand() % (3 - 1 + 1) + 1;
    h->habilidades = cjto_aleat(qtd_hab_heroi, N_HABILIDADES);

    return h;
}

heroi_t *destroi_heroi(heroi_t *h)
{
    if (!h)
        return NULL;

    if (h->habilidades)
        cjto_destroi(h->habilidades);
    
    free(h);

    return NULL;
}

// bases
base_t *cria_base (int id)
{
    base_t *b;

    b = malloc(sizeof(struct base_t));
    if (!b)
        return NULL;

    b->id_base = id;

    b->local.x = rand() % ((N_TAMANHO_MUNDO - 1) - 0 + 1) + 0;
    b->local.y = rand() % ((N_TAMANHO_MUNDO - 1) - 0 + 1) + 0;

    b->fila_max = 0;
    b->n_missoes_participadas = 0;
    b->lotacao = rand() % (10 - 3 + 1) + 3;
    b->presentes = cjto_cria(N_HEROIS);
    b->espera = fila_cria();

    return b;
}

base_t *destroi_base(base_t *b)
{
    if (!b)
        return NULL;

    if (b->presentes)
        cjto_destroi(b->presentes);

    if (b->espera)
        fila_destroi(b->espera);

    free(b);
    return NULL;
}

// missao
missao_t *cria_missao (int id)
{
    missao_t *m;

    m = malloc(sizeof(struct missao_t));
    if (!m)
        return NULL;

    m->id_missao = id;
    m->local.x = rand() % ((N_TAMANHO_MUNDO - 1) - 0 + 1) + 0;
    m->local.y = rand() % ((N_TAMANHO_MUNDO - 1) - 0 + 1) + 0;

    // habilidades missao
    int qtd_hab_missao = rand() % (6 - 3 + 1) + 3;
    m->perigo = rand() % (100 - 0 + 1) + 0;
    m->habilidades = cjto_aleat(qtd_hab_missao, N_HABILIDADES);
    m->tentativas = 0;
    m->cumprida = 0;

    return m;
}

missao_t *destroi_missao(missao_t *m)
{
    if (!m)
        return NULL;

    if (m->habilidades)
        cjto_destroi(m->habilidades);

    free(m);
    return NULL;
}

// calculo de distancia
int calcula_distancia(struct local_t c1, struct local_t c2)
{
  return sqrt(((c2.x - c1.x) * (c2.x - c1.x)) + ((c2.y - c1.y) * (c2.y - c1.y)));
}