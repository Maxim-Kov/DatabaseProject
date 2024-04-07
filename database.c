#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sockutils.h"



#define STRING_TYPE 0
#define INT_TYPE 1

struct Field {
    char name[50];
    int type;
};

struct DataType {
    char name[50];
    int num_fields;
    struct Field *fields;
    void ****data;
    int *num_data;
};

struct Field createField(char name[], int type) {
    struct Field new_field;
    strcpy(new_field.name, name);
    new_field.type = type;
    return new_field;
}

struct DataType createDataType(char name[], int num_fields, struct Field fields[]) {
    struct DataType new_data_type;
    strcpy(new_data_type.name, name);
    new_data_type.num_fields = num_fields;
    new_data_type.fields = malloc(num_fields * sizeof(struct Field));
    if (new_data_type.fields == NULL) {
        printf("Memory allocation failed :(\n");
        exit(1);
    }
    for (int i = 0; i < num_fields; i++) {
        new_data_type.fields[i] = fields[i];
    }
    new_data_type.data = NULL;
    new_data_type.num_data = malloc(sizeof(int));
    if (new_data_type.num_data == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    *new_data_type.num_data = 0;
    return new_data_type;
}

void displayDataTypes(struct DataType data_types[], int num_data_types) {
    printf("Stored Data Types:\n");
    for (int i = 0; i < num_data_types; i++) {
        printf("%d. %s\n", i + 1, data_types[i].name);
    }
}

void addDataToDataType(struct DataType data_types[], int num_data_types) {
    if (num_data_types == 0) {
        printf("No data types available. Create a data type first.\n");
        return;
    }

    printf("Choose the data type to add data to:\n");
    displayDataTypes(data_types, num_data_types);
    int index;
    printf("Enter the index of the data type: ");
    scanf("%d", &index);
    if (index < 1 || index > num_data_types) {
        printf("Invalid index.\n");
        return;
    }

    struct DataType *selected_data_type = &data_types[index - 1];
    printf("Enter data for the %s:\n", selected_data_type->name);
    if (selected_data_type->data == NULL) {
        selected_data_type->data = malloc(sizeof(void *));
        if (selected_data_type->data == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
    } else {
        selected_data_type->data = realloc(selected_data_type->data,
                                           (selected_data_type->num_data[0] + 1) * sizeof(void *));
        if (selected_data_type->data == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }
    }

    selected_data_type->data[selected_data_type->num_data[0]] = malloc(selected_data_type->num_fields * sizeof(void *));
    if (selected_data_type->data[selected_data_type->num_data[0]] == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for (int i = 0; i < selected_data_type->num_fields; i++) {
        printf("Enter data for field '%s': ", selected_data_type->fields[i].name);
        if (selected_data_type->fields[i].type == STRING_TYPE) {
            char *input = malloc(100 * sizeof(char));
            if (input == NULL) {
                printf("Memory allocation failed.\n");
                exit(1);
            }
            scanf("%s", input);
            selected_data_type->data[selected_data_type->num_data[0]][i] = (void *)input;
        } else if (selected_data_type->fields[i].type == INT_TYPE) {
            int *input = malloc(sizeof(int));
            if (input == NULL) {
                printf("Memory allocation failed.\n");
                exit(1);
            }
            scanf("%d", input);
            selected_data_type->data[selected_data_type->num_data[0]][i] = (void *)input;
        } else {
            printf("Invalid field type.\n");
            return;
        }
    }
    (*selected_data_type->num_data)++;
}

void viewDataTypeData(struct DataType data_types[], int num_data_types) {
    if (num_data_types == 0) {
        printf("No data types available. Create a data type first.\n");
        return;
    }

    printf("Choose the data type to view data:\n");
    displayDataTypes(data_types, num_data_types);
    int index;
    printf("Enter the index of the data type: ");
    scanf("%d", &index);
    if (index < 1 || index > num_data_types) {
        printf("Invalid index.\n");
        return;
    }

    struct DataType *selected_data_type = &data_types[index - 1];
    printf("Data for %s:\n", selected_data_type->name);
    for (int i = 0; i < *selected_data_type->num_data; i++) {
        printf("Entry %d:\n", i + 1);
        for (int j = 0; j < selected_data_type->num_fields; j++) {
            printf("Field '%s': ", selected_data_type->fields[j].name);
            if (selected_data_type->fields[j].type == STRING_TYPE) {
                printf("%s\n", (char *)selected_data_type->data[i][j]);
            } else if (selected_data_type->fields[j].type == INT_TYPE) {
                printf("%d\n", *((int *)selected_data_type->data[i][j]));
            }
        }
    }
}

void deleteDataType(struct DataType data_types[], int *num_data_types) {
    if (*num_data_types == 0) {
        printf("No data types available.\n");
        return;
    }

    printf("Choose the data type to delete:\n");
    displayDataTypes(data_types, *num_data_types);
    int index;
    printf("Enter the index of the data type: ");
    scanf("%d", &index);
    if (index < 1 || index > *num_data_types) {
        printf("Invalid index.\n");
        return;
    }

    free(data_types[index - 1].fields);

    for (int i = 0; i < *data_types[index - 1].num_data; i++) {
        for (int j = 0; j < data_types[index - 1].num_fields; j++) {
            free(data_types[index - 1].data[i][j]);
        }
        free(data_types[index - 1].data[i]);
    }

    free(data_types[index - 1].data);
    free(data_types[index - 1].num_data);

    for (int i = index - 1; i < *num_data_types - 1; i++) {
        data_types[i] = data_types[i + 1];
    }

    (*num_data_types)--;
    printf("Data type deleted successfully.\n");
}

void deleteDataEntry(struct DataType data_types[], int num_data_types) {
    if (num_data_types == 0) {
        printf("No data types available. Create a data type first.\n");
        return;
    }

    printf("Choose the data type to delete data from:\n");
    displayDataTypes(data_types, num_data_types);
    int index;
    printf("Enter the index of the data type: ");
    scanf("%d", &index);
    if (index < 1 || index > num_data_types) {
        printf("Invalid index.\n");
        return;
    }

    struct DataType *selected_data_type = &data_types[index - 1];

    if (*selected_data_type->num_data == 0) {
        printf("No data entries available for this data type.\n");
        return;
    }

    printf("Choose the data entry to delete:\n");
    for (int i = 0; i < *selected_data_type->num_data; i++) {
        printf("%d. Entry %d\n", i + 1, i + 1);
    }
    int entry_index;
    printf("Enter the index of the data entry: ");
    scanf("%d", &entry_index);
    if (entry_index < 1 || entry_index > *selected_data_type->num_data) {
        printf("Invalid entry index.\n");
        return;
    }

    for (int i = 0; i < selected_data_type->num_fields; i++) {
        free(selected_data_type->data[entry_index - 1][i]);
    }
    free(selected_data_type->data[entry_index - 1]);

    for (int i = entry_index - 1; i < *selected_data_type->num_data - 1; i++) {
        selected_data_type->data[i] = selected_data_type->data[i + 1];
    }

    (*selected_data_type->num_data)--;
    printf("Data entry deleted successfully.\n");
}

int main() {
    struct DataType data_types[10];
    int num_data_types = 0;

    char input[50];

    //SERVER INFO, allows port 8080, up to 5 people users waiting, but services one user
    int server = make_server("8080", 5);
    while(1){
        int client = server_accept(server);
        dup2(client, 0);
        dup2(client, 1);
        dup2(client, 2);

    while (1) {
        printf("Type a command or type '.help' to see possible commands: ");
        scanf("%s", input);
        
        if (strcmp(input, ".exit") == 0) {
            printf("Exiting program.\n");
            break;
        } else if (strcmp(input, ".help") == 0) {
            printf("\nPossible Commands:\n");
            printf(".exit : Exit the program\n");
            printf(".help : Show possible commands\n");
            printf("create : Create a new data type\n");
            printf("add : Add data to a data type\n");
            printf("view : View data of a specific data type\n");
            printf("del_datatype : Delete an entire data type\n");
            printf("del_dataentry : Delete a single data entry within a data type\n");
        } else if (strcmp(input, "create") == 0) {
            printf("Enter the name of the new data type: ");
            char name[50];
            scanf("%s", name);
            int num_fields;
            printf("Enter the number of fields for the new data type: ");
            scanf("%d", &num_fields);
            struct Field *fields = malloc(num_fields * sizeof(struct Field));
            if (fields == NULL) {
                printf("Memory allocation failed.\n");
                exit(1);
            }
            printf("Enter field details:\n");
            for (int i = 0; i < num_fields; i++) {
                printf("Field %d:\n", i + 1);
                printf("\tName: ");
                scanf("%s", fields[i].name);
                printf("\tType (0 for string, 1 for integer): ");
                scanf("%d", &fields[i].type);
            }
            data_types[num_data_types++] = createDataType(name, num_fields, fields);
            printf("Data type created successfully.\n");
        } else if (strcmp(input, "add") == 0) {
            addDataToDataType(data_types, num_data_types);
        } else if (strcmp(input, "view") == 0) {
            viewDataTypeData(data_types, num_data_types);
        } else if (strcmp(input, "del_datatype") == 0) {
            deleteDataType(data_types, &num_data_types);
        } else if (strcmp(input, "del_dataentry") == 0) {
            deleteDataEntry(data_types, num_data_types);
        } else {
            printf("Unknown command. Type '.help' to see possible commands.\n");
        }
    }

    for (int i = 0; i < num_data_types; i++) {
        for (int j = 0; j < *data_types[i].num_data; j++) {
            for (int k = 0; k < data_types[i].num_fields; k++) {
                free(data_types[i].data[j][k]);
            }
            free(data_types[i].data[j]);
        }
        free(data_types[i].fields);
        free(data_types[i].data);
        free(data_types[i].num_data);
        }
    }
    return 0;
}
