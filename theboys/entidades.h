#ifndef ENTIDADES_H
#define ENTIDADES_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "conjunto.h"

#define T_FIM_DO_MUNDO 525600
#define N_TAMANHO_MUNDO 20000
#define N_HABILIDADES 10
#define N_HEROIS (N_HABILIDADES * 5)
#define N_BASES (N_HEROIS / 5)
#define N_MISSOES (T_FIM_DO_MUNDO / 100)

typedef struct local_t
{
  int x;
  int y;
} local_t;

typedef struct heroi_t
{
  int id;
  struct cjto_t *habilidades; // Habilidades que o heroi possui
  int paciencia, velocidad, experiencia;
  int base_id;
  int vivo;
} heroi_t;

typedef struct base_t
{
  int id;
  local_t local;
  int lotacao;
  struct cjto_t *presentes; // IDs dos herois que estao atualmente na base
  struct fila *espera; // Fila para poder entrar na base
  int n_missoes_participadas;
  int fila_max;
} base_t;

typedef struct missao_t
{
  int id;
  local_t local;
  struct cjto_t *habilidades;
  int tentativas;
} missao_t;

typedef struct mundo_t
{
  heroi_t *herois;
  base_t *bases;
  missao_t *missoes;
  int n_herois, n_bases, n_missoes, n_habilidades;
  int relogio;
  struct fprio *lef;

  int eventos_tratados, missoes_cumpridas, herois_mortos, tentativas_min, tentativas_max,
  tentativas_total, n_compostos_v;
} mundo_t;

typedef struct event_t
{
    int tipo;
    int tempo; 
    int h_id;  // id del héroe 
    int b_id;  // id de la base 
    int m_id;  // id da missao
} event_t;

#endif