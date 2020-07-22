#include <sys/types.h> //readdir,opendir
#include <dirent.h> //readdir,opendir
#include <stdio.h> //printf
#include <string.h> //strlen
#include <stdlib.h> //malloc, atoi

#define MAX_FILELEN 30
#define MAX_FILENUM 10

struct input_files{
	char **files;
	int num_files;
	int chosen_file;
	int f:1;
};

struct input_files listfiles(){
	DIR *d;
	struct dirent *dir;
	struct input_files captures;
	char directory[] = "./captures";
	//allocate memory for MAX_FILENUM amount of char pointers.
	captures.files = malloc(MAX_FILENUM*sizeof(char*));
	for(int i=0;i<10;i++){
		//allocate memory for MAX_FILELEN characters in a filename.
		captures.files[i] = malloc(MAX_FILELEN*sizeof(char));
	}
	
	d = opendir(directory);
	if(d){
		int count = 1;
		while((dir = readdir(d)) != NULL && count <= MAX_FILENUM){
			if(strlen(dir->d_name)>2 && strlen(dir->d_name) < MAX_FILELEN){
				printf("%d. %s\n",count,dir->d_name);
				captures.files[count-1] = dir->d_name;
				for(int i=0;i<strlen(dir->d_name);i++){
					captures.files[count-1][i]=dir->d_name[i];
				}
				count++;
			}
		}
		closedir(d);
		captures.num_files = count-1;
		return captures;
	}
	else{
		printf("Directory does not exist.\n");
		captures.f = 1;
		return captures;
	}
}

struct input_files getfile(struct input_files captures){
	printf("Please enter the number of the file you wish to read: ");
	char input[MAX_FILELEN];
	fgets(input,MAX_FILELEN,stdin);
	int val = atoi(input);
	captures.chosen_file = val;
	//printf("\nNumber you chose: %d\nAffiliated File: %s\n",val,captures.files[val-1]);
	//printf("Number of captures: %d\n",captures.num_files);
	return captures;
}

void decode(struct input_files captures){
	FILE *fm_file;
	fm_file = fopen(captures.files[captures.chosen_file-1], "r");
	char buff[250];
	
	//location in memory, size in bytes of elements, number of elements to read, file to read from.
	fread(buff,1,100,fm_file);
	printf("The first byte: %d\n",buff[1]);
	
	fclose(fm_file);
}


int main(){
	struct input_files captures = listfiles();
	if(captures.f == 0){
		captures = getfile(captures);
		printf("Now decoding %s...\n",captures.files[captures.chosen_file-1]);
		decode(captures);
	}
	else{
		printf("exiting...\n");
	}
}
