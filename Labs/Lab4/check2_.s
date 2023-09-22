        .data
num:    .word 3
msg:    .asciiz "x ($t0) equals "
new_line:.asciiz "\n"

        .text
main:   lw $t0, num
        li $t1, 5
        slt $t2, $t0, $t1
        beq $t2, 1, comparesize
        li $v0, 4
        la $a0, msg
        syscall
        li $v0, 1
        move $a0 $t0
        syscall
        li $v0, 4
        la $a0, new_line
        syscall
        jr $ra


comparesize:
        addi $t0, $t0, 3
        li $v0, 4
        la $a0, msg
        syscall
        li $v0, 1
        move $a0, $t0
        syscall
        li $v0, 4
        la $a0, new_line
        syscall
        jr $ra
