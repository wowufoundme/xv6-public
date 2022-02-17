#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void uniq (int fd, char *name, int cflag) {
    
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
    
    // Now we have the lines in 2D array in the format below
    /*
        a b c d e f \n \0 \0 \0
        a b c d e f \n \0 \0 \0
        a b c d e f \n \0 \0 \0
        d e f \n \0 \0 \0
    */

    int flag = 0, cnt = 1;
    int k, y;

    for (i = 0; i < 19; i++) {
    	for (j = 0; j < 128; j++) {
		if (arr[i][j] == arr[i+1][j]) continue;
		else {
			flag = 1;
			break;
		}
	}
	if (flag == 0) cnt++;
	else {
		flag = 0;
		if (cflag == 1) 
			printf(1, "%d", cnt);
		cnt = 1;
		for (k = 0; k < 128; k++) 
			printf(1, "%c", arr[i][k]);
	}
    }

    if (flag == 0) {
    	if (cflag == 1) printf(1, "%d", cnt);
    }
    else {
    	if (cflag == 1) printf(1, "1");
	for (y = 0; y < 128; y++) {
		printf(1, "%c", arr[19][y]);
	}
    }
    exit();
}

int main (int argc, char *argv[]) {

    int i, fd;

    for ( i = 1; i < argc; ++i ) {
        if ( (fd = open(argv[i], 0)) < 0 ) {
	    printf(1, "marker\n");
            printf(1, "uniq: cannot open the file %s\n", argv[i]);
            exit();
        }
	
	uniq(fd, argv[i], 0);
	exit();
    
    }
    exit();
}
