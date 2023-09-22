        .data
even:   .asciiz "EVEN\n"
odd:    .asciiz "ODD\n"
msg:    .asciiz "Enter an integer:\n"

        .text
        .globl main
main:   
        #reads an integer
        li $v0, 4
        la $a0, msg
        syscall
        li $v0, 5
        syscall

        #compare input with 1
        andi $t0, $v0, 1
        beq $t0, $zero, EVEN

        #input is odd
        li $v0, 4
        la $a0, odd
        syscall

        add $v0, $zero, 1

        jr $ra

        #input is even
EVEN:
        li $v0, 4
        la $a0, even
        syscall

        add $v0, $zero, 0

        jr $ra

