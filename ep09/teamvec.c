#include "teamvec.h"
#include <stdlib.h>

struct teamvec {
    Team **data;
    int size;
    int capacity;
};

TeamVec *tv_create(void) {
    TeamVec *tv = malloc(sizeof(TeamVec));

    if (tv == NULL)
        return NULL;

    tv->size = 0;
    tv->capacity = 4;

    tv->data = malloc(tv->capacity * sizeof(Team *));

    if (tv->data == NULL) {
        free(tv);
        return NULL;
    }

    return tv;
}

void tv_insert(TeamVec *tv, Team *t) {
    if (tv == NULL || t == NULL)
        return;

    if (tv->size == tv->capacity) {
        int new_capacity = tv->capacity * 2;

        Team **temp = realloc(
            tv->data,
            new_capacity * sizeof(Team *)
        );

        if (temp == NULL)
            return;

        tv->data = temp;
        tv->capacity = new_capacity;
    }

    tv->data[tv->size] = t;
    tv->size++;
}

int tv_size(TeamVec *tv) {
    if (tv == NULL)
        return 0;

    return tv->size;
}

Team *tv_get(TeamVec *tv, int i) {
    if (tv == NULL || i < 0 || i >= tv->size)
        return NULL;

    return tv->data[i];
}

void tv_free(TeamVec *tv) {
    if (tv != NULL) {
        for (int i = 0; i < tv->size; i++)
            team_free(tv->data[i]);

        free(tv->data);
        free(tv);
    }
}
