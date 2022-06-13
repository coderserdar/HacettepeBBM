/* Proc2.c */


#include <sys/types.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

	if(argc != 2) {
		printf ("ARGUMENT NUMBER\n");
		exit(-1);
	}


struct passwd *temp;

temp = getpwnam(argv[1]);

	if(temp != NULL)
		printf("%s %d %d %s", temp -> pw_name, temp -> pw_uid, temp -> pw_gid, temp -> pw_dir);

return 0;

}
