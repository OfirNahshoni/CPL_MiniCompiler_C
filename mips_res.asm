# Eldar Garret 312434293
# Ofir Nahshoni 204616718

# Variables declarations
.data
la $fp, 0($sp)
sw $ra, -4($fp)
addi $sp, $sp, -4
# Main program
.text
main:
# Free the Stack
lw $ra, -4($fp)
addi $sp, $sp, 4
lw $fp, 0($sp)
jr $ra
