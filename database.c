#include <stdio.h>
#include <stdlib.h>
//#include "database.h"
#include <string.h>

void commandselection();
void commands(char command);
void createfile();
void deletefile();
void editfile();
void readfile();
void metacommand();
char command[100];
char input[100];

int main() {

    while (1) {
        printf("type a command associated by number in or .help for help or .exit to exit\n");
        metacommand();
        commands(*command); 
    }
    return 0;
}
void metacommand() {
    scanf("%s", input);
    if (strcmp(input, ".help") == 0) {
        commandselection();
    } else if (strcmp(input, ".exit") == 0) {
        exit(0);
    }
    strcpy(command, input);
}
void commandselection() {
    printf("\nCommands:\n");
    printf("1. Read File\n");
    printf("2. Create file\n");
    printf("3. Edit file\n");
    printf("4. Delete file\n");
    printf("Enter command as a corresponding number:\n");
}

void commands(char command) {
    switch (command) {
    case '1':
        readfile();
        break;
    case '2':
        createfile();
        break;
    case '3':
        editfile();
        break;
    case '4':
        deletefile();
        break;
    default:
        printf("Invalid command\n");
        break;
    }
}

void createfile() {
    FILE *file;
    char filename[100];
    printf("Give the file a name:");
    scanf("%s", filename);
    file = fopen(filename, "w");
    fclose(file);
    printf("File created\n");
}

void readfile() {
    FILE *file;
    char filename[100];
    char letters;
    printf("Give name of file you want to read: ");
    scanf("%s", filename);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }
    while ((letters = getc(file)) != EOF) {
        printf("%c", letters);
    }
    fclose(file);
}

void editfile() {
    FILE *file;
    char filename[100];
    char *text = NULL;
    size_t length = 0;

    printf("Give filename you want to edit: ");
    scanf("%s", filename);
    file = fopen(filename, "a+"); 
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    printf("Type in input for data and then type 'exit' to exit:\n");
    while (1) {
        char input[100];
        fgets(input, sizeof(input), stdin);
        if (strcmp(input, "exit\n") == 0) {
            break;
        }
        size_t input_length = strlen(input);
        text = realloc(text, (length) * sizeof(char));
        if (text == NULL) {
            printf("Memory allocation failed\n");
            return;
        }
        strcpy(text + length, input);
        length += input_length;
    }
    fputs(text, file);
    fclose(file);
    free(text);
    printf("File '%s' edited successfully.\n", filename);
}

void deletefile() {
    char filename[100];
    printf("Give filename you want to delete: ");
    scanf("%s", filename);
    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully\n", filename);
    } else {
        printf("Error deleting file\n");
    }
}