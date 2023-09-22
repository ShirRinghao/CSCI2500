        .data
prompt: .asciiz "Enter an integer: "
msg1:   .asciiz "byte #1: "
msg2:   .asciiz "\nbyte #2: "
msg3:   .asciiz "\nbyte #3: "
msg4:   .asciiz "\nbyte #4: "

        .text
        .globl main
main:   li $v0, 4
        la $a0, prompt
        syscall

        li $v0, 5
        syscall
        add $a0, $v0, $zero

        jal display
        li $v0, 10
        syscall

display:
        addu $s0, $a0, 0
        #Byte 1
        srl $t0, $s0, 24
        li $v0, 4
        la $a0, msg1
        syscall

        li  $v0, 1
        move $a0, $t0
        syscall

        #Byte 2
        sll $t0, $s0, 8
        srl $t1, $t0, 24
        li $v0, 4
        la $a0, msg2
        syscall

        li $v0, 1
        move $a0, $t1
        syscall

        #Byte3
        sll $t0, $s0, 16
        srl $t1, $t0, 24
        li $v0, 4
        la $a0, msg3
        syscall

        li $v0, 1
        move $a0, $t1
        syscall

        #Byte 4
        sll $t0, $s0, 24
        srl $t1, $t0, 24
        li $v0, 4
        la $a0, msg4
        syscall

        li $v0, 1
        move $a0, $t1
        syscall

        jr $ra 


