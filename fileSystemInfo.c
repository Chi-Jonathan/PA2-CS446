#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>

int ls_sim(struct dirent*);

int ls_sim_verbose(struct dirent*);

int main(int argc, char* argv[]){
	char* args[argc];
	memset(args, 0, argc*sizeof(int));
	int count = 0;
	struct dirent *pDirent;
	DIR *dir;
	for(int i = 0; i < argc; i++){
		args[i] = argv[i+1];
		count++;
	}
	if(args[0] == NULL || strcmp(args[0], "ls") != 0){
		printf("An error has occurred. Options are:\nls\nls -la\nls <path>\nls -la <path>\n");
		return -1;
	}
	else if(argc == 2){
		dir = opendir("./");
		if(dir == NULL){
			printf("An error has occurred. Options are:\nls\nls -la\nls <path>\nls -la <path>\n");
			return -1;
		}
		while(ls_sim(readdir(dir)) == 0);
	}
	if(argc == 3){
		if(strcmp(args[1], "-la") == 0){
			dir = opendir("./");
			while(ls_sim(readdir(dir)) == 0);
		}
		else if(strcmp(args[1], "-l") == 0){
			dir = opendir("./");
			printf("Filename               Mode         I-Node       Size(B)    Links\n");
			printf("=================================================================\n");
			while(ls_sim_verbose(readdir(dir)) != -1);
		}
		else{
			dir = opendir(args[1]);
			if(dir == NULL){
				printf("An error has occurred. Options are:\nls\nls -la\nls <path>\nls -la <path>\n");
				return -1;
			}
			while(ls_sim(readdir(dir)) == 0);
		}
	}
	else if(argc == 4){
		dir = opendir(args[2]);
		if(dir == NULL){
			printf("An error has occurred. Options are:\nls\nls -la\nls <path>\nls -la <path>\n");
			return -1;
		}
		if(strcmp(args[1], "-la") == 0){
			while(ls_sim(readdir(dir)) == 0);
		}
		else if(strcmp(args[1], "-l") == 0){
			printf("Filename               Mode         I-Node       Size(B)    Links\n");
			printf("=================================================================\n");
			while(ls_sim_verbose(readdir(dir)) != -1);
		}
	}
}

int ls_sim(struct dirent* pDirent){
	if(pDirent==NULL){
		return 1;
	}
	printf("%s\n", pDirent -> d_name);
	return 0;
}

void strmode(mode_t mode, char * buf) {
  const char chars[] = "rwxrwxrwx";
  for (size_t i = 0; i < 9; i++) {
    buf[i] = (mode & (1 << (8-i))) ? chars[i] : '-';
  }
  buf[9] = '\0';
}

int ls_sim_verbose(struct dirent* pDirent){
	if(pDirent==NULL){
		return -1;
	}
	char mode[10];
	char buffer[100];
	struct stat sb;
	strcpy(buffer, "./");
	strcat(buffer, pDirent -> d_name);
	if(stat(buffer, &sb) == -1){
		return 1;
	}
	strmode(sb.st_mode, mode);
	printf("%s",pDirent -> d_name);
	printf("%*s",32-strlen(pDirent -> d_name),mode);
	printf("%10li",sb.st_ino);
	printf("%13ld",sb.st_size);
	printf("%8ld\n",sb.st_nlink);
	return 0;
}