/*
 *
 * Author: Amanzou Amine, Jeremy Paulino
 *
 * Created on 20 mai 2012
 */

#ifndef ANALYSEUR_H
#define ANALYSEUR_H

#include "requetes.h"
#include "HeaderTable.h"
#include "Line.h"

query* analyseur(const char*);

/*Fonction remplissant les structure de facon récursive de la fin au début*/
void recursive_update_header(fields *f, line_header *h, int i);
void recursive_update_line(names* n, values* v, line_header* h, line* l);

int compteFields(fields* f);
int compteNames(names* n);
int compteValues(values* v);

int queryCreate(query* q);
int queryInsert(query* q);
int querySelectall(query* q);
void execute(query *q);

#endif

/* fin de analyseur.h */
