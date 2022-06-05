#include "file_directory.h"

void insert_fd(File_file_tq *f, const char *name, const char *path){

	assert(path != NULL);

	File_file *tmp = malloc(sizeof(struct file_file));
	if(tmp == NULL){

		perror("malloc failed");
		exit(1);
	}

	int size = strlen(path) + 2;// pour / et \0
	if(name != NULL){

		size += strlen(name);
	}

	tmp->name = malloc(sizeof(char) * size);
	tmp->suivant = NULL;
	if(tmp->name == NULL){

		perror("malloc failed");
		exit(1);
	}

	strcpy(tmp->name, path);
	if(name != NULL){

		strcat(tmp->name, "/");
		strcat(tmp->name, name);
	}

	if(f->tete == NULL){
		f->tete = tmp;
		f->queue = tmp;
	}
	else{

		f->queue->suivant = tmp;
		f->queue = tmp;
	}

	printf("Insertion : %s\n", f->queue->name);
}

void supp_tete_fd(File_file_tq *f){

	assert(f != NULL);

	if(f->tete != NULL){

		File_file *tmp = f->tete;
		f->tete = f->tete->suivant;
		if(f->tete == NULL){

			f->queue = NULL;
		}

		if(tmp->name != NULL){

			free(tmp->name);
			tmp->name = NULL;
		}
		free(tmp);
		tmp = NULL;
	}
}