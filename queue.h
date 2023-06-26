#ifndef __QUEUE__
#define __QUEUE__

#include <stdio.h>

typedef struct fila_t fila_t ;

struct fila_t
{
  fila_t *prev, *next ;
} ;

/* ------------------------------------------------------------------------------
 * fila_add: adiciona elemento no fim da fila
 * ------------------------------------------------------------------------------ */

void fila_add (fila_t **queue, fila_t *elem) ;

/* ------------------------------------------------------------------------------
 * fila_remove: remove um elemento da fila e retorna ele
 * ------------------------------------------------------------------------------ */

fila_t *fila_remove (fila_t **queue, fila_t *elem) ;
#endif