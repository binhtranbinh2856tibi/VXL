.data
entera: .asciiz "Enter number a: "
enterb: .asciiz "Enter number b: "
result: .asciiz "Product = "
.text 
.globl main
main:
li $v0, 4
la $a0, entera
syscall
li $v0, 5
syscall
move $t0, $v0

li $v0, 4
la $a0, enterb
syscall
li $v0, 5
syscall
move $t1, $v0

mul $t2, $t0, $t1

li $v0, 4
la $a0, result
syscall
li $v0, 1
move $a0, $t2
syscall
li $v0, 10
syscall

