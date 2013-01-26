/*
 * 
 * Author: Amanzou Amine, Jeremy Paulino
 *
 * Created on 20 mai 2012
 */

#ifndef LittleBD_HeaderTable_h
#define LittleBD_HeaderTable_h

#include "data.h"

typedef struct data_header {
    enum type t;
    char* name_col;
} data_header;

typedef struct line_header {
    unsigned int count;
    struct line_header *next;
    data_header array[TAB_SIZE];
} line_header;

line_header *create_header(unsigned int size);
int update_header (line_header *l, data_header d, unsigned int place);
int delete_header (line_header *l);
void print_header (line_header *l);
void printCell_header (data_header d);

unsigned int getPlace (char* nameCol, line_header* lh);
int getType (char* nameCol, line_header* lh, enum type* t);

data_header * makeCar_header(char* c);
data_header * makeInt_header(char* c);
#endif
