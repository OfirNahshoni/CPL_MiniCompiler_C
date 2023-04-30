#ifndef ST_HASH
#define ST_HASH

#include <stdlib.h>

// Define a constant for the maximum length of a name
#define MAX_NAME_LENGTH 9

// Define a struct to represent an entry in the symbol table
typedef struct symbol_table_entry {
    char* name;
    char type; // i, s, r
    // New fields
    bool is_init; // Is initialized
    bool is_const;
    struct symbol_table_entry* next;
} symbol_table_entry;

// Define a struct to represent the entire symbol table
typedef struct symbol_table {
    symbol_table_entry** entries; // array of entries
    int size; // size of the array
    int count; // count of entries currently in the array
} symbol_table;

// Functions Declarations - for the symbol table
symbol_table* create_symbol_table(int size);
void free_symbol_table(symbol_table* table);
unsigned long hash(char* str, int size);
symbol_table_entry* lookup(symbol_table* table, char* name);
void add_attribute(symbol_table* table, char* name, char type, bool is_att_const, bool is_att_init);
void print(symbol_table* table);

#endif /* ST_HASH */