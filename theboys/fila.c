#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

// Cria uma fila vazia.
// Retorno: ponteiro para a fila criada ou NULL se erro.
struct fila_t *fila_cria ()
{
    struct fila_t *f = malloc(sizeof(struct fila_t));
    if (!f) 
    {
        return NULL;
    }
    f->prim = NULL;
    f->num = 0;
    return f;
}

// Libera todas as estruturas de dados da fila, inclusive os itens.
// Retorno: NULL.
struct fila_t *fila_destroi (struct fila_t *f)
{
    if (!f) 
    {
        return NULL;
    }
    
    struct fila_nodo_t *atual = f->prim;
    struct fila_nodo_t *aux;
    
    while (atual != NULL) 
    {
        aux = atual;
        atual = atual->prox;
        
        free(aux);
    }
    
    free(f);
    return NULL;
}

// Insere um item no final da fila (politica FIFO).
// Retorno: 1 se tiver sucesso ou 0 se falhar.
int fila_insere (struct fila_t *f, int item)
{
    if (!f)
    {
        return 0;
    }

    struct fila_nodo_t *novo = malloc(sizeof(struct fila_nodo_t));
    if (!novo)
    {
        return 0;
    }

    novo->item = item;
    novo->prox = NULL;

    if (f->prim == NULL)
    {
        f->prim = novo;
    } 
    else
    {
        f->ult->prox = novo;
    }

    f->ult = novo;
    f->num++;

    return 1;
}

// Retira o primeiro item da fila e o devolve
// Retorno 1 se a operação foi bem sucedida e 0 caso contrário
int fila_retira (struct fila_t *f, int *item)
{
    if (!f || f->num == 0)
    {
        return 0;
    }
    
    struct fila_nodo_t *aux = f->prim;
    *item = aux->item;
    
    f->prim = aux->prox;
    
    if (f->prim == NULL)
    f->ult = NULL;
    
    free(aux);
    
    f->num--;
    return 1;
}

// Informa o número de itens na fila.
// Retorno: N >= 0 ou -1 se erro.
int fila_tamanho (struct fila_t *f)
{
    if (f == NULL) 
    {
        return -1;
    }
    return f->num;
}

// Imprime o conteúdo da fila 
void fila_imprime (struct fila_t *f)
{
    if (!f || !f->prim)
    {
        printf("FILA VAZIA\n");
        return;
    }
    
    struct fila_nodo_t *aux = f->prim;
    
    while (aux != NULL) 
    {
        printf("%d", aux->item);
        if (aux->prox != NULL) 
        {
            printf(" ");
        }
        aux = aux->prox;
    }
    printf("\n");
}