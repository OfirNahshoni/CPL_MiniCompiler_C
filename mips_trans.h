#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

/* Global varibles */
extern int current_reg;

/* Functions declarations */

// Rellocate register index functions
int next_reg();
void reset_reg();
// Generate mips code functions
void generate_mips_header(FILE* mips_file);
void generate_mips_footer(FILE* mips_file);
void generate_mips_assignment(FILE* mips_file, const char* dest, const char* src);
void generate_mips_input(FILE* mips_file, const char* var);
void generate_mips_output(FILE* mips_file, const char* var);
void generate_mips_arithmetic(FILE* mips_file, const char* dest, const char* src1, const char* src2, const char op);
// 
char* concatenate_mips_code(char* code1, char* code2);
int get_register(int* current_reg);
char* create_mips_code(int reg, int val);
