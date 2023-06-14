#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>

typedef struct t_map {
    int nlinhas;
    int ncolunas;
    int cores;
    int cor_atual;
    int **map;
} t_map;

void paint(t_map *map, int l, int c, int cor) {
    
    map->map[l][c] = cor;
    if (l < map->nlinhas-1 && map->map[l+1][c] == map->cor_atual)
        paint(map, l+1, c, cor);
    if (l > 0 && map->map[l-1][c] == map->cor_atual)
        paint(map, l-1, c, cor);
    if (c > 0 && map->map[l][c-1] == map->cor_atual)
        paint(map, l, c-1, cor);
    if (c < map->ncolunas-1 && map->map[l][c+1] == map->cor_atual)
        paint(map, l, c+1, cor);
}

int winCheck(t_map *map) {
    int cor = map->map[1][1];
    for (int i = 0; i < map->ncolunas; i++) {
        for (int j = 0; j < map->nlinhas; j++) {
            if (map->map[i][j] != cor)
                return 0;
        }
    }
    return 1;
}

t_map * gera_mapa(int linhas, int colunas, int cores) {
    t_map *new;

    new = malloc(sizeof(t_map));

    srand(time(NULL));
    new->nlinhas = linhas;
    new->ncolunas = colunas;
    int **tabuleiro = (int**)malloc(linhas * sizeof(int*));
    for(int i = 0; i < linhas; i++) tabuleiro[i] = (int*)malloc(colunas * sizeof(int));
    new->map = tabuleiro;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            new->map[i][j] = rand() % cores;
        }
    }
    new->cor_atual = new->map[0][0];
    return new;
}

t_map * le_mapa() {
    t_map *new;
    int cores;
    int teste;
    scanf("%d %d %d\n", &new->nlinhas, &new->ncolunas, &cores);
    for (int i = 0; i < new->nlinhas; i++) {
        for (int j = 0; j < new->ncolunas; j++) {
            scanf("%d ", &teste);
            if (teste > cores) {
                printf("tabuleiro invalido. verifique os valores\n");
                exit(1);
            }else{
                new->map[i][j] = teste;
            }
        }
    }
    return new;
}

void mostra_mapa(t_map *map) {

    for (int i = 0; i < map->nlinhas; i++) {
        for (int j = 0; j < map->ncolunas; j++) {
            printf("%d ", map->map[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void jogada(t_map *map, char canto, int prox_cor) {
    if (canto == 'a')
        paint(map, 0, 0, prox_cor);
    else if (canto == 'b')
        paint(map, 0, map->ncolunas-1, prox_cor);
    else if (canto == 'c')
        paint(map, map->nlinhas-1, map->ncolunas-1, prox_cor);
    else if (canto == 'd')
        paint(map, map->nlinhas-1, 0, prox_cor);
    
    map->cor_atual = prox_cor;
}

int main() {
    t_map *map;
    int tentativas = 25;
    int venceu = 0;
    char canto = 'a';
    int prox_cor;

    map = gera_mapa(20, 20, 6);
    map = le_mapa();
    
    // main game loop
    for (int i = 0; i < tentativas; i++) {
        if (winCheck(map)) {
            venceu = 1;
            break;
        }
        mostra_mapa(map);
        scanf("%c %d", &canto, &prox_cor);
        getc(stdin);
        jogada(map, canto, prox_cor);

    }
    venceu ? printf("venceste\n"): printf("perdeste\n");
}
