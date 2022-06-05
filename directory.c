#include "directory.h"

File_file_tq get_all_path_file(const char *path, const char *extension){

	assert(extension != NULL);
	assert(path != NULL);

	File_file_tq file;
	file.tete = NULL;
	file.queue = NULL;

	if(extension != NULL && path != NULL){	

		int size_extension = strlen(extension);

		DIR *dir = open_directory(path);
		struct dirent *current_file = NULL;
		insert_fd(&file, NULL, path);

		while((current_file = readdir(dir)) != NULL){

			if(strcmp(current_file->d_name, ".") != 0 && strcmp(current_file->d_name, "..") != 0){

				int size_path = strlen(current_file->d_name);
				int i = size_extension;
				int j = size_path;

				while(i >= 0 && j >= 0){

					if(strcmp(&extension[i], &current_file->d_name[j]) != 0){

						j = -1;
					}
					else{

						i -= 1;
						j -= 1;
					}
				}
				if(i < 0){

					insert_fd(&file, current_file->d_name, file.tete->name);
				}
			}
		}

		close_directory(&dir);
		supp_tete_fd(&file);
	}

	return file;
}

File_file_tq get_all_path_file_s(const char *path, const char *extension){

	assert(extension != NULL);
	assert(path != NULL);

	File_file_tq file_directory;
	file_directory.tete = NULL;
	file_directory.queue = NULL;

	File_file_tq file;
	file.tete = NULL;
	file.queue = NULL;

	if(extension != NULL && path != NULL){	

		int size_extension = strlen(extension);

		insert_fd(&file_directory, NULL, path);

		while(file_directory.tete != NULL){

			DIR *dir = open_directory(file_directory.tete->name);
			struct dirent *current_file = NULL;

			while((current_file = readdir(dir)) != NULL){

				if(strcmp(current_file->d_name, ".") != 0 && strcmp(current_file->d_name, "..") != 0){

					int is_dir = check_if_directory(current_file);
					
					//si c'est pas un repertoire alors on rentre dans le if
					if(is_dir == 0){

						int size_path = strlen(current_file->d_name);
						int i = size_extension;
						int j = size_path;

						while(i >= 0 && j >= 0){

							if(strcmp(&extension[i], &current_file->d_name[j]) != 0){

								j = -1;
							}
							else{

								i -= 1;
								j -= 1;
							}
						}
						if(i < 0){

							insert_fd(&file, current_file->d_name, file_directory.queue->name);
						}
					}
					else{

						insert_fd(&file_directory, current_file->d_name, file_directory.tete->name);
					}
				}
			}

			supp_tete_fd(&file_directory);
			close_directory(&dir);
		}
	}

	return file;
}

int file_exist(const char *filename, const char *path){

	assert(filename != NULL);
	assert(path != NULL);

	int found = 0;

	if(filename != NULL && path != NULL){

		DIR *dir = open_directory(path);
		struct dirent *current_file = NULL;

		while((current_file = readdir(dir)) != NULL && found == 0){

			if(strcmp(current_file->d_name, filename) == 0){

				found = 1;
			}
		}

		close_directory(&dir);
	}
	return found;
}

int file_exist_s(const char *filename, const char *path){

	assert(filename != NULL);
	assert(path != NULL);

	int found = 0;
	File_file_tq file;
	file.tete = NULL;
	file.queue = NULL;

	if(filename != NULL && path != NULL){

		insert_fd(&file, NULL, path);

 		while(file.tete != NULL && found == 0){

			DIR *dir = open_directory(file.tete->name);

			struct dirent *current_file = NULL;

			while((current_file = readdir(dir)) != NULL && found == 0){

				if(strcmp(current_file->d_name, filename) == 0){

					found = 1;
				}
				else if(strcmp(current_file->d_name, ".") != 0 && strcmp(current_file->d_name, "..") != 0 && check_if_directory(current_file) == 1){

					insert_fd(&file, current_file->d_name, file.tete->name);
				}
			}

			supp_tete_fd(&file);
			close_directory(&dir);
		}
	}

	while(file.tete != NULL){

		supp_tete_fd(&file);
	}

	return found;
}

void close_directory(DIR **dir){

	assert(*dir != NULL);

	if(*dir != NULL){

		closedir(*dir);
		*dir = NULL;
	}
}

DIR *open_directory(const char *path){

	assert(path != NULL);

	DIR *directory = NULL;

	if(path != NULL){

		directory = opendir(path);
		if(directory == NULL){

			perror("opendir failed");
			exit(1);
		}
	}

	return directory;
}

int check_if_directory(struct dirent *current_file){

	assert(current_file != NULL);
	int is_dir = 0;

	if(current_file != NULL){
		//verification si repertoire
		if(current_file->d_type == DT_DIR){

			is_dir = 1;
		}
		else if(current_file->d_type == DT_UNKNOWN){

			struct stat stat_directory;
			stat(current_file->d_name, &stat_directory);
			if((stat_directory.st_mode & S_IFMT) == S_IFDIR){

				is_dir = 1;
			}
		}
	}

	return is_dir;
}