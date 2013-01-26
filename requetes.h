/*
 * 
 * Author: Amanzou Amine, Jeremy Paulino
 *
 * Created on 20 mai 2012
 */

#ifndef REQUETES_H
#define REQUETES_H

#include "data.h"

typedef struct fields {
  char* name;
  enum type kind;
  struct fields* next;
} fields;

typedef struct values {
  data* value;
  struct values* next;
} values;

typedef struct names {
  char* name;
  struct names* next;
} names;

typedef struct {
  union {
    char* name;
    data* value;
  } content;
  enum {
    FIELD_TERM,
    CONSTANT_TERM
  } kind;
} term;

struct condition;

typedef struct {
  term* left;
  term* right;
} contentComparison;

typedef struct {
  struct condition* left;
  struct condition* right;
} contentBinary;

typedef struct {
  struct condition* daughter;
} contentUnary;

typedef struct condition {
  union {
    contentComparison three;
    contentBinary two;
    contentUnary one;
  } content;
  enum {
    DISJUNCTION,
    CONJUNCTION,
    NEGATION,
    EQUALITY,
    SUPERIORITY,
    INFERIORITY
  } kind;
} condition;

typedef struct {
  char* tableName;
  fields* fieldsList;
} contentCreate;

typedef struct {
  char* tableName;
  names* fieldNamesList;
  values* fieldValuesList;
} contentInsert;

typedef struct {
  char* tableName;
  condition* clause;
} contentDelete;

typedef struct {
  char* tableName;
} contentDrop;

typedef struct {
  names* fieldNamesList;
  names* tableNamesList;
  condition* clause;
} contentSelect;

typedef struct {
  char* namefile;
} contentLoad;

typedef struct {
  union {
    contentCreate create;
    contentInsert insert;
    contentDelete delete;
    contentDrop drop;
    contentSelect select;
    contentLoad load;
  } content;
  enum {
    CREATE_QUERY,
    INSERT_QUERY,
    DELETE_QUERY,
    DROP_QUERY,
    SELECT_QUERY,
    SAVE_QUERY,
    LOAD_QUERY,
    EXIT_QUERY
  } kind;
} query;

fields* addField(char*, enum type, fields*);
values* addValue(data*, values*);
names* addName(char*, names*);
names* addFile (char *nm);

term* makeFieldTerm(char*);
term* makeConstantTerm(data*);
term* makeConstantNull();

condition* makeDisjunction(condition*, condition*);
condition* makeConjunction(condition*, condition*);
condition* makeNegation(condition*);
condition* makeEquality(term*, term*);
condition* makeInferiority(term*, term*);
condition* makeSuperiority(term*, term*);

query* makeCreate(char*, fields*);
query* makeInsert(char*, names*, values*);
query* makeDelete(char*, condition*);
query* makeDrop(char*);
query* makeSelect(names*, names*, condition*);
query* makeLoad(char*);
query* makeSave();
query* makeExit();

#endif

/* fin de requetes.h */
