#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void uniq (int fd, char *name) {
    printf(1, "Entered uniq\n");
    //  Create a 2d array to store the sentences in them
    char arr[20][128];
    int n, x;
    int i = 0, j = 0;
    //  Reading the file buffer by buffer till there are some contents in the file
    while ( (n = read(fd, buf, sizeof(buf))) > 0 ) {
        //  Looping through every character in buffer
        for ( x = 0; x < n; x++ ) {
            char ch = buf[x];
            arr[i][j] = ch;
	    if ( ch == '\n') {		
		i++;
		j = 0;
		continue;
	    }
	    j++;
	    if ( j == 1025 ) j = 0;
        }
    }
    printf(1, "%c", arr[0][0]);
    // Now we have the lines in 2D array in the format below
    /*
        a b c d e f \n \0 \0 \0
        a b c d e f \n \0 \0 \0
        a b c d e f \n \0 \0 \0
        d e f \n \0 \0 \0
    */
}

int main (int argc, char *argv[]) {

    int i, fd;

    for ( i = 1; i < argc; ++i ) {
        if ( (fd = open(argv[i], 0)) < 0 ) {
	    printf(1, "marker\n");
            printf(1, "uniq: cannot open the file %s\n", argv[i]);
            exit();
        }
	printf(1, "marker 2\n");
	uniq(fd, argv[i]);
	exit();
    }
    exit();
}
