        .data
list:   .word 12, 100, 101, 5, 123456789, 18
msg:    .asciiz "Number of Odd Integers is: "
        .text
        .globl main
main:
        la $a0, list
        li $a1, 6
        li $t0, 0
        li $t1, 0
        li $t2, 0
        li $t3, 0


numodds:
        #check if it is at the end of the list
        beq $t3 $a1, Exit

        #load the value in the list
        lw $t0, 0($a0)

        #increment the location in the list
        #use and to check the number
        addi $a0, $a0, 4
        andi $t1, $t0, 1
        addi $t3, $t3, 1

        #Check if it is an even or odd number
        beq $t1, $zero, numodds
        addi $t2, $t2, 1

        #check if it is at the end of the list
        beq $t3 $a1, Exit
        j numodds

Exit:
        la $a0, msg
        li $v0, 4
        syscall

        move $a0, $t2
        li $v0, 1
        syscall

        li $v0, 10
        syscall
