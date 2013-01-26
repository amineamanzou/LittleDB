/*
 * File:   parseur.y
 * Author: Luc Hernandez
 *
 * Created on 19 mai 2012
 */


%{
#include <stdlib.h>
#include <stdio.h>
#include "requetes.h"
%}

/* en cas de Bison version 2.4
%define api.pure
%output "parseur.c"
*/
%pure-parser
%output="parseur.c"

%parse-param {query** result}
%defines

%union {
  int integer;
  char* name;
  char character;
  fields* fieldsList;
  enum type kind;
  values* valuesList;
  data* value;
  names* namesList;
  condition* clause;
  term* comparisonTerm;
  query* unused;
}

%{
int yylex(YYSTYPE* lvalp);
void yyerror (query** result, const char *);
%}

%token <integer> CONSTANT_INT
%token <character> CONSTANT_CHAR
%token <name> IDENTIFIER SYMBOL_ALL SQL_FILE SQL_OLD_FILE
%token SYMBOL_CREATE SYMBOL_TABLE SYMBOL_INSERT SYMBOL_INTO SYMBOL_VALUES SYMBOL_LOAD SYMBOL_SAVE SYMBOL_EXIT
%token SYMBOL_DELETE SYMBOL_FROM SYMBOL_WHERE SYMBOL_DROP SYMBOL_SELECT
%token OPERATOR_AND OPERATOR_OR TYPE_INT TYPE_CHAR
%type <fieldsList> fields_list
%type <kind> a_kind
%type <valuesList> values_list
%type <value> a_value
%type <namesList> names_list ETOILE
%type <clause> clause_1 clause_2 clause_3
%type <character> a_comparator
%type <comparisonTerm> a_term
%type <unused> the_query

%start the_query

%%

the_query      : SYMBOL_CREATE SYMBOL_TABLE IDENTIFIER '(' fields_list ')'
                  {
                    *result = makeCreate($3, $5);
                  }
               | SYMBOL_INSERT SYMBOL_INTO IDENTIFIER '(' names_list ')' SYMBOL_VALUES '(' values_list ')'
                  {
                    *result = makeInsert($3, $5, $9);
                  }
               | SYMBOL_DELETE SYMBOL_FROM IDENTIFIER SYMBOL_WHERE clause_3
                  {
                    *result = makeDelete($3, $5);
                  }
               | SYMBOL_DROP SYMBOL_TABLE IDENTIFIER
                  {
                    *result = makeDrop($3);
                  }
               | SYMBOL_SELECT names_list SYMBOL_FROM names_list SYMBOL_WHERE clause_3
                  {
                    *result = makeSelect($2, $4, $6);
                  }
               | SYMBOL_SELECT ETOILE SYMBOL_FROM names_list
                  {
                    *result = makeSelect($2, $4, NULL);
                  }
		| SYMBOL_SELECT ETOILE SYMBOL_FROM names_list SYMBOL_WHERE clause_3
		  {
		    *result = makeSelect($2,$4,$6);
		  }
		| SYMBOL_LOAD SQL_FILE
		  {
		    *result = makeLoad($2);
		  }
		| SYMBOL_LOAD SQL_OLD_FILE
		  {
		    *result = makeLoad($2);
		  }
		| SYMBOL_SAVE
		  {
		    *result = makeSave();
		  }
		| SYMBOL_EXIT
		  {
		    *result = makeExit();
		  }
               ;

ETOILE	       : SYMBOL_ALL
		  {
		    $$ = addFile ($1); 
		  }
	       ;

names_list     : IDENTIFIER
                  {
                    $$ = addName($1, NULL);
                  }
               | names_list ',' IDENTIFIER
                  {
                    $$ = addName($3, $1);
                  }
	       ;


values_list    : a_value
                  {
                    $$ = addValue($1, NULL);
                  }
               | values_list ',' a_value
                  {
                    $$ = addValue($3, $1);
                  }
               ;


a_value        : CONSTANT_INT
                  {
                    $$ = makeInt($1);
                  }
               | CONSTANT_CHAR
                  {
                    $$ = makeCar($1);
                  }
               ;


fields_list    : IDENTIFIER a_kind
                  {
                    $$ = addField($1, $2, NULL);
                  }
               | fields_list ',' IDENTIFIER a_kind
                  {
                    $$ = addField($3, $4, $1);
                  }
               ;


a_kind         : TYPE_INT
                  {
                    $$ = Entier;
                  }
               | TYPE_CHAR
                  {
                    $$ = Caractere;
                  }
               ;


clause_3       : clause_3 OPERATOR_OR clause_2
                  {
                    $$ = makeDisjunction($1, $3);
                  }
               | clause_2
                  {
                    $$ = $1;
                  }
               ;


clause_2       : clause_2 OPERATOR_AND clause_1
                  {
                    $$ = makeConjunction($1, $3);
                  }
               | clause_1
                  {
                    $$ = $1;
                  }
               ;


clause_1       : a_term a_comparator a_term
                  {
                    if ($2 == '=')
                      $$ = makeEquality($1, $3);
                    else if($2 == '<')
                      $$ = makeInferiority($1, $3);
		    else
		      $$ = makeSuperiority($1, $3);
                  }
               | '!' clause_1
                  {
                    $$ = makeNegation($2);
                  }
               | '(' clause_3 ')'
                  {
                    $$ = $2;
                  }
               ;


a_term         : a_value
                  {
                    $$ = makeConstantTerm($1);
                  }
	       | IDENTIFIER
                  {
                    $$ = makeFieldTerm($1);
                  }
               ;


a_comparator   : '='
                  {
                    $$ = '=';
                  }
               | '<'
                  {
                    $$ = '<';
                  }

               | '>'
                  {
                    $$ = '>';
                  }
               ;

%%

void yyerror (query** resultat, const char *s) {
  fprintf (stderr, "%s\n", s);
}

/* fin de parseur.y */
