/*
Auteur Gautier Levesque
06/06/2022
*/

/*include standards entrer/sortie et malloc*/
#include <stdio.h>
#include <stdlib.h>

#include "directory.h"

/*fonction principale*/
int main(void){

	printf("fichier trouver bidule.txt : %d\n", file_exist_s("bidule.txt", "."));

	const char *extension[] = {".c", ".h"};
	File_file_tq file = get_all_path_file_s(".", extension, 2);

	while(file.tete != NULL){

		printf("fichier : %s\n", file.tete->name);
		supp_tete_fd(&file);
	}

	return 0;
}