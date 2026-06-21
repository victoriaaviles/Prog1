// programa principal do projeto "The Boys - 2026/1"
// Autor: Maria Victoria Aviles, GRR 20250429

#include <stdio.h>
#include <stdlib.h>
#include "mundo.h"
#include "fprio.h"

int main ()
{
  srand(0);
  mundo_t *w = mundo_criar();

  w = mundo_criar();

  if (!w)
    return -1;

  struct fprio_t *lef;
  lef = fprio_cria();

  if (!lef)
  {
    mundo_destruir(w);
    return -1;
  }

  agendar_evento (w, lef);
  execute_events(w, lef);
  
  return (0) ;
}
