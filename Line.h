/*
 * 
 * Author: Amanzou Amine, Jeremy Paulino
 *
 * Created on 20 mai 2012
 */

#ifndef LittleBD_Line_h
#define LittleBD_Line_h

#include "data.h"


typedef struct line{
    unsigned int count;
    struct line *next;
    data array[TAB_SIZE];
} line;


line *create_line(unsigned int size);
int update_line (line *l, data d, unsigned int place);
int delete_line (line *l);
void print_line (line *l);
void printCell (data d);

int min_data(data d1, data d2);


#endif
