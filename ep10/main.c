#include "team.h"
#include "teamlist.h"
#include <stdio.h>

// Este arquivo não pode depender da implementação escolhida em config.mk:
// use apenas as funções de team.h e teamlist.h.

#define LINE_SIZE 256
#define NAME_WIDTH 17

// Imprime o nome preenchido com espaços até NAME_WIDTH colunas visíveis.
// printf conta bytes, não letras: cada byte de continuação UTF-8
// (formato 10xxxxxx) ganha um espaço extra para compensar.
static void print_name(const char *name) {
    int bytes = 0;
    int continuation = 0;

    for (const char *p = name; *p != '\0'; p++) {
        bytes++;
        if (((unsigned char)*p & 0xC0) == 0x80)
            continuation++;
    }

    int letters = bytes - continuation;
    printf("%s", name);

    for (int i = letters; i < NAME_WIDTH; i++)
        putchar(' ');
}

int main(void) {
    TeamList *tl = tl_create();

    if (tl == NULL) {
        fprintf(stderr, "Erro: sem memória para criar a lista\n");
        return 1;
    }

    FILE *f = fopen("teams.csv", "r");

    if (f == NULL) {
        fprintf(stderr, "Erro: não foi possível abrir teams.csv\n");
        tl_free(tl);
        return 1;
    }

    char line[LINE_SIZE];

    while (fgets(line, sizeof(line), f) != NULL) {
        int id;
        char name[LINE_SIZE];

        // formato: id,nome (o nome vai até o fim da linha)
        if (sscanf(line, "%d,%255[^\r\n]", &id, name) == 2) {
            Team *t = team_create(id, name);

            if (t != NULL)
                tl_append(tl, t);
        }
    }

    fclose(f);

    printf("%-5s%-*s%-4s%-4s%-4s%-4s%-4s%-4s%s\n",
           "ID", NAME_WIDTH, "Time", "V", "E", "D", "GM", "GS", "S", "PG");

    for (int i = 0; i < tl_size(tl); i++) {
        Team *t = tl_get(tl, i);

        int v = team_wins(t);
        int e = team_draws(t);
        int d = team_losses(t);
        int gm = team_goals_scored(t);
        int gs = team_goals_conceded(t);
        int s = gm - gs;
        int pg = 3 * v + e;

        printf("%-5d", team_id(t));
        print_name(team_name(t));
        printf("%-4d%-4d%-4d%-4d%-4d%-4d%d\n", v, e, d, gm, gs, s, pg);
    }

    tl_free(tl);
    return 0;
}
