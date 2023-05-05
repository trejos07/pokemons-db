#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    Pokemon_init(
        self, 
        atoi(strtok(str, delimiter)), //id
        strtok(NULL, delimiter), //name
        strtok(NULL, delimiter), //form
        strtok(NULL, delimiter), //type1
        strtok(NULL, delimiter), //type2
        atoi(strtok(NULL, delimiter)), //total
        atoi(strtok(NULL, delimiter)), //hp
        atoi(strtok(NULL, delimiter)), //attack
        atoi(strtok(NULL, delimiter)), //defense
        atoi(strtok(NULL, delimiter)), //sp_atk
        atoi(strtok(NULL, delimiter)), //sp_def
        atoi(strtok(NULL, delimiter)), //speed
        atoi(strtok(NULL, delimiter)) //gen
    );
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
    snprintf(buffer, sizeof buffer, "%d,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d\n",self->id, self->name, self->form, self->type1, self->type2, self->total, self->hp, self->attack, self->defense, self->sp_atk, self->sp_def, self->speed, self->generation);
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
    Pokemon** pokemons;  // Dynamic array of Pokemon
    int count;          // Number of Pokemon in the database
    int capacity;       // Current capacity of the dynamic array
};

PokemonList* PokemonList_new() 
{
    PokemonList* list = malloc(sizeof(PokemonList));
    list->count = 0;
    list->capacity = POKEMONS_LIST_INIT_CAPACITY;
    list->pokemons = malloc(sizeof(Pokemon) * list->capacity);
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
    if (self->count == self->capacity) {
        // If the list is full, resize the dynamic array
        self->capacity *= 2;
        self->pokemons = realloc(self->pokemons, sizeof(Pokemon) * self->capacity);
    }
    
    // Add the Pokemon to the list and increment the count
    self->pokemons[self->count] = pokemon;
    self->count++;
}

void PokemonList_remove(PokemonList* self, int index) 
{
    // Check if the index is out of bounds
    if (index >= self->count || index < 0) {
        return;
    }

    // Free the memory allocated for the Pokemon
    Pokemon_reset(self->pokemons[index]); 

    // Shift the elements to the left to fill the gap
    for (int i = index; i < self->count - 1; i++) {
        self->pokemons[i] = self->pokemons[i+1];
    }

    // Clear the memory of the last element
    // Decrement the count
    Pokemon_reset(self->pokemons[self->count - 1]); 
    self->count--; 
}

void PokemonList_clear(PokemonList *self)
{
    // Clear the memory of each pokemon entry, memory is still reserved 
    for (int i = 0; i < self->count; i++) {
        Pokemon_reset(self->pokemons[i]);
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
    printf("Loading from %s\n", filename);

    const char delimiter[2] = ",";
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error: could not open file %s\n", filename);
        return;
    }

    printf("0\n");
    if (self->count > 0) {
        printf("Clear %d entries\n", self->count);
        PokemonList_clear(self); //clear before starting to store new records
    }

    printf("1\n");
    char line[1000];
    printf("2\n");
    fgets(line, 1000, fp); // skip header line
    printf("3\n");

    while (fgets(line, 1000, fp)) {
        printf("%s\n", line);
        Pokemon* p = Pokemon_new();
        Pokemon_init_from_str(p, &line);
        PokemonList_add(self, p);
    }    

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
    PokemonList_clear(self->query_result);

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
* Main
****************************************************************************/
#define MAX_COMMAND_LENGTH 30
#define MAX_VALUE_LENGTH 30

int main() {
    char command[MAX_COMMAND_LENGTH]; //create an array of MAX_COMMAND_LENGTH size in memory to store the command string
    char argument[MAX_COMMAND_LENGTH];// same here to store the arguments as strings
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

