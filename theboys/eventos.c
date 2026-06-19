#include <stdio.h>
#include <math.h>
#include <time.h>
#include "conjunto.h"
#include "entidades.h"
#include "eventos.h"

void evento_chega (mundo_t *w, event_t *event) 
{
    int h_id = event->h_id; // h_id = heroi id
    int b_id = event->b_id; // b_id = base id
    
    w->herois[h_id].base_id = b_id;
    
    int numpresentes = cjto_card(w->bases[b_id].presentes);
    int vagaslivres = w->bases[b_id].lotacao - numpresentes;
    int tamfila = fila_tamanho(w->bases[b_id].espera);
    
    int decisaoespera;
    
    if (vagaslivres > 0 && tamfila == 0)
        decisaoespera = 1; //verdade
    else
        decisaoespera = (w->herois[h_id].paciencia > (10 * tamfila));

    printf("%6d: CHEGA HEROI %2d BASE %d (%2d/%2d) %s\n",
        w->relogio, h_id, b_id, numpresentes, w->bases[b_id].lotacao, 
        decisaoespera ? "ESPERA" : "DESISTE");

    if (decisaoespera)
        agendar_evento(w, EVENT_ESPERA, w->relogio, h_id, b_id, -1);
    else
        agendar_evento(w, EVENT_DESISTE, w->relogio, h_id, b_id, -1);
}

void evento_espera (mundo_t *w, event_t *event)
{
    int h_id = event->h_id; // h_id = heroi id
    int b_id = event->b_id; // b_id = base id

    int tamfila = fila_tamanho(w->bases[b_id].espera);

    printf("%6d: ESPERA HEROI %2d BASE %d (%2d)\n", 
        w->relogio, h_id, b_id, tamfila);
  
    fila_insere(w->bases[b_id].espera, h_id);

    agendar_evento(w, EVENT_AVISA, w->relogio, -1, b_id, -1);
}

void evento_desiste (mundo_t *w, event_t *event)
{
    int h_id = event->h_id; // h_id = heroi id
    int b_id = event->b_id; // b_id = base id

    printf("%6d: DESIST HEROI %2d BASE %d\n", 
        w->relogio, h_id, b_id);

    int d_id = rand() % N_BASES; // d_id = destino id

    agendar_evento(w, EVENT_VIAJA, w->relogio, h_id, d_id, -1);
}

void evento_avisa (mundo_t *w, event_t *event)
{
    int b_id = event->b_id;
    base_t *base = &w->bases[b_id];

    printf("%6d: AVISA PORTEIRO BASE %d (%2d/%2d) FILA [ ", 
        w->relogio, b_id, cjto_card(base->presentes), base->lotacao);

    fila_imprime(base->espera);
    printf(" ]\n");

    while ((cjto_card(base->presentes) < base->lotacao) && 
        (fila_tamanho(base->espera) > 0))
    {
        int h_id_admit = fila_retira(base->espera, 0);
        cjto_insere(base->presentes, h_id_admit); 
        printf("%6d: AVISA PORTEIRO BASE %d ADMITE %2d\n", w->relogio, b_id, h_id_admit);   
        agendar_evento(w, EVENT_ENTRA, w->relogio, h_id_admit, b_id, -1);
    }
}

void evento_entra (mundo_t *w, event_t *event)
{
    int h_id = event->h_id;
    int b_id = event->b_id;
    heroi_t *h = &w->herois[h_id];
    base_t *b = &w->bases[b_id];

    int tempo_permanencia = 15 + h->paciencia * ((rand() % 20) + 1); //calculo do tempo de permanencia na base
    int temposaida = w->relogio + tempo_permanencia;

    printf("%6d: ENTRA HEROI %2d BASE %d (%2d/%2d) SAI %d\n", 
        w->relogio, h_id, b_id, cjto_card(b->presentes), b->lotacao, temposaida);

    agendar_evento(w, EVENT_SAI, temposaida, h_id, b_id, -1);
}

void evento_sai (mundo_t *w, event_t *event)
{
    int h_id = event->h_id;
    int b_id = event->b_id;
    base_t *base = &w->bases[b_id];

    cjto_retira(base->presentes, h_id);

    int num_presentes = cjto_card(base->presentes);

    printf("%6d: SAI HEROI %2d BASE %d (%2d/%2d)\n", 
        w->relogio, h_id, b_id, num_presentes, base->lotacao);

    int d_id = rand() % w->n_bases;

    agendar_evento(w, EVENT_VIAJA, w->relogio, h_id, d_id, -1);
    agendar_evento(w, EVENT_AVISA, w->relogio, -1, b_id, -1);
}

void evento_viaja (mundo_t *w, event_t *event)
{
    int h_id = event->h_id;
    int d_id = event->b_id;

    heroi_t *h = &w->herois[h_id];

    int base_atual_id = h->base_id;      // base atual
    local_t loc_origem = w->bases[base_atual_id].local;
    local_t loc_destino = w->bases[d_id].local;

    double dist = sqrt(pow(loc_destino.x - loc_origem.x, 2) + 
        pow(loc_destino.y - loc_origem.y, 2));          // distância cartesiana
    
    int duracao = (int)dist / h->velocidad;      // duracao da viagem

    int tempo_cheg = w->relogio + duracao;     // tempo de chegada

    printf("%6d: VIAJA HEROI %2d BASE %d BASE %d DIST %d VEL %d CHEGA %d\n", 
        w->relogio, h_id, base_atual_id, d_id, (int)dist, h->velocidad, tempo_cheg);

    agendar_evento(w, EVENT_CHEGA, tempo_cheg, h_id, d_id, -1);
}

void evento_morre (mundo_t *w, event_t *event)
{
    int h_id = event->h_id;
    int m_id = event->m_id;
    int b_id = w->herois[h_id].base_id;

    cjto_retira(w->bases[b_id].presentes, h_id);     //retira heroi do cjto
    w->herois[h_id].vivo = 0;

    printf("%6d: MORRE HEROI %2d MISSAO %d\n", w->relogio, h_id, m_id);

    agendar_evento(w, EVENT_AVISA, w->relogio, -1, b_id, -1);
}

void evento_missao (mundo_t *w, event_t *event)
{
    int m_id = event->m_id;
    missao_t *m = &w->missoes[m_id];
    int bmp_id = -1; 
    double dist_min = -1.0;

    m->tentativas++;

    printf("%6d: MISSAO %d TENT %d HAB REQ: [ ", w->relogio, m_id, m->tentativas);
    cjto_imprime(m->habilidades);
    printf(" ]\n");

    for (int i = 0; i < w->n_bases; i++) 
    {
        base_t *b = &w->bases[i];
        double d = sqrt(pow(m->local.x - b->local.x, 2) + pow(m->local.y - b->local.y, 2));     // dist base -> missao

        struct cjto_t *habs_base = cjto_cria(w->n_habilidades);
        for (int j = 0; j < w->n_herois; j++) 
        {
            if (cjto_pertence(b->presentes, j)) 
            {
                struct cjto_t *temp = habs_base;
                habs_base = cjto_uniao(temp, w->herois[j].habilidades);
                cjto_destroi(temp);
            }
        }

        if (cjto_contem(habs_base, m->habilidades)) 
        {
            if (bmp_id == -1 || d < dist_min) 
            {
                dist_min = d;
                bmp_id = i;
            }
        }
        cjto_destroi(habs_base);
    }

    if (bmp_id != -1) 
    {
        processar_sucesso_missao(w, m_id, bmp_id);
    } 
    else 
    {
        if (w->relogio % 2500 == 0 && w->n_compostos_v > 0) 
        {
            int base_proxima = encontrar_base_mais_proxima_absoluta(w, m);
            w->n_compostos_v--;

        int h_morre = encontrar_heroi_mais_experiente(w, base_proxima);
            agendar_evento(w, EVENT_MORRE, w->relogio, h_morre, base_proxima, m_id);

            processar_sucesso_missao(w, m_id, base_proxima);
        }
        else 
        {
            printf("%6d: MISSAO %d IMPOSSIVEL\n", w->relogio, m_id);    //adia 24 hrs missao impossivel
            agendar_evento(w, EVENT_MISSAO, w->relogio + 1440, -1, -1, m_id);
        }
    }   
}

void evento_fim (mundo_t *w, event_t *event)
{
    printf("%6d: FIM\n", w->relogio);

    for (int i = 0; i < w->n_herois; i++) 
    {
        heroi_t *h = &w->herois[i];
        printf("HEROI %2d %s PAC %3d VEL %4d EXP %4d HABS [ ", 
               h->id, h->vivo ? "VIVO " : "MORTO", h->paciencia, 
               h->velocidad, h->experiencia);
        cjto_imprime(h->habilidades);
        printf(" ]\n");
    }

    for (int i = 0; i < w->n_bases; i++) 
    {
        base_t *b = &w->bases[i];

        printf("BASE %2d LOT %2d FILA MAX %2d MISSOES %d\n", 
            b->id, b->lotacao, b->fila_max, b->n_missoes_participadas);
    }

    double taxa_sucesso = ((double)w->missoes_cumpridas / w->n_missoes) * 100;
    double taxa_mortalidade = ((double)w->herois_mortos / w->n_herois) * 100;

    printf("EVENTOS TRATADOS: %d\n", w->eventos_tratados);
    printf("MISSOES CUMPRIDAS: %d/%d (%.1f%%)\n", 
        w->missoes_cumpridas, w->n_missoes, taxa_sucesso);
    printf("TENTATIVAS/MISSAO: MIN %d, MAX %d, MEDIA %.1f\n", 
        w->tentativas_min, w->tentativas_max, (double)w->tentativas_total / w->n_missoes);
    printf("TAXA MORTALIDADE: %.1f%%\n", taxa_mortalidade);
}