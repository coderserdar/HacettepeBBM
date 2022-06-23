#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 30

typedef struct stu *stu_ptr; 

typedef struct stu{ 
  stu_ptr leftChild; 
  int no; 
  char name[20]; 
  char surname[20]; 
  int grade; 
  stu_ptr rightChild; 
}student; 

int findchar(char* str,char c)
{
	int i;
	int len = strlen(str);
	for(i = 0; i < len; i++)
	{
		if(str[i] == c)
		{
			return i;
		}
	}

	return -1; // failure
}


void Operations(FILE * , FILE *);
stu_ptr deleteNode(int ,stu_ptr);
void findGrade(char [], char [],stu_ptr,FILE *,int*);
extern int addNode(stu_ptr, int);
extern void printTree(stu_ptr);
extern int calculateAverage(stu_ptr);
int depth(stu_ptr);
int MAX(int,int);
stu_ptr wander(stu_ptr,int);
void wanderAndWrite(stu_ptr,int,FILE *);
stu_ptr findMax(stu_ptr);

int main (int argc , char *argv[])
{
	if (argc < 2)
	{
		printf("The parameters are wrong.\n");
		exit(-1);
	}
	else if(argc > 2)
	{
		printf("There are too much parameters..\n");
		exit(1);
	}
	else
	{
		FILE *input,*output;
		input = fopen(argv[1],"r");
		if((input = fopen(argv[1],"r")) == NULL)
		{
			printf("Input File can not be opened.\n");
		}
		output = fopen("output.txt","w");
		if((output = fopen("output.txt","w")) == NULL)
		{
			printf("Output File can not be opened.\n");
		}
		Operations(input,output);
	}
	return 0;
}// end of the main function


void Operations(FILE * inputFile , FILE * outputFile)
{
	
	char name[20],surname[20];
	char command[10];
	int no,grade,result;
	int i = 0 ,a = 0, b = 0;
	stu_ptr root = (stu_ptr) malloc (sizeof(student));
	root->leftChild = NULL ;
	root->rightChild = NULL ;
	//stu_ptr temp = (stu_ptr) malloc (sizeof(student));
	while( !feof(inputFile) )
	{
		fscanf(inputFile, "%s", command);
		
		if(strcmp(command,"ADD") == 0)
		{
			stu_ptr tempstudent = (stu_ptr) malloc (sizeof(student));
			tempstudent->leftChild = NULL ;
			tempstudent->rightChild = NULL ;
			fscanf(inputFile,"%d %s %s %d",&no,name,surname,&grade);
			strcpy(tempstudent->name,name);
			strcpy(tempstudent->surname,surname);
			tempstudent->no = no;
			tempstudent->grade = grade ;
			if(b == 0)
			{
				strcpy(root->name,name);
				strcpy(root->surname,surname);
				root->no = no;
				root->grade = grade ;
				//printf("%s %s %d %d\n",root->name,root->surname,root->no,root->grade);
				i = addNode(root,no);
			}
			else
			{
				i = addNode(tempstudent,no);
				//fprintf(outputFile,"%d\n",i);
			}
			b++;
		}//if the line equals to "ADD"
		
		else if(strcmp(command,"DELETE") == 0)
		{
			stu_ptr temp ;
			fscanf(inputFile,"%d",&no);
			if(root == NULL)
			{
				fprintf(outputFile,"Tree is empty\n");
			}
			else
			{
				fprintf(outputFile,"Route:");
				wanderAndWrite(root,no,outputFile);
				temp = wander(root,no);
				if(temp == NULL)
				{
					printf("\n%d Node not found!\n");
					fprintf(outputFile,"\n%d Node not found!\n",no);
				}
				else
				{
					printf("\n %d is deleted\n",temp->no);
					deleteNode(no , temp);
					
				}
			}
		}//if the line equals to "DELETE"
		
		else if(strcmp(command,"AVERAGE") == 0)
		{
			int sum = 0 ,acounter = 0;
			acounter = calculateAverage(root);
			if(acounter == 0)
			{
				printf("Tree is empty.\n");
				fprintf(outputFile,"Tree is empty.\n");
			}
			else
			{
				printf("Average: %d\n",acounter);
				fprintf(outputFile,"Average: %d\n",acounter);
			}
			
		}//if the line equals to "AVERAGE"
		
		if(strcmp(command,"PRINT") == 0)
		{
			int e = 0 ;
			if(root)
			{
				printTree(root);
			}
			else
			{
				fprintf(outputFile,"Tree is empty.\n");
			}
			
		}//if the line equals to "PRINT"
		
		
		else if(strcmp(command,"FINDGRADE") == 0)
		{
			int d ;
			d = 0;
			fscanf(inputFile,"%s %s",name,surname);
			findGrade(name,surname,root,outputFile,&d);
			if(d == 0)
			{
				printf("Node not found\n");
				fprintf(outputFile,"Node not found\n");
			}
			
		}//if the line equals to "PRINT"
		else
		{
			//printf("This context is not suitable for the suitable input.\n");
		}
		
	}
	
}//end of the Operation function

void findGrade(char n[],char sur[],stu_ptr root,FILE *output,int *d)
{	
	if(root)
	{
		//printf("%s %s\n",root->name , root->surname);
		if((strcmp(root->name,n) == 0) && (strcmp(root->surname,sur) == 0))
		{
			*d = 1 ;
			printf("Grade: %d\n",root->grade);
			fprintf(output,"Grade: %d\n",root->grade);
		}
		else
		{
			findGrade(n,sur,root->leftChild,output,&(*d));
			findGrade(n,sur,root->rightChild,output,&(*d));
		}
	}
		
}//this function is used to find the grade of a student with the given parameters..

stu_ptr deleteNode(int no ,stu_ptr T)
{
	 stu_ptr TmpCell ;
	 if( T->leftChild && T->rightChild )  /* Two children */
	 {
	     TmpCell = findMax( T->leftChild );
	     T->no = TmpCell->no;
	     strcpy(T->name,TmpCell->name);
	     strcpy(T->surname,TmpCell->surname);
	     T->grade = TmpCell->grade;
	     T->leftChild = deleteNode( T->no, T->leftChild );
	 }
	 else  /* One or zero children */
	 {
	     TmpCell = T;
	     if( T->leftChild == NULL ) /* Also handles 0 children */
	          T = T->rightChild;
	     else if( T->rightChild == NULL )
	          T = T->leftChild;
	     free( TmpCell );
	 }
	 return T;
}//this is used to delete a node

stu_ptr wander(stu_ptr root , int no)
{
	if(root)
	{
		if(root->no==no)
		{
			return (root);
		}
		else if(root->no < no)
		{
			return wander(root->rightChild,no);
		}
		else
		{
			return wander(root->leftChild,no);
		}
	}
	return NULL;
}//this is used to find an element in the tree

void wanderAndWrite(stu_ptr root , int no , FILE *output)
{
	if(root)
	{
		printf(" -> %d",root->no);
		fprintf(output," -> %d",root->no);
		if(no < root->no)
		{
			wanderAndWrite(root->leftChild,no,output);
		}
		else if(no > root->no)
		{
			wanderAndWrite(root->rightChild,no,output);
		}
	}
	
}//this is used to find an element in the tree

stu_ptr findMax( stu_ptr T )
{
	if( T != NULL )
        while( T->rightChild != NULL )
            T = T->rightChild;

    return T;
}

