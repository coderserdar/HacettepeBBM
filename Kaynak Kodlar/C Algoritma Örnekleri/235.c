#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<string.h>

/* this structure is used for storing the name of each entry in turn. */
struct dirent* entry;




////////////////////////////////////////////////////
void scan(char* dirPath){
	/* open the directory "/home/users" for reading. */
	DIR* dir = opendir(dirPath);	
	
	if (!dir) {
	    perror("opendir");
	    exit(1);
	}
	
	
	//printf("Directory contents:\n");
	while ( (entry = readdir(dir)) != NULL) {
		
		//printf("|--");
   		//printf("%s\n", entry->d_name);
		DIR* contDir=opendir(entry->d_name);
		//printf("%s\n", entry->d_name);
		if(contDir){
			char *point=".";
			char *doublePoint="..";
			if(strcmp(entry->d_name,point) != 0){
				if(strcmp(entry->d_name,doublePoint) != 0){
					//printf("girdi!!!\n");
					printf("\n");
					printf("|--");
					printf("%s", entry->d_name);
					printf("/\n");
					printf("    ");
					char *newPath;
					char *slash="/";
					char *FinalnewPath;
					

					/* Getting a path when it is directory and put slash end of it */
					//okunan sey directory ise sonuna slash koy
		 			
					
					/* Getting a path when it is directory and put sub directory name end of it */
					//slash koyduktan sonra sundirectoryinin adini koy yeni path olsun
		 			
					//scan(FinalnewPath);

				}//end of if(strcmp(entry->d_name,doublePoint) != 0)
				
			}// end of if(strcmp(entry->d_name,point) != 0)
			
		}// end of if(contDir)
		else{
			printf("|--");
			printf("%s\n", entry->d_name);
		}
		/*
		if(okunan sey directory ise){
			char* newPath=copy(dirPath,entry->d_name);
			scan(newPath);
		}
		else{
			printf();
		}*/
			
	}//end of while
	

	
	if (closedir(dir) == -1) {
	    perror("closedir");
	    exit(1);
	}

	return;

}
//////////////////////////////////////
int main(){
	char *temDirPath="/home/ziya/Desktop/deneme";
	printf(temDirPath);
	printf("\n");
	scan(temDirPath);
	
	return 0;

}

