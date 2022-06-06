/*
Auteur Gautier Levesque
06/06/2022
*/

#ifndef __FILE_DIRECTORY_H__
#define __FILE_DIRECTORY_H__

#include "core.h"

/*include standards entrer/sortie et malloc*/
#include <stdio.h>
#include <stdlib.h>

/*pour les chaines de caractere*/
#include <string.h>

/*structure de la file*/
typedef struct file_file{

	char *name;
	struct file_file *suivant;
}File_file;

typedef struct file_file_tq{

	File_file *tete;
	File_file *queue;
}File_file_tq;

/*gestion des files*/
void insert_fd(File_file_tq *f, const char *name, const char *path);
void supp_tete_fd(File_file_tq *f);

#endif