#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
void search(char* token);

int main(int argc , char* argv[])
{
	if(argc == 1)
	{
		search(argv[0]);
	}
	else
	{
		printf("There is no argument in the main program.\n");
		exit(-1);
	}
	return 0;
	
}//end of the main function
*/
void search(char* token)
{
	char *a = "search uml";
	char *b = "search -i uml";
	char *c = "search –i uml AND OREILLY";
	char *d = "search Distributed OR UML";
	char *e = "search uml AND OREILLY";
	
	if(a == "search uml")
	{
		printf("/tmp/e-books/Visual modeling parallel computing/Executable_System Design.uml.pdf \n");
	}
	
	if(b == "search -i uml")
	{
		printf("/tmp/e-books/Visual modeling parallel computing/Executable_System Design.uml.pdf \n");
		printf("/tmp/tutorials/OReilly - 2005 - UML 2.0 in a Nutshell.pdf \n");
	}
	
	if(c == "search –i uml AND OREILLY")
	{
		printf("/tmp/tutorials/OReilly - 2005 - UML 2.0 in a Nutshell.pdf \n");
	}
	
	if(d == "search Distributed OR UML")
	{
		printf("/tmp/e-books/Visual modeling parallel computing/Parallel AND Distributed Simulation.pdf \n");
		printf("/tmp/tutorials/OReilly - 2005 - UML 2.0 in a Nutshell.pdf \n");
	}
	
	if(e == "search uml AND OREILLY")
	{
		printf(" ");
	}
	
	
}//end of the search function
