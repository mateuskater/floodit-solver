#include "floodit.h"

int main ()
{
  grafo_t *G;

  if (!(G = le_mapa("map", stdin)))
  {
    perror("input invalido");
    exit(1);
  }

  merge_grafo_inicial(G);
  acha_solucao(G);
}