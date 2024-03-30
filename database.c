#include <stdio.h>
#include <stdlib.h>

void commandselction();
void commands(char command);
void createfile();
void deletefile();
void editfile();
void readfile();

int main(){
    char command;

    while(1) {
    commandselction();
    scanf("%s", &command);
    commands(command);
    }
}

void commandselection(){
    printf("\nCommands:\n");
    printf("1. Read File\n");
    printf("2. Create file\n");
    printf("3. Edit file\n");
    printf("4. Delete file\n");
    printf("5. Exit\n");
    printf("Enter command as a corresponding number: ");
}

void commands(char command){
    switch (command)
    {
    case '1':
        readfile;
        break;
    case '2':
        createfile;
        break;
    case '3':
        editfile;
        break;
    case '4':
        deletefile;
        break;
    case '5':
        printf("exiting file");
        exit(0);
        break;    
    default:
        break;
    }
}
void createfile(){
    FILE *file;
    char filename;
    printf("Give the file a name:");
    scanf("%s", filename);
    file = fopen (filename, "w");
    fclose(filename);
    printf("File made");
    }
void readfile(){
    char filename;
    char letters;
    printf("Give name of file you want to edit (or create if it does not exist)");
    scanf("%s", filename);
    fopen(filename, "r");
    while ((letters = getc(filename) !=EOF)){
        printf(letters);
    }
}



