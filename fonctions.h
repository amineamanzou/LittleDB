/*
 * 
 * Author: Amanzou Amine, Jeremy Paulino
 *
 * Created on 20 mai 2012
 */

#ifndef FONCTIONS_H
#define FONCTIONS_H

#include "analyseur.h"

void restitue (query * q);

void affiche_term (term * t);

void affiche_namesList(names* NamesList);

void recursive_conditions (condition * c);

void affiche_term_lecture (term * t);

void recursive_conditions_lecture (condition * c);

void affiche_select (query * q);

void affiche_create (query * q);

void affiche_insert (query * q);

void affiche_delete (query * q);

void affiche_drop (query * q);

void affiche_load (query * q);

void affiche_save (query * q);

void affiche_exit (query * q);

void affiche (query * q);

#endif
