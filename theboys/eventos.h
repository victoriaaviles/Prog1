#ifndef EVENTOS
#define EVENTOS

#include "entidades.h"

#define EVENT_CHEGA   1
#define EVENT_ESPERA  2
#define EVENT_DESISTE 3
#define EVENT_AVISA   4
#define EVENT_ENTRA   5
#define EVENT_SAI     6
#define EVENT_VIAJA   7
#define EVENT_MISSAO  8
#define EVENT_MORRE   9
#define EVENT_FIM     10

void evento_chega (mundo_t *w, event_t *event);

void evento_espera (mundo_t *w, event_t *event);

void evento_desiste (mundo_t *w, event_t *event);

void evento_avisa (mundo_t *w, event_t *event);

void evento_entra (mundo_t *w, event_t *event);

void evento_sai (mundo_t *w, event_t *event);

void evento_viaja (mundo_t *w, event_t *event);

void evento_morre (mundo_t *w, event_t *event);

void evento_missao (mundo_t *w, event_t *event);

void evento_fim (mundo_t *w, event_t *event);

#endif