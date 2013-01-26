/*
 * File:   lexeur.l
 * Author: Luc Hernandez
 *
 * Created on 19 mai 2012
 */

%option noyywrap nounput nostack
%option outfile="lexeur.c" header-file="lexeur.h"

%{

#include <stdlib.h>
#include <string.h>
#include "requetes.h"
#include "parseur.h"

#define YY_DECL int yylex(YYSTYPE *lvalp)

%}

SQL [[:alpha:]][[:alnum:]#$_]*[\.]sql
SQLOLD [[:alpha:]][[:alnum:]#$_]*[\.]sql[\.]old
ENTIER [+\-]?[1-9][0-9]*|[0]
BLANC [[:space:]]+
ID [[:alpha:]][[:alnum:]#$_]*

%%

CREATE {
        return SYMBOL_CREATE;
}

TABLE {
        return SYMBOL_TABLE;
}

INSERT {
        return SYMBOL_INSERT;
}

INTO {
        return SYMBOL_INTO;
}

VALUES {
        return SYMBOL_VALUES;
}

DELETE {
        return SYMBOL_DELETE;
}

FROM {
        return SYMBOL_FROM;
}

WHERE {
        return SYMBOL_WHERE;
}

DROP {
        return SYMBOL_DROP;
}

SELECT {
        return SYMBOL_SELECT;
}

EXIT {
	return SYMBOL_EXIT;
}
SAVE {
	return SYMBOL_SAVE;
}
LOAD {
	return SYMBOL_LOAD;
}

AND {
        return OPERATOR_AND;
}


OR {
        return OPERATOR_OR;
}

INT {
        return TYPE_INT;
}

CHAR {
        return TYPE_CHAR;
}

[\*] {
	lvalp->name = (char*) malloc((1+yyleng)*sizeof(char));
        strcpy(lvalp->name, yytext);
	return SYMBOL_ALL;
}

{SQL} {
        lvalp->name = (char*) malloc((1+yyleng)*sizeof(char));
        strcpy(lvalp->name, yytext);
        return SQL_FILE;
}
{SQLOLD} {
        lvalp->name = (char*) malloc((1+yyleng)*sizeof(char));
        strcpy(lvalp->name, yytext);
        return SQL_OLD_FILE;
}
{ID} {
        lvalp->name = (char*) malloc((1+yyleng)*sizeof(char));
        strcpy(lvalp->name, yytext);
        return IDENTIFIER;
}

[)(,=<>!] {
        return yytext[0];
}

{ENTIER} {
        lvalp->integer = atoi(yytext);
        return CONSTANT_INT;
}

'.' {
        lvalp->character = yytext[1];
        return CONSTANT_CHAR;
}

'\\.' {
        if (yytext[2] == '0')
          lvalp->character = '\0';
        else if (yytext[2] == 'b')
          lvalp->character = '\b';
        else if (yytext[2] == 'n')
          lvalp->character = '\n';
        else if (yytext[2] == 'r')
          lvalp->character = '\r';
        else if (yytext[2] == 't')
          lvalp->character = '\t';
        else if (yytext[2] == 'Z')
          lvalp->character = 26;
        else
          lvalp->character = yytext[2];
        return CONSTANT_CHAR;
}

'''' {
        lvalp->character = '\'';
        return CONSTANT_CHAR;
}

{BLANC} ;

. {
        printf("Expression incorrecte : \"%s\"\n", yytext);
        return 0;
}

<<EOF>> {
        return 0;
}

%%

/* fin de lexeur.l */
