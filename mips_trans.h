#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

/* Global varibles */
extern int current_reg;

/* Functions declarations */

// Rellocate register index functions
void reset_reg();

// Generate function
void generate_mips_header(FILE* mips_file);
void generate_mips_data_section(FILE* mips_file);
void generate_mips_text_section(FILE* mips_file);
void generate_mips_footer(FILE* mips_file);

// Declarations
void translate_declar(FILE* mips_file, char type, char* id, char* sval);

// Assignments
void translate_assignment(FILE *mips_file, char* id, char* value, char type);

// Input & Output
void translate_input(FILE* mips_file, char* id, char type);
void translate_output(FILE* mips_file, char* value, char type);