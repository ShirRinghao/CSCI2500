        .data
msg:    .asciiz "GCD(45, 54) is "
new_line: .asciiz "\n"
        .text
main:   li $t0, 54
        li $t1, 45


gcd:
        bne $t0, $t1, loop
        li $v0, 4
        la $a0, msg
        syscall
        li $v0, 1
        move $a0, $t0
        syscall
        li $v0, 4
        la $a0, new_line
        syscall
        li $v0 10
        syscall

        jr $ra


loop:
        bgt $t0, $t1, greater
        sub $t1, $t1, $t0
        j gcd


greater:
        sub $t0, $t0, $t1
        j gcd
