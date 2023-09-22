	.section	__TEXT,__text,regular,pure_instructions
	.build_version macos, 10, 14	sdk_version 10, 14
	.globl	_compute                ## -- Begin function compute
	.p2align	4, 0x90
_compute:                               ## @compute
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	pushq	%r15
	pushq	%r14
	pushq	%r12
	pushq	%rbx
	subq	$512, %rsp              ## imm = 0x200
	.cfi_offset %rbx, -48
	.cfi_offset %r12, -40
	.cfi_offset %r14, -32
	.cfi_offset %r15, -24
	movq	___stack_chk_guard@GOTPCREL(%rip), %rax
	movq	(%rax), %rax
	movq	%rax, -40(%rbp)
	movl	%edi, -340(%rbp)
	## InlineAsm Start
	movq	%rsp, %rax
	## InlineAsm End
	movq	%rax, -352(%rbp)
	## InlineAsm Start
	movq	%rbp, %rax
	## InlineAsm End
	movq	%rax, -360(%rbp)
	movq	-352(%rbp), %rsi
	movq	-360(%rbp), %rdx
	movq	-360(%rbp), %rax
	movq	-352(%rbp), %rcx
	subq	%rcx, %rax
	leaq	L_.str(%rip), %rdi
	movq	%rax, %rcx
	movb	$0, %al
	callq	_printf
	movq	%rbp, %rcx
	movq	%rcx, -368(%rbp)
	movq	-368(%rbp), %rsi
	leaq	L_.str.1(%rip), %rdi
	movl	%eax, -372(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	-192(%rbp), %rcx
	movq	%rcx, %rdx
	movq	-368(%rbp), %rsi
	subq	%rsi, %rdx
	movq	%rcx, %rsi
	addq	$144, %rsi
	movq	%rcx, %rdi
	addq	$144, %rdi
	movq	-368(%rbp), %r8
	subq	%r8, %rdi
	leaq	L_.str.2(%rip), %r8
	movq	%rdi, -384(%rbp)        ## 8-byte Spill
	movq	%r8, %rdi
	movq	%rsi, -392(%rbp)        ## 8-byte Spill
	movq	%rcx, %rsi
	movq	-392(%rbp), %rcx        ## 8-byte Reload
	movq	-384(%rbp), %r8         ## 8-byte Reload
	movl	%eax, -396(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	leaq	-336(%rbp), %rcx
	movq	%rcx, %rdx
	movq	-368(%rbp), %rsi
	subq	%rsi, %rdx
	movq	%rcx, %rsi
	addq	$144, %rsi
	movq	%rcx, %rdi
	addq	$144, %rdi
	movq	-368(%rbp), %r8
	subq	%r8, %rdi
	leaq	L_.str.3(%rip), %r8
	movq	%rdi, -408(%rbp)        ## 8-byte Spill
	movq	%r8, %rdi
	movq	%rsi, -416(%rbp)        ## 8-byte Spill
	movq	%rcx, %rsi
	movq	-416(%rbp), %rcx        ## 8-byte Reload
	movq	-408(%rbp), %r8         ## 8-byte Reload
	movl	%eax, -420(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movq	-360(%rbp), %rcx
	movzbl	8(%rcx), %esi
	movq	-360(%rbp), %rcx
	movzbl	9(%rcx), %edx
	movq	-360(%rbp), %rcx
	movzbl	10(%rcx), %ecx
	movq	-360(%rbp), %rdi
	movzbl	11(%rdi), %r8d
	movq	-360(%rbp), %rdi
	movzbl	12(%rdi), %r9d
	movq	-360(%rbp), %rdi
	movzbl	13(%rdi), %r10d
	movq	-360(%rbp), %rdi
	movzbl	14(%rdi), %r11d
	movq	-360(%rbp), %rdi
	movzbl	15(%rdi), %ebx
	leaq	L_.str.4(%rip), %rdi
	movl	%r10d, (%rsp)
	movl	%r11d, 8(%rsp)
	movl	%ebx, 16(%rsp)
	movl	%eax, -424(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movl	$8, %ecx
	movl	%ecx, %edi
	leaq	-336(%rbp), %r14
	movq	%r14, %r15
	addq	$144, %r15
	leaq	L_.str.5(%rip), %r12
	movq	%rdi, -432(%rbp)        ## 8-byte Spill
	movq	%r12, %rdi
	movq	%r14, %rsi
	movq	-432(%rbp), %rdx        ## 8-byte Reload
	movq	%r15, %rcx
	movq	-432(%rbp), %r8         ## 8-byte Reload
	movl	%eax, -436(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movl	$144, %r9d
	movl	%r9d, %edx
	movl	$8, %r9d
	movl	%r9d, %r8d
	leaq	-336(%rbp), %rcx
	movq	%rcx, %rsi
	addq	$24, %rsi
	leaq	L_.str.6(%rip), %rdi
	movq	%rsi, -448(%rbp)        ## 8-byte Spill
	movq	%rcx, %rsi
	movq	-448(%rbp), %rcx        ## 8-byte Reload
	movl	%eax, -452(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movl	$24, %r9d
	movl	%r9d, %edx
	movl	$8, %r9d
	movl	%r9d, %r8d
	leaq	-336(%rbp), %rcx
	movq	%rcx, %rsi
	addq	$4, %rsi
	leaq	L_.str.7(%rip), %rdi
	movq	%rsi, -464(%rbp)        ## 8-byte Spill
	movq	%rcx, %rsi
	movq	-464(%rbp), %rcx        ## 8-byte Reload
	movl	%eax, -468(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movl	$8, %r9d
	movl	%r9d, %ecx
	leaq	-336(%rbp), %rdx
	movq	%rdx, %rsi
	addq	$24, %rsi
	leaq	L_.str.8(%rip), %rdi
	movq	%rsi, -480(%rbp)        ## 8-byte Spill
	movq	%rdx, %rsi
	movq	%rcx, %rdx
	movq	-480(%rbp), %r8         ## 8-byte Reload
	movq	%rcx, -488(%rbp)        ## 8-byte Spill
	movq	%r8, %rcx
	movq	-488(%rbp), %r8         ## 8-byte Reload
	movl	%eax, -492(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movl	$8, %r9d
	movl	%r9d, %ecx
	leaq	-336(%rbp), %rdx
	movq	%rdx, %rsi
	addq	$4, %rsi
	leaq	L_.str.9(%rip), %rdi
	movq	%rsi, -504(%rbp)        ## 8-byte Spill
	movq	%rdx, %rsi
	movq	%rcx, %rdx
	movq	-504(%rbp), %r8         ## 8-byte Reload
	movq	%rcx, -512(%rbp)        ## 8-byte Spill
	movq	%r8, %rcx
	movq	-512(%rbp), %r8         ## 8-byte Reload
	movl	%eax, -516(%rbp)        ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movq	___stack_chk_guard@GOTPCREL(%rip), %rcx
	movq	(%rcx), %rcx
	movq	-40(%rbp), %rdx
	cmpq	%rdx, %rcx
	movl	%eax, -520(%rbp)        ## 4-byte Spill
	jne	LBB0_2
## %bb.1:
	addq	$512, %rsp              ## imm = 0x200
	popq	%rbx
	popq	%r12
	popq	%r14
	popq	%r15
	popq	%rbp
	retq
LBB0_2:
	callq	___stack_chk_fail
	ud2
	.cfi_endproc
                                        ## -- End function
	.globl	_get_bio                ## -- Begin function get_bio
	.p2align	4, 0x90
_get_bio:                               ## @get_bio
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$48, %rsp
	movq	%rdi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movq	%rdx, -24(%rbp)
	leaq	L_.str.10(%rip), %rdi
	movb	$0, %al
	callq	_printf
	movq	-8(%rbp), %rsi
	leaq	L_.str.11(%rip), %rdi
	movl	%eax, -28(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_scanf
	leaq	L_.str.12(%rip), %rdi
	movl	%eax, -32(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movq	-16(%rbp), %rsi
	leaq	L_.str.13(%rip), %rdi
	movl	%eax, -36(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_scanf
	leaq	L_.str.14(%rip), %rdi
	movl	%eax, -40(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_printf
	movq	-24(%rbp), %rsi
	leaq	L_.str.15(%rip), %rdi
	movl	%eax, -44(%rbp)         ## 4-byte Spill
	movb	$0, %al
	callq	_scanf
	movl	%eax, -48(%rbp)         ## 4-byte Spill
	addq	$48, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_vowels                 ## -- Begin function vowels
	.p2align	4, 0x90
_vowels:                                ## @vowels
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$80, %rsp
	movq	%rdi, -8(%rbp)
	leaq	L_.str.16(%rip), %rdi
	movq	%rdi, -40(%rbp)
	movl	$0, -24(%rbp)
	movl	$0, -12(%rbp)
LBB2_1:                                 ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB2_3 Depth 2
	movslq	-12(%rbp), %rax
	movq	-8(%rbp), %rdi
	movq	%rax, -48(%rbp)         ## 8-byte Spill
	callq	_strlen
	movq	-48(%rbp), %rdi         ## 8-byte Reload
	cmpq	%rax, %rdi
	jae	LBB2_10
## %bb.2:                               ##   in Loop: Header=BB2_1 Depth=1
	movl	$0, -16(%rbp)
LBB2_3:                                 ##   Parent Loop BB2_1 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movslq	-16(%rbp), %rax
	movq	-40(%rbp), %rdi
	movq	%rax, -56(%rbp)         ## 8-byte Spill
	callq	_strlen
	movq	-56(%rbp), %rdi         ## 8-byte Reload
	cmpq	%rax, %rdi
	jae	LBB2_8
## %bb.4:                               ##   in Loop: Header=BB2_3 Depth=2
	movq	-8(%rbp), %rax
	movslq	-12(%rbp), %rcx
	movsbl	(%rax,%rcx), %edx
	movq	-40(%rbp), %rax
	movslq	-16(%rbp), %rcx
	movsbl	(%rax,%rcx), %esi
	cmpl	%esi, %edx
	jne	LBB2_6
## %bb.5:                               ##   in Loop: Header=BB2_3 Depth=2
	movl	-24(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -24(%rbp)
LBB2_6:                                 ##   in Loop: Header=BB2_3 Depth=2
	jmp	LBB2_7
LBB2_7:                                 ##   in Loop: Header=BB2_3 Depth=2
	movl	-16(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -16(%rbp)
	jmp	LBB2_3
LBB2_8:                                 ##   in Loop: Header=BB2_1 Depth=1
	jmp	LBB2_9
LBB2_9:                                 ##   in Loop: Header=BB2_1 Depth=1
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	jmp	LBB2_1
LBB2_10:
	movl	-24(%rbp), %eax
	addl	$1, %eax
	movslq	%eax, %rdi
	callq	_malloc
	movq	%rax, -32(%rbp)
	movl	$0, -12(%rbp)
	movl	$0, -20(%rbp)
LBB2_11:                                ## =>This Loop Header: Depth=1
                                        ##     Child Loop BB2_13 Depth 2
	movslq	-12(%rbp), %rax
	movq	-8(%rbp), %rdi
	movq	%rax, -64(%rbp)         ## 8-byte Spill
	callq	_strlen
	movq	-64(%rbp), %rdi         ## 8-byte Reload
	cmpq	%rax, %rdi
	jae	LBB2_20
## %bb.12:                              ##   in Loop: Header=BB2_11 Depth=1
	movl	$0, -16(%rbp)
LBB2_13:                                ##   Parent Loop BB2_11 Depth=1
                                        ## =>  This Inner Loop Header: Depth=2
	movslq	-16(%rbp), %rax
	movq	-40(%rbp), %rdi
	movq	%rax, -72(%rbp)         ## 8-byte Spill
	callq	_strlen
	movq	-72(%rbp), %rdi         ## 8-byte Reload
	cmpq	%rax, %rdi
	jae	LBB2_18
## %bb.14:                              ##   in Loop: Header=BB2_13 Depth=2
	movq	-8(%rbp), %rax
	movslq	-12(%rbp), %rcx
	movsbl	(%rax,%rcx), %edx
	movq	-40(%rbp), %rax
	movslq	-16(%rbp), %rcx
	movsbl	(%rax,%rcx), %esi
	cmpl	%esi, %edx
	jne	LBB2_16
## %bb.15:                              ##   in Loop: Header=BB2_13 Depth=2
	movq	-8(%rbp), %rax
	movslq	-12(%rbp), %rcx
	movb	(%rax,%rcx), %dl
	movq	-32(%rbp), %rax
	movl	-20(%rbp), %esi
	movl	%esi, %edi
	addl	$1, %edi
	movl	%edi, -20(%rbp)
	movslq	%esi, %rcx
	movb	%dl, (%rax,%rcx)
LBB2_16:                                ##   in Loop: Header=BB2_13 Depth=2
	jmp	LBB2_17
LBB2_17:                                ##   in Loop: Header=BB2_13 Depth=2
	movl	-16(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -16(%rbp)
	jmp	LBB2_13
LBB2_18:                                ##   in Loop: Header=BB2_11 Depth=1
	jmp	LBB2_19
LBB2_19:                                ##   in Loop: Header=BB2_11 Depth=1
	movl	-12(%rbp), %eax
	addl	$1, %eax
	movl	%eax, -12(%rbp)
	jmp	LBB2_11
LBB2_20:
	movq	-32(%rbp), %rax
	movslq	-20(%rbp), %rcx
	movb	$0, (%rax,%rcx)
	movq	-32(%rbp), %rax
	addq	$80, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.globl	_main                   ## -- Begin function main
	.p2align	4, 0x90
_main:                                  ## @main
	.cfi_startproc
## %bb.0:
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset %rbp, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register %rbp
	subq	$32, %rsp
	movl	$0, -4(%rbp)
	movl	%edi, -8(%rbp)
	movq	%rsi, -16(%rbp)
	movl	$5, %edi
	callq	_compute
Ltmp0:                                  ## Block address taken
## %bb.1:
	leaq	L_.str.17(%rip), %rdi
	xorl	%eax, %eax
	movb	%al, %cl
	leaq	Ltmp0(%rip), %rsi
	movb	%cl, %al
	callq	_printf
	xorl	%edx, %edx
	movl	%eax, -20(%rbp)         ## 4-byte Spill
	movl	%edx, %eax
	addq	$32, %rsp
	popq	%rbp
	retq
	.cfi_endproc
                                        ## -- End function
	.section	__TEXT,__cstring,cstring_literals
L_.str:                                 ## @.str
	.asciz	"rsp = %p, rbp = %p, stack size = %lu\n"

L_.str.1:                               ## @.str.1
	.asciz	"Stack frame starts at address %p\n\n"

L_.str.2:                               ## @.str.2
	.asciz	"1. nums2 starts at address %p, frame offset %ld, ends at address %p, frame offset %ld\n"

L_.str.3:                               ## @.str.3
	.asciz	"2. nums starts at address %p, frame offset %ld, ends at address %p, frame offset %ld\n"

L_.str.4:                               ## @.str.4
	.asciz	"3. return address (%%rbp + 8) is %02x%02x%02x%02x%02x%02x%02x%02x (appears reverse on a little-endian system)\n\n"

L_.str.5:                               ## @.str.5
	.asciz	"1. &nums is %p, sizeof %lu, &nums + 1 is %p, sizeof %lu\n"

L_.str.6:                               ## @.str.6
	.asciz	"2. nums is %p, sizeof %lu, nums + 1 is %p, sizeof %lu\n"

L_.str.7:                               ## @.str.7
	.asciz	"3. nums[0] is %p, sizeof %lu, nums[0] + 1 is %p, sizeof %lu\n"

L_.str.8:                               ## @.str.8
	.asciz	"4. &nums[0] is %p, sizeof %lu, &nums[0] + 1 is %p, sizeof %lu\n"

L_.str.9:                               ## @.str.9
	.asciz	"6. &nums[0][0] is %p, sizeof %lu, &nums[0][0] + 1 is %p, sizeof %lu\n\n"

L_.str.10:                              ## @.str.10
	.asciz	"Enter your first name: "

L_.str.11:                              ## @.str.11
	.asciz	"%s"

L_.str.12:                              ## @.str.12
	.asciz	"Enter your graduation year: "

L_.str.13:                              ## @.str.13
	.asciz	"%d"

L_.str.14:                              ## @.str.14
	.asciz	"Enter your current GPA: "

L_.str.15:                              ## @.str.15
	.asciz	"%f"

L_.str.16:                              ## @.str.16
	.asciz	"aeiouAEIOU"

L_.str.17:                              ## @.str.17
	.asciz	"Next instruction after a call to compute() is at address %p\n"


.subsections_via_symbols
