#include <stdlib.h>

#include "PokemonDB.h"
#include "PokemonList.c"

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
    PokemonList_clear(self->query_result, 0);

    for (int i = 0; i < self->pokemonList->count; i++) {
        Pokemon* p = self->pokemonList->pokemons[i];

        if (Pokemon_match_stat(p, field_name, field_value)) {
            self->query_result->pokemons[self->query_result->count] = p;
            self->query_result->count++;
        }
    }

    return self->query_result->pokemons;
}