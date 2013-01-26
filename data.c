/*
 *
 * Author: Amanzou Amine, Jeremy Paulino
 *
 * Created on 20 mai 2012
 */

#include <stdlib.h>
#include "data.h"

data * makeCar(char c) {
  data *d = malloc(sizeof(data));
  d->t = Caractere; d->v.c = c;
  return d;
}

data * makeInt(int i) {
  data *d = malloc(sizeof(data));
  d->t = Entier; d->v.i = i;
  return d;
}

/* fin de data.c */
