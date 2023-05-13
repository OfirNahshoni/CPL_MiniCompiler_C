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
		.data
			str1_new: .asciiz "ofir new"
		.text
			# Load address of new string into $t0
			la $t0, str1_new
			# Load address of destination string into $t1
			la $t1, str1
		str_copy_loop_str1:
			# Load byte from new string into $t2
			lb $t2, 0($t0)
			# Store byte to destination string
			sb $t2, 0($t1)
			# If zero byte (end of string) is encountered, exit the loop
			beqz $t2, str_copy_end_str1
			# Increment address of new string
			addiu $t0, $t0, 1
			# Increment address of destination string
			addiu $t1, $t1, 1
			j str_copy_loop_str1
		str_copy_end_str1:
		# Print output
		.data
			str_to_print: .asciiz "OFIRRRRR"
		.text
			# Load address of output string into $a0
			la $a0, str_to_print
			# Load system call to print a string
			li $v0, 4
			syscall
	# Free the Stack
	lw $ra, -4($fp)
	addi $sp, $sp, 4
	lw $fp, 0($sp)
	jr $ra
	# Load system call to terminate the program
	li $v0, 10
	syscall