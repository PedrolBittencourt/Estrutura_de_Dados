#include "teamlist.h"
#include <stdlib.h>

// Implementação do TAD TeamList com VETOR DINÂMICO.

#define INITIAL_CAPACITY 4

struct teamlist {
    Team **items;
    int size;
    int capacity;
};

TeamList *tl_create(void) {
    TeamList *tl = malloc(sizeof(TeamList));

    if (tl == NULL)
        return NULL;

    tl->items = malloc(INITIAL_CAPACITY * sizeof(Team *));

    if (tl->items == NULL) {
        free(tl);
        return NULL;
    }

    tl->size = 0;
    tl->capacity = INITIAL_CAPACITY;

    return tl;
}

void tl_append(TeamList *tl, Team *t) {
    if (tl->size == tl->capacity) {
        int new_capacity = tl->capacity * 2;
        Team **new_items = realloc(tl->items, new_capacity * sizeof(Team *));

        if (new_items == NULL)
            return;

        tl->items = new_items;
        tl->capacity = new_capacity;
    }

    tl->items[tl->size] = t;
    tl->size++;
}

int tl_size(TeamList *tl) {
    return tl->size;
}

Team *tl_get(TeamList *tl, int i) {
    if (i < 0 || i >= tl->size)
        return NULL;

    return tl->items[i];
}

void tl_free(TeamList *tl) {
    if (tl == NULL)
        return;

    for (int i = 0; i < tl->size; i++)
        team_free(tl->items[i]);

    free(tl->items);
    free(tl);
}
