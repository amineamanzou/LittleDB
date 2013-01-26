/*
 *
 * Author: Amanzou Amine, Jeremy Paulino
 *
 * Created on 20 mai 2012
 */

#include "analyseur.h"
#include "lexeur.h"
#include "parseur.h"
#include "Table.h"
#include "HeaderTable.h"
#include "Line.h"
#include "DataBase.h"

extern unsigned int c_table;
extern char* nameLittleDB;
extern DB_type LittleBD[MAX_SIZE];

query* analyseur(const char* text) {
  query* q = NULL;
  YY_BUFFER_STATE buffer;

  buffer = yy_scan_string(text);
  yyparse(&q);
  yy_delete_buffer(buffer);

  return q;
}

int compteFields(fields* f){
	int retour = 0;
	if (f == NULL)
		return retour;
	else
		while (f != NULL) {
			f=f->next;
			retour++;
		}
	return retour;
}
int compteNames(names* n){
	int retour = 0;
	if (n == NULL)
		return retour;
	else
		while(n != NULL){
			n=n->next;
			retour++;
		}
	return retour;
}
int compteValues(values *v){
	int retour = 0;
	if (v == NULL)
		return retour;
	else
		while(v != NULL){
			v=v->next;
			retour++;
		}
	return retour;
}

void recursive_update_line( names* n, values* v, line_header* h, line* l){
	unsigned int place; //ou sera place les donnees
	data d ;  // qui recuperera le type et servira a la verification de correspondanc

	//limite de recursion
	if (v == NULL || n == NULL)
		return;	
	//deplacement a la fin
	recursive_update_line(n->next,v->next,h,l);
	//Verification des correspondances requete <-> table existante
	if (getType(n->name,h,&(d.t)) != 0){
		printf ("Mauvaise correspondance de nom de colonne : %s \n",n->name);
		return;
	}
	else if ( d.t != v->value->t ){
		printf("Mauvaise correspondance de type pour la colonne : %s corrigez le type en ", n->name);
		printCell (d);
		printf("\n");
		return;
	}
	else { // on peut remplir data et l'envoyer a updt
		if ( d.t == Caractere )
			d.v.c = v->value->v.c;
		else 
			d.v.i = v->value->v.i;
		place = getPlace (n->name,h);
		update_line(l,d,place);
	}

}
void recursive_update_header(fields *f,line_header *h, int i){
	if (f == NULL)
		return;
	else{
		recursive_update_header(f->next,h,i-1);
		data_header* d = NULL;
		if (f->kind == Caractere)
			d = makeCar_header(f->name);
		else
			d = makeInt_header(f->name);
		update_header(h,*d,i);
	}
}

int queryCreate(query* q) {
	int nbCol = compteFields(q->content.create.fieldsList);
	table* Newtab = NULL;
	line_header* h = NULL;
	/*Verification par rapport a la BD*/
	if (nameLittleDB == NULL){
		printf("La BD n'existe pas creation de : FirstBD \n");
		create_bd("FirstBD");
	}
	else if (c_table >= MAX_SIZE) {
		printf("La BD est pleine.\n");
		return -1;
	}

	// preparation header et creation table avec header
	h = create_header(nbCol);
	Newtab = create_table(q->content.create.tableName, nbCol, h);
	recursive_update_header(q->content.create.fieldsList, Newtab->st, nbCol);
	// Ajout a la Database
	add_table(Newtab->name,Newtab);
	print_table(Newtab);
	return 1;
}

int queryInsert(query *q){
	int retour = 0;

	table* Tab = addr_table(q->content.insert.tableName);
	line* nouveau = create_line(Tab->nb_col);
	
	//remplissage recursif et verification requete
	recursive_update_line(q->content.insert.fieldNamesList,q->content.insert.fieldValuesList,Tab->st,nouveau);
	
	// ajout a la table
	addLine(nouveau,Tab);
	
	// augmente le nbr de ligne
	increase_line(Tab->name);

	// affiche
	print_line(nouveau);
	return retour;
}

int querySelectall(query* q);
	
void execute(query *q){
   if (q->kind == DROP_QUERY)
      printf("Utilisation de la fonction récursive deleteTable, pas encore implementee ...\n");
   else if (q->kind == CREATE_QUERY)
      queryCreate(q);
   else if (q->kind == INSERT_QUERY)
      printf("Insert dans la table une ligne et affiche le nombre de ligne modifié ou une erreur si le type ou les noms ne correspondent pas avec la table cree\n");
   else if (q->kind == SELECT_QUERY){
      //querySelectall(q);
      printf("Fonction a implementer ...\n");
   }
   else if (q->kind == DELETE_QUERY)
       printf("Utilisation de la fonction deleteLine\n");
   else if (q->kind == SAVE_QUERY)
      printf("Ecriture sur le fichier .sql, sauvegarde .sql.old\n");
   else if (q->kind == LOAD_QUERY)
      printf("Chargement de la BDD en cour ... Non implementé\n");
   else if (q->kind == EXIT_QUERY)
      printf("Fermeture et nettoyage ... free recursif\n");
}

/* fin de analyseur.c */
