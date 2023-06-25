#include "queue.h"

/* ------------------------------------------------------------------------------ */

void fila_add(fila_t **fila, fila_t *elem)
{
  if (!fila || !elem)
  {
    fprintf(stderr, "Erro ao adicionar na fila\n");
    return;
  }

  if (*fila) // se a fila nao esta vazia
  {
    fila_t *last = (*fila)->prev;
    elem->next = (*fila);
    (*fila)->prev = elem;
    elem->prev = last;
    last->next = elem;
  }
  else
  {
    (*fila) = elem;
    (*fila)->next = (*fila)->prev = elem;
  }

  return;
}

/* ------------------------------------------------------------------------------ */

fila_t *fila_remove(fila_t **fila, fila_t *elem)
{
  if (!fila || !elem)
  {
    fprintf(stderr, "Erro ao remover da fila\n");
    return NULL;
  }

  fila_t *aux = elem;

  if (aux == (*fila))                                  // se for o comeco da fila
    (*fila) = aux->next == aux ? NULL : (*fila)->next; // se for o unico elemento da fila

  elem->prev->next = elem->next;
  elem->next->prev = elem->prev;
  elem->next = elem->prev = NULL;
  return elem;
}