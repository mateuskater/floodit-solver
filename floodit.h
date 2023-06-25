#ifndef _FLOODIT_H
#define _FLOODIT_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "graph.h"
#include "queue.h"

#define idx(cols, i, j) ((cols) * (i) + (j))

typedef struct node_t node_t;

struct node_t
{
  node_t *prev, *next;
  node_t *pai;
  grafo_t *mapa_atual;
  int cor;
  double g;
  double h;
};

grafo_t *le_mapa(char *nome, FILE *input);

int merge_grafo_inicial(grafo_t *map);

int transfere_vizinhos(grafo_t *map, vertice_t *receiver, int cor);

int propaga_cor(grafo_t *map, vertice_t *root, int cor);

int acha_solucao(grafo_t *map);

void add_fila_prioridade(node_t **queue, node_t *elem);

grafo_t *clona_grafo(grafo_t *old);

node_t *busca_cor_filhos(node_t *node, int cor);

int a_star(grafo_t *map, node_t *open_nodes);

/* ------------------------------------------------------------------------------ */

#endif