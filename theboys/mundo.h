#ifndef WORLD
#define WORLD

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "conjunto.h"
#include "fila.h"
#include "fprio.h"
#include "entidades.h"


mundo_t* mundo_criar();

void agendar_evento(mundo_t *w, struct fprio_t *lef);

void execute_events(mundo_t *w, struct fprio_t *lef);

// Analisa as bases disponiveis ordenadas por distancia e verifica qual delas possui herois com as habilidades necessarias 
// para a missao.
// Retorna o ID da base escolhida ou -1 se a missao for impossivel
int encontrar_base_mais_proxima(mundo_t *w, struct missao_t *mi, struct fprio_t *dists);

void mundo_destruir(mundo_t *w);

#endif