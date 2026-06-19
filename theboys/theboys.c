// programa principal do projeto "The Boys - 2026/1"
// Autor: Maria Victoria Aviles, GRR 20250429

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "conjunto.h"
#include "fila.h"
#include "fprio.h"
#include "entidades.h"
#include "eventos.h"

// minimize o uso de variáveis globais

int main ()
{
  srand(0);
  mundo_t *w = mundo_criar();

  for(int i=0; i<N_HEROIS; i++) 
    agendar_evento(w, EVENT_CHEGA, rand()%4320, i, rand()%N_BASES, -1);
    for(int i=0; i<N_MISSOES; i++) 
      agendar_evento(w, EVENT_MISSAO, rand()%T_FIM_DO_MUNDO, -1, -1, i);
    agendar_evento(w, EVENT_FIM, T_FIM_DO_MUNDO, -1, -1, -1);

  event_t *ev;
  int t;
  int tipo;
  while ((ev = fprio_retira(w->lef, &tipo, &t))) 
  {
    w->relogio = t;
    w->eventos_tratados++;

    if (ev->h_id != -1 && !w->herois[ev->h_id].vivo && ev->tipo != EVENT_MORRE) 
    {
      free(ev); continue;
    }

    switch (ev->tipo) 
    {
      case EVENT_CHEGA: evento_chega(w, ev); break;
      case EVENT_ESPERA: evento_espera(w, ev); break;
      case EVENT_DESISTE: evento_avisa(w, ev); break;
      case EVENT_AVISA: evento_chega(w, ev); break;
      case EVENT_ENTRA: evento_espera(w, ev); break;
      case EVENT_SAI: evento_avisa(w, ev); break;
      case EVENT_VIAJA: evento_chega(w, ev); break;
      case EVENT_MISSAO: evento_espera(w, ev); break;
      case EVENT_MORRE: evento_avisa(w, ev); break;
      case EVENT_FIM: evento_fim(w, ev); mundo_destruir(w); free(ev); return 0;
    }

    free(ev);
  }
  return (0) ;
}
