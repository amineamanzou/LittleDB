/*
 * 
 * Author: Amanzou Amine, Jeremy Paulino
 *
 * Created on 20 mai 2012
 */

#include <stdlib.h>
#include <stdio.h>

#include "Line.h"
#include "HeaderTable.h"
#include "Table.h"
#include "DataBase.h"
#include "fonctions.h"
#include "requetes.h"
#include "analyseur.h"

#define QUERY_MAX 150

void
testfusion(char * req, query* q);
void 
pause (void);

int
main (void)
{
	char* requete;
	query* q=NULL;
	line* ligne= create_line(7);;
	data *d;

	system("clear");

	printf(" Test et simultation d'une session d'utilisation de littleBD avec un pronpteur \n");
	printf(" Exercice 1 : Comprehension LOAD SAVE EXIT SELECT * FROM Table \n\n");

	requete = "LOAD basededonnee.sql";
	testfusion(requete,q);
	
	requete = "LOAD basededonnee.sql.old";
	testfusion(requete,q);
	printf(" /*prise en charge des fichiers.old */ \n");
	
	pause();

	requete = "SAVE";
	testfusion(requete,q);
	
	requete = "EXIT";
	testfusion(requete,q);

	requete = "SELECT * FROM Table";
	testfusion(requete,q);

	pause();
	
	printf(" Exercice 2 : Fusion de query et de la structure \n\n");
	printf(" Requete implemente CREATE TABLE \n");

	requete = "CREATE TABLE toto ( id INT, ville CHAR)";
	testfusion(requete,q);

	printf(" Comprehenion et restitution des autres requetes : \n");

	requete = "DELETE FROM toto WHERE id = '1'";
	testfusion(requete,q);

	requete = "INSERT INTO toto ( id , ville ) VALUES ( 1 , 'c' )";
	testfusion(requete,q);

	pause();
	
	requete = "DROP TABLE toto";
	testfusion(requete,q);
	
	requete = "SELECT id FROM toto WHERE ! ( id > 1 AND c = 'c' )";
	testfusion(requete,q);

	pause();

	printf(" Exercice 3.1 : Effacer une ligne \n\n");
	printf(" Create Line ( 7 ) \n");
	print_line (ligne);
	
	printf(" Remplissage de la ligne ... \n");
	d=makeInt(1);
	update_line(ligne,*d,1);
	d=makeCar('c');
	update_line(ligne,*d,2);
	d=makeInt(345);
	update_line(ligne,*d,3);
	d=makeInt(2113);
	update_line(ligne,*d,4);
	d=makeInt(303);
	update_line(ligne,*d,6);
	
	print_line(ligne);
	printf("\n Deleteline \n");
	delete_line(ligne);
	print_line(ligne);
	
	
	return EXIT_SUCCESS;
}

void
testfusion(char * req, query *q){
 	printf("-----------------------------------------\n");
	printf(" Query --> %s\n", req);
  	q = analyseur (req);
  	affiche (q);
      	printf("\nRestitution : ");
	restitue (q);

 	execute(q);
  	printf("-----------------------------------------\n\n");
}
void
pause (void) {
	printf("Entrée pour passez aux exemples suivants ...");
	getchar();
  	system("clear");
}
