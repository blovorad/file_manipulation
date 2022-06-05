#ifndef __DIRECTORY_H__
#define __DIRECTORY_H__

#include "file_directory.h"

/*pour la gestion des repertoires et navigation dans les fichiers*/
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

/*fonction d'ouverture d'un repertoire / fermeture d'un repertoire*/
DIR *open_directory(const char *path);
void close_directory(DIR **dir);

/*fonction de recherche d'un fichier dans un dossier*/
int file_exist(const char *filename, const char *path);
/*fonction de recherche d'un fichier dans un dossier et sous-dossier*/
int file_exist_s(const char *filename, const char *path);

/*fonction de sauvegarde de tous les fichiers selon extension, d'un dossier*/
File_file_tq get_all_path_file(const char *path, const char *extension);
/*fonction de sauvegarde de tous les fichiers selon extension, de dossier/sous-dossier*/
File_file_tq get_all_path_file_s(const char *path, const char *extension);

/*verification si repertoire*/
int check_if_directory(struct dirent *current_file);

#endif