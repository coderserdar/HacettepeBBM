#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


//this is used to run the program in the -d mode
void traverse(char *fn, int indent,int counter) {
  DIR *dir;
  struct dirent *entry;
  int count;
  int b,c;
  char path[1025];
  struct stat info;

	for (count=0; count<indent; count++) printf(" ");
		//printf("%s\n", fn);

	if ((dir = opendir(fn)) == NULL)
		perror("opendir() error");
	else
	{
		while ((entry = readdir(dir)) != NULL) {
			if (entry->d_name[0] != '.') {
				strcpy(path, fn);
				strcat(path, "/");
				strcat(path, entry->d_name);

				if(indent == 0)
				{
					printf("|-- ");
				}

				else
				{
					printf("|");
					for(c = 0 ; c < indent ; c++)
						printf("\t");
					printf("|-- ");
				}

				//printf("%s\n", entry->d_name);
				b = strlen(entry->d_name);
				if((entry->d_name[b-2] == '.') || (entry->d_name[b-4] == '.') || (entry->d_name[b-5] == '.'))
				{
					printf("%s",entry->d_name);
					if (stat(entry->d_name, &info) < 0)
					{
						for(c = 4 ; c > indent ; c--)
							printf("\t");
						printf("%d\t\t%s\n", info.st_size , ctime(&info.st_atime));
					}
				}
				else
				{
					printf("%s/\n",entry->d_name);
					counter++;
				}




				if (stat(path, &info) != 0)
					fprintf(stderr, "stat() error on %s: %s\n", path,
							strerror(errno));
				else if (S_ISDIR(info.st_mode))
				{
					//printf("%s\n",path);
					traverse(path, indent+1,counter);
				}
			}
		}
		closedir(dir);
	}

}// end of the traverse


void f_copy(char* path1, char* path2, char* name){

	char source[256];
	char target[256];
	char* content;
	int size;
	struct stat info;
	int s;
	int t;
	
	
	strcpy(source, path1);
	strcpy(target, path2);
	strcat(source, "/");
	strcat(target, "/");
	strcat(source, name);
	strcat(target, name);
	
	stat(source, &info);
	size = info.st_size;
	
	content = (char*)malloc(size);
	
	s = open(source, O_RDWR);
	t = creat(target, S_IRWXG);
	read(s, content, size);
	write(t, content, size);
	
	close(t);
	close(s);
}



//this is used to run the program in the -i mode
void i(char *fn1, char *fn2) {
	
}// end of the i function


//this is used to run the program in the -u mode

void u(char *fn1, char *fn2){
	
	DIR *dir1;
	DIR *dir2;
	struct dirent *entry1;
	struct dirent *entry2;
	int count;
	char path1[1025];
	char path2[1025];
	char command[1025]; 
	struct stat info1;
	struct stat info2;
	
	if ((dir1 = opendir(fn1)) == NULL)
		perror("opendir() error");
	else {
		while((entry1 = readdir(dir1)) != NULL) {
			if (entry1->d_name[0] != '.') {
									
				strcpy(path1, fn1);
				strcat(path1, "/");
				strcat(path1, entry1->d_name);
				
				if (stat(path1, &info1) != 0)
					printf("stat() error on %s: %s\n", path1, strerror(errno));

				if((dir2 = opendir(fn2)) == NULL) 
					perror("opendir() error");
				else {
					count = 0;					
					while((entry2 = readdir(dir2)) != NULL)	{			
						if (entry2->d_name[0] != '.') {
							
							if(strcmp(entry1->d_name, entry2->d_name)!=0)
								continue;
							count++;
							
							if (S_ISDIR(info1.st_mode)) {
							
								strcpy(path2, fn2);
								strcat(path2, "/");
								strcat(path2, entry2->d_name);
								if (stat(path2, &info2) != 0)
									printf("stat() error on %s: %s\n", path2, strerror(errno));
								else
									u(path1, path2);
							}
						}
					}
					if(count == 0) {		// extra directory
						if (S_ISDIR(info1.st_mode)) {
							printf("copy\t %s/ %s/\n", path1, fn2);   
							strcpy(command, "cp -r ");
							strcat(command, path1);
							strcat(command, " ");
							strcat(command, fn2);
							system(command); 
						}else {
							printf("copy\t %s %s/\n", path1, fn2);   
							strcpy(command, "cp -r ");
							strcat(command, path1);
							strcat(command, " ");
							strcat(command, fn2);
							system(command);	
						}	
					}
					closedir(dir2);				
				}
			}	
		}	
		closedir(dir1);
	}
}// end of the u function




int main(int argc , char *argv[])
{
	char *mode , *firstdir , *seconddir ;

	if(argc < 4)
	{
		printf("Parameters are wrong.\n");
		exit(-1);
	}
	else if (argc > 4)
	{
		printf("There are too much parameters.\n");
		exit(-5);
	}
	else
	{
		mode = argv[1];
		firstdir = argv[2];
		seconddir = argv[3];
		if(strcmp(mode,"-d") == 0)
		{
			printf("%s\t\t\t\t\t size\t\t time stamp\t\t\t state",firstdir);
			traverse(firstdir,0,0);
			printf("\n%s\t\t\t\t\t size\t\t time stamp\t\t\t state",seconddir);
			traverse(seconddir,0,0);
		}
		else if(strcmp(mode,"-i") == 0)
		{
			u(argv[2], argv[3]);
			u(argv[3], argv[2]);
		}
		else if(strcmp(mode,"-u") == 0)
		{
			u(argv[2], argv[3]);
			u(argv[3], argv[2]);
		}
		else
		{
			printf("This mode is not defined in this program.\n");
			exit(-2);
		}
	}
	return 0;
}// end of the main function

