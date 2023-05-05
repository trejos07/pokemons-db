#include <stdio.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 20
#define MAX_VALUE_LENGTH 20

void load_command(char *file_name) {
    // Implement the logic for the "load" command here
    printf("Loading file: %s\n", file_name);
}

void save_command(char* filename) {
    // Implement the logic for the "save" command here
    printf("Data saved to file '%s'.\n", filename);
}

void size_command() {
    // Implement the logic for the "size" command here
    printf("Getting size...\n");
}

void range_command(int range) {
    // Implement the logic for the "range" command here
    printf("Getting range: %d\n", range);
}

void show_command(int id) {
    // Implement the logic for the "show" command here
    printf("Showing ID: %d\n", id);
}


void search_command(char *stat, char *value) {
    printf("Searching for %s with value %s\n", stat, value);
}

int main() {
    char command[MAX_COMMAND_LENGTH]; //create an array of MAX_COMMAND_LENGTH size in memory to store the command string
    char argument[MAX_COMMAND_LENGTH];// same here to store the arguments as strings
    char arg_value[MAX_VALUE_LENGTH]; 
    int argument_int;// should do the same for int values 

    while (1) {
        printf("Enter command: "); //print text requesting user input 
        scanf("%s", command);// look for user command as string type

        if (strcmp(command, "exit") == 0) { //check if comand is exit
            printf("Exiting the application...\n");
            break;
        }
        else if (strcmp(command, "load") == 0) {
            scanf("%s", argument); // look for command's argument as string type
            load_command(argument);//call load function with argument
        }
        else if (strcmp(command, "save") == 0) {
            scanf("%s", argument);
            save_command(argument);
        }
        else if (strcmp(command, "size") == 0) {
            size_command();
        }
        else if (strcmp(command, "range") == 0) {
            scanf("%d", &argument_int); // look for command's argument as string type
            range_command(argument_int); // call range funtion with the int argument
        }
        else if (strcmp(command, "show") == 0) {
            //TODO: add show search
            scanf("%d", &argument_int); 
            show_command(argument_int);
        }
        else if (strcmp(command, "search") == 0) {
            scanf("%s", argument);
            scanf("%s", arg_value);
            search_command(argument, arg_value);
        }
        else {
            printf("Invalid command: %s\n", command);
        }
    }

    return 0;
}
