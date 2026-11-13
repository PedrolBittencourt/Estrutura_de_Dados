#include "team.h"
#include <stdlib.h>
#include <string.h>

struct team {
    int id;
    char *name;
    int wins;
    int draws;
    int losses;
    int goals_scored;
    int goals_conceded;
};

Team *team_create(int id, const char *name) {
    Team *t = malloc(sizeof(Team));

    if (t == NULL)
        return NULL;

    t->name = malloc(strlen(name) + 1);

    if (t->name == NULL) {
        free(t);
        return NULL;
    }

    strcpy(t->name, name);

    t->id = id;
    t->wins = 0;
    t->draws = 0;
    t->losses = 0;
    t->goals_scored = 0;
    t->goals_conceded = 0;

    return t;
}

int team_id(Team *t) {
    return t->id;
}

const char *team_name(Team *t) {
    return t->name;
}

int team_wins(Team *t) {
    return t->wins;
}

int team_draws(Team *t) {
    return t->draws;
}

int team_losses(Team *t) {
    return t->losses;
}

int team_goals_scored(Team *t) {
    return t->goals_scored;
}

int team_goals_conceded(Team *t) {
    return t->goals_conceded;
}

void team_free(Team *t) {
    if (t != NULL) {
        free(t->name);
        free(t);
    }
}
