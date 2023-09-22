# hw3.s
# NAME: <Linghao Shi>

        .data
newline:.asciiz "\n"
tab:    .asciiz "\t"
l_brckt:.asciiz "["
r_brckt:.asciiz "]"

        # global parameters n, k, and m (e.g., 4x3 multiply by 3x4),
        # which the user inputs in the matrix_size procedure
n:      .word 4
k:      .word 3
m:      .word 4

txt1:   .asciiz "Please enter values for n, k, and m:\n"
txt2:   .asciiz "Please enter values for the first matrix ("
txt3:   .asciiz "Please enter values for the second matrix ("
txt4:   .asciiz "x"
txt5:   .asciiz "):"
txt6:   .asciiz "multiplied by\n"
txt7:   .asciiz "equals\n"

################################################################################

        .text
        .globl main
        .globl matrix_multiply
        .globl matrix_print
        .globl matrix_ask
        .globl matrix_sizes

################################################################################

matrix_sizes:
        # Ask the user for the matrix sizes, i.e., n, k, and m,
        # which correspond to multiplying an nxk matrix by a kxm matrix
        li $v0, 4
        la $a0, txt1
        syscall

        #n value
        li $v0, 5
        syscall
        move $s0, $v0

        #k value
        li $v0, 5
        syscall
        move $s1, $v0

        #m value
        li $v0, 5
        syscall
        move $s2, $v0

        jr $ra

################################################################################

matrix_ask:
        # Ask the user for the matrix values to store in
        # the memory address indicated by the $a0 register
        li $v0, 5
        syscall
        add $t1, $v0, $zero
        sw $t1, 0($a0)

        addi $a0, $a0, 4
        addi $t0, $t0, -4
        bne $t0, $zero, matrix_ask

        jr $ra

################################################################################

main:
        # Initialize stack as necessary

        # Obtain user input values n, k, and m
        jal matrix_sizes

        #output first matrix prompt
        li $v0, 4
        la $a0, txt2
        syscall

        li $v0, 1
        move $a0, $s0
        syscall

        li $v0, 4
        la $a0, txt4
        syscall

        li $v0, 1
        move $a0, $s1
        syscall

        li $v0, 4
        la $a0, txt5
        syscall

        li $v0, 4
        la $a0, newline
        syscall

        # Allocate space for matrix
        mul $a0, $s0, $s1
        sll $a0, $a0, 2
        add $t0, $a0, $zero

        li $v0, 9
        syscall
        move $s3, $v0
        add $a0, $s3, $zero

        # Get input for matrix A
        jal matrix_ask

        #output second matrix prompt
        li $v0, 4
        la $a0, txt3
        syscall

        li $v0, 1
        move $a0, $s1
        syscall

        li $v0, 4
        la $a0, txt4
        syscall

        li $v0, 1
        move $a0, $s2
        syscall

        li $v0, 4
        la $a0, txt5
        syscall

        li $v0, 4
        la $a0, newline
        syscall

      	# Allocate space for matrices
        mul $a0, $s1, $s2
        sll $a0, $a0, 2
        add $t0, $a0, $zero

        li $v0, 9
        syscall
        move $s4, $v0
        add $a0, $s4, $zero

        # Get input for matrix B
        jal matrix_ask

        mul $a0, $s0, $s2
        sll $a0, $a0, 2
        add $t0, $a0, $zero

				li $v0, 4
        la $a0, newline
        syscall

        # Perform multiplication to get matrix C
        jal matrix_multiply

        # Output result
        jal matrix_print

        # Cleanup stack and return

        jr $ra


################################################################################

matrix_multiply:
        # multiply matrix A (address $a0) by  matrix B (address $a1),
        # storing the result in matrix C (address $a2)

        #allocate the result matrix
        mul $t0, $s0, $s2       #find the size of result matrix
        sll $a0, $t0, 2
        li $v0, 9
        syscall

				#Set matrices for calculation
        move $s7, $v0
        move $a3, $s7
        move $a1, $s3
        move $a2, $s4
        li $t0, 0       #i = 0
        li $t1, 0       #j = 0
        li $t2, 0       #k = 0

mult_loop1:
				#check if at the end of the matrix
        beq $t0, $s0, return
        li $t1, 0
mult_loop2:
				#check if at the end of a column
        beq $t1, $s2, increment
        li $t2, 0
mult_loop3:
				#check if we need to store the value
        beq $t2, $s1, store_val

				#store return address
        addi $sp, $sp, -4
        sw  $ra, 0($sp)

				#Calculate the address at matrix A
        jal calc_address_1
        add $a1, $a1, $t3
        lw $t3, 0($a1)
        move $a1, $s3

				#Calculate the address at matrix A
        jal calc_address_2
        add $a2, $a2, $t5
        lw $t5, 0($a2)
        move $a2, $s4

        lw $ra, 0($sp)
        addi $sp, $sp, 4

				#Loop through, do the calculation, then add up the results
        mul $t7, $t3, $t5
        add $s6, $s6, $t7
        addi $t2, $t2, 1
        j mult_loop3

calc_address_1:
        mul $t3, $t0, $s1
        sll $t3, $t3, 2
        sll $t4, $t2, 2
        add $t3, $t3, $t4

        jr $ra

calc_address_2:
        mul $t5, $s2, $t2
        sll $t5, $t5, 2
        sll $t6, $t1, 2
        add $t5, $t5, $t6

        jr $ra

store_val:
        sw $s6, 0($a3)
        addi $a3, $a3, 4

        li $s6, 0
        li $t2, 0
        addi $t1, $t1, 1
        j mult_loop2


increment:
        addi $t0, $t0, 1
        j mult_loop1

return:
        jr $ra
################################################################################

matrix_print:
        # print matrix (address $a0)
        addi $sp, $sp, -8
        sw $ra, 0($sp)
        jal print_first_matrix

        li $v0, 4
        la $a0, txt6
        syscall

        jal print_second_matrix

        li $v0, 4
        la $a0, txt7
        syscall

        jal print_result_matrix

        lw $ra, 0($sp)
        addi $sp, $sp, 8
        jr $ra

print_first_matrix:
        sw $ra, 4($sp)
        move $t0, $s0           #store number of rows into $t0
        move $t1, $s1           #store number of columns into $t1
        move $t2, $zero         #use $t2 to keep track of number of rows
        move $a1, $s3           #move array to a1
        j print_row

        lw $ra, 4($sp)
        jr $ra

print_second_matrix:
        sw $ra, 4($sp)
        move $t0, $s1           #store number of rows into $t0
        move $t1, $s2           #store number of columns into $t1
        move $t2, $zero         #use $t2 to keep track of number of rows
        move $a1, $s4           #move array to a1
        j print_row

        lw $ra, 4($sp)
        jr $ra

print_result_matrix:
        sw $ra, 4($sp)
        move $t0, $s0           #store number of rows into $t0
        move $t1, $s2           #store number of columns into $t1
        move $t2, $zero         #use $t2 to keep track of number of rows
        move $a1, $s7           #move array to a1
        j print_row

        lw $ra, 4($sp)
        jr $ra

print_row:
        li $v0, 4
        la $a0, l_brckt
        syscall

        move $t3, $zero
        jal print_col

        li $v0, 4
        la $a0, r_brckt
        syscall

        li $v0, 4
        la $a0, newline
        syscall

        addi $t2, $t2, 1
        bne $t2, $t0, print_row

        lw $ra, 4($sp)
        jr $ra

print_col:
        li $v0, 1
        lw $a0, 0($a1)
        syscall

        li $v0, 4
        la $a0, tab
        syscall

        addi $a1, $a1, 4
        addi $t3, $t3, 1
        bne $t3, $t1, print_col

        jr $ra
