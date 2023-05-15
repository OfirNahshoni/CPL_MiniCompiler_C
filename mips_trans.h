#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>

#include "my_structs.h"

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
char* generate_reg_name(char type);
char* generate_label(); //

// Cast int to float
void cast_int2float(FILE* mips_file, char* int_reg_name, char** float_reg_name, bool is_dest_reg_float);

// Declarations
void translate_declar(FILE* mips_file, char type, char* id, char* sval);

// Assignments
void translate_assignment(FILE *mips_file, char* id, char* exp_val, bool is_exp_num, char id_type, char* id_reg_name, bool need2cast, bool is_exp);

// Input & Output
void translate_input(FILE* mips_file, char* id, char type);
void translate_output(FILE* mips_file, char* value, char type);

// Arithmetic operations
void perform_arithmetic_op(FILE* mips_file, Op op, char* reg1_name, char* reg2_name, char type);
void translate_arithmetic_op(FILE* mips_file, Op op, char* sval1, char* reg1_name, char reg1_type, bool reg1_is_num, bool reg1_is_paran, char* sval2, char* reg2_name, char reg2_type, bool reg2_is_num, bool reg2_is_paran, char result_type);

// If
void translate_if_else(FILE* mips_file, char* condition, char* then_stmt, char* else_stmt); //

// Loops
void translate_while(FILE* mips_file, char* condition, char* stmt); //
void translate_foreach(FILE* mips_file, char* arr_base, int arr_len, char* stmt); //
