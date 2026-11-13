#include "teamlist.h"
#include <stdlib.h>

// Implementação do TAD TeamList com LISTA DUPLAMENTE ENCADEADA.

struct node {
    Team *team;
    struct node *next;
    struct node *prev;
};

struct teamlist {
    struct node *first;
    struct node *last;
    int size;
};

TeamList *tl_create(void) {
    TeamList *tl = malloc(sizeof(TeamList));

    if (tl == NULL)
        return NULL;

    tl->first = NULL;
    tl->last = NULL;
    tl->size = 0;

    return tl;
}

void tl_append(TeamList *tl, Team *t) {
    struct node *n = malloc(sizeof(struct node));

    if (n == NULL)
        return;

    n->team = t;
    n->next = NULL;
    n->prev = tl->last;

    if (tl->last == NULL)
        tl->first = n;
    else
        tl->last->next = n;

    tl->last = n;
    tl->size++;
}

int tl_size(TeamList *tl) {
    return tl->size;
}

Team *tl_get(TeamList *tl, int i) {
    if (i < 0 || i >= tl->size)
        return NULL;

    struct node *cur;

    // Anda a partir da ponta mais próxima da posição pedida
    if (i < tl->size / 2) {
        cur = tl->first;
        for (int k = 0; k < i; k++)
            cur = cur->next;
    } else {
        cur = tl->last;
        for (int k = tl->size - 1; k > i; k--)
            cur = cur->prev;
    }

    return cur->team;
}

void tl_free(TeamList *tl) {
    if (tl == NULL)
        return;

    struct node *cur = tl->first;

    while (cur != NULL) {
        struct node *next = cur->next; // guarda o próximo antes de liberar
        team_free(cur->team);
        free(cur);
        cur = next;
    }

    free(tl);
}
