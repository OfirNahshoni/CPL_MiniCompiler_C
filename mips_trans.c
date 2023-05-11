#include "mips_trans.h"

int current_reg = 0;

void reset_reg()
{ // Function to reset the register index
	current_reg = 0;
}

void generate_mips_header(FILE* mips_file)
{
    fprintf(mips_file, "# Eldar Garret 312434293\n");
    fprintf(mips_file, "# Ofir Nahshoni 204616718\n\n");
    fprintf(mips_file, "# Variables declarations\n");
    fprintf(mips_file, ".data\n");
    fprintf(mips_file, "la $fp, 0($sp)\n");
    fprintf(mips_file, "sw $ra, -4($fp)\n");
    fprintf(mips_file, "addi $sp, $sp, -4\n");
}

void generate_mips_body(FILE* mips_file)
{
    fprintf(mips_file, "# Main program\n");
    fprintf(mips_file, ".text\n");
	fprintf(mips_file, "main:\n"); // Main label
}

void generate_mips_footer(FILE* mips_file)
{
    fprintf(mips_file, "# Free the Stack\n");
    fprintf(mips_file, "lw $ra, -4($fp)\n");
    fprintf(mips_file, "addi $sp, $sp, 4\n");
    fprintf(mips_file, "lw $fp, 0($sp)\n");
    fprintf(mips_file, "jr $ra\n");
}

void translate_declar(FILE* mips_file, char type, char* id, char* sval) {
    switch (type)
    {
        case 'i': // int
            fprintf(mips_file, "%s:\t.word %s", id, sval);
            break;
        case 'r': // real
            fprintf(mips_file, "%s:\t.float %s", id, sval);
            break;
        case 's': // string
            fprintf(mips_file, "%s:\t.asciiz %s", id), sval;
            break;
        default:
            break;
    }
}