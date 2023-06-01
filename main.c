#include <stdio.h>
#include <stdlib.h>
#include <strings.h>

int main(){
    int cores;
    int linhas;
    int colunas;

    int teste;

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
    printf("feito\n");
}