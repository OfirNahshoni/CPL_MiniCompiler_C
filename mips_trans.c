#include "mips_trans.h"
#include "my_structs.h"

int current_reg = 0;

void reset_reg() {
	current_reg = 0;
}

void generate_mips_header(FILE* mips_file) {
    fprintf(mips_file, "# Eldar Garret 312434293\n");
    fprintf(mips_file, "# Ofir Nahshoni 204616718\n\n");
}

void generate_mips_data_section(FILE* mips_file) {
    fprintf(mips_file, "# Variables declarations\n");
    fprintf(mips_file, ".data\n");
    fprintf(mips_file, "\tMAX_INPUT_LEN: .word 100\n");
}

void generate_mips_text_section(FILE* mips_file) {
    fprintf(mips_file, ".text\n");
    fprintf(mips_file, "\t# Main program\n");
    fprintf(mips_file, "\t.global main\n");
	fprintf(mips_file, "\tmain:\n"); // Main label
}

void generate_mips_footer(FILE* mips_file) {
    fprintf(mips_file, "\t# Free the Stack\n");
    fprintf(mips_file, "\tlw $ra, -4($fp)\n");
    fprintf(mips_file, "\taddi $sp, $sp, 4\n");
    fprintf(mips_file, "\tlw $fp, 0($sp)\n");
    fprintf(mips_file, "\tjr $ra\n");
    fprintf(mips_file, "\t# Load system call to terminate the program\n");
    fprintf(mips_file, "\tli $v0, 10\n");
    fprintf(mips_file, "\tsyscall");
}

void translate_declar(FILE* mips_file, char type, char* id, char* sval) {
    switch (type)
    {
        case 'i': // int
            fprintf(mips_file, "\t%s:\t.word %s\n", id, sval);
            break;
        case 'r': // real
            fprintf(mips_file, "\t%s:\t.float %s\n", id, sval);
            break;
        case 's': // string
            fprintf(mips_file, "\t%s:\t.asciiz %s\n", id, sval);
            break;
        default:
            break;
    }
}

void translate_assignment(FILE *mips_file, char* id, char* value, char type) {
    switch (type)
    {
        case 'i': // int
            fprintf(mips_file, "\t\t# Load integer into temp reg\n");
            fprintf(mips_file, "\t\tli $t0, %s\n", value);
            fprintf(mips_file, "\t\t# Store temp reg's value into id\n");
            fprintf(mips_file, "\t\tsw $t0, %s\n", id);
            break;
        case 'r': // real
            fprintf(mips_file, "\t\t.data\n");
            fprintf(mips_file, "\t\t\t# Align to a word boundary\n");
            fprintf(mips_file, "\t\t\t.align 2\n");
            fprintf(mips_file, "\t\t\t%s_to_assign: .float %s\n", id, value);
            fprintf(mips_file, "\t\t.text\n");
            fprintf(mips_file, "\t\t\t# Load float value into float reg\n");
            fprintf(mips_file, "\t\t\tl.s $f0, %s_to_assign\n", id);
            fprintf(mips_file, "\t\t\t# Store float value to id (memory)\n");
            fprintf(mips_file, "\t\t\ts.s $f0, %s\n", id);
            break;
        case 's': // string
            fprintf(mips_file, "\t\t.data\n");
            fprintf(mips_file, "\t\t\t%s_new: .asciiz %s\n", id, value);
            fprintf(mips_file, "\t\t.text\n");
            fprintf(mips_file, "\t\t\t# Load address of new string into $t0\n");
            fprintf(mips_file, "\t\t\tla $t0, %s_new\n", id);
            fprintf(mips_file, "\t\t\t# Load address of destination string into $t1\n");
            fprintf(mips_file, "\t\t\tla $t1, %s\n", id);
            fprintf(mips_file, "\t\tstr_copy_loop_%s:\n", id);
            fprintf(mips_file, "\t\t\t# Load byte from new string into $t2\n");
            fprintf(mips_file, "\t\t\tlb $t2, 0($t0)\n");
            fprintf(mips_file, "\t\t\t# Store byte to destination string\n");
            fprintf(mips_file, "\t\t\tsb $t2, 0($t1)\n");
            fprintf(mips_file, "\t\t\t# If zero byte (end of string) is encountered, exit the loop\n");
            fprintf(mips_file, "\t\t\tbeqz $t2, str_copy_end_%s\n", id);
            fprintf(mips_file, "\t\t\t# Increment address of new string\n");
            fprintf(mips_file, "\t\t\taddiu $t0, $t0, 1\n");
            fprintf(mips_file, "\t\t\t# Increment address of destination string\n");
            fprintf(mips_file, "\t\t\taddiu $t1, $t1, 1\n");
            fprintf(mips_file, "\t\t\tj str_copy_loop_%s\n", id);
            fprintf(mips_file, "\t\tstr_copy_end_%s:\n", id);
            break;
        default:
            break;
    }
}

void translate_input(FILE* mips_file, char* id, char type) {
    fprintf(mips_file, "\t\t# Get input from user\n");
    switch (type)
    {
        case 'i': // int
            fprintf(mips_file, "\t\t# Load system call to read an integer\n");
            fprintf(mips_file, "\t\tli $v0, 5\n");
            fprintf(mips_file, "\t\tsyscall\n");
            fprintf(mips_file, "\t\t# Store input value in %s\n", id);
            fprintf(mips_file, "\t\tsw $v0, %s\n", id);
            break;
        case 'r': // real
            fprintf(mips_file, "\t\t# Load system call to read floating point number\n");
            fprintf(mips_file, "\t\tli $v0, 6\n");
            fprintf(mips_file, "\t\tsyscall\n");
            fprintf(mips_file, "\t\t# Store input value in %s\n", id);
            fprintf(mips_file, "\t\ts.s $f0, %s\n", id);
            break;
        case 's': // string
            fprintf(mips_file, "\t\t# Load address of string to store the input\n");
            fprintf(mips_file, "\t\tla $a0, %s\n", id);
            fprintf(mips_file, "\t\t# Load maximum input length\n");
            fprintf(mips_file, "\t\tli $a1, MAX_INPUT_LEN\n");
            fprintf(mips_file, "\t\t# Load system call to read a string\n");
            fprintf(mips_file, "\t\tli $v0, 8\n");
            fprintf(mips_file, "\t\tsyscall\n");
            fprintf(mips_file, "\t\t# Store input value in %s\n", id);
            fprintf(mips_file, "\t\tsw $a0, %s\n", id);
            break;
        default:
            break;
    }
}

void translate_output(FILE* mips_file, char* value, char type) {
    fprintf(mips_file, "\t\t# Print output\n");
    switch (type)
    {
        case 'i': // int
            fprintf(mips_file, "\t\t# Load integer value into $a0\n");
            fprintf(mips_file, "\t\tli $a0, %s\n", value);
            fprintf(mips_file, "\t\t# Load system call to print an integer\n");
            fprintf(mips_file, "\t\tli $v0, 1\n");
            fprintf(mips_file, "\t\tsyscall\n");
            break;
        case 'r': // real
            fprintf(mips_file, "\t\t# Load address of floating point number into $f12\n");
            fprintf(mips_file, "\t\tl.s $f12, %s\n", value);
            fprintf(mips_file, "\t\t# Load system call to a print floating point number\n");
            fprintf(mips_file, "\t\tli $v0, 2\n");
            fprintf(mips_file, "\t\tsyscall\n");
            break;
        case 's': // string
            fprintf(mips_file, "\t\t.data\n");
            fprintf(mips_file, "\t\t\tstr_to_print: .asciiz %s\n", value);
            fprintf(mips_file, "\t\t.text\n");
            fprintf(mips_file, "\t\t\t# Load address of output string into $a0\n");
            fprintf(mips_file, "\t\t\tla $a0, str_to_print\n");
            fprintf(mips_file, "\t\t\t# Load system call to print a string\n");
            fprintf(mips_file, "\t\t\tli $v0, 4\n");
            fprintf(mips_file, "\t\t\tsyscall\n");
            break;
        default:
            break;
    }
}