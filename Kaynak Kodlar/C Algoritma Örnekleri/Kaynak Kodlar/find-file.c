/*
 * find-file.c - find all files residing in the given sub-directory,
 * whose names contain the given string.
 */

#include <stdio.h>              /* standard input/output routines.    */
#include <dirent.h>             /* readdir(), etc.                    */
#include <sys/stat.h>           /* stat(), etc.                       */
#include <string.h>             /* strstr(), etc.                     */
#include <unistd.h>             /* getcwd(), etc.                     */

#define MAX_DIR_PATH 2048	/* maximal full path we support.      */

/*
 * function: findfile. recusively traverse the current directory, searching
 *                     for files with a given string in their name.
 * input:    string to match.
 * output:   any file found, printed to the screen with a full path.
 */
void
findfile(char* pattern)
{
    DIR* dir;			/* pointer to the scanned directory. */
    struct dirent* entry;	/* pointer to one directory entry.   */
    char cwd[MAX_DIR_PATH+1];	/* current working directory.        */
    struct stat dir_stat;       /* used by stat().                   */

    /* first, save path of current working directory */
    if (!getcwd(cwd, MAX_DIR_PATH+1)) {
	perror("getcwd:");
	return;
    }


    /* open the directory for reading */
    dir = opendir(".");
    if (!dir) {
	fprintf(stderr, "Cannot read directory '%s': ", cwd);
	perror("");
	return;
    }

    /* scan the directory, traversing each sub-directory, and */
    /* matching the pattern for each file name.               */
    while ((entry = readdir(dir))) {
	/* check if the pattern matchs. */
	if (entry->d_name && strstr(entry->d_name, pattern)) {
	    printf("%s/%s\n", cwd, entry->d_name);
	}
        /* check if the given entry is a directory. */
        if (stat(entry->d_name, &dir_stat) == -1) {
	    perror("stat:");
	    continue;
        }
	/* skip the "." and ".." entries, to avoid loops. */
	if (strcmp(entry->d_name, ".") == 0)
	    continue;
	if (strcmp(entry->d_name, "..") == 0)
	    continue;
	/* is this a directory? */
        if (S_ISDIR(dir_stat.st_mode)) {
            /* Change into the new directory */
            if (chdir(entry->d_name) == -1) {
	        fprintf(stderr, "Cannot chdir into '%s': ", entry->d_name);
	        perror("");
	        continue;
            }
	    /* check this directory */
	    findfile(pattern);

            /* finally, restore the original working directory. */
            if (chdir("..") == -1) {
	        fprintf(stderr, "Cannot chdir back to '%s': ", cwd);
	        perror("");
	        exit(1);
            }
        }
    }
}

/*
 * function: main. find files with a given pattern in their names, in
 *                 a given directory tree.
 * input:    path to directory to search, and pattern to match.
 * output:   names of all matching files on the screen.
 */
void
main(int argc, char* argv[])
{
    char* dir_path;		/* path to the directory. */
    char* pattern;		/* pattern to match.      */
    struct stat dir_stat;       /* used by stat().        */

    /* read command line arguments */
    if (argc != 3 || !argv[1] || !argv[2]) {
	fprintf(stderr, "Usage: %s <directory path> <file name pattern>\n",
		argv[0]);
	exit(1);
    }
    dir_path = argv[1];
    pattern = argv[2];

    /* make sure the given path refers to a directory. */
    if (stat(dir_path, &dir_stat) == -1) {
	perror("stat:");
	exit(1);
    }
    if (!S_ISDIR(dir_stat.st_mode)) {
	fprintf(stderr, "'%s' is not a directory\n", dir_path);
	exit(1);
    }
    
    /* change into the given directory. */
    if (chdir(dir_path) == -1) {
	fprintf(stderr, "Cannot change to directory '%s': ", dir_path);
	perror("");
	exit(1);
    }

    /* recursively scan the directory for the given file name pattern. */
    findfile(pattern);
}

