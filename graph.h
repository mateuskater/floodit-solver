#ifndef _GRAPH_H
#define _GRAPH_H

/* ------------------------------------------------------------------------------ */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "queue.h"

/* ------------------------------------------------------------------------------ */

typedef struct grafo_t grafo_t;
typedef struct vertice_t vertice_t;
typedef struct edge_t edge_t;

/* ------------------------------------------------------------------------------
 * structure: graph
 * ------------------------------------------------------------------------------
 * vertices: graph vertices
 * nome: graph nome
 * size: graph size (number of vertices)
 * ------------------------------------------------------------------------------ */

struct grafo_t
{
  vertice_t *vertices;
  char *nome;
  int tam;
};

/* ------------------------------------------------------------------------------
 * structure: vertice
 * ------------------------------------------------------------------------------
 * prev: pointer to the previous vertice
 * next: pointer to the next vertice
 * arestas: pointer to a list of arestas that connect to the vertice
 * value: vertice value (generic)
 * grau: current vertice grau
 * id: vertice id (must be unique)
 * ------------------------------------------------------------------------------ */

struct vertice_t
{
  vertice_t *prev, *next;
  edge_t *arestas;
  int value;
  int grau;
  int id;
};

/* ------------------------------------------------------------------------------
 * structure: edge
 * ------------------------------------------------------------------------------
 * prev: ponteiro para a proxima aresta
 * next: ponteiro para a proxima aresta
 * vertice: vertice conectado a essa aresta
 * ------------------------------------------------------------------------------ */

struct edge_t
{
  edge_t *prev, *next;
  vertice_t *vertice;
};

/* ------------------------------------------------------------------------------
 * function: cria_grafo
 * ------------------------------------------------------------------------------
 * cria um grafo com esse nome
 * nome: nome do grafo novo
 * retorna ponteiro para o grafo criado
 * ------------------------------------------------------------------------------ */

grafo_t *cria_grafo(char *nome);

/* ------------------------------------------------------------------------------
 * adiciona_vertice
 * ------------------------------------------------------------------------------
 * insere um vertice no grafo selecionado
 *
 * g: grafo no qual o vertice vai ser inserido
 * value: valor do vertice
 * id: id do vertice
 *
 * retorna ponteiro para o vertice adicionado
 * ------------------------------------------------------------------------------ */

vertice_t *add_vertice(grafo_t *g, int value, int id);

/* ------------------------------------------------------------------------------
 * remove_vertice
 * ------------------------------------------------------------------------------
 * remove um vertice de um grafo selecionado
 *
 * g: grafo de que o vertice vai ser removido
 * v: vertice to be removed
 * direcionado: indicates if the graph is directed (1) or not (0)
 *
 * retorna ponteiro para o vertice removido
 * ------------------------------------------------------------------------------ */

vertice_t *remove_vertice(grafo_t *g, vertice_t *v, int direcionado);

/* ------------------------------------------------------------------------------
 * add_aresta
 * ------------------------------------------------------------------------------
 * insere uma aresta do v1 para o v2. Se o grafo for nao direcionado,
 * essa funcao deve ser chamada nas duas pontas pra criar uma aresta bidirecional
 *
 * v1: vertice que vai receber v2 na vizinhanca
 * v2: vertice que vai ser adicionado para vizinhanca de v1
 *
 * retorna 0 se der erro ou 1 se nao der erro
 * ------------------------------------------------------------------------------ */

int add_aresta(vertice_t *v1, vertice_t *v2);

/* ------------------------------------------------------------------------------
 * remove_aresta
 * ------------------------------------------------------------------------------
 * remove a aresta que conecta v1 a v2. Se o grafo for nao direcionado, essa
 * funcao deve ser chamada nas duas pontas para criar uma aresta bidirecional.
 *
 * v1: vertice que vai ter v2 removido de sua vizinhanca
 * v2: vertice que vai ser removido da vizinhanca de v1
 *
 * retorna ponteiro para a aresta removida
 * ------------------------------------------------------------------------------ */

edge_t *remove_aresta(vertice_t *v1, vertice_t *v2);

/* ------------------------------------------------------------------------------
 * busca_aresta
 * ------------------------------------------------------------------------------
 * busca por uma aresta especifica no vertice
 *
 * e: aresta para buscar
 * v: vertice que a aresta conecta
 *
 * retorna ponteiro para a aresta encontrada ou NULL se nao encontrada
 * ------------------------------------------------------------------------------ */

edge_t *busca_aresta(edge_t *e, vertice_t *v);

/* ------------------------------------------------------------------------------
 * function: search_neighbourhood
 * ------------------------------------------------------------------------------
 * verifies if if v1 has v2 as a neighbour.
 *
 * v1: vertice which the neighbourhood will be searched
 * v2: vertice to search in the neighbourhood of v1
 *
 * returns: 1 if there is neighbourhood or 0 if there is not
 * ------------------------------------------------------------------------------ */

int busca_vizinhanca(vertice_t *v1, vertice_t *v2);

/* ------------------------------------------------------------------------------
 * destroi_grafo
 * ------------------------------------------------------------------------------
 * libera toda a memoria usada pelo grafo
 * g: grafo
 *
 * retorna 0 se houve erro ou 1 se nao houve erro
 * ------------------------------------------------------------------------------ */

int destroi_grafo(grafo_t *g);

/* ------------------------------------------------------------------------------ */

#endif