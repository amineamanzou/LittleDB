/*
 *
 * Author: Amanzou Amine, Jeremy Paulino
 *
 * Created on 20 mai 2012
 */

#include "Line.h"
#include "HeaderTable.h"

#ifndef LittleBD_Table_h
#define LittleBD_Table_h

typedef struct s_line {
    line *l;
    struct s_line *next;
} s_line;


typedef struct table {
    char *name;
    unsigned int nb_col;
    void * index;
    line_header *st;
    s_line *first;
} table;

table *create_table(char * name, unsigned int nb_col, line_header *lh);

int criterion(line *l1, line *l2);
void addLine(line *l, table *t);
void print_table(table *t);

#endif
