#include <stdlib.h>
#include <string.h>

#ifndef Pokemon_C
#define Pokemon_C

#include "Pokemon.h"

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

#endif