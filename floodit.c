#include "floodit.h"

grafo_t *le_mapa (char *nome, FILE *input)
{
  int altura, largura, ncores;

  assert(fscanf(input, "%d %d %d", &altura, &largura, &ncores));

  if (altura <= 0 || largura <= 0 || ncores <= 0)
    return NULL;

  grafo_t *mapa = cria_grafo(nome);
  vertice_t **matriz_mapa = (vertice_t **) malloc(altura * largura * sizeof(vertice_t *));
  int cor;

  for (int i = 0; i < altura; ++i)
  {
    for (int j = 0; j < largura; ++j)
    {
      assert(fscanf(input, "%d", &cor));
      matriz_mapa[idx(largura, i, j)] = add_vertice(mapa, cor, idx(largura, i, j));
    }
  }

  for (int i = 0; i < altura; ++i){
    for (int j = 0; j < largura; ++j){
      vertice_t *atual = matriz_mapa[idx(largura, i, j)];
      vertice_t *vizinho = NULL;

      if (i > 0) // tem vizinho acima
      {
        vizinho = matriz_mapa[idx(largura, i - 1, j)];
        if (!busca_vizinhanca(atual, vizinho))
          add_aresta(atual, vizinho);
        if (!busca_vizinhanca(vizinho, atual))
          add_aresta(vizinho, atual);
      }

      if (i < altura - 1) // tem vizinho abaixo
      { 
        vizinho = matriz_mapa[idx(largura, i + 1, j)];
        if (!busca_vizinhanca(atual, vizinho))
          add_aresta(atual, vizinho);
        if (!busca_vizinhanca(vizinho, atual))
          add_aresta(vizinho, atual);
      }

      if (j > 0) // tem vizinho na esquerda
      {
        vizinho = matriz_mapa[idx(largura, i, j - 1)];
        if (!busca_vizinhanca(atual, vizinho))
          add_aresta(atual, vizinho);
        if (!busca_vizinhanca(vizinho, atual))
          add_aresta(vizinho, atual);
      }

      if (j < largura - 1) // tem vizinho na direita
      {
        vizinho = matriz_mapa[idx(largura, i, j + 1)];
        if (!busca_vizinhanca(atual, vizinho))
          add_aresta(atual, vizinho);
        if (!busca_vizinhanca(vizinho, atual))
          add_aresta(vizinho, atual);
      }
    }
  }

  free(matriz_mapa);
  return mapa;
}

int merge_grafo_inicial (grafo_t *mapa)
{
  if (!mapa)
    return 0;

  vertice_t *iter_vertice = mapa->vertices;
  unsigned int tam = mapa->tam;

  // percorre o grafo e merge as cores iniciais
  for (unsigned int i = 0; i < tam; ++i)
  {
    transfere_vizinhos(mapa, iter_vertice, iter_vertice->valor);
    iter_vertice = iter_vertice->next;
  }

  return 1;
}

int transfere_vizinhos (grafo_t *mapa, vertice_t *receptor, int cor)
{
  if (!mapa || !receptor || cor < 0)
    return 0;

  aresta_t *arestas_iterador = receptor->arestas, *aux;
  unsigned int i = 0, tam = receptor->grau;

  while (i < tam)
  {
    if ((arestas_iterador->vertice->valor == cor) && (aux = arestas_iterador->vertice->arestas))
    {
      do
      {
        if ((receptor->id != aux->vertice->id) && !busca_vizinhanca(receptor, aux->vertice))
        {
          add_aresta(receptor, aux->vertice);
          add_aresta(aux->vertice, receptor);
        }
      }
      while ((aux = aux->next) != arestas_iterador->vertice->arestas);

      free(remove_vertice(mapa, arestas_iterador->vertice, 0));

      i = 0;
      tam = receptor->grau;
      arestas_iterador = receptor->arestas;
    }
    else
    {
      i++;
      arestas_iterador = arestas_iterador->next;
    }
  }

  return 1;
}

int propaga_cor (grafo_t *mapa, vertice_t *raiz, int cor)
{
  if (!mapa || !raiz || cor < 0)
    return 0;

  raiz->valor = cor;
  transfere_vizinhos(mapa, raiz, cor);
  return 1;
}

int a_star (grafo_t *mapa, node_t *nodos_abertos)
{
  if (!mapa)
    return 0;

  node_t *node, *node_filho;
  aresta_t *node_arestas;

  while (nodos_abertos)
  {
    // atualiza mapa do topo
    node = nodos_abertos;
    node->mapa_atual = clona_grafo(node->mapa_atual);
    propaga_cor(node->mapa_atual, node->mapa_atual->vertices, node->cor);

    node_arestas = node->mapa_atual->vertices->arestas;

    // cria todos os filhos possiveis
    if (node_arestas)
    {
      do
      {
        node_filho = busca_cor_filhos(node, node_arestas->vertice->valor);

        if (!node_filho){
          node_filho = (node_t *) malloc(sizeof(node_t));
          node_filho->next = node_filho->prev = NULL;
          node_filho->pai = node;
          node_filho->cor = node_arestas->vertice->valor;
          node_filho->mapa_atual = node_filho->pai->mapa_atual;

          // heuristica ------------------------------

          int i = 0, grau = 0;
          aresta_t *a_it = node_filho->mapa_atual->vertices->arestas; // iterar sobre arestas

          do
          {
            if (a_it->vertice->valor == node_filho->cor)
            {
              i++;
              grau += a_it->vertice->grau - 1;
            }
          }
          while ((a_it = a_it->next) != node_filho->mapa_atual->vertices->arestas);

          node_filho->g = node->g + 2.0;
          node_filho->h = (node_filho->mapa_atual->tam - i) * 1.0;
          node_filho->h -= grau * 0.95;

          if (node_filho->h <= 0)
            node_filho->h = 0.0;

          node_filho->h += (node_filho->mapa_atual->tam - i) * 1.0;

          // ----------------------------------------

          add_fila_prioridade(&(nodos_abertos), node_filho);
        }
      }
      while ((node_arestas = node_arestas->next) != node->mapa_atual->vertices->arestas);
    }
    else
    {
      int tam = 0;
      node_t *it = node;

      do
      {
        it = it->pai;
        tam++;
      }
      while(it->pai);

      // imprime pais ate a raiz
      int *vetor_solucao = malloc(tam * sizeof(int));
      printf("%d\n", tam);

      for (int i = 0; i < tam; ++i)
      {
        vetor_solucao[i] = node->cor;
        node = node->pai;
      }

      for (int i = tam - 1; i >= 0; --i)
        printf("a %d ", vetor_solucao[i]);
      printf("\n");

      free(vetor_solucao);
      break;
    }

    fila_remove((fila_t **) &(nodos_abertos), (fila_t *) node);
  }

  return 1;
}

node_t *busca_cor_filhos (node_t *node, int cor)
{
  node_t *iterador = node;

  if (!iterador)
    return NULL;

  do
    if (iterador->cor == cor && iterador->pai == node)
      return iterador;
  while ((iterador = iterador->next) != node);

  return NULL;
}

int acha_solucao (grafo_t *mapa)
{
  // cria arvore de busca
  node_t *raiz = malloc(sizeof(node_t));
  raiz->pai = NULL;
  raiz->next = raiz->prev = raiz;
  raiz->g = 0.0;
  raiz->h = mapa->tam;
  raiz->cor = mapa->vertices->valor;
  raiz->mapa_atual = mapa;

  node_t *nodos_abertos = raiz;
  return a_star(mapa, nodos_abertos);
}

void add_fila_prioridade (node_t **fila, node_t *elem)
{
  if (!fila || !elem)
  {
    fprintf(stderr, "Error: add_fila_prioridade\n");
    return ;
  }

  if (*fila)
  {
    node_t *iterador = (*fila);
    double elem_f = elem->g + elem->h, iterator_f;

    if(elem->h <= 1)
    {
      iterator_f = iterador->g + iterador->h;
      iterador = iterador->next;
    }
    else
    {
      do
      {
        iterator_f = iterador->g + iterador->h;
        iterador = iterador->next;
      }
      while ((iterator_f < elem_f) && (iterador != (*fila)));
    }

    elem->next = iterador;
    elem->prev = iterador->prev;
    iterador->prev->next = elem;
    iterador->prev = elem;

    if (((*fila)->g + (*fila)->h) > elem_f)
      (*fila) = elem;
  }
  else
  {
    (*fila) = elem;
    (*fila)->next = (*fila)->prev = elem;
  }

  return ;
}

grafo_t *clona_grafo (grafo_t *old)
{
  grafo_t *new = cria_grafo("new");

  vertice_t *iter_vertice = old->vertices;
  unsigned int tam = old->tam;

  vertice_t **v_old = (vertice_t **) malloc(sizeof(vertice_t *) * tam);
  vertice_t **v_new = (vertice_t **) malloc(sizeof(vertice_t *) * tam);
  int i = 0;

  do
  {
    v_new[i] = add_vertice(new, iter_vertice->valor, iter_vertice->id);
    v_old[i] = iter_vertice;
    i++;
  }
  while ((iter_vertice = iter_vertice->next) != old->vertices);

  aresta_t *a;
  vertice_t *vizinho = NULL;

  for (int j = 0; j < i; ++j)
  {
    a = v_old[j]->arestas;
    do
    {
      for (int k = 0; k < i; ++k)
      {
        if (v_new[k]->id == a->vertice->id)
        {
          vizinho = v_new[k];
          k = i;
        }
      }

      aresta_t *aux;
      aux = (aresta_t *) malloc(sizeof(aresta_t));
      aux->vertice = vizinho;
      aux->next = aux->prev = NULL;
      fila_add((fila_t **) &(v_new[j]->arestas), (fila_t *) aux);
      v_new[j]->grau++;
    }
    while ((a = a->next) != v_old[j]->arestas);
  }

  free(v_old);
  free(v_new);
  return new;
}