/*
 * 
 * Author: Amanzou Amine, Jeremy Paulino
 *
 * Created on 20 mai 2012
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HeaderTable.h"


line_header *create_header(unsigned int size) {
    
    line_header * new_line = (line_header *)malloc(sizeof(line_header));
    line_header * local_line = new_line;
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
            local_line->next = (line_header *)malloc(sizeof(line_header));
            local_line = local_line->next;
        }
    } while (local_size > 0);
    
    return new_line;
}


int update_header (line_header *l, data_header d, unsigned int place) {
    line_header * local_line = l;
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


int delete_line (line_header *l);

void printCell_header (data_header d) {
    if (d.t == Caractere)
        printf("\tCHAR");
    if (d.t == Entier)
        printf("\tINT");
    if (d.t == Vide)
        printf("NULL\t");
}


void print_header (line_header *l) {
    line_header *courant = l;
    int i;
    
    printf("TYPE:");
    while (courant != NULL) {
        for (i = 0; i < courant->count; i++) {
            printCell_header(courant->array[i]);
        }
        courant = courant->next;
    }
    courant=l;
    printf("\nNAME:");
    while (courant != NULL) {
        for (i = 0; i < courant->count; i++) {
            printf("\t%s",courant->array[i].name_col);
        }
        courant = courant->next;
    }
}

unsigned int
getPlace (char* nameCol, line_header* lh){
    unsigned int place = 0, j;
    line_header       *courant = lh;
 
    while (courant != NULL){
        for (j=0; j<courant->count; j++ ) 
            if(!strcmp(courant->array[j].name_col, nameCol)){ //la bonne colonne
                place = place + j + 1;
                return place;
            }
        place = place + j;
        courant = courant->next;
    }
    return 0; // n'existe pas
}


int
getType(char *nameCol, line_header* lh, enum type* t)
{
    line_header       *courant = lh;
	int             j = 0;

    if (lh == NULL)
		return -1;
        
	while (courant != NULL) {
		for (j = 0; j < courant->count; j++){
			if(!strcmp(courant->array[j].name_col, nameCol)){ //la bonne colonne
                *t = courant->array[j].t;
                return 0;
            }
        }
		courant = courant->next;
	}
    return -1;
}


data_header * makeCar_header(char* c) {
    data_header *d = (data_header *)malloc(sizeof(data_header));
    d->name_col = (char*) malloc ((strlen(c)+1)*sizeof(char));
    strcpy(d->name_col,c); d->t = Caractere; 
    return d;
}
data_header * makeInt_header(char* c) {
    data_header *d = malloc(sizeof(data_header)); 
    d->name_col = (char*) malloc ((strlen(c)+1)*sizeof(char));
    strcpy(d->name_col,c); d->t = Entier; 
    return d;
}

