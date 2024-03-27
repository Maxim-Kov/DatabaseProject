#include <stdio.h>

main(){
    FILE *fp;
    char *filename[100];
    char writtenchar;


    printf("type in file name to label or create:\n");
    fgets(filename, sizeof(filename), stdin);
    fp = fopen(filename, "w");
    printf("Enter info:\n");
    while( (writtenchar = getchar()) != EOF) {
        putc(writtenchar,fp);
}

}