/* Proc1.c */

#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>

int main() {

struct passwd *temp;

temp = getpwent();

	while(temp != NULL) {
		printf("%s ", temp -> pw_name);
	
	temp = getpwent();		
	}

return 0;

}
