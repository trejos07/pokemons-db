#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/***************************************************************************
* Class Pokemon
****************************************************************************/
#define POKEMON_MAX_NAME_LEN 100

typedef struct Pokemon Pokemon;

struct Pokemon
{
    int id;
    char name[POKEMON_MAX_NAME_LEN];
    char form[POKEMON_MAX_NAME_LEN];
    char type1[POKEMON_MAX_NAME_LEN];
    char type2[POKEMON_MAX_NAME_LEN];
    int total;
    int hp;
    int attack;
    int defense;
    int sp_atk;
    int sp_def;
    int speed;
    int generation;
};

// Pokemon *Pokemon_new();
// void Pokemon__destroy(Pokemon *self);
// void Pokemon_init_from_str(Pokemon *self, char *str);
// void Pokemon_print_multi_line(Pokemon *self);
// void Pokemon_print_one_line(Pokemon *self);
// char* Pokemon_to_string_csv(Pokemon *self, char *buffer);


// Allocation + initialization (equivalent to "new Pokemon")
Pokemon *Pokemon_new()
{
    Pokemon *result = (Pokemon *) malloc(sizeof(Pokemon));
    return result;
}

void Pokemon_init(Pokemon *self, int id, const char* name, const char* form, const char* type1, const char* type2, int total, int hp, int attack, int defense, int sp_atk, int sp_def, int speed, int generation)
{
    self->id = id;
    
    strncpy(self->name, name, sizeof(self->name) - 1);
    // the above line copy a string but without overflow the char array size,
    // thats the reason why we have the next line, a string needs to be terminated, 
    // the \0 char represents the end of a string
    self->name[sizeof(self->name) - 1] = '\0';

    strncpy(self->form, form, sizeof(self->form) - 1);
    self->form[sizeof(self->form) - 1] = '\0';

    strncpy(self->type1, type1, sizeof(self->type1) - 1);
    self->type1[sizeof(self->type1) - 1] = '\0';

    strncpy(self->type2, type2, sizeof(self->type2) - 1);
    self->type2[sizeof(self->type2) - 1] = '\0';

    self->total = total;
    self->hp = hp;
    self->attack = attack;
    self->defense = defense;
    self->sp_atk = sp_atk;
    self->sp_def = sp_def;
    self->speed = speed;
    self->generation = generation;
}

void Pokemon_init_from_str(Pokemon *self, char* str)
{
    const char delimiter[2] = ",";
    int id = atoi(strtok(str, delimiter));
    char* name = strtok(NULL, delimiter);
    char* form = strtok(NULL, delimiter);
    char* type1 = strtok(NULL, delimiter);
    char* type2 = strtok(NULL, delimiter);
    int total = atoi(strtok(NULL, delimiter));
    int hp = atoi(strtok(NULL, delimiter));
    int attack = atoi(strtok(NULL, delimiter));
    int defense = atoi(strtok(NULL, delimiter));
    int sp_atk = atoi(strtok(NULL, delimiter));
    int sp_def = atoi(strtok(NULL, delimiter));
    int speed = atoi(strtok(NULL, delimiter));
    int gen = atoi(strtok(NULL, delimiter));

    Pokemon_init(self, id, name, form, type1, type2, total, hp, attack, defense, sp_atk, sp_def, speed, gen);
}

// Destructor (without deallocation)
void Pokemon_reset(Pokemon *self)
{
    // Set all fields to their default value
    self->id = 0;
    
    memset(self->name, 0, sizeof(self->name));
    memset(self->form, 0, sizeof(self->form));
    memset(self->type1, 0, sizeof(self->type1));
    memset(self->type2, 0, sizeof(self->type2));

    self->total = 0;
    self->hp = 0;
    self->attack = 0;
    self->defense = 0;
    self->sp_atk = 0;
    self->sp_def = 0;
    self->speed = 0;
    self->generation = 0;
}

// Destructor + deallocation (equivalent to "delete pokemon")
void Pokemon_destroy(Pokemon *self)
{
    if (self) {
        Pokemon_reset(self);
        free(self);
    }
}

void Pokemon_print_multi_line(Pokemon *self)
{
    printf("-----------------------\n");
    printf("| ID: %16d |\n", self->id);
    printf("| Name: %14s |\n", self->name);
    printf("| Form: %14s |\n", self->form);
    printf("| Type 1: %12s |\n", self->type1);
    printf("| Type 2: %12s |\n", self->type2);
    printf("| Total: %13d |\n", self->total);
    printf("| HP: %16d |\n", self->hp);
    printf("| Attack: %12d |\n", self->attack);
    printf("| Defense: %11d |\n", self->defense);
    printf("| Sp. Atk: %11d |\n", self->sp_atk);
    printf("| Sp. Def: %11d |\n", self->sp_def);
    printf("| Speed: %13d |\n", self->speed);
    printf("| Generation: %8d |\n", self->generation);
    printf("-----------------------\n");
}

void Pokemon_print_one_line(Pokemon *self)
{
    printf("| %-4d | %-20s | %-24s | %-10s | %-10s | %5d | %4d | %6d | %7d | %7d | %7d | %5d | %3d |\n", self->id, self->name, self->form, self->type1, self->type2, self->total, self->hp, self->attack, self->defense, self->sp_atk, self->sp_def, self->speed, self->generation);
}

void Pokemon_to_string_csv(Pokemon *self, FILE *buffer)
{
    fprintf(buffer, "%d,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d\n",self->id, self->name, self->form, self->type1, self->type2, self->total, self->hp, self->attack, self->defense, self->sp_atk, self->sp_def, self->speed, self->generation);
}

int Pokemon_match_stat(Pokemon *self, char *field_name, char *field_value)
{
    if (strcmp(field_name, "ID") == 0 && atoi(field_value) == self->id) {
        return 1;
    } else if (strcmp(field_name, "Name") == 0 && strcmp(field_value, self->name) == 0) {
        return 1;
    } else if (strcmp(field_name, "Form") == 0 && strcmp(field_value, self->form) == 0) {
        return 1;
    } else if (strcmp(field_name, "Type1") == 0 && strcmp(field_value, self->type1) == 0) {
        return 1;
    } else if (strcmp(field_name, "Type2") == 0 && strcmp(field_value, self->type2) == 0) {
        return 1;
    } else if (strcmp(field_name, "Total") == 0 && atoi(field_value) == self->total) {
        return 1;
    } else if (strcmp(field_name, "HP") == 0 && atoi(field_value) == self->hp) {
        return 1;
    } else if (strcmp(field_name, "Attack") == 0 && atoi(field_value) == self->attack) {
        return 1;
    } else if (strcmp(field_name, "Defense") == 0 && atoi(field_value) == self->defense) {
        return 1;
    } else if (strcmp(field_name, "Sp. Atk") == 0 && atoi(field_value) == self->sp_atk) {
        return 1;
    } else if (strcmp(field_name, "Sp. Def") == 0 && atoi(field_value) == self->sp_def) {
        return 1;
    } else if (strcmp(field_name, "Speed") == 0 && atoi(field_value) == self->speed) {
        return 1;
    } else if (strcmp(field_name, "Generation") == 0 && atoi(field_value) == self->generation) {
        return 1;
    }

    return 0;
}

/***************************************************************************
* Class PokemonList
****************************************************************************/
#define POKEMONS_LIST_INIT_CAPACITY 100

typedef struct PokemonList PokemonList;

struct PokemonList {
    Pokemon** pokemons;  // Dynamic array of pointers to Pokemons
    int count;          // Number of Pokemon in the database
    int capacity;       // Current capacity of the dynamic array
};

PokemonList* PokemonList_new() 
{
    PokemonList* list = malloc(sizeof(PokemonList));
    list->count = 0;
    list->capacity = POKEMONS_LIST_INIT_CAPACITY;
    list->pokemons = malloc(sizeof(Pokemon*) * list->capacity);
    return list;
}

void PokemonList_destroy(PokemonList* self) 
{
    for (int i = 0; i < self->count; i++) {
        Pokemon_destroy(self->pokemons[i]);
    }
    free(self->pokemons);
    free(self);
}

void PokemonList_add(PokemonList* self, Pokemon *pokemon)
{
    if (self->count >= self->capacity) {
        // If the list is full, resize the dynamic array
        self->capacity *= 2;
        self->pokemons = realloc(self->pokemons, sizeof(Pokemon*) * self->capacity);
    }
    
    // Add the Pokemon to the list and increment the count
    self->pokemons[self->count] = pokemon;
    self->count++;
}

void PokemonList_remove(PokemonList* self, int index, bool clear_pokemon_memory) 
{
    // Check if the index is out of bounds
    if (index >= self->count || index < 0) {
        return;
    }

    // clear the memory allocated for the Pokemon and the pointer
    if (clear_pokemon_memory) {
        Pokemon_reset(self->pokemons[index]);
    }
    self->pokemons[index] = NULL;

    // Shift the elements to the left to fill the gap
    for (int i = index; i < self->count - 1; i++) {
        self->pokemons[i] = self->pokemons[i+1];
    }

    // Clear the memory of the last element
    // Decrement the count
    if (clear_pokemon_memory) {
        Pokemon_reset(self->pokemons[self->count - 1]);
    }
    self->pokemons[self->count - 1] = NULL;
    self->count--; 
}

// Clears each pointer to each pokemon entry,  we don't want reference those pokemons anymore, also resets the count.
// The clear_pokemon_memory argument sets the memory to the default values for each pokemon.
// The memory for the pointer array and each pokemon data is still allocated.
void PokemonList_clear(PokemonList *self, bool clear_pokemon_memory)
{
    for (int i = 0; i < self->count; i++) {
        if (clear_pokemon_memory) {
            Pokemon_reset(self->pokemons[i]);
        }
        self->pokemons[i] = NULL;
    }

    // Reset the count
    self->count = 0;

    // Resize the dynamic array to the initial capacity
    self->capacity = POKEMONS_LIST_INIT_CAPACITY;
    self->pokemons = realloc(self->pokemons, sizeof(Pokemon) * self->capacity);
}

void PokemonList_print_as_table(PokemonList *self, int range)
{
    printf("| %-4s | %-20s | %-24s | %-10s | %-10s | %-5s | %-4s | %-6s | %-7s | %-7s | %-7s | %-5s | %-3s |\n", "ID","Name","Form","Type 1","Type 2","Total","HP","Attack","Defense","Sp. Atk","Sp. Def","Speed","Gen");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------\n");

    if (range < 0 || range > self->count) {
        range = self->count;
    }

    for (int i = 0; i < range; i++) {
        Pokemon_print_one_line(self->pokemons[i]);
    }
}

void PokemonList_save_as_csv(PokemonList *self, char* filename)
{
    FILE* filePointer = fopen(filename, "w"); // Open file for writing

    if (filePointer == NULL) {
        printf("Error: Failed to open file '%s' for writing.\n", filename);
        return;
    }

    // Write header row
    fprintf(filePointer, "\"ID\",\"Name\",\"Form\",\"Type1\",\"Type2\",\"Total\",\"HP\",\"Attack\",\"Defense\",\"Sp. Atk\",\"Sp. Def\",\"Speed\",\"Generation\"\n");

    // Write each matching Pokemon as a row in the CSV file
    for (int i = 0; i < self->count; i++) {
        Pokemon_to_string_csv(self->pokemons[i], filePointer);
    }

    fclose(filePointer); // Close the file
    printf("Data saved to file '%s'.\n", filename);
}

void PokemonList_load_from_csv_file(PokemonList *self, char* filename)
{
    const char delimiter[2] = ",";
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error: could not open file %s\n", filename);
        return;
    }

    if (self->count > 0) {
        PokemonList_clear(self, true); //clear before starting to store new records
    }

    char* line = malloc(sizeof(char) * 1000);
    fgets(line, 1000, fp); // skip header line

    while (fgets(line, 1000, fp)) {
        Pokemon* p = Pokemon_new();
        Pokemon_init_from_str(p, line);
        PokemonList_add(self, p);
    }    

    free(line);
    fclose(fp);
    printf("Loaded %d pokemons from file %s\n", self->count, filename);
}

/***************************************************************************
* Class PokemonDB
****************************************************************************/

typedef struct PokemonDB PokemonDB;

struct PokemonDB {
    PokemonList* pokemonList;
    PokemonList* query_result;
};

PokemonDB* PokemonDB_new() 
{
    PokemonDB* db = malloc(sizeof(PokemonDB));
    db->pokemonList = PokemonList_new();
    db->query_result = PokemonList_new();
    return db;
}

void PokemonDB_destroy(PokemonDB *self)
{
    PokemonList_destroy(self->pokemonList);
    PokemonList_destroy(self->query_result);
    free(self);
}

Pokemon** PokemonDB_find_pokemon_by_field(PokemonDB *self, char* field_name, char* field_value)
{
    PokemonList_clear(self->query_result, false);

    for (int i = 0; i < self->pokemonList->count; i++) {
        Pokemon* p = self->pokemonList->pokemons[i];

        if (Pokemon_match_stat(p, field_name, field_value)) {
            self->query_result->pokemons[self->query_result->count] = p;
            self->query_result->count++;
        }
    }

    return self->query_result->pokemons;
}

/***************************************************************************
* ICommandOperation
****************************************************************************/

typedef struct ICommandOperation ICommandOperation;

struct ICommandOperation {
    void (*execute)(ICommandOperation *);
};

void Execute(ICommandOperation *self){
    self->execute(self);
}

/***************************************************************************
* PokemonDBOperation
****************************************************************************/

typedef struct PokemonDBOperation PokemonDBOperation;

struct PokemonDBOperation {
    ICommandOperation base;
    PokemonDB *pokemon_db;
    void (*execute_implementation)(PokemonDBOperation *);
};

void PokemonDBOperation_execute(ICommandOperation *operation)
{
    PokemonDBOperation *self = (PokemonDBOperation *) operation;

    if (self->execute_implementation == NULL) {
        printf("missing execute impewmentacion");
        return;
    }

    self->execute_implementation(self);
}

PokemonDBOperation* PokemonDBOperation_new(PokemonDB *pokemon_db, void (*execute_implementation)(PokemonDBOperation *))
{
    PokemonDBOperation* operation = malloc(sizeof(PokemonDBOperation*));
    operation->pokemon_db = pokemon_db;
    operation->base.execute = PokemonDBOperation_execute;
}

/***************************************************************************
* ICommand
****************************************************************************/

typedef struct ICommand ICommand;

struct ICommand {
    void (*execute)(ICommand *);
    void (*un_execute)(ICommand *);
};

void ICommand_execute(ICommand *self)
{
    self->execute(self);
}

void ICommand_un_execute(ICommand *self)
{
    self->un_execute(self);
}

/***************************************************************************
* BaseCommand
****************************************************************************/

typedef struct BaseCommand BaseCommand;

struct BaseCommand {
    ICommand base;
    ICommandOperation* execute_operation;
    ICommandOperation* un_execute_operation;
};

void BaseCommand_execute(ICommand *command)
{
    BaseCommand *self = (BaseCommand *) command;
    self->execute_operation->execute(self->execute_operation);
}

void BaseCommand_un_execute(ICommand *command)
{
    BaseCommand *self = (BaseCommand *) command;
    self->un_execute_operation->execute(self->un_execute_operation);
}

void BaseCommand_destroy(BaseCommand* command)
{
    free(command->execute_operation);
    free(command->un_execute_operation);
    free(command);
}

BaseCommand* BaseCommand_new(ICommandOperation* execute_operation, ICommandOperation* un_execute_operation)
{
    BaseCommand* command = malloc(sizeof(BaseCommand*));
    command->base.execute = BaseCommand_execute;
    command->base.execute = BaseCommand_un_execute;
    command->execute_operation = execute_operation;
    command->un_execute_operation = un_execute_operation;
    return command;
}

/***************************************************************************
* CommandList
****************************************************************************/

typedef struct CommandStack CommandStack;

struct CommandStack {
    ICommand** commands;
    int history_size;
    int count;
};

CommandStack* CommandStack_new(int history_size)
{
    CommandStack* commandList = malloc(sizeof(CommandStack*));
    commandList->count = 0;
    commandList->history_size = history_size;
    commandList->commands = malloc(sizeof(ICommand*)* history_size);
    return commandList;
}

void CommandStack_destroy(CommandStack* self) 
{
    free(self->commands);
    free(self);
}

void CommandStack_push(CommandStack* self, ICommand * command)
{
    char overflow = self->count >= self->history_size;

    if (overflow) {
        // Shift the elements to the left to make a gap at the end the new element
        for (int i = 0; i < self->count - 1; i++) {
            self->commands[i] = self->commands[i+1];
        }
    }

    self->commands[self->count] = command;

    if (!overflow) {
        self->count++;
    }
}

ICommand* CommandStack_peak(CommandStack* self)
{
    return self->commands[self->count - 1];
}

ICommand* CommandStack_pop(CommandStack* self)
{
    if (self->count == 0) {
        return NULL;
    }

    ICommand* last = self->commands[self->count - 1];
    self->commands[self->count - 1] = NULL;
    self->count--;
    return last;
}

void CommandStack_clear(CommandStack* self)
{
    for (int i = 0; i < self->count; i++) {
        self->commands[i] = NULL;
    }

    self->count = 0;
}

/***************************************************************************
* CommandRecorder
****************************************************************************/

typedef struct CommandRecorder CommandRecorder;

struct CommandRecorder {
    int history_size;
    CommandStack* doHistory;
    CommandStack* undoHistory;
};

CommandRecorder* CommandRecorder_new(int history_size)
{
    CommandRecorder* recorder = malloc(sizeof(CommandRecorder));
    recorder->history_size = history_size;
    recorder->doHistory = CommandStack_new(history_size);
    recorder->undoHistory = CommandStack_new(history_size);
}

void CommandRecorder_destroy(CommandRecorder* self)
{
    CommandStack_destroy(self->doHistory);
    CommandStack_destroy(self->undoHistory);
    free(self);
}

void CommandRecorder_record(CommandRecorder* self, ICommand* command)
{
    if (self->undoHistory->count > 0) {
        CommandStack_clear(self->undoHistory);
    }

    CommandStack_push(self->doHistory, command);
}

void CommandRecorder_swap_stacks(CommandStack* from, CommandStack* to, int to_move_count, void (*command_move_callback)(ICommand*))
{
    for (int i = 0; i < to_move_count; i++) {
        if (from->count == 0) {
            break;
        }

        ICommand* command = CommandStack_peak(from);
        command_move_callback(command);
        CommandStack_push(to, command);
        CommandStack_pop(from);
    }
    
}

void CommandRecorder_redo(CommandRecorder* self, int redo_count)
{
    CommandRecorder_swap_stacks(self->undoHistory, self->doHistory, redo_count, ICommand_execute);
}

void CommandRecorder_undo(CommandRecorder* self, int undo_count)
{
    CommandRecorder_swap_stacks(self->doHistory, self->undoHistory, undo_count, ICommand_un_execute);
}

/***************************************************************************
* CLICommand
****************************************************************************/
typedef struct CLICommandData CLICommandData;

struct CLICommandData {
    int record;
    const char* name;
    const char* help_text;

    ICommand* (*get_command)(char** args, int arg_count, void* context);
};

CLICommandData* CLICommandData_new(char* name, char* help_text, int record) 
{
    CLICommandData* command = malloc(sizeof(CLICommandData));
    command->name = name;
    command->help_text = help_text;
    command->record = record;
    return command;
}

/***************************************************************************
* CLICommandDataList
****************************************************************************/

#define COMMAND_LIST_CAPACITY 32

typedef struct CLICommandDataList CLICommandDataList;

struct CLICommandDataList {
    CLICommandData** commands;
    int commandsCount;
};

CLICommandDataList* CLICommandDataList_new() 
{
    CLICommandDataList* list = malloc(sizeof(CLICommandDataList));
    list->commandsCount = 0;
    list->commands = malloc(sizeof(CLICommandData*) * COMMAND_LIST_CAPACITY);
    return list;
}

void CLICommandDataList_destroy(CLICommandDataList* self) 
{
    free(self->commands);
    free(self);
}

void CLICommandDataList_add(CLICommandDataList* self, CLICommandData* command)
{
    if (self->commandsCount >= COMMAND_LIST_CAPACITY) {
        return;
    }
    
    self->commands[self->commandsCount] = command;
    self->commandsCount++;
}

const CLICommandData* CLICommandDataList_find_by_name(CLICommandDataList *self, const char* name) 
{
    for (int i = 0; i < self->commandsCount; i++) {
        if (strcmp(self->commands[i]->name, name) == 0) {
            return self->commands[i];
        }
    }
    return NULL;
}

/***************************************************************************
* CLIRunner
****************************************************************************/
typedef struct CLIRunner CLIRunner;

struct CLIRunner {
    CLICommandDataList* knownCommands;
    CommandRecorder* commandRecorder;
    void* context;
};

CLIRunner* CLIRunner_new(void* context) 
{
    CLIRunner* runner = malloc(sizeof(CLIRunner));
    runner->commandRecorder = CommandRecorder_new(5);
    runner->knownCommands = CLICommandDataList_new();
    runner->context = context;
    return runner;
}

int CLIRunner_execute(CLIRunner *self, char** args, int arg_count)
{
    if (arg_count == 0) {
        return;
    }

    CLICommandData* commandData = CLICommandDataList_find_by_name(self->knownCommands, args[0]);

    if (commandData == NULL) {
        printf("Error: unknown command '%s'\n", args[0]);
        return;
    }

    ICommand* command = commandData->get_command(args, arg_count, self->context);
    command->execute(command);

    if (commandData->record) {
        CommandRecorder_record(self->commandRecorder, &command);
    }
}

/***************************************************************************
* PokemonDBShowCommadData
****************************************************************************/
typedef struct PokemonDBShowCommadData PokemonDBShowCommadData;

struct PokemonDBShowCommadData {
    CLICommandData base;
    PokemonDB* pokemonDB;
};


PokemonDBShowCommadData* PokemonDBShowCommadData_new(PokemonDB* pokemonDB)
{
    PokemonDBShowCommadData* command = malloc(sizeof(PokemonDBShowCommadData));
    command->base.name = "show";
    command->base.help_text = "Show a pokemon with the specified ID";
    command->base.record = 0;
    command->base.get_command = PokemonDBShowCommadData_execute;
    command->pokemonDB = pokemonDB;
    return command;
}

void PokemonDBShowCommadData_execute(char** args, int arg_count, void* contex)
{
    PokemonDB* db = (PokemonDB*) contex;

    BaseCommand_new(PokemonDBOperation_new(execute), PokemonDBOperation_new(un_execute));

}

void Test()
{
    CLIRunner* runner = CLIRunner_new();

    

    // CLICommandList_add(runner->knownCommands, PokemonDBShowCommadData());

}



#define MAX_ARGS 10
#define MAX_ARG_LEN 256

int parse_line(char *line, int max_args, char *argv[]) {
    int argc = 0; //args count
    char arg[MAX_ARG_LEN]; //arg
    char *p = line;
    char *q = arg;
    int in_quote = 0;
    int in_escape = 0;

    // Parse the input string
    while (*p != '\0' && argc < max_args) {
        if (*p == '\\' && !in_escape) {
            // Handle escape sequence
            in_escape = 1;
        } else if (*p == '"' && !in_escape) {
            // Handle quoted string
            in_quote = !in_quote;
        } else if ((*p == ' ' || *p == '\t' || *p == '\n') && !in_quote) {
            // End of argument
            if (q > arg) {
                // Add the argument to argv
                *q = '\0';
                argv[argc] = strdup(arg);
                argc++;
                q = arg;
            }
        } else {
            // Add character to argument
            *q = *p;
            q++;
        }

        // Reset escape sequence flag
        in_escape = 0;

        // Move to the next character
        p++;
    }

    // Add the last argument, if any
    if (q > arg) {
        *q = '\0';
        argv[argc] = strdup(arg);
        argc++;
    }

    // Add a NULL terminator at the end of the argv array
    argv[argc] = NULL;

    return argc;
}



/***************************************************************************
* Main
****************************************************************************/
#define MAX_COMMAND_LENGTH 30
#define MAX_VALUE_LENGTH 30

// int main() {

int main(int argc, char *argv[]) {
    char buffer[100];
    char command[MAX_COMMAND_LENGTH];
    char argument[MAX_COMMAND_LENGTH];
    int value;
    
    // check if interactive mode is enabled
    int interactive_mode = 0;
    if (argc == 2 && strcmp(argv[1], "-i") == 0) {
        interactive_mode = 1;
        printf("Entering interactive mode...\n");
        return 0;
    }

    // char command[MAX_COMMAND_LENGTH]; //create an array of MAX_COMMAND_LENGTH size in memory to store the command string
    // char argument[MAX_COMMAND_LENGTH];// same here to store the arguments as strings
    char arg_value[MAX_VALUE_LENGTH]; 
    int argument_int;// should do the same for int values 

    PokemonDB *pokemon_db = PokemonDB_new();

    while (1) {
        printf("Enter command: "); //print text requesting user input 
        scanf("%s", command);// look for user command as string type

        if (strcmp(command, "exit") == 0) { //check if comand is exit
            printf("Exiting the application...\n");
            break;
        }
        else if (strcmp(command, "load") == 0) {
            scanf("%s", argument); // look for command's argument as string type
            PokemonList_load_from_csv_file(pokemon_db->pokemonList, argument);
        }
        else if (strcmp(command, "save") == 0) {
            scanf("%s", argument);
            PokemonList_save_as_csv(pokemon_db->query_result, argument);
        }
        else if (strcmp(command, "size") == 0) {
            printf("size: %d\n", pokemon_db->pokemonList->count);
        }
        else if (strcmp(command, "mkpok") == 0) {
            printf("size: %d\n", pokemon_db->pokemonList->count);
        }
        else if (strcmp(command, "range") == 0) {
            scanf("%d", &argument_int); // look for command's argument as string type
            PokemonList_print_as_table(pokemon_db->pokemonList, argument_int);
        }
        else if (strcmp(command, "show") == 0) {
            //TODO: add show search
            scanf("%s", argument);

            if (strcmp(argument, "search") == 0) {
                PokemonList_print_as_table(pokemon_db->query_result, -1);
                continue;
            }

            Pokemon** p = PokemonDB_find_pokemon_by_field(pokemon_db, "ID", argument);
            Pokemon_print_multi_line(*p);
        }
        else if (strcmp(command, "search") == 0) {
            scanf("%s", argument);
            scanf("%s", arg_value);
            PokemonDB_find_pokemon_by_field(pokemon_db, argument, arg_value);
            PokemonList_print_as_table(pokemon_db->query_result, -1);
        }
        else {
            printf("Invalid command: %s\n", command);
        }
    }

    PokemonDB_destroy(pokemon_db);
    return 0;
}