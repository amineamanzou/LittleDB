/*
 * 
 * Author: Amanzou Amine, Jeremy Paulino
 *
 * Created on 20 mai 2012
 */

#include <stdio.h>
#include <stdlib.h>
#include "Line.h"


line *create_line(unsigned int size) {
    
    line * new_line = (line *)malloc(sizeof(line));
    line * local_line = new_line;
    int local_size = size;
    int i;
    
    if (size == 0) { 
        free(new_line);
        perror("Error : No line created (size is NULL)"); 
    }
   do 
    {
        local_line->count = (local_size > TAB_SIZE)?TAB_SIZE:local_size;
        for (i = 0; i < TAB_SIZE; i++) {
            local_line->array[i].t = Vide;
        }
        local_size = local_size - TAB_SIZE;
        if (local_size > 0) {
            local_line->next = (line *)malloc(sizeof(line));
            local_line = local_line->next;
        }
    } while (local_size > 0);
    
    return new_line;
}


int update_line (line *l, data d, unsigned int place) {
    line * local_line = l;
    int local_place = place;
    
    while ((local_line != NULL) && (local_place > TAB_SIZE))  {
        local_line = local_line->next;
        local_place = local_place - TAB_SIZE;
    }
    
    if (local_line == NULL)
        return -1;

    if (local_place > local_line->count)
        return -1;
    
    local_line->array[local_place-1] = d;
    return 0;
}


int delete_line (line *l){
	line * courant=l;
	if (courant->next!=NULL)
	  {
		while(courant->next!=NULL)
		  {
			courant=courant->next;
		  }
		free(courant);
		delete_line(courant);
	  }
	free(courant);
	return 1;
}

void printCell (data d) {
    if (d.t == Caractere)
        printf("%8c\t", d.v.c);
    if (d.t == Entier)
        printf("%8d\t", d.v.i);
    if (d.t == Vide)
        printf("NULL\t");
}


void print_line (line *l) {
    int i;
    while (l != NULL) {
        for (i = 0; i < l->count; i++) {
            printCell(l->array[i]);
        }
        l = l->next;
    }
}

int min_data (data d1, data d2) {
    if (d1.t == Entier)
        return (d1.v.i < d2.v.i);
    if (d1.t == Caractere)
        return (d1.v.c < d2.v.c);
    else return 1; /* the first is NULL then is the min */
}


