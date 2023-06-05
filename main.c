#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

typedef struct t_map{
    int nlinhas;
    int ncolunas;
    int cores;
    int cor_atual;
    int **map;
}

void paint(t_map *map, int l, int c, int cor){
    
    map->map[l][c] = cor;
    if (l < map->nlinhas && map->map[l+1][c] == map->cor_atual)
        paint(map, l+1, c, cor);
    if (l < map->nlinhas && map->map[l-1][c] == map->cor_atual)
        paint(map, l-1, c, cor);
    if (c < map->ncolunas && map->map[l][c+1] == map->cor_atual)
        paint(map, l, c+1, cor);
    if (c < map->ncolunas && map->map[l][c-1] == map->cor_atual)
        paint(map, l, c-1, cor);
}
int winCheck(t_map *map){
    int cor = map->map[1][1];
    for (int i = 0; i < map->ncolunas; i++){
        for (int j = 0; j < map->nlinhas; j++){
            if (map->map[i][j] != cor)
                return 0;
        }
    }
    return 1;
}

int main(){
    t_map map;
    int cores;
    int linhas;
    int colunas;
    int tentativas = 10;
    int teste;
    int venceu = 0;
    int **tabuleiro;
    
    scanf("%d %d %d\n", &linhas, &colunas, &cores);
    tabuleiro = (int**)malloc(linhas * sizeof(int*));
    for(int i = 0; i < linhas; i++) tabuleiro[i] = (int*)malloc(colunas * sizeof(int));
    for (int i = 0; i < linhas; i++){
        for (int j = 0; j < colunas; j++){
            scanf("%d ", &teste);
            if (teste > cores){
                printf("tabuleiro invalido. verifique os valores\n");
                exit(1);
            }else{
                tabuleiro[i][j] = teste;
            }
        }
    }
    // main game loop
    for (int i = 0; i < tentativas; i++){
       if (winCheck(map)){
           venceu = 1;
           break;
       }
       scanf("%d", &prox_cor);
       paint(map, 0, 0, prox_cor); 
    }
    if venceu printf("venceste\n") else printf("perdeste\n");
}
