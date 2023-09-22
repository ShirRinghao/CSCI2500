            .data
prompt:     .asciiz "Enter positive integer:\n"
txt1:       .asciiz "For $"
txt2:       .asciiz ", you need:\n"
dot:        .asciiz "."
quarters:   .asciiz " quarters\n"
quarter:    .asciiz " quarter\n"
dime:       .asciiz " dime\n"
dimes:      .asciiz " dimes\n"
pennies:    .asciiz " pennies\n"
penny:      .asciiz " penny\n"
nickels:    .asciiz " nickels\n"
nickel:     .asciiz " nickel\n"
zeros:    .asciiz "0"
            .text
main:
    li $v0, 4
    la $a0, prompt
    syscall

    #get input values
    li $v0, 5
    syscall
    move $s0, $v0

    #Calculation for quarters
    move $t0, $s0
    li $t1, 25
    divu $t0, $t1
    mflo $s1
    mfhi $t2

    #Calculation for dimes
    li $t1, 10
    divu $t2, $t1
    mflo $s2
    mfhi $t3

    #Calculation for nickles
    li $t1, 5
    divu $t3, $t1
    mflo $s3
    mfhi $t3

    #Calculation for pennies
    li $t2, 1
    divu $t3, $t2
    mflo $s4

    li $t5, 100
    move $t4, $s0
    divu $t4, $t5
    mflo $s6

    mul $t5, $s6, 100
    sub $s5, $s0, $t5

print_msg:
    #output text
    li $v0, 4
    la $a0, txt1
    syscall

    li $v0, 1
    move $a0, $s6
    syscall

    li $v0, 4
    la $a0, dot
    syscall

    blt $s5, 10, zero
    li $v0, 1
    move $a0, $s5
    syscall

    li $v0, 4
    la $a0, txt2
    syscall

    j print_quarter

zero:
    li $v0, 4
    la $a0, zeros
    syscall

    blt $s5, 1, secondzero
    li $v0, 1
    move $a0, $s5
    syscall

    li $v0, 4
    la $a0, txt2
    syscall
    j print_quarter
    
secondzero:
    li $v0, 4
    la $a0, zeros
    syscall
    li $v0, 4
    la $a0, txt2
    syscall

print_quarter:
    li $v0, 1
    move $a0, $s1
    syscall

    bge $s1, 2, print_quarters
    li $v0, 4
    la $a0, quarter
    syscall
    j print_dime

print_quarters:
    li $v0, 4
    la $a0, quarters
    syscall

print_dime:
    li $v0, 1
    move $a0, $s2
    syscall

    bge $s2, 2, print_dimes
    li $v0, 4
    la $a0, dime
    syscall
    j print_nickel

print_dimes:
    li $v0, 4
    la $a0, dimes
    syscall

print_nickel:
    li $v0, 1
    move $a0, $s3
    syscall

    bge $s3, 2, print_nickels
    li $v0, 4
    la $a0, nickel
    syscall
    j print_penny

print_nickels:
    li $v0, 4
    la $a0, nickels
    syscall

print_penny:
    li $v0, 1
    move $a0, $s4
    syscall

    bge $s4, 2, print_pennies
    li $v0, 4
    la $a0, penny
    syscall

    jr $ra

print_pennies:
    li $v0, 4
    la $a0, pennies
    syscall

    jr $ra
