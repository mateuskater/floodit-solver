#include "graph.h"

grafo_t *cria_grafo (char *nome)
{
  grafo_t *g = (grafo_t *) malloc(sizeof(grafo_t));

  g->nome = (char *) calloc(strlen(nome), sizeof(char));
  strcpy(g->nome, nome);
  g->vertices = NULL;
  g->tam = 0;

  return g;
}

vertice_t *add_vertice (grafo_t *g, int valor, int id)
{
  if (!g)
    return NULL;

  vertice_t *new_vertex = (vertice_t *) malloc(sizeof(vertice_t));

  g->tam++;

  new_vertex->next = new_vertex->prev = NULL;
  new_vertex->arestas = NULL;
  new_vertex->grau = 0;
  new_vertex->valor = valor;
  new_vertex->id = id;

  fila_add((fila_t **) &(g->vertices), (fila_t *) new_vertex);
  return new_vertex;
}

vertice_t *remove_vertice (grafo_t *g, vertice_t *v, int is_directed)
{
  if (!g || !v)
    return NULL;

  g->tam--;

  while(v->arestas) // removes all arestas from the vertex
  {
    if (is_directed)
    {
      free(remove_aresta(v->arestas->vertice, v));
      free(fila_remove((fila_t **) &(v->arestas), (fila_t *) v->arestas));
    }
    else
    {
      free(remove_aresta(v->arestas->vertice, v));
      free(remove_aresta(v, v->arestas->vertice));
    }
  }

  return (vertice_t *) fila_remove((fila_t **) &(g->vertices), (fila_t *) v);
}

int add_aresta (vertice_t *v1, vertice_t *v2)
{
  if (!v1 || !v2)
    return 0;

  aresta_t *new = (aresta_t *) malloc(sizeof(aresta_t));

  new->vertice = v2;
  new->next = new->prev = NULL;
  // insere v2 em v1
  fila_add((fila_t **) &(v1->arestas), (fila_t *) new);
  v1->grau++;

  return 1;
}

aresta_t *remove_aresta (vertice_t *v1, vertice_t *v2)
{
  if (!v1 || !v2)
    return NULL;

  aresta_t *aux;

  if ((aux = busca_aresta(v1->arestas, v2)))
  {
    v1->grau--;
    // remove v2 de v1
    return (aresta_t *) fila_remove((fila_t **) &(v1->arestas), (fila_t *) aux);
  }

  return NULL;
}

aresta_t *busca_aresta (aresta_t *e, vertice_t *v)
{
  if (!e || !v)
    return NULL;

  aresta_t *iter = e;

  do
    if (iter->vertice == v) // if the edge is found
      return iter;
  while ((iter = iter->next) != e);

  return NULL;
}

int busca_vizinhanca (vertice_t *v1, vertice_t *v2)
{
  if (!v1 || !v2)
    return 0;

  aresta_t *iter;

  if ((iter = v1->arestas))
    do
      if (iter->vertice == v2) // checks if v1 has v2 as a neighbour
        return 1;
    while ((iter = iter->next) != v1->arestas);

  return 0;
}

int destroi_grafo (grafo_t *g)
{
  if (!g)
    return 0;

  while (g->vertices) // enquanto ainda existirem vertices para remover
  {
    while (g->vertices->arestas) // enquanto ainda existir arestas para remover
      free(fila_remove((fila_t **) &(g->vertices->arestas), (fila_t *) g->vertices->arestas));
    free(fila_remove((fila_t **) &(g->vertices), (fila_t *) g->vertices));
  }

  free(g->nome);
  free(g);
  return 1;
}