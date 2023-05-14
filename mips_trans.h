#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

/* Global varibles */
extern int int_counter;
extern int float_counter;
extern int string_counter;
extern int current_label;

/* Functions declarations */

// Generate function
void generate_mips_header(FILE* mips_file);
void generate_mips_data_section(FILE* mips_file);
void generate_mips_text_section(FILE* mips_file);
void generate_mips_footer(FILE* mips_file);
char* generate_reg_name(char type); //
char* generate_label(); //

// Declarations
void translate_declar(FILE* mips_file, char type, char* id, char* sval);

// Assignments
void translate_assignment(FILE *mips_file, char* id, char* value, char type, char* reg_name);

// Input & Output
void translate_input(FILE* mips_file, char* id, char type);
void translate_output(FILE* mips_file, char* value, char type);

// If
void translate_if_else(FILE* mips_file, char* condition, char* then_stmt, char* else_stmt); //

// Loops
void translate_while(FILE* mips_file, char* condition, char* stmt); //
void translate_foreach(FILE* mips_file, char* arr_base, int arr_len, char* stmt); //