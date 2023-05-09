#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

/* Global varibles */
int current_reg = 0;

/* Functions declarations */

// Rellocate register index functions
int next_reg();
void reset_reg();

// Generate mips code functions
void generate_mips_header();
void generate_mips_footer();
void generate_mips_assignment(const char* dest, const char* src);
void generate_mips_input(const char* var);
void generate_mips_output(const char* var);
void generate_mips_arithmetic(const char* dest, const char* src1, const char* src2, const char op);