# Eldar Garret 312434293
# Ofir Nahshoni 204616718

# Variables declarations
.data
	MAX_INPUT_LEN: .word 100
	x2:	.word 0
	x1:	.word 0
	w2:	.float 0
	w1:	.float 0
	str2:	.asciiz 0
	str1:	.asciiz 0
.text
	# Main program
	.global main
	main:
		# Load int value into $t0
		li $t0, 1
		# Store $t0 into x1 (in .data section)
		sw $t0, x1
		# Load x1 value to $t0
		lw $t0, x1
		# Cast int to float
		mtc1 $t0, $f0
		cvt.s.w $f0, $f0
		# Store $f0 value into w1
		s.s $f0, w1
		# Free the Stack
		lw $ra, -4($fp)
		addi $sp, $sp, 4
		lw $fp, 0($sp)
		jr $ra
		# Load system call to terminate the program
		li $v0, 10
		syscall