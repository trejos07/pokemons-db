#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 30
#define MAX_VALUE_LENGTH 30
#define POKEMONS_INIT_CAPACITY 2000
#define MAX_NAME_LEN 1000

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    char form[MAX_NAME_LEN];
    char type1[MAX_NAME_LEN];
    char type2[MAX_NAME_LEN];
    int total;
    int hp;
    int attack;
    int defense;
    int sp_atk;
    int sp_def;
    int speed;
    int generation;
} Pokemon;

typedef struct {
    Pokemon* pokemons;  // Dynamic array of Pokemon
    int count;          // Number of Pokemon in the database
    int capacity;       // Current capacity of the dynamic array
} PokemonDB;

PokemonDB* pokemon_db = NULL;

Pokemon** matching_pokemons = NULL;
int matching_pokemon_count = 0;

void clear_pokemon_db(PokemonDB* db)
{
    memset(db->pokemons, 0, sizeof(db->pokemons)); //clear the memory reserved by the array 
    db->count = 0; //Reset the count
}

PokemonDB* create_pokemon_db(int capacity)
{
    PokemonDB* db = malloc(sizeof(PokemonDB));
    if (db == NULL) {
        printf("Error: could not allocate memory for Pokemon DB\n");
        return NULL;
    }

    db->pokemons = malloc(capacity * sizeof(Pokemon));
    if (db->pokemons == NULL) {
        printf("Error: could not allocate memory for Pokemon DB\n");
        free(db);
        return NULL;
    }

    db->count = 0;
    db->capacity = capacity;

    return db;
}

void destroy_pokemon_db(PokemonDB* pokemon_db)
{
    if (pokemon_db == NULL) {
        return;
    }

    // Free each dynamically allocated Pokemon struct
    for (int i = 0; i < pokemon_db->count; i++) {
        free(pokemon_db->pokemons[i].name);
        free(pokemon_db->pokemons[i].form);
        free(pokemon_db->pokemons[i].type1);
        free(pokemon_db->pokemons[i].type2);
    }

    // Free the dynamically allocated array of Pokemon structs
    free(pokemon_db->pokemons);

    // Free the PokemonDB struct itself
    free(pokemon_db);
}

void print_pokemon_table_header()
{
    printf("| %-4s | %-20s | %-24s | %-10s | %-10s | %-5s | %-4s | %-6s | %-7s | %-7s | %-7s | %-5s | %-3s |\n", "ID","Name","Form","Type 1","Type 2","Total","HP","Attack","Defense","Sp. Atk","Sp. Def","Speed","Gen");
    printf("--------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

void print_pokemon_as_table_entry(Pokemon p)
{
    printf("| %-4d | %-20s | %-24s | %-10s | %-10s | %5d | %4d | %6d | %7d | %7d | %7d | %5d | %3d |\n",
             p.id, p.name, p.form, p.type1, p.type2, p.total, p.hp, p.attack, p.defense, p.sp_atk, p.sp_def, p.speed, p.generation);
}

void print_pokemon_as_object(Pokemon p)
{
    printf("-----------------------\n");
    printf("| ID: %16d|\n", p.id);
    printf("| Name: %14s|\n", p.name);
    printf("| Form: %14s|\n", p.form);
    printf("| Type 1: %12s|\n", p.type1);
    printf("| Type 2: %12s|\n", p.type2);
    printf("| Total: %13d|\n", p.total);
    printf("| HP: %16d|\n", p.hp);
    printf("| Attack: %12d|\n", p.attack);
    printf("| Defense: %11d|\n", p.defense);
    printf("| Sp. Atk: %11d|\n", p.sp_atk);
    printf("| Sp. Def: %11d|\n", p.sp_def);
    printf("| Speed: %13d|\n", p.speed);
    printf("| Generation: %8d|\n", p.generation);
    printf("-----------------------\n");
}

Pokemon* find_pokemon_by_id(int id)
{
    for (int i = 0; i < pokemon_db->count; i++) {
        if (pokemon_db->pokemons[i].id == id) {
            return &pokemon_db->pokemons[i];
        }
    }

    return NULL;
}

Pokemon** find_pokemon_by_field(char* field_name, char* field_value, int* count)
{
    Pokemon** matching_pokemons = (Pokemon**)malloc(pokemon_db->count * sizeof(Pokemon*));
    *count = 0;
    for (int i = 0; i < pokemon_db->count; i++) {
        Pokemon* p = &pokemon_db->pokemons[i];
        if (strcmp(field_name, "ID") == 0 && atoi(field_value) == p->id) {
            matching_pokemons[*count] = p;
            (*count)++;
        } else if (strcmp(field_name, "Name") == 0 && strcmp(field_value, p->name) == 0) {
            matching_pokemons[*count] = p;
            (*count)++;
        } else if (strcmp(field_name, "Form") == 0 && strcmp(field_value, p->form) == 0) {
            matching_pokemons[*count] = p;
            (*count)++;
        } else if (strcmp(field_name, "Type1") == 0 && strcmp(field_value, p->type1) == 0) {
            matching_pokemons[*count] = p;
            (*count)++;
        } else if (strcmp(field_name, "Type2") == 0 && strcmp(field_value, p->type2) == 0) {
            matching_pokemons[*count] = p;
            (*count)++;
        } else if (strcmp(field_name, "Total") == 0 && atoi(field_value) == p->total) {
            matching_pokemons[*count] = p;
            (*count)++;
        } else if (strcmp(field_name, "HP") == 0 && atoi(field_value) == p->hp) {
            matching_pokemons[*count] = p;
            (*count)++;
        } else if (strcmp(field_name, "Attack") == 0 && atoi(field_value) == p->attack) {
            matching_pokemons[*count] = p;
            (*count)++;
        } else if (strcmp(field_name, "Defense") == 0 && atoi(field_value) == p->defense) {
            matching_pokemons[*count] = p;
            (*count)++;
        } else if (strcmp(field_name, "Sp. Atk") == 0 && atoi(field_value) == p->sp_atk) {
            matching_pokemons[*count] = p;
            (*count)++;
        } else if (strcmp(field_name, "Sp. Def") == 0 && atoi(field_value) == p->sp_def) {
            matching_pokemons[*count] = p;
            (*count)++;
        } else if (strcmp(field_name, "Speed") == 0 && atoi(field_value) == p->speed) {
            matching_pokemons[*count] = p;
            (*count)++;
        } else if (strcmp(field_name, "Generation") == 0 && atoi(field_value) == p->generation) {
            matching_pokemons[*count] = p;
            (*count)++;
        }
    }
    return matching_pokemons;
}

void load_command(char* filename)
{
    const char delimiter[2] = ",";
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error: could not open file %s\n", filename);
        return;
    }

    if (pokemon_db == NULL) {
        pokemon_db = create_pokemon_db(POKEMONS_INIT_CAPACITY); // create  a new db because is Null
    } else {
        clear_pokemon_db(pokemon_db); //clear db before starting to store new records
    }

    char line[1000];
    fgets(line, 1000, fp); // skip header line

    while (fgets(line, 1000, fp)) {

        if (pokemon_db->count >= pokemon_db->capacity) {// Need to resize the dynamic list

            printf("DB capacity reached, DB memory will be reallocated, New capacity: %d\n", pokemon_db->capacity * 2);
            void* temp_ptr = realloc(pokemon_db->pokemons, pokemon_db->capacity * sizeof(Pokemon) * 2);

            if (temp_ptr == NULL) {
                printf("Error: could not allocate memory for Pokemon DB\n");
                fclose(fp);
                return;
            }

            pokemon_db->capacity *= 2;
            pokemon_db->pokemons = temp_ptr;
        }

        char* token = strtok(line, delimiter);
        pokemon_db->pokemons[pokemon_db->count].id = atoi(token); 

        token = strtok(NULL, delimiter);
        strcpy(pokemon_db->pokemons[pokemon_db->count].name, token); 

        token = strtok(NULL, delimiter);
        strcpy(pokemon_db->pokemons[pokemon_db->count].form, token); 

        token = strtok(NULL, delimiter);
        strcpy(pokemon_db->pokemons[pokemon_db->count].type1, token); 

        token = strtok(NULL, delimiter);
        strcpy(pokemon_db->pokemons[pokemon_db->count].type2, token); 

        token = strtok(NULL, delimiter);
        pokemon_db->pokemons[pokemon_db->count].total = atoi(token); 

        token = strtok(NULL, delimiter);
        pokemon_db->pokemons[pokemon_db->count].hp = atoi(token); 

        token = strtok(NULL, delimiter);
        pokemon_db->pokemons[pokemon_db->count].attack = atoi(token); 

        token = strtok(NULL, delimiter);
        pokemon_db->pokemons[pokemon_db->count].defense = atoi(token); 

        token = strtok(NULL, delimiter);
        pokemon_db->pokemons[pokemon_db->count].sp_atk = atoi(token); 

        token = strtok(NULL, delimiter);
        pokemon_db->pokemons[pokemon_db->count].sp_def = atoi(token); 

        token = strtok(NULL, delimiter);
        pokemon_db->pokemons[pokemon_db->count].speed = atoi(token); 

        token = strtok(NULL, delimiter);
        pokemon_db->pokemons[pokemon_db->count].generation = atoi(token); 

        pokemon_db->count++;
    }    

    fclose(fp);
    printf("Loaded %d pokemons from file %s\n", pokemon_db->count, filename);
}

void save_command(char* filename)
{
    FILE* fp = fopen(filename, "w"); // Open file for writing

    if (fp == NULL) {
        printf("Error: Failed to open file '%s' for writing.\n", filename);
        return;
    }

    // Write header row
    fprintf(fp, "\"ID\",\"Name\",\"Form\",\"Type1\",\"Type2\",\"Total\",\"HP\",\"Attack\",\"Defense\",\"Sp. Atk\",\"Sp. Def\",\"Speed\",\"Generation\"\n");

    // Write each matching Pokemon as a row in the CSV file
    for (int i = 0; i < matching_pokemon_count; i++) {
        Pokemon* p = matching_pokemons[i];
        fprintf(fp, "%d,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d\n",
            p->id, p->name, p->form, p->type1, p->type2, p->total, p->hp, p->attack,
            p->defense, p->sp_atk, p->sp_def, p->speed, p->generation);
    }

    fclose(fp); // Close the file
    printf("Data saved to file '%s'.\n", filename);
}

void size_command()
{
    printf("size: %d\n", pokemon_db->count);
}

void range_command(int range)
{
    printf("Getting range: %d\n\n", range);

    if (range > pokemon_db->count) {
        range = pokemon_db->count;
    }

    print_pokemon_table_header();
    for (int i = 0; i < range; i++) {
        print_pokemon_as_table_entry(pokemon_db->pokemons[i]);
    }
}

void show_command(int id)
{

    printf("Showing ID: %d\n", id);
    Pokemon* p = find_pokemon_by_id(id); // search for pokemon with ID

    if (p == NULL) {
        printf("pokemon with given ID: %d not found", id);
        return;
    }

    print_pokemon_as_object(*p);
}

void print_search_command()
{
    printf("Found %d Pokemons:\n", matching_pokemon_count);

    print_pokemon_table_header();
    for (int i = 0; i < matching_pokemon_count; i++) {
        print_pokemon_as_table_entry(*matching_pokemons[i]);
    }
}

void search_command(char *stat, char *value)
{
    printf("Searching for %s with value %s\n", stat, value);

    // call find_pokemon_by_field to search for the matching Pokemon
    matching_pokemons = find_pokemon_by_field(stat, value, &matching_pokemon_count);

    print_search_command();
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
            scanf("%s", argument);

            if (strcmp(argument, "search") == 0) {
                print_search_command();
                continue;
            }

            show_command(atoi(argument));
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

    destroy_pokemon_db(pokemon_db);
    free(matching_pokemons);
    return 0;
}

