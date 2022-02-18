#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];

void uniq(int fd, char * name, int cflag, int dFlag, int iFlag) {

    //  Create a 2d array to store the sentences in them
    char arr[20][128];
    int n, x;
    int i = 0, j = 0, check = 0;

    //  Reading the file buffer by buffer till there are some contents in the file
    while ((n = read(fd, buf, sizeof(buf))) > 0) {
        
        // 1026
        // 512 --> 512 -- > 2

        //  Looping through every character in buffer
        for (x = 0; x < n; x++) {
            char ch = buf[x];
            arr[i][j] = ch;
            if ( iFlag == 1 ) {
                if ( check ) {
                    //  Compare previous line
                    if ( (int) (ch) - (int) (arr[i - 1][j]) == 32 || (int) (ch) - (int) (arr[i - 1][j]) == -32 ) {
                        arr[i][j] = arr[i-1][j];
                    }
                }            
            }
            if (ch == '\n') {
                check = 1;
                i++;
                j = 0;
                continue;
            }
            j++;
            if (j == 129) j = 0;
        }
    }

    // Now we have the lines in 2D array in the format below
    /*
        a b D d e f \n \0 \0 \0
        m n D p e f \n \0 \0 \0
        a b c d e f \n \0 \0 \0
        d e f \n \0 \0 \0
    */

    // 65 -- 90     A -- Z
    // 97 -- 122    a -- z
    // if ( iFlag == 1 ) {
    //     if ( n1 - n2 != 0) {
    //         chToCompare = (char) (  ) 
    //     }
    // }

    int flag = 0, cnt = 1;
    int k;

    for (i = 0; i < 20; i++) {
        if (arr[i][0] == '\0') break;
        for (j = 0; j < 128; j++) {
            if(arr[i][j] == '\0') break;
            
            char chToCompare = arr[i][j], nextChToCompare = arr[i + 1][j];
            
            if(chToCompare == nextChToCompare) continue;
            else {
                flag = 1;
                break;
            }
        }
        if (flag == 0) cnt++;
        else {
            flag = 0;
            if (cflag == 1) { 
                printf(1, "%d ", cnt);
            }
            if ( dFlag == 1 && cnt > 1 ) {
                for (k = 0; k < 128; k++)
                    if (arr[i][k] != '\0')
                        printf(1, "%c", arr[i][k]);
            }
            if ( dFlag == 0 ) {
                for (k = 0; k < 128; k++)
                    if (arr[i][k] != '\0')
                            printf(1, "%c", arr[i][k]);
            }
            cnt = 1;
        }
    }
    
    int p;
    for (p = 0; p <= 20; p++) {
        if (arr[p][0] == '\0') {
            break;
        }
    }

    int y;
    if ( p != i ) {
        if (flag == 0) {
            if (cflag == 1) printf(1, "%d ", cnt);
        } else {
            if (cflag == 1) printf(1, "1 ");
        }
        for (y = 0; y < 128; y++) {
            printf(1, "%c", arr[p - 1][y]);
        }
    }

    exit();
}

int main(int argc, char *argv[]) {

    int i, fd;

    int cFlag = 0, dFlag = 0, iFlag = 0;

    // -c , -i, - d

    // [0]uniq -c -d -i README.md

    // Checking if -c flag is given in the CLI
    for ( i = 0; i < argc; i++ ) {
        if (strcmp("-c", argv[i]) == 0)
            cFlag = 1;
    }

    // Checking if -d flag is given in the CLI
    for ( i = 0; i < argc; i++ ) {
        if (strcmp("-d", argv[i]) == 0)
            dFlag = 1;
    }

    // Checking if -i flag is given in the CLI
    for ( i = 0; i < argc; i++ ) {
        if (strcmp("-i", argv[i]) == 0)
            iFlag = 1;
    }


    if ((fd = open(argv[argc - 1], 0)) < 0) {
        uniq (0, "", cFlag, dFlag, iFlag);
        exit();
    }

    else {
        uniq(fd, argv[argc - 1], cFlag, dFlag, iFlag);
    }
    exit();
}
