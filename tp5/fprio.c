#include <stdio.h>
#include <stdlib.h>
#include "fprio.h"

struct fpnodo_t
{
  void *item ;          // item associado ao nodo
  int   tipo ;          // tipo do item
  int   prio ;          // prioridade do item
  struct fpnodo_t *prox;    // próximo nodo
};

// descreve uma fila de prioridades
struct fprio_t
{
  struct fpnodo_t *prim ;   // primeiro nodo da fila
  int num ;         // número de itens na fila
} ;

// A COMPLETAR

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fprio_t *fprio_cria ()
{
  struct fprio_t *f = malloc(sizeof(struct fprio_t));
  if (!f) return NULL;
  f->prim = NULL;
  f->num = 0;
  return f;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fprio_t *fprio_destroi (struct fprio_t *f)
{
  if (!f) return NULL;

  struct fpnodo_t *atual = f->prim;
  struct fpnodo_t *aux;

  while (atual != NULL) 
  {
    aux = atual;
    atual = atual->prox;

    free(aux->item); 

    free(aux);
    }

  free(f);
    
    return NULL;
}

// Insere o item na fila, mantendo-a ordenada por prioridades crescentes.
// Itens com a mesma prioridade devem respeitar a politica FIFO (retirar
// na ordem em que inseriu).
// Inserir duas vezes o mesmo item (o mesmo ponteiro) é um erro.
// Retorno: número de itens na fila após a operação ou -1 se erro.
int fprio_insere (struct fprio_t *f, void *item, int tipo, int prio)
{
  if (!f || !item) return -1;

  struct fpnodo_t *aux = f->prim;
  while (aux) 
  {
    if (aux->item == item) return -1;
    aux = aux->prox;
  }

  struct fpnodo_t *novo = malloc(sizeof(struct fpnodo_t));
  if (!novo) return -1;

  novo->item = item;
  novo->tipo = tipo;
  novo->prio = prio;

  if (!f->prim || prio < f->prim->prio) 
  {
    novo->prox = f->prim;
        f->prim = novo;
  } 
  else {
  aux = f->prim;
  while (aux->prox != NULL && aux->prox->prio <= prio) 
  {
    aux = aux->prox;
  }

  novo->prox = aux->prox;
  aux->prox = novo;
  }

  f->num++;
  return f->num;
}

// Retira o primeiro item da fila e o devolve; o tipo e a prioridade
// do item são devolvidos nos parâmetros "tipo" e "prio".
// Retorno: ponteiro para o item retirado ou NULL se fila vazia ou erro.
void *fprio_retira (struct fprio_t *f, int *tipo, int *prio)
{
  if (f == NULL || f->prim == NULL) 
  {
    return NULL;
  }

  struct fpnodo_t *remover = f->prim;

  void *item = remover->item;

  if (tipo != NULL) *tipo = remover->tipo;
  if (prio != NULL) *prio = remover->prio;

  f->prim = f->prim->prox;
  
  f->num--;

  free(remover);

  return item;
}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fprio_tamanho (struct fprio_t *f)
{
  if (f == NULL) 
  {
    return -1;
  }

  return f->num;
}

// Imprime o conteúdo da fila no formato "(tipo prio) (tipo prio) ..."
// Para cada item deve ser impresso seu tipo e sua prioridade, com um
// espaço entre valores, sem espaços antes ou depois e sem nova linha.
void fprio_imprime (struct fprio_t *f)
{
  if (!f || !f->prim) return;

  struct fpnodo_t *aux = f->prim;

  while (aux != NULL) 
  {
    printf("(%d %d)", aux->tipo, aux->prio);
        
    if (aux->prox != NULL) 
    {
      printf(" ");
    }
        
    aux = aux->prox;
  }
}