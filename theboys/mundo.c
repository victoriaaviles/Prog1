#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mundo.h"
#include "conjunto.h"
#include "fila.h"
#include "fprio.h"
#include "entidades.h"
#include "eventos.h"

mundo_t* mundo_criar() 
{
    mundo_t *w;

    w = malloc(sizeof(mundo_t));
    if (!w)
        return NULL;

    w->n_herois = N_HEROIS;
    w->n_bases = N_BASES;
    w->n_missoes = N_MISSOES;
    w->n_habilidades = N_HABILIDADES;
    w->relogio = T_INICIO;
    w->tamanho_mundo.x = N_TAMANHO_MUNDO;
    w->tamanho_mundo.y = N_TAMANHO_MUNDO;

    w->total_events = 0;

    for (int i = 0; i < w->n_bases; i++) 
    {
        w->bases[i] = cria_base(i);
        
        if (!w->bases[i].id_base)
        {
            mundo_destruir (w);
            return NULL;
        }
    }

    for (int i = 0; i < w->n_herois; i++) 
    {
        w->herois[i].id_heroi = cria_heroi(i);

        if (!w->herois[i].id_heroi)
        {
            mundo_destruir (w);
            return NULL;
        }
    }

    for (int i = 0; i < w->n_missoes; i++) 
    {
        w->missoes[i].id_missao = cria_missao (i);

        if (!w->missoes[i].id_missao)
        {
            mundo_destruir (w);
            return NULL;
        }
    }
    return w;
}

void agendar_evento(mundo_t *w, struct fprio_t *lef)
{
    int base, tempo, status_fprio;
    struct event_t *evento;

    for (int i = 0; i < w->n_herois; i++)
    {
        base = rand() % ((w->n_bases -1) - 0 + 1) + 0;
        tempo = rand() % (4320 - 0 + 1) + 0;
        evento = cria_evento(tempo, EVENT_CHEGA, i, base);

        status_fprio = fprio_insere(lef, evento, EVENT_CHEGA, tempo);
        if (status_fprio < 0)
            return;
    }

    for (int i = 0; i < w->n_missoes; i++)
    {
        tempo = aleat(0, T_FIM_DO_MUNDO);

        evento = cria_evento(tempo, EVENT_MISSAO, i, -1);

        status_fprio = fprio_insere(lef, evento, EVENT_MISSAO, tempo);
        if (status_fprio < 0)
            return;
    }

    tempo = T_FIM_DO_MUNDO;
    evento = cria_evento(tempo, EVENT_FIM, -1, -1);
    status_fprio = fprio_insere(lef, evento, EVENT_CHEGA, tempo);

    if (status_fprio < 0)
        return;
}

void execute_events(mundo_t *w, struct fprio_t *lef)
{
    struct event_t *evento;
    int tipo, prio;

    while (w->relogio < T_FIM_DO_MUNDO)
    {
        evento = fprio_retira(lef, &tipo, &prio);

        if (!evento)
            return;
        
        w->relogio = evento->tempo;
        w->total_events++;

        switch (evento->tipo) 
        {
            case EVENT_CHEGA: evento_chega(w, evento, lef); break;
            case EVENT_ESPERA: evento_espera(w, evento, lef); break;
            case EVENT_DESISTE: evento_avisa(w, evento, lef); break;
            case EVENT_AVISA: evento_chega(w, evento, lef); break;
            case EVENT_ENTRA: evento_espera(w, evento, lef); break;
            case EVENT_SAI: evento_avisa(w, evento, lef); break;
            case EVENT_VIAJA: evento_chega(w, evento, lef); break;
            case EVENT_MISSAO: evento_espera(w, evento, lef); break;
            case EVENT_MORRE: evento_avisa(w, evento, lef); break;
            case EVENT_FIM: evento_fim(w, evento, lef); 
            mundo_destruir(w); break;
        }

        free(evento);
    }

    while (fprio_tamanho(lef) > 0)
    {
        evento = fprio_retira(lef, &tipo, &prio);
        if (evento)
            free(evento);
    }
}

int encontrar_base_mais_proxima(mundo_t *w, struct missao_t *mi, struct fprio_t *dists) 
{
    int id_base_proxima = -1;
    int id_base, dist;
    struct cjto_t *total_habilidades, *novo_total;

    while (fprio_tamanho(dists) > 0 && id_base_proxima < 0)
    {
        id_base = -1;
        dist = 1;

        total_habilidades = cjto_cria(w->n_habilidades);
        if (!total_habilidades)
            return -1;

        fprio_retira (dists, &id_base, &dist);

        printf ("%6d: MISSAO %d BASE %d DIST %d HEROIS [ ", w->relogio, mi->id_missao, id_base, dist);
        cjto_imprime (w->bases[id_base].presentes);
        print("]\n");

        for (int h = 0; h < w->n_herois; h++)
        {
            if (cjto_pertence (w->bases[id_base].presentes, h))
            {
                printf("%6d: MISSAO %d HAB HEROI %2d: [ ", w->relogio, mi->id_missao, h);
                cjto_imprime(w->herois[h].habilidades);
                printf(" ]\n");

                novo_total = cjto_uniao(total_habilidades, w->herois[h].habilidades);
                if (novo_total)
                {
                    cjto_destroi(total_habilidades);
                    total_habilidades = novo_total;
                }
            }
        }

        printf("%6d: MISSAO %d UNIAO HAB BASE %d: [ ", w->relogio, mi->id_missao, id_base);
        cjto_imprime(total_habilidades);
        printf(" ]\n");

        if (cjto_contem(total_habilidades, mi->habilidades))
        id_base_proxima = id_base;

        cjto_destroi(total_habilidades);
    }

    return id_base_proxima;
}

void mundo_destruir(mundo_t *w) 
{
    if (!w) 
        return NULL;

    for (int i = 0; i < w->n_herois; i++)
        destroi_heroi(&w->herois[i]);

    for (int i = 0; i < w->n_bases; i++) 
    {
        destroi_base(&w->bases[i]);
    }

    for (int i = 0; i < w->n_missoes; i++)
        destroi_missao(&w->missoes[i]);

    free(w);

    return NULL;
}