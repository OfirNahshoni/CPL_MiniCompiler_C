#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "symbol_table.h"


// A function to create a new symbol table with a given size
symbol_table* create_symbol_table(int size) {
    // Allocate memory for the symbol table and set its properties
    symbol_table* table = (symbol_table*)malloc(sizeof(symbol_table));
    table->size = size;
    table->count = 0;
    table->entries = (symbol_table_entry**)calloc(size, sizeof(symbol_table_entry*));
    
    return table;
}

// A function to free the memory used by a symbol table
void free_symbol_table(symbol_table* table) {
    symbol_table_entry* temp_entry;
    for (int i = 0; i < table->size; i++) {
        temp_entry = table->entries[i];
        // Free all the linked lists
        while (temp_entry != NULL)
        {
            symbol_table_entry* to_free = temp_entry;
            temp_entry = temp_entry->next;
            free(to_free);
        }
    }
    free(table->entries); // Free entries
    free(table); // Free whole table
}

// A hash function to generate an index for a given string and table size
unsigned long hash(char* str, int size) {
    // Initialize a hash value
    unsigned long hash = 5381;
    int c;
    // For each character in the string, update the hash value
    while ((c = *str++) != 0) {
        hash = ((hash << 5) + hash) + c;
    }

    // Return the hash value modulo the table size to get an index in the valid range
    return hash % size;
}

// A function to look up an entry in the symbol table by name
symbol_table_entry* lookup(symbol_table* table, char* name) {
    symbol_table_entry* temp_entry;

    // Generate an index for the name using the hash function
    int index = hash(name, table->size);
    temp_entry = table->entries[index];

    // Search for the entry starting at the generated index using linear probing
    while (temp_entry != NULL) {
        // Return the address of a table entry
        if (strcmp(table->entries[index]->name, name) == 0)
            return table->entries[index];

        // else
        temp_entry = temp_entry->next;
    }

    // If we didnt find it
    return NULL;
}


// A function to add symbol to the symbol table
void add_attribute(symbol_table* table, char* name, char type, bool is_att_const, bool is_att_init) {
    // compute hash value for name
    int index = hash(name, table->size);

    symbol_table_entry* temp_entry = lookup(table, name);

    if (temp_entry != NULL) {
        fprintf(stderr, "Redeclaration the ID");
        return;
    }

    // Allocate new entry
    temp_entry = (symbol_table_entry*)malloc(sizeof(symbol_table_entry));

    // init temp_entry
    temp_entry->name = strdup(name);
    temp_entry->type = type;
    temp_entry->is_init = is_att_init;
    temp_entry->is_const = is_att_const;

    // Connect to linked list
    temp_entry->next = table->entries[index];
    table->entries[index] = temp_entry; // This is the head now

    table->count++; // Update count of entries in the table
}

// Print nicely the symbol table
void print(symbol_table* table) {
    symbol_table_entry* temp_entry;
    printf("Symbol Table:\n");
    for (int i = 0; i < table->size; i++) {
        temp_entry = table->entries[i];
        while (temp_entry != NULL) {
            printf("Index: %d, Name: %s, Type: %c, Is init: %d, Is Const: %d\n", i, temp_entry->name, temp_entry->type, temp_entry->is_init, temp_entry->is_const);
            temp_entry = temp_entry->next;
        }
    }
}