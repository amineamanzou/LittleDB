/*
 * 
 * Author: Amanzou Amine, Jeremy Paulino
 *
 * Created on 20 mai 2012
 */

#ifndef LittleBD_DataBase_h
#define LittleBD_DataBase_h

#include "data.h"
#include "Table.h"

typedef struct DB_type {
    char *nameTable;
    unsigned int nb_line;
    table *t;
} DB_type;



void create_bd(char *namedb);
int add_table(char *nametable, table *t);
int search_table(char *nametable);
table *addr_table(char *nametable);
int increase_line(char *nametable);
int decrease_line(char *nametable);

#endif
