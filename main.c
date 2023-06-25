#include "floodit.h"

/* ------------------------------------------------------------------------------ */

int main ()
{
  grafo_t *G;

  if (!(G = le_mapa("map", stdin)))
  {
    perror("unable to read input");
    exit(1);
  }

  merge_grafo_inicial(G);
  find_solution(G);
}