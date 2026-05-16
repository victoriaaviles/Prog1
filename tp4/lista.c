#include "lista.h"
#include <stdlib.h>

struct nodo 
{
    int chave;
    struct nodo *prox;
};

struct lista 
{
    struct nodo *ini;
    struct nodo *ptr; /* ponteiro para algum nodo da lista (iterador) */
    int tamanho;
};

struct lista *lista_cria ()
{
    struct lista *list = malloc (sizeof (struct lista));

    if (list != NULL)
    {
        list -> ini = NULL;
        list -> ptr = NULL;
        list -> tamanho = 0;
    }

    return list;
}

void lista_destroi (struct lista **lista)
{
    if (lista == NULL || *lista == NULL)
    return;

    struct nodo *atual = (*lista) -> ini;
    struct nodo *proximo;

    while (atual != NULL)
    {
        proximo = atual -> prox;
        free (atual);
        atual = proximo;
    }

    free (*lista);
    *lista = NULL;
}

int lista_insere_inicio (struct lista *lista, int chave)
{
    if (lista == NULL)
    {
        return 0;
    }

    struct nodo *novo = (struct nodo *) malloc(sizeof(struct nodo));

    if (novo == NULL)
    {
        return 0;
    }

    novo->chave = chave;
    novo->prox = lista->ini;
    lista->ini = novo;
    lista->tamanho++;

    return 1;
}

int lista_insere_fim (struct lista *lista, int chave)
{
    if (lista == NULL)
    {
        return 0;
    }

    struct nodo *novo = (struct nodo *) malloc(sizeof(struct nodo));
    if (novo == NULL)
    {
        return 0;
    }

    novo->chave = chave;
    novo->prox = NULL;

    if (lista_vazia (lista))
    {
        lista->ini = novo;
    }

    else 
    {
        struct nodo *aux = lista->ini;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }

        aux->prox = novo;
    }

    lista->tamanho++;

    return 1;
}

int lista_insere_ordenado (struct lista *lista, int chave)
{
    if (lista == NULL)
    {
    return 0;
    }

    struct nodo *novo = (struct nodo *) malloc(sizeof(struct nodo));
    if (novo == NULL)
    {
    return 0;
    }
    
    novo->chave = chave;

    struct nodo *anterior = NULL;
    struct nodo *atual = lista->ini;

    while (atual != NULL && atual->chave < chave) 
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (anterior == NULL) 
    {
        novo->prox = lista->ini;
        lista->ini = novo;
    } 
    else 
    {
        novo->prox = atual;
        anterior->prox = novo;
    }

    lista->tamanho++;
    return 1;
}

int lista_remove_inicio (struct lista *lista, int *chave)
{
    if (lista_vazia(lista))
    {
        return 0; 
    }

    struct nodo *aux = lista->ini;
    if (chave != NULL)
    {
        *chave = aux->chave;
    }

    lista->ini = aux->prox;
    free(aux);

    lista->tamanho--;
    return 1;
}

int lista_remove_fim (struct lista *lista, int *chave)
{
    if (lista_vazia(lista)) 
    {
        return 0;
    }

    struct nodo *anterior = NULL;
    struct nodo *atual = lista->ini;

    while (atual->prox != NULL) 
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (chave != NULL)
    {
        *chave = atual->chave;
    }

    if (anterior == NULL)
    {
        lista->ini = NULL;
    } 
    else 
    {
        anterior->prox = NULL;
    }

    free(atual);
    lista->tamanho--;
    return 1;
}

int lista_remove_ordenado (struct lista *lista, int chave)
{
    if (lista_vazia(lista)) 
    {
        return 0;
    }

    struct nodo *anterior = NULL;
    struct nodo *atual = lista->ini;

    while (atual != NULL && atual->chave != chave) 
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL)
    {
        return 0;
    }

    if (anterior == NULL) 
    {
        lista->ini = atual->prox;
    } 
    else 
    {
        anterior->prox = atual->prox;
    }

    free(atual);
    lista->tamanho--;
    return 1;
}

int lista_vazia (struct lista *lista)
{
    if (lista == NULL || lista->ini == NULL)
    {
        return 1;
    }
    return 0;
}

int lista_tamanho (struct lista *lista)
{
    if (lista == NULL)
    {
        return 0;
    }

    return lista->tamanho;
}

int lista_pertence (struct lista *lista, int chave)
{
    if (lista_vazia (lista))
    {
        return 0;
    }

    int valor_atual;

    lista_inicia_iterador (lista);

    while (lista_incrementa_iterador (lista, &valor_atual))
    {
        if (valor_atual == chave)
        {
            return 1;
        }
    }

    return 0;
}

void lista_inicia_iterador (struct lista *lista)
{
    if (lista != NULL)
    {
        lista->ptr = lista->ini;
    }
}

int lista_incrementa_iterador (struct lista *lista, int *chave)
{
    if (lista == NULL || lista->ptr == NULL)
    {
        return 0;
    }

    *chave = lista->ptr->chave;
    lista->ptr = lista->ptr->prox;
    return 1;
}
