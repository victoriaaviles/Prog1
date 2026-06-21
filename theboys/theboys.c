// programa principal do projeto "The Boys - 2026/1"
// Autor: Maria Victoria Aviles, GRR 20250429

#include <stdio.h>
#include <stdlib.h>
#include "mundo.h"
#include "fprio.h"

int main ()
{
  srand(0);

  // inicializacao do mundo
  mundo_t *w = mundo_criar();

  if (!w)
    return -1;

  // eventos futuros
  struct fprio_t *lef;
  lef = fprio_cria();

  if (!lef)
  {
    mundo_destruir(w);
    return -1;
  }

  // eventos iniciais 
  // simulacao do mundo
  agendar_evento (w, lef);
  execute_events(w, lef);

  mundo_destruir (w);
  fprio_destroi (lef);

  return (0) ;
}
