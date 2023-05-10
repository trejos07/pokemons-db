#ifndef PokemonList_H
#define PokemonList_H

#include "Pokemon.h"

#define POKEMONS_LIST_INIT_CAPACITY 100

typedef struct PokemonList PokemonList;

PokemonList* PokemonList_new();
void PokemonList_destroy(PokemonList* self);

void PokemonList_add(PokemonList* self, Pokemon *pokemon);
void PokemonList_remove(PokemonList* self, int index, int clear_pokemon_memory);
void PokemonList_clear(PokemonList *self, int clear_pokemon_memory);

void PokemonList_load_from_csv_file(PokemonList *self, char* filename);
void PokemonList_save_as_csv(PokemonList *self, char* filename);

void PokemonList_print_as_table(PokemonList *self, int range);

#endif