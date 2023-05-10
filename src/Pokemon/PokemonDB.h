#ifndef PokemonDB_H
#define PokemonDB_H

#include "Pokemon.h"

typedef struct PokemonDB PokemonDB;

PokemonDB* PokemonDB_new();
void PokemonDB_destroy(PokemonDB *self);

Pokemon** PokemonDB_find_pokemon_by_field(PokemonDB *self, char* field_name, char* field_value);

#endif