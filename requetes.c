/*
 *
 * Author: Amanzou Amine, Jeremy Paulino
 *
 * Created on 20 mai 2012
 */

#include <stdlib.h>
#include <string.h>
#include "requetes.h"

fields* addField(char* nm, enum type k, fields* nx) {
  fields* tmp = (fields*) malloc(sizeof(fields));
  tmp->name = nm;
  tmp->kind = k;
  tmp->next = nx;
  return tmp;
}

values* addValue(data* v, values* nx) {
  values* tmp = (values*) malloc(sizeof(values));
  tmp->value = v;
  tmp->next = nx;
  return tmp;
}

names* addName(char*nm , names* nx) {
  names* tmp = (names*) malloc(sizeof(names));
  tmp->name = nm;
  tmp->next = nx;
  return tmp;
}

names* addFile (char *nm){
  names* tmp = (names*) malloc(sizeof(names));
  tmp->name = nm;
  tmp->next = NULL;
  return tmp;
}

term* makeFieldTerm(char* n) {
  term* tmp = (term*) malloc(sizeof(term));
  tmp->kind = FIELD_TERM;
  tmp->content.name = n;
  return tmp;
}

term* makeConstantTerm(data* v) {
  term* tmp = (term*) malloc(sizeof(term));
  tmp->kind = CONSTANT_TERM;
  tmp->content.value = v;
  return tmp;
}

/*term* makeConstantNull() {
	term* tmp = (term*) malloc(sizeof(term));
	tmp->kind = Vide;
	return tmp;
}*/

condition* makeDisjunction(condition* l, condition* r) {
  condition* tmp = (condition*) malloc(sizeof(condition));
  tmp->kind = DISJUNCTION;
  tmp->content.two.left = l;
  tmp->content.two.right = r;
  return tmp;
}

condition* makeConjunction(condition* l, condition* r) {
  condition* tmp = (condition*) malloc(sizeof(condition));
  tmp->kind = CONJUNCTION;
  tmp->content.two.left = l;
  tmp->content.two.right = r;
  return tmp;
}

condition* makeNegation(condition* d) {
  condition* tmp = (condition*) malloc(sizeof(condition));
  tmp->kind = NEGATION;
  tmp->content.one.daughter = d;
  return tmp;
}

condition* makeEquality(term* l, term* r) {
  condition* tmp = (condition*) malloc(sizeof(condition));
  tmp->kind = EQUALITY;
  tmp->content.three.left = l;
  tmp->content.three.right = r;
  return tmp;
}

condition* makeInferiority(term* l, term* r) {
  condition* tmp = (condition*) malloc(sizeof(condition));
  tmp->kind = INFERIORITY;
  tmp->content.three.left = l;
  tmp->content.three.right = r;
  return tmp;
}

condition* makeSuperiority(term* l, term* r) {
  condition* tmp = (condition*) malloc(sizeof(condition));
  tmp->kind = SUPERIORITY;
  tmp->content.three.left = l;
  tmp->content.three.right = r;
  return tmp;
}

query* makeCreate(char* tn, fields* fl) {
  query* tmp = (query*) malloc(sizeof(query));
  tmp->kind = CREATE_QUERY;
  tmp->content.create.tableName = tn;
  tmp->content.create.fieldsList = fl;
  return tmp;
}

query* makeInsert(char* tn, names* fnl, values* fvl) {
  query* tmp = (query*) malloc(sizeof(query));
  tmp->kind = INSERT_QUERY;
  tmp->content.insert.tableName = tn;
  tmp->content.insert.fieldNamesList = fnl;
  tmp->content.insert.fieldValuesList = fvl;
  return tmp;
}

query* makeDelete(char* tn, condition* cl) {
  query* tmp = (query*) malloc(sizeof(query));
  tmp->kind = DELETE_QUERY;
  tmp->content.delete.tableName = tn;
  tmp->content.delete.clause = cl;
  return tmp;
}

query* makeDrop(char* tn) {
  query* tmp = (query*) malloc(sizeof(query));
  tmp->kind = DROP_QUERY;
  tmp->content.drop.tableName = tn;
  return tmp;
}

query* makeSelect(names* fnl, names* tnl, condition* cl) {
  query* tmp = (query*) malloc(sizeof(query));
  tmp->kind = SELECT_QUERY;
  tmp->content.select.fieldNamesList = fnl;
  tmp->content.select.tableNamesList = tnl;
  tmp->content.select.clause = cl;
  return tmp;
}

query* makeLoad(char* tn)
{
	query* tmp = (query*) malloc(sizeof(query));
	tmp->kind = LOAD_QUERY;
	tmp->content.load.namefile = tn;
	return tmp;
}
query* makeSave()
{
	query* tmp = (query*) malloc(sizeof(query));
	tmp->kind = SAVE_QUERY;
	return tmp;
}
query* makeExit()
{
	query* tmp = (query*) malloc(sizeof(query));
	tmp->kind = EXIT_QUERY;
	return tmp;
}
