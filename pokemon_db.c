#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 20
#define MAX_VALUE_LENGTH 20
#define MAX_POKEMONS 2000
#define MAX_NAME_LEN 200

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
    Pokemon pokemons[MAX_POKEMONS];
    int count;
} PokemonDB;

PokemonDB pokemon_db = {0};

Pokemon** matching_pokemons = NULL;
int matching_pokemon_count = 0;

void clear_db(PokemonDB* db)
{
    memset(db->pokemons, 0, sizeof(db->pokemons)); //clear the memory reserved by the array 
    db->count = 0; //Reset the count
}

void print_pokemon(Pokemon p) {
    //printf("\t| ID: %d | Name: %s | Form: %s |", p.id, p.name, p.form);
    printf("\tID: %d\n", p.id);
    printf("\tName: %s\n", p.name);
    printf("\tForm: %s\n", p.form);
    printf("\tType 1: %s\n", p.type1);
    printf("\tType 2: %s\n", p.type2);
    printf("\tTotal: %d\n", p.total);
    printf("\tHP: %d\n", p.hp);
    printf("\tAttack: %d\n", p.attack);
    printf("\tDefense: %d\n", p.defense);
    printf("\tSp. Atk: %d\n", p.sp_atk);
    printf("\tSp. Def: %d\n", p.sp_def);
    printf("\tSpeed: %d\n", p.speed);
    printf("\tGeneration: %d\n", p.generation);
}

Pokemon* find_pokemon_by_id(int id) {
    for (int i = 0; i < pokemon_db.count; i++) {
        if (pokemon_db.pokemons[i].id == id) {
            return &pokemon_db.pokemons[i];
        }
    }

    return NULL;
}

Pokemon** find_pokemon_by_field(char* field_name, char* field_value, int* count) {
    Pokemon** matching_pokemons = (Pokemon**)malloc(pokemon_db.count * sizeof(Pokemon*));
    *count = 0;
    for (int i = 0; i < pokemon_db.count; i++) {
        Pokemon* p = &pokemon_db.pokemons[i];
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
    char delimiter = ',';
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error: could not open file %s\n", filename);
        return;
    }

    char line[1000];
    fgets(line, 1000, fp); // skip header line

    clear_db(&pokemon_db); //clear db before starting to store new records

    while (fgets(line, 1000, fp)) {

        if (pokemon_db.count >= MAX_POKEMONS) {
            printf("Warning: DB max capacity reached, to load the entire file increas MAX_POKEMONS variable.\n");
            break;
        }

        char* token = strtok(line, &delimiter);
        pokemon_db.pokemons[pokemon_db.count].id = atoi(token); 

        token = strtok(NULL, &delimiter);
        strcpy(pokemon_db.pokemons[pokemon_db.count].name, token); 

        token = strtok(NULL, &delimiter);
        strcpy(pokemon_db.pokemons[pokemon_db.count].form, token); 

        token = strtok(NULL, &delimiter);
        strcpy(pokemon_db.pokemons[pokemon_db.count].type1, token); 

        token = strtok(NULL, &delimiter);
        strcpy(pokemon_db.pokemons[pokemon_db.count].type2, token); 

        token = strtok(NULL, &delimiter);
        pokemon_db.pokemons[pokemon_db.count].total = atoi(token); 

        token = strtok(NULL, &delimiter);
        pokemon_db.pokemons[pokemon_db.count].hp = atoi(token); 

        token = strtok(NULL, &delimiter);
        pokemon_db.pokemons[pokemon_db.count].attack = atoi(token); 

        token = strtok(NULL, &delimiter);
        pokemon_db.pokemons[pokemon_db.count].defense = atoi(token); 

        token = strtok(NULL, &delimiter);
        pokemon_db.pokemons[pokemon_db.count].sp_atk = atoi(token); 

        token = strtok(NULL, &delimiter);
        pokemon_db.pokemons[pokemon_db.count].sp_def = atoi(token); 

        token = strtok(NULL, &delimiter);
        pokemon_db.pokemons[pokemon_db.count].speed = atoi(token); 

        token = strtok(NULL, &delimiter);
        pokemon_db.pokemons[pokemon_db.count].generation = atoi(token); 

        pokemon_db.count++;
    }    

    fclose(fp);
    printf("Loaded %d pokemons from file %s\n", pokemon_db.count, filename);
}

void size_command() {
    printf("size: %d\n", pokemon_db.count);
}

void range_command(int range) {
    printf("Getting range: %d\n\n", range);

    if (range > pokemon_db.count) {
        range = pokemon_db.count;
    }

    for (int i = 0; i < range; i++) {
        printf("Pokemon %d:\n", i+1);
        print_pokemon(pokemon_db.pokemons[i]);
        printf("\n");
    }
}

void show_command(int id) {

    printf("Showing ID: %d\n", id);
    Pokemon* p = find_pokemon_by_id(id); // search for pokemon with ID

    if (p == NULL) {
        printf("pokemon with given ID: %d not found", id);
        return;
    }

    printf("Pokemon found!\n");
    print_pokemon(*p);
}

void print_search_command() {
    printf("Found %d Pokemons:\n", matching_pokemon_count);

    for (int i = 0; i < matching_pokemon_count; i++) {
        printf("Pokemon %d:\n", i+1);
        print_pokemon(*matching_pokemons[i]);
        printf("\n");
    }
}

void search_command(char *stat, char *value) {
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
            load_command(argument);
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
