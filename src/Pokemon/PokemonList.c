#include <stdlib.h>

#ifndef PokemonList_C
#define PokemonList_C

#include "PokemonList.h"
#include "Pokemon.c"

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

void PokemonList_remove(PokemonList* self, int index, int clear_pokemon_memory) 
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
void PokemonList_clear(PokemonList *self, int clear_pokemon_memory)
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
    FILE* fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("Error: could not open file %s\n", filename);
        return;
    }

    if (self->count > 0) {
        PokemonList_clear(self, 1); //clear before starting to store new records
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

#endif