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
void generate_mips_body(FILE* mips_file);
void generate_mips_footer(FILE* mips_file);

// Declarations
void translate_declar(FILE* mips_file, char type, char* id, char* sval);