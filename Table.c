/*
 * 
 * Author: Amanzou Amine, Jeremy Paulino
 *
 * Created on 20 mai 2012
 */

#include <stdio.h>
#include <stdlib.h>

#include "Table.h"

table * create_table(char *name, unsigned int nb_col, line_header *lh) {
    table *tab = (table *)(malloc(sizeof(table)));
    
    tab->name = name;
    tab->nb_col = nb_col;
    tab->st = lh;
    
    tab->first = NULL;
    tab->index = NULL;
    
    return tab;
    
}

int criterion(line *l1, line *l2) {
    return min_data(l1->array[0],l2->array[0]); 
}

void addLine(line *l, table *t) {
    s_line *sl = (s_line *)malloc(sizeof(s_line));
    s_line *courant = t->first;
    s_line *predecessor;
    
    sl->l = l;
    sl->next = NULL;
    
    if (t->first == NULL)
        t->first = sl;
    else {
        while (courant != NULL && criterion(courant->l, sl->l)) {
            /* courant->l < sl->l */ 
            predecessor = courant;
            courant = courant->next;
        }
        if (courant == NULL)
            predecessor->next = sl;
        else {
            sl->next = courant;
            predecessor->next = sl;
        }
    }
}

void print_table(table *t) {
    s_line *sl = t->first;
    int i = 1;
    
    printf("\n");
    printf("Nom de la table : %s\n",t->name);
    print_header(t->st);
    printf("\n");
    while(sl != NULL) {
        printf("%3d: ", i++);
        print_line(sl->l);
        printf("\n");
        sl = sl->next;
    }
}
