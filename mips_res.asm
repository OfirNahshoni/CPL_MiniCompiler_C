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
		li $t0, 3
		# Store $t0 into x1 (in .data section)
		sw $t0, x1
		# Load int value into $t0
		li $t0, 1
		# Store $t0 into x2 (in .data section)
		sw $t0, x2
		# Arithmetic operation
		# Load x1 value into $t0
		lw $t0, x1
		# Load int value 2 into $t1
		li $t1, 2
		add $t0, $t0, $t1
		# Arithmetic operation
		# Load int value 5 into $t1
		li $t1, 5
		# Load x2 value into $t2
		lw $t2, x2
		add $t1, $t1, $t2
		# Arithmetic operation
		mul $t0, $t0, $t1
		# Cast int to float
		mtc1 $t0, $f0
		cvt.s.w $f0, $f0
		# Store $f0 value into w2
		s.s $f0, w2
		# Free the Stack
		lw $ra, -4($fp)
		addi $sp, $sp, 4
		lw $fp, 0($sp)
		jr $ra
		# Load system call to terminate the program
		li $v0, 10
		syscall