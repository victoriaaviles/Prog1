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
/* ---------------------------------------------------------------------- */

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

int lista_insere_inicio (struct lista *lista, int chave){

}

int lista_insere_fim (struct lista *lista, int chave){
}

int lista_insere_ordenado (struct lista *lista, int chave){
}

int lista_remove_inicio (struct lista *lista, int *chave){
}

int lista_remove_fim (struct lista *lista, int *chave){
}

int lista_remove_ordenado (struct lista *lista, int chave){
}

int lista_vazia (struct lista *lista){
}

int lista_tamanho (struct lista *lista){
}

int lista_pertence (struct lista *lista, int chave){
}

void lista_inicia_iterador (struct lista *lista){
}

int lista_incrementa_iterador (struct lista *lista, int *chave){
}
