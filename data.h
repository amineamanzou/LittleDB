/*
 *
 * Author: Amanzou Amine, Jeremy Paulino
 *
 * Created on 20 mai 2012
 */

#ifndef DATA_H
#define DATA_H

#define MAX_SIZE 10
#define TAB_SIZE 4

enum type {Caractere = 0, Entier = 1, Vide = 2};

union valeur {
  char c;
  int i;
};

typedef struct data {
  enum type t;
  union valeur v;
} data;

data * makeCar(char);
data * makeInt(int);

#endif

/* fin de data.h */
