#include "mips_trans.h"
#include "my_structs.h"

int int_counter = 0;
int float_counter = 0;
int string_counter = 0;
int current_label = 0;

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
    fprintf(mips_file, "\t\t# Free the Stack\n");
    fprintf(mips_file, "\t\tlw $ra, -4($fp)\n");
    fprintf(mips_file, "\t\taddi $sp, $sp, 4\n");
    fprintf(mips_file, "\t\tlw $fp, 0($sp)\n");
    fprintf(mips_file, "\t\tjr $ra\n");
    fprintf(mips_file, "\t\t# Load system call to terminate the program\n");
    fprintf(mips_file, "\t\tli $v0, 10\n");
    fprintf(mips_file, "\t\tsyscall");
}

// Function that generates temporary register name (for int variables)
char* generate_reg_name(char type) {
    char* reg_name = malloc(sizeof(char) * 4);
    switch (type)
    {
        case 'i': // int
            sprintf(reg_name, "$t%d", (int_counter++) % 10); // 0-9
            break;
        case 'r': // real
            sprintf(reg_name, "$f%d", (float_counter++) % 30); // 0-29
            break;
        case 's':
            sprintf(reg_name, "$s%d", (string_counter++) % 8); // 0-7
            break;
        default:
            break;
    }
    return reg_name;
}

char* generate_label() {
    char* label_name = malloc(sizeof(char) * 20);
    sprintf(label_name, "L%d", current_label++);
    return label_name;
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

void translate_assignment(FILE *mips_file, char* id, char* value, char type, char* reg_name) {
    char* reg_name_new;
    char* reg_name_dest;
    char* reg_name_byte;

    switch (type)
    {
        case 'i': // int
            fprintf(mips_file, "\t\t# Load address of id into a register\n");
            fprintf(mips_file, "\t\tla $at, %s\n", id);
            fprintf(mips_file, "\t\t# Load integer into temp reg\n");
            fprintf(mips_file, "\t\tli %s, %s\n", reg_name, value);
            fprintf(mips_file, "\t\t# Store temp reg's value into id\n");
            fprintf(mips_file, "\t\tsw %s, 0($at)\n", reg_name);
            break;
        case 'r': // real
            // mips - Declarations
            fprintf(mips_file, "\t\t.data\n");
            fprintf(mips_file, "\t\t\t# Align to a word boundary\n");
            fprintf(mips_file, "\t\t\t.align 2\n");
            fprintf(mips_file, "\t\t\t%s_to_assign: .float %s\n", id, value);
            // mips - actions
            fprintf(mips_file, "\t\t.text\n");
            fprintf(mips_file, "\t\t\t# Load float value into float reg\n");
            fprintf(mips_file, "\t\t\tl.s %s, %s_to_assign\n", reg_name, id);
            fprintf(mips_file, "\t\t\t# Load address of id into a register\n");
            fprintf(mips_file, "\t\tla $at, %s\n", id);
            fprintf(mips_file, "\t\t\t# Store float value to id (memory)\n");
            fprintf(mips_file, "\t\t\ts.s %s, 0($at)\n", reg_name);
            break;

        case 's': // string
            // Generate 2 string reg_names
            reg_name_new = generate_reg_name('s'); // $s0
            reg_name_dest = generate_reg_name('s'); // $s1
            reg_name_byte = generate_reg_name('s'); // $s2
            // mips - Declarations
            fprintf(mips_file, "\t\t.data\n");
            fprintf(mips_file, "\t\t\t%s_new: .asciiz %s\n", id, value);
            // mips - actions
            fprintf(mips_file, "\t\t.text\n");
            fprintf(mips_file, "\t\t\t# Load address of new string into temp reg\n");
            fprintf(mips_file, "\t\t\tla %s, %s_new\n", reg_name_new, id);
            fprintf(mips_file, "\t\t\t# Load address of destination string into temp reg\n");
            fprintf(mips_file, "\t\t\tla %s, %s\n", reg_name_dest, id);
            fprintf(mips_file, "\t\tstr_copy_loop_%s:\n", id);
            fprintf(mips_file, "\t\t\t# Load byte from new string into temp reg\n");
            fprintf(mips_file, "\t\t\tlb %s, 0(%s)\n", reg_name_byte, reg_name_new);
            fprintf(mips_file, "\t\t\t# Store byte to destination string\n");
            fprintf(mips_file, "\t\t\tsb %s, 0(%s)\n", reg_name_byte, reg_name_dest);
            fprintf(mips_file, "\t\t\t# If zero byte (end of string) is encountered, exit the loop\n");
            fprintf(mips_file, "\t\t\tbeqz %s, str_copy_end_%s\n", reg_name_byte, id);
            fprintf(mips_file, "\t\t\t# Increment address of new string\n");
            fprintf(mips_file, "\t\t\taddiu %s, %s, 1\n", reg_name_new, reg_name_new);
            fprintf(mips_file, "\t\t\t# Increment address of destination string\n");
            fprintf(mips_file, "\t\t\taddiu %s, %s, 1\n", reg_name_dest, reg_name_dest);
            fprintf(mips_file, "\t\t\tj str_copy_loop_%s\n", id);
            fprintf(mips_file, "\t\tstr_copy_end_%s:\n", id);
            free(reg_name_new);
            free(reg_name_dest);
            free(reg_name_byte);
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
            fprintf(mips_file, "\t\tla $at, %s\n", id);
            fprintf(mips_file, "\t\tsw $v0, 0($at)\n");
            break;
        case 'r': // real
            fprintf(mips_file, "\t\t# Load system call to read floating point number\n");
            fprintf(mips_file, "\t\tli $v0, 6\n");
            fprintf(mips_file, "\t\tsyscall\n");
            fprintf(mips_file, "\t\t# Store input value in %s\n", id);
            fprintf(mips_file, "\t\tla $at, %s\n", id);
            fprintf(mips_file, "\t\ts.s $f0, 0($at)\n");
            break;
        case 's': // string
            fprintf(mips_file, "\t\t# Load address of string to store the input\n");
            fprintf(mips_file, "\t\tla $a0, %s\n", id);
            fprintf(mips_file, "\t\t# Load maximum input length\n");
            fprintf(mips_file, "\t\tli $a1, MAX_INPUT_LEN\n");
            fprintf(mips_file, "\t\t# Load system call to read a string\n");
            fprintf(mips_file, "\t\tli $v0, 8\n");
            fprintf(mips_file, "\t\tsyscall\n");
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
            fprintf(mips_file, "\t\t# Load address of integer value into $at\n");
            fprintf(mips_file, "\t\tla $at, %s\n", value);
            fprintf(mips_file, "\t\t# Load value from memory into $a0\n");
            fprintf(mips_file, "\t\tlw $a0, 0($at)\n");
            fprintf(mips_file, "\t\t# Load system call to print an integer\n");
            fprintf(mips_file, "\t\tli $v0, 1\n");
            fprintf(mips_file, "\t\tsyscall\n");
            break;
        case 'r': // real
            fprintf(mips_file, "\t\t# Load address of floating point number into $at\n");
            fprintf(mips_file, "\t\tla $at, %s\n", value);
            fprintf(mips_file, "\t\t# Load value from memory into $f12\n");
            fprintf(mips_file, "\t\tl.s $f12, 0($at)\n");
            fprintf(mips_file, "\t\t# Load system call to a print floating point number\n");
            fprintf(mips_file, "\t\tli $v0, 2\n");
            fprintf(mips_file, "\t\tsyscall\n");
            break;
        case 's': // string
            fprintf(mips_file, "\t\t# Load address of output string into $a0\n");
            fprintf(mips_file, "\t\tla $a0, %s\n", value);
            fprintf(mips_file, "\t\t# Load system call to print a string\n");
            fprintf(mips_file, "\t\tli $v0, 4\n");
            fprintf(mips_file, "\t\tsyscall\n");
            break;
        default:
            break;
    }
}
