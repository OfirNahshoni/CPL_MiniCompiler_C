#include "mips_trans.h"

int next_reg()
{ // Function to get the next available register index
	current_reg++;
	return current_reg - 1;
}

void reset_reg()
{ // Function to reset the register index
	current_reg = 0;
}

void generate_mips_header()
{
	// Intro
    printf("#Eldar Garret 312434293\n#Ofir Nahshoni 204616718\n");
    printf(".data\n");
    printf(".text\n");
	// Main label
    printf("main:\n");
	// Stack
    printf("la $fp, 0($sp)\n");
    printf("sw $ra, -4($fp)\n");
    printf("addi $sp, $sp, -4\n");
}

void generate_mips_footer()
{
    printf("lw $ra, -4($fp)\n");
    printf("addi $sp, $sp, 4\n");
    printf("lw $fp, 0($sp)\n");
    printf("jr $ra\n");
}

void generate_mips_assignment(const char* dest, const char* src)
{
    printf("move $%s, $%s\n", dest, src);
}

void generate_mips_input(const char* var) 
{
    printf("li $v0, 5\n");
    printf("syscall\n");
    printf("move $%s, $v0\n", var);
}

void generate_mips_output(const char* var) 
{
    printf("move $a0, $%s\n", var);
    printf("li $v0, 1\n");
    printf("syscall\n");
}

void generate_mips_arithmetic(const char* dest, const char* src1, const char* src2, const char op)
{
    switch (op) {
        case '+':
            printf("add $%s, $%s, $%s\n", dest, src1, src2);
            break;
        case '-':
            printf("sub $%s, $%s, $%s\n", dest, src1, src2);
            break;
        case '*':
            printf("mul $%s, $%s, $%s\n", dest, src1, src2);
            break;
        case '/':
            printf("div $%s, $%s, $%s\n", dest, src1, src2);
            break;
    }
}