#ifndef EVENTOS
#define EVENTOS

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "entidades.h"
#include "fprio.h"
#include "entidades.h"

event_t *cria_event(int tempo, int tipo, int h_id, int b_id, int m_id);

void evento_chega (mundo_t *w, event_t *event, struct fprio_t *lef);

void evento_espera (mundo_t *w, event_t *event, struct fprio_t *lef);

void evento_desiste (mundo_t *w, event_t *event, struct fprio_t *lef);

void evento_avisa (mundo_t *w, event_t *event, struct fprio_t *lef);

void evento_entra (mundo_t *w, event_t *event, struct fprio_t *lef);

void evento_sai (mundo_t *w, event_t *event, struct fprio_t *lef);

void evento_viaja (mundo_t *w, event_t *event, struct fprio_t *lef);

void evento_morre (mundo_t *w, event_t *event, struct fprio_t *lef);

void evento_missao (mundo_t *w, event_t *event, struct fprio_t *lef);

void evento_fim (mundo_t *w, event_t *event);

#endif