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
	z2:	.word 5
	z1:	.float 11.2
.text
	# Main program
	.global main
	main:
		# Load address of id into a register
		la $at, x1
		# Load integer into temp reg
		li $t0, 2
		# Store temp reg's value into id
		sw $t0, 0($at)
		# Get input from user
		# Load system call to read an integer
		li $v0, 5
		syscall
		# Store input value in x1
		la $at, x1
		sw $v0, 0($at)
		# Get input from user
		# Load system call to read floating point number
		li $v0, 6
		syscall
		# Store input value in w1
		la $at, w1
		s.s $f0, 0($at)
		# Print output
		# Load address of output string into $a0
		la $a0, "Ofir"
		# Load system call to print a string
		li $v0, 4
		syscall
		# Print output
		# Load address of integer value into $at
		la $at, x1
		# Load value from memory into $a0
		lw $a0, 0($at)
		# Load system call to print an integer
		li $v0, 1
		syscall
		# Free the Stack
		lw $ra, -4($fp)
		addi $sp, $sp, 4
		lw $fp, 0($sp)
		jr $ra
		# Load system call to terminate the program
		li $v0, 10
		syscall