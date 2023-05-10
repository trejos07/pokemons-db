#include <stdio.h>
#include <stdlib.h>

#ifndef POKEMON_H
#define POKEMON_H

#define POKEMON_MAX_NAME_LEN 100

typedef struct Pokemon Pokemon;

Pokemon *Pokemon_new();
void Pokemon_init(Pokemon *self, int id, const char* name, const char* form, const char* type1, const char* type2, int total, int hp, int attack, int defense, int sp_atk, int sp_def, int speed, int generation);
void Pokemon_init_from_str(Pokemon *self, char* str);
void Pokemon_reset(Pokemon *self);
void Pokemon_destroy(Pokemon *self);
void Pokemon_print_multi_line(Pokemon *self);
void Pokemon_print_one_line(Pokemon *self);
void Pokemon_to_string_csv(Pokemon *self, FILE *buffer);
int Pokemon_match_stat(Pokemon *self, char *field_name, char *field_value);

#endif