#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "conjunto.h"
#include "entidades.h"
#include "eventos.h"
#include "fila.h"
#include "fprio.h"
#include "mundo.h"

struct event_t *cria_event(int tipo, int tempo, int h_id, int b_id, int m_id)
{
    event_t *event;

    event = malloc(sizeof(struct event_t));
    if (!event)
        return NULL;

    event->tempo = tempo;
    event->tipo = tipo;
    event->h_id = h_id;
    event->m_id = m_id;
    event->b_id = b_id;

    return event;
}

// Heroi H chegando em uma base B no instante T
void evento_chega (mundo_t *w, event_t *event, struct fprio_t *lef)
{
    heroi_t *h = &w->herois[event->h_id];
    base_t *b = &w->bases[event->b_id];
    int temp = event->tempo;

    printf("%6d: CHEGA  HEROI %2d BASE %d (%2d/%2d) ", temp, h, b, cjto_card(b->presentes), b->lotacao);

    h->base_id = b->id_base;
    int espera = 0;
    int evento_tipo;

    // verifica se há vagas e se a fila é vazia
    if (cjto_card(b->presentes) < b->lotacao && fila_tamanho(b->presentes) == 0)
        espera = 1;
    else
        espera = (h->paciencia) > (10 * fila_tamanho(b->espera));

    if (espera == 1)
    {
        printf ("ESPERA");
        event = cria_event (evento_espera, temp, h, b, -1);
        fprio_insere (lef, event, 0, temp);
    }
    else
    {
        printf ("DESISTE");
        event_t *event = cria_event (evento_desiste, temp, h, b, -1);
        fprio_insere (lef, event, 0, temp);
    }
}

void evento_espera (mundo_t *w, event_t *event, struct fprio_t *lef)
{
    heroi_t *h = &w->herois[event->h_id];
    base_t *b = &w->bases[event->b_id];
    int temp = event->tempo;

    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)", temp, h, b, fila_tamanho(b->espera));

    fila_insere (b->espera, h);

    if (fila_tamanho (b->espera) > b->fila_max)
        b->fila_max = fila_tamanho(b->espera);

    event_t *event = cria_event (evento_avisa, temp, h, b, -1);
    fprio_insere (lef, event, 0, temp);
}

void evento_desiste (mundo_t *w, event_t *event, struct fprio_t *lef)
{
    heroi_t *h = &w->herois[event->h_id];
    base_t *b = &w->bases[event->b_id];
    int temp = event->tempo;

    printf("%6d: DESIST HEROI %2d BASE %d\n", temp, h, b);

    int d_id = rand() % N_BASES; // d_id = destino id

    event_t *event = cria_event (evento_viaja, temp, h, d_id, -1);
    fprio_insere (lef, event, 0, temp);
}

void evento_avisa (mundo_t *w, event_t *event, struct fprio_t *lef)
{
    base_t *b = &w->bases[event->b_id];
    int temp = event->tempo;

    printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ", 
        temp, b->id_base, cjto_card(b->presentes), b->lotacao);

    fila_imprime(b->espera);
    printf(" ]\n");

    while ((cjto_card(b->presentes) < b->lotacao) && 
        (fila_tamanho(b->espera) > 0))
    {
        int h_id;
        fila_retira(b->espera, &h_id);
        cjto_insere(b->presentes, h_id); 

        printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", temp, b, h_id);   
        
        event_t *event = cria_event (evento_entra, temp, h_id, b, -1);
        fprio_insere (lef, event, 0, temp);
    }
}

void evento_entra (mundo_t *w, event_t *event, struct fprio_t *lef)
{
    heroi_t *h = &w->herois[event->h_id];
    base_t *b = &w->bases[event->b_id];
    int temp = event->tempo;

    int temp_permanencia = 15 + h->paciencia * ((rand() % 20) + 1); //calculo do tempo de permanencia na base
    int temposaida = w->relogio + temp_permanencia;

    printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", 
        temp, h, b, cjto_card(b->presentes), b->lotacao, temposaida);

    event_t *event = cria_event (evento_entra, temp, h, b, -1);
    fprio_insere (lef, event, 0, temp + temp_permanencia);
}

void evento_sai (mundo_t *w, event_t *event, struct fprio_t *lef)
{
    heroi_t *h = &w->herois[event->h_id];
    base_t *b = &w->bases[event->b_id];
    int temp = event->tempo;

    int status;
    int dest;

    if (h->morto)
        return;

    status = cjto_retira(b->presentes, h->id_heroi);
    if (status < 0)
        return;

    dest =  0 + rand() % ((w->n_bases - 1) - 0 + 1);

    event_t *evento_viaja = cria_event(evento_viaja, temp, h, dest, -1);

    status = fprio_insere (lef, event, 0, temp);
    if (status < 0)
        return;
    
    event_t *evento_avisa = cria_event(evento_avisa, temp, -1, b->id_base, -1);
    
    status = fprio_insere (lef, event, 0, temp);
    if (status < 0)
        return;

    printf("%6d: SAI  HEROI %2d BASE %d (%2d/%2d)", temp, h, b, (cjto_card(b->presentes)), b->lotacao);
}

void evento_viaja (mundo_t *w, event_t *event, struct fprio_t *lef)
{
    heroi_t *h = &w->herois[event->h_id];
    base_t *d = &w->bases[event->b_id];
    int temp = event->tempo;
    int dest = event->b_id;

    int status;

    if (h->morto)
        return;

    base_t *b = &w->bases[h->base_id];
    
    int dist = calcula_distancia(b->local, d->local);
    int duracao = dist / h->velocidad;

    event_t *event = cria_event (evento_chega, temp + duracao, h->id_heroi, dest, -1);
    fprio_insere(lef, event, 0, temp + duracao);

    if (status < 0)
        return;
    
    printf("%6d: VIAJA  HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d", temp, h, h->base_id, dest, (int)(dist + 0.5), h->velocidad, temp + duracao);
}

void evento_morre (mundo_t *w, event_t *event, struct fprio_t *lef)
{
    heroi_t *h = &w->herois[event->h_id];
    base_t *b = &w->bases[event->b_id];
    missao_t *m = &w->missoes[event->b_id];
    int temp = event->tempo;

    if (!b->presentes)
        return;
    
    cjto_retira(b->presentes, h->id_heroi);     //retira heroi do cjto
    h->morto = 1;   //////

    printf("%6d: MORRE  HEROI %2d MISSAO %d", temp, h, m);
    event_t *event = cria_event(evento_avisa, temp, -1, b->id_base, -1);
    fprio_insere (lef, event, 0, temp);
}

void evento_missao (mundo_t *w, event_t *event, struct fprio_t *lef)
{
    missao_t *m = &w->missoes[event->h_id];
    int temp = event->tempo;

    int bmp_id; 
    int dist;
    int risco;

    heroi_t *heroi;
    int tipo;
    int prio;
    int status;

    struct fprio_t *dists_bases = fprio_cria ();

    m->tentativas++;

    printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", temp, m->id_missao, m->tentativas);
    cjto_imprime(m->habilidades);
    printf(" ]\n");

    for (int i = 0; i < w->n_bases; i++) 
    {
        dist = calcula_distancia (w->bases[i].local, m->local);

        status = fprio_insere(dists_bases, &w->bases[i], w->bases[i].id_base, dist);

        if (status < 0)
            return;
    }

    bmp_id = encontrar_base_mais_proxima (w, m, dists_bases);

    if (bmp_id >= 0)
    {
        m->cumprida = true;
        struct base_t *b = &w->bases[bmp_id];

        b->n_missoes_participadas++;


        for (int j = 0; j < w->n_herois; j++)
        {
            if (cjto_pertence(b->presentes, j)) 
            {
                heroi = &w->herois[j];
                risco = m->perigo / (heroi->paciencia + heroi->experiencia + 1.0);

                if (risco > (rand() % (30 - 0 + 1) + 0))
                {
                    event_t *event = cria_event (evento_morre, temp, j, bmp_id, m);
                    status = fprio_insere(lef, event, 0, temp);

                    if (status < 0)
                        return;
                }
                else
                {
                    heroi->experiencia++;
                }
            }
        }

        printf("%6d: MISSAO %d CUMPRIDA BASE %d HABS: [ ", temp, m, w->bases[bmp_id].id_base);
        cjto_imprime(m->habilidades);
        printf(" ]\n");
    }
    else
    {
        event_t *event = cria_event (evento_missao, temp + 24 * 60, -1, -1, m);

        status = fprio_insere (lef, event, 0, temp + 24 * 60);
        if (status < 0)
            return;
        printf ("%6d: MISSAO %d IMPOSSIVEL\n", temp, m->id_missao);
    }

    while (fprio_tamanho(dists_bases) > 0)
        fprio_retira(dists_bases, &tipo, &prio);
        
    fprio_destroi (dists_bases);
}

void evento_fim (mundo_t *w, event_t *event, struct fprio_t *lef)
{
    heroi_t *heroi;
    base_t *base;
    int temp = event->tempo;

    int missoes_cumpridas = 0;
    int mortos_totais = 0;
    int soma_tent = 0;
    int max_tent = w->missoes[0].tentativas;
    int min_tent = w->missoes[0].tentativas;
    char *msg;

    printf("%6d: FIM\n\n", temp);

    // herois
    for (int h = 0; h < w->n_herois; h++)
    {
        heroi = &w->herois[h];
        msg = heroi->morto ? "MORTO" : "VIVO";

        printf("HEROI %2d %5s PAC %3d VEL %4d EXP %4d HABS [ ", heroi->id_heroi, msg, heroi->paciencia, heroi->velocidad, heroi->experiencia);

        if (heroi->morto)
            mortos_totais++;

        cjto_imprime (heroi->habilidades);
        printf(" ]\n");
    }

    // base
    for (int b = 0; b < w->n_bases; b++)
    {
        base = &w->bases[b];
        printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n", base->id_base, base->lotacao, base->fila_max, base->n_missoes_participadas);
    }

    printf("EVENTOS TRATADOS: %d\n", w->total_events);

    for (int m = 0; m < w->n_missoes; m++)
    {
        if (w->missoes[m].cumprida)
            missoes_cumpridas++;

        soma_tent += w->missoes[m].tentativas;

        if (w->missoes[m].tentativas > max_tent)
            max_tent = w->missoes[m].tentativas;

        if (w->missoes[m].tentativas < min_tent)
            min_tent = w->missoes[m].tentativas;
    }

    // missoes
    if (w->n_missoes > 0)
        printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n",
           missoes_cumpridas, w->n_missoes, (float)(missoes_cumpridas * 100) / w->n_missoes);
    else
        printf("MISSOES CUMPRIDAS: 0/%d (0.0%%)\n", w->n_missoes);

    printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", min_tent, max_tent, soma_tent / (float)w->n_missoes);
         
    printf("TAXA MORTALIDADE: %.1f%%\n", 100 * (mortos_totais) / (float)w->n_herois);
}