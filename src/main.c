#include "./Pokemon/PokemonDB.h"
#include "./CLI/CLIRunner.c"
#include "./Pokemon/Command/PokemonDBShowCommand.h"

int main() {

    PokemonDB* pokemon_db = PokemonDB_new();
    CLIRunner* runner = CLIRunner_new(pokemon_db);

    CLICommandDataCollection_add(runner->knownCommands, CLICommandData_new("exit", "quit the program", 0, CLIRunnerExitCommand_from_args));
    CLICommandDataCollection_add(runner->knownCommands, CLICommandData_new("show", "Show a pokemon with the specified ID", 0, PokemonDBShowCommand_from_args));

    CLIRunner_listen(runner);

    CLIRunner_destroy(runner);
    PokemonDB_destroy(pokemon_db);
    return 0;
}