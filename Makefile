# 
# File:   Makefile
# Author: Pierre Valarcher
#
# Created on 23 mai 2012
#

CC = gcc
LEX = flex

OFILES = main.o \
         DataBase.o \
         HeaderTable.o \
         Table.o \
         Line.o\
         parseur.o \
         lexeur.o \
         requetes.o \
         data.o \
         analyseur.o \
	 fonctions.o


EXE = exampleBD

but : ${EXE}

${EXE} : ${OFILES}
	$(CC) $(CFLAGS) -o ${EXE} ${OFILES}

fonctions.o : fonctions.c fonctions.h analyseur.h

analyseur.o : analyseur.c analyseur.h requetes.h data.h lexeur.c parseur.c DataBase.c

data.o : data.c data.h

requetes.o : requetes.c requetes.h data.h

parseur.o : parseur.c parseur.h requetes.h data.h

parseur.c : parseur.y
	bison parseur.y

lexeur.o : lexeur.c parseur.c


Line.o : Line.c data.h

Table.o : Table.c Table.h 

HeaderTable.o : HeaderTable.c HeaderTable.h 

DataBase.o : DataBase.c DataBase.h

main.o : main.c analyseur.h Line.h HeaderTable.h Table.h DataBase.h

# nettoyage des fichiers crees

clean :
	-rm -f ${OFILES} ${EXE} parseur.c parseur.h lexeur.c lexeur.h
	
mrproper : clean but

.PHONY : but clean mrproper

# fin du Makefile
