#include "mips_trans.h"

int current_reg = 0;

int next_reg()
{ // Function to get the next available register index
	current_reg++;
	return current_reg - 1;
}

void reset_reg()
{ // Function to reset the register index
	current_reg = 0;
}

void generate_mips_header(FILE* mips_file)
{
    // Intro
    fprintf(mips_file, "#Eldar Garret 312434293\n#Ofir Nahshoni 204616718\n");
    fprintf(mips_file, ".data\n");
    fprintf(mips_file, ".text\n");
	// Main label
    fprintf(mips_file, "main:\n");
	// Stack
    fprintf(mips_file, "la $fp, 0($sp)\n");
    fprintf(mips_file, "sw $ra, -4($fp)\n");
    fprintf(mips_file, "addi $sp, $sp, -4\n");
}

void generate_mips_footer(FILE* mips_file)
{
    fprintf(mips_file, "lw $ra, -4($fp)\n");
    fprintf(mips_file, "addi $sp, $sp, 4\n");
    fprintf(mips_file, "lw $fp, 0($sp)\n");
    fprintf(mips_file, "jr $ra\n");
}

void generate_mips_assignment(FILE* mips_file, const char* dest, const char* src)
{
    fprintf(mips_file, "move $%s, $%s\n", dest, src);
}

void generate_mips_input(FILE* mips_file, const char* var) 
{
    fprintf(mips_file, "li $v0, 5\n");
    fprintf(mips_file, "syscall\n");
    fprintf(mips_file, "move $%s, $v0\n", var);
}

void generate_mips_output(FILE* mips_file, const char* var) 
{
    fprintf(mips_file, "move $a0, $%s\n", var);
    fprintf(mips_file, "li $v0, 1\n");
    fprintf(mips_file, "syscall\n");
}

void generate_mips_arithmetic(FILE* mips_file, const char* dest, const char* src1, const char* src2, const char op)
{
    switch (op) {
        case '+':
            fprintf(mips_file, "add $%s, $%s, $%s\n", dest, src1, src2);
            break;
        case '-':
            fprintf(mips_file, "sub $%s, $%s, $%s\n", dest, src1, src2);
            break;
        case '*':
            fprintf(mips_file, "mul $%s, $%s, $%s\n", dest, src1, src2);
            break;
        case '/':
            fprintf(mips_file, "div $%s, $%s, $%s\n", dest, src1, src2);
            break;
    }
}

// Function to concatenate two mips code snippets
char* concatenate_mips_code(char* code1, char* code2) {
    char* result = malloc(strlen(code1) + strlen(code2) + 1); // Allocate memory for the result
    strcpy(result, code1); // Copy the first code snippet to the result
    strcat(result, code2); // Append the second code snippet to the result
    free(code1); // Free the memory used by the input snippets
    free(code2);
    return result; // Return the result
}

// Function to get the next available register index
int get_register(int* current_reg) {
    (*current_reg)++; // Increment the register index
    return (*current_reg) - 1; // Return the updated register index
}

// Function to create a mips code snippet that stores a value in a register
char* create_mips_code(int reg, int val) {
    char* result = malloc(100); // Allocate memory for the result
    sprintf(result, "li $%d, %d\n", reg, val); // Generate the mips code
    return result; // Return the result
}
