#include "conjunto.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct cjto_t *cjto_cria(int cap) {
    struct cjto_t *c = malloc(sizeof(struct cjto_t));
    if (!c) return NULL;

    c->cap = cap;
    c->num = 0;
    c->flag = calloc(cap, sizeof(bool)); // Inicializa todos como false (0)
    
    if (!c->flag) {
        free(c);
        return NULL;
    }
    return c;
}

struct cjto_t *cjto_destroi(struct cjto_t *c) {
    if (c) {
        free(c->flag);
        free(c);
    }
    return NULL;
}

struct cjto_t *cjto_copia(struct cjto_t *c) {
    if (!c) return NULL;
    struct cjto_t *novo = cjto_cria(c->cap);
    if (!novo) return NULL;

    novo->num = c->num;
    for (int i = 0; i < c->cap; i++) novo->flag[i] = c->flag[i];
    return novo;
}

struct cjto_t *cjto_aleat(int n, int cap) {
    struct cjto_t *c = cjto_cria(cap);
    if (!c) return NULL;
    
    srand(time(NULL));
    int cont = 0;
    while (cont < n) {
        int r = rand() % cap;
        if (!c->flag[r]) {
            c->flag[r] = true;
            c->num++;
            cont++;
        }
    }
    return c;
}

int cjto_insere(struct cjto_t *c, int item) {
    if (!c || item < 0 || item >= c->cap) return -1;
    if (!c->flag[item]) {
        c->flag[item] = true;
        c->num++;
    }
    return c->num;
}

int cjto_retira(struct cjto_t *c, int item) {
    if (!c || item < 0 || item >= c->cap) return -1;
    if (c->flag[item]) {
        c->flag[item] = false;
        c->num--;
    }
    return c->num;
}

int cjto_card(struct cjto_t *c) {
    return c ? c->num : -1;
}

int cjto_pertence(struct cjto_t *c, int item) {
    if (!c || item < 0 || item >= c->cap) return -1;
    return c->flag[item] ? 1 : 0;
}

int cjto_iguais(struct cjto_t *c1, struct cjto_t *c2) {
    if (!c1 || !c2 || c1->cap != c2->cap) return -1;
    if (c1->num != c2->num) return 0;
    for (int i = 0; i < c1->cap; i++)
        if (c1->flag[i] != c2->flag[i]) return 0;
    return 1;
}

int cjto_contem(struct cjto_t *c1, struct cjto_t *c2) {
    if (!c1 || !c2) return -1;
    for (int i = 0; i < c2->cap; i++)
        if (c2->flag[i] && (i >= c1->cap || !c1->flag[i])) return 0;
    return 1;
}

struct cjto_t *cjto_uniao(struct cjto_t *c1, struct cjto_t *c2) {
    if (!c1 || !c2) return NULL;
    struct cjto_t *res = cjto_copia(c1);
    for (int i = 0; i < c2->cap; i++)
        if (c2->flag[i]) cjto_insere(res, i);
    return res;
}

struct cjto_t *cjto_inter(struct cjto_t *c1, struct cjto_t *c2) {
    if (!c1 || !c2) return NULL;
    struct cjto_t *res = cjto_cria(c1->cap < c2->cap ? c1->cap : c2->cap);
    for (int i = 0; i < res->cap; i++)
        if (c1->flag[i] && c2->flag[i]) cjto_insere(res, i);
    return res;
}

struct cjto_t *cjto_dif(struct cjto_t *c1, struct cjto_t *c2) {
    if (!c1 || !c2) return NULL;
    struct cjto_t *res = cjto_copia(c1);
    for (int i = 0; i < c2->cap; i++)
        if (i < res->cap && c2->flag[i]) cjto_retira(res, i);
    return res;
}

void cjto_imprime(struct cjto_t *c) {
    if (!c) return;
    bool primeiro = true;
    for (int i = 0; i < c->cap; i++) {
        if (c->flag[i]) {
            if (!primeiro) printf(" ");
            printf("%d", i);
            primeiro = false;
        }
    }
}