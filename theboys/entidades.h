#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "conjunto.h"
#include "fila.h"

#define T_INICIO 0
#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)

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

typedef struct local_t
{
  int x;
  int y;
} local_t;

typedef struct heroi_t
{
  int id_heroi;
  struct cjto_t *habilidades; // Habilidades que o heroi possui
  int paciencia, velocidad, experiencia;
  int base_id;
  bool morto;
} heroi_t;

typedef struct base_t
{
  int id_base;
  local_t local;
  int lotacao;
  struct cjto_t *presentes; // IDs dos herois que estao atualmente na base
  struct fila_t *espera; // Fila para poder entrar na base
  int n_missoes_participadas;
  int fila_max;
} base_t;

typedef struct missao_t
{
  int id_missao;
  local_t local;
  struct cjto_t *habilidades;
  int tentativas;
  int perigo;
  bool cumprida;
} missao_t;

typedef struct mundo_t
{
  heroi_t *herois;
  base_t *bases;
  missao_t *missoes;
  int n_herois, n_bases, n_missoes, n_habilidades;
  int relogio;
  local_t tamanho_mundo;
  int total_events;
} mundo_t;

typedef struct event_t
{
    int tipo;
    int tempo; 
    int h_id;  // id del héroe 
    int b_id;  // id de la base 
    int m_id;  // id da missao
} event_t;

int calcula_distancia(struct local_t c1, struct local_t c2);

heroi_t *cria_heroi (int id);
heroi_t *destroi_heroi(heroi_t *h);

base_t *cria_base (int id);
base_t *destroi_base(base_t *b);

missao_t *cria_missao (int id);
missao_t *destroi_missao(missao_t *m);


#endif