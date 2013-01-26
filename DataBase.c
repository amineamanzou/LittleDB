/*
 *
 * Author: Amanzou Amine, Jeremy Paulino
 *
 * Created on 20 mai 2012
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "DataBase.h"

DB_type LittleBD[MAX_SIZE];
unsigned int c_table = 0;
char *nameLittleDB = NULL;

void create_bd(char *namedb) {
    
    nameLittleDB = (char *)malloc(sizeof(strlen(namedb)));
    nameLittleDB = namedb;
    
}
                                 
int add_table(char *nametable, table *t) {
    
    if (c_table < MAX_SIZE - 1) {
        LittleBD[c_table].nameTable = nametable;
        LittleBD[c_table].t = t;
        LittleBD[c_table].nb_line = 0;
    
        return c_table++;
    }
    else return -1;
}

int search_table(char *nametable) {
    int i = 0;
    
    while ((i < c_table) && !strcmp(LittleBD[i].t->name,nametable)) {
        i++;
    }
    if (i == c_table) return -1;
    else /* (strcmp(LittleBD[i].t->name,nametable)) */
        return i;
}

table *addr_table(char *nametable) {
    int r = search_table(nametable);
    
    if (r == -1) return NULL;
    else return LittleBD[r].t;
}

int increase_line(char *nametable) {
    int r = search_table(nametable);
    
    if (r == -1) return -1;
    else {
        LittleBD[r].nb_line++;
        return LittleBD[r].nb_line;
    }
}

int decrease_line(char *nametable) {
    int r = search_table(nametable);
    
    if (r == -1) return -1;
    else {
        LittleBD[r].nb_line--;
        return LittleBD[r].nb_line;
    }
}

