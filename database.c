#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "data.db"

typedef struct {
    char name[50];
    int age;
} Person;

int main() {
    Person *persons = NULL;
    int count = 0;

    count = loadFromFile(&persons);

    char command[100];
    char name[50];
    int age, index;

    while (1) {
        printf("\nEnter command or enter .help for help:\n");
        fgets(command, sizeof(command), stdin);

        if (strcmp(command, "read\n") == 0) {
            read(persons, count);
        } else if (sscanf(command, "create %s %d", name, &age) == 2) {
            create(&persons, &count, name, age);
            saveToFile(persons, count);
        } else if (sscanf(command, "edit %d %s %d", &index, name, &age) == 3) {
            edit(persons, count, index, name, age);
            saveToFile(persons, count);
        } else if (sscanf(command, "delete %d", &index) == 1) {
            delete(&persons, &count, index);
            saveToFile(persons, count);
        } else if (strcmp(command, ".exit\n") == 0) {
            free(persons);
        } else if (strcmp(command, ".help\n") == 0) {
            Help();
        } else {
            printf("Invalid command.\n");
        }
    }
}

void Help() {
    printf("\nAvailable commands:\n");
    printf("create <name> <age>: Create a new person\n");
    printf("read: Read all persons\n");
    printf("update <index> <name> <age>: Update a person\n");
    printf("delete <index>: Delete a person\n");
    printf(".exit: Exit the program\n");
    printf(".help: Display this help message\n");
}

void create(Person **persons, int *count, char *name, int age) {
    *persons = realloc(*persons, (*count + 1) * sizeof (Person));
    if (*persons != NULL) {
        strcpy((*persons)[*count].name, name);
        (*persons)[*count].age = age;
        (*count)++;
    }
}

int loadFromFile(Person **persons) {
    FILE *file = fopen(FILENAME, "rb");
    int count = 0;
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        count = fileSize / sizeof(Person);
        rewind(file);
        *persons = malloc(count * sizeof(Person));
        if (*persons != NULL) {
            fread(*persons, sizeof(Person), count, file);
        } else {
            printf("Memory allocation failed.\n");
            count = 0;
        }
        fclose(file);
    }
    return count;
}

void deletePerson(Person **persons, int *count, int index) {
    if (index >= 0 && index < *count) {
        for (int i = index; i < *count - 1; i++) {
            (*persons)[i] = (*persons)[i + 1];
        }
        *persons = realloc(*persons, (*count - 1) * sizeof(Person));
        (*count)--;
        printf("Person deleted.\n");
    } else {
        printf("Invalid Person.\n");
    }
}

void read(Person **persons, int *count) {
}

void edit(Person **persons, int *count, char * name, int age) {

}