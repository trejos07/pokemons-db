cmake_minimum_required(VERSION 3.5)
project(pokemon-db)

# Add executable
file(GLOB_RECURSE SOURCES "src/*.c" "src/*.h")
add_executable(pokemon-db ${SOURCES})

# Set C standard
set_target_properties(pokemon-db PROPERTIES 
    C_STANDARD 11
    C_STANDARD_REQUIRED YES
    C_EXTENSIONS NO
)

# Include directories
target_include_directories(pokemon-db PRIVATE 
    src
)

# Set compiler flags
if(MSVC)
    target_compile_options(pokemon-db PRIVATE /W4 /wd4100 /wd4996)
else()
    target_compile_options(pokemon-db PRIVATE -Wall -Wextra -pedantic -Werror -Wno-unused-parameter)
endif()