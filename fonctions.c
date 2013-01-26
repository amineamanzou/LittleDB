/*
 *
 * Author: Amanzou Amine, Jeremy Paulino
 *
 * Created on 20 mai 2012
 */

#include <stdlib.h>
#include <stdio.h>
#include "fonctions.h"

void
affiche_term (term * t)
{
  if (t->kind == FIELD_TERM)
    printf ("Le nom de champs est : %s\n", t->content.name);
  else
    {
      if (t->content.value->t == Caractere)
	printf ("\tLe caractère est : %c\n", t->content.value->v.c);
      else if (t->content.value->t == Entier)
	printf ("\tL'entier est : %d\n", t->content.value->v.i);
      else if (t->content.value->t == Vide)
	printf ("\tLa valeur est nulle !\n");
    }
}

void
recursive_conditions (condition * c)
{
  if (c->kind == EQUALITY || c->kind == SUPERIORITY || c->kind == INFERIORITY)
    {
      affiche_term (c->content.three.left);
      affiche_term (c->content.three.right);
    }

  else if (c->kind == DISJUNCTION || c->kind == CONJUNCTION)
    {
      recursive_conditions (c->content.two.left);
      recursive_conditions (c->content.two.right);
    }

  else if (c->kind == NEGATION)
    {
      recursive_conditions (c->content.one.daughter);
    }
}


void
affiche_term_lecture (term * t)
{
  if (t->kind == FIELD_TERM)
    printf (" %s ", t->content.name);
  else
    {
      if (t->content.value->t == Caractere)
	printf (" '%c' ", t->content.value->v.c);
      else if (t->content.value->t == Entier)
	printf (" %d ", t->content.value->v.i);
      else if (t->content.value->t == Vide)
	printf (" NULL ");
    }
}

void
recursive_conditions_lecture (condition * c)
{
  if (c->kind == EQUALITY)
    {
      affiche_term_lecture (c->content.three.left);
      printf (" = ");
      affiche_term_lecture (c->content.three.right);
    }


  else if (c->kind == SUPERIORITY)
    {
      affiche_term_lecture (c->content.three.left);
      printf (" > ");
      affiche_term_lecture (c->content.three.right);
    }

  else if (c->kind == INFERIORITY)
    {
      affiche_term_lecture (c->content.three.left);
      printf (" < ");
      affiche_term_lecture (c->content.three.right);
    }

  else if (c->kind == DISJUNCTION)
    {
      affiche_term_lecture (c->content.three.left);
      printf (" OR ");
      affiche_term_lecture (c->content.three.right);
    }


  else if (c->kind == CONJUNCTION)
    {
      recursive_conditions_lecture (c->content.two.left);
      printf (" AND ");
      recursive_conditions_lecture (c->content.two.right);
    }

  else if (c->kind == NEGATION)
    {
      printf (" ! ");
      recursive_conditions_lecture (c->content.one.daughter);
    }
}


void
restitue (query * q)
{
  fields *suivant = q->content.create.fieldsList;
  names *attribut = q->content.select.fieldNamesList;
  names *tab = q->content.select.tableNamesList;
  names *insrt = q->content.insert.fieldNamesList;
  values* valeur = q->content.insert.fieldValuesList;

  if (q->kind == DROP_QUERY)
    printf ("DROP TABLE %s ;\n",q->content.drop.tableName);
  else if (q->kind == DELETE_QUERY)
    {
      printf ("DELETE FROM %s WHERE",q->content.delete.tableName);
      recursive_conditions_lecture (q->content.delete.clause);
      printf (" ;\n");
    }
  else if (q->kind == CREATE_QUERY)
    {
      printf ("CREATE TABLE %s ( ",q->content.create.tableName);

      while (suivant != NULL)
	{
	  printf (" %s ", suivant->name);
	  if (suivant->kind == Caractere)
	    printf ("CHAR");
	  else
	    printf ("INT");
	  suivant = suivant->next;
	  if (suivant != NULL)
	    printf (", ");
	}

      printf (" );\n");
    }
  else if (q->kind == SELECT_QUERY)
    {
      printf ("SELECT ");
      affiche_namesList(attribut);
      printf (" FROM ");
      affiche_namesList(tab);

      if (q->content.select.clause != NULL)
	{
		printf (" WHERE ");
		recursive_conditions_lecture (q->content.select.clause);
	}
	printf (" ;\n");
    }
  else if (q->kind == INSERT_QUERY)
    {
	printf("INSERT INTO %s ( ",q->content.insert.tableName);
	affiche_namesList(insrt);
	printf(" ) ");
	printf(" VALUES ( ");
	while (valeur != NULL)
    	{
		if(valeur->value->t == Caractere)
			printf("'%c'",valeur->value->v.c);
		else if(valeur->value->t == Entier)
			printf("%d",valeur->value->v.i);
		else if (valeur->value->t == Vide)
			printf("NULL");
		else 
			printf("ERROR"); 
		valeur = valeur->next;
    		if (valeur!=NULL)
			printf(", ");
	}
	printf(" );\n");
    }
  else if (q->kind == LOAD_QUERY)
   {
	printf("LOAD %s ;\n",q->content.load.namefile);
   }
  else if (q->kind == SAVE_QUERY)
	printf("SAVE ;\n");
  else if (q->kind == EXIT_QUERY)
	printf("EXIT ;\n");
}

void
affiche_namesList(names* NamesList)
{
	while (NamesList != NULL)
	{
	  printf (" %s", NamesList->name);
	  NamesList = NamesList->next;
	  if (NamesList!=NULL)
		printf(",");
	}
}
void
affiche_select (query * q)
{
  names *suivant = q->content.select.tableNamesList;
  names *nouveau = q->content.select.fieldNamesList;

  while (suivant != NULL)
    {
      printf ("Le nom de la table est : %s\n", suivant->name);
      suivant = suivant->next;
    }

  while (nouveau != NULL)
    {
      printf ("Le nom d'un attribut est : %s\n", nouveau->name);
      nouveau = nouveau->next;
    }

  if (q->content.select.clause != NULL)
    recursive_conditions (q->content.select.clause);
}

void
affiche_create (query * q)
{
  fields *suivant = q->content.create.fieldsList;

  printf ("Le nom de la table est : %s\n", q->content.create.tableName);

  while (suivant != NULL)
    {
      printf ("Le nom d'un attribut est : %s", suivant->name);
      if (suivant->kind == Caractere)
	printf (" CHAR \n");
      else
	printf (" INT \n");
      suivant = suivant->next;
    }
}

void
affiche_insert (query * q)
{
  names *suivant = q->content.insert.fieldNamesList;
  values* valeur = q->content.insert.fieldValuesList;

  printf ("Le nom de la table est : %s\n", q->content.insert.tableName);

  while (suivant != NULL)
    {
      printf ("Le nom d'un attribut est : %s\n", suivant->name);
      suivant = suivant->next;
    }	
  while (valeur != NULL)
    {
	printf ("La valeur a inserer est : ");
	if(valeur->value->t == Caractere)
		printf("'%c'\n",valeur->value->v.c);
	else if(valeur->value->t == Entier)
		printf("%d\n",valeur->value->v.i);
	else if (valeur->value->t == Vide)
		printf("NULL\n");
	else 
		printf("ERROR\n"); 
	valeur = valeur->next;
    }
}

void
affiche_delete (query * q)
{
  printf ("Le nom de la table est : %s\n", q->content.delete.tableName);

  recursive_conditions (q->content.delete.clause);
}

void
affiche_drop (query * q)
{
  printf ("Le nom de la table est : %s\n", q->content.drop.tableName);
}

void
affiche_load (query * q)
{
  printf ("Requête LOAD : Fichier %s \n",q->content.load.namefile);
}
void
affiche_save (query * q)
{
  printf ("Requête SAVE \n");
}
void
affiche_exit (query * q)
{
  printf ("Requête EXIT \n");
}

void
affiche (query * q)
{
  if (q->kind == CREATE_QUERY)
    {
      affiche_create (q);
    }
  if (q->kind == SELECT_QUERY)
    {
      affiche_select (q);
    }
  if (q->kind == INSERT_QUERY)
    {
      affiche_insert (q);
    }
  if (q->kind == DELETE_QUERY)
    {
      affiche_delete (q);
    }
  if (q->kind == DROP_QUERY)
    {
      affiche_drop (q);
    }
  if (q->kind == LOAD_QUERY)
    {
      affiche_load (q);
    }
  if (q->kind == SAVE_QUERY)
    {
      affiche_save (q);
    }
  if (q->kind == EXIT_QUERY)
    {
      affiche_exit (q);
    }
}
