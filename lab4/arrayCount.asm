#arrayCount.asm
  .data 
arrayA: .word 11, 0, 31, 22, 9, 17, 6, 9   # arrayA has 8 values
count:  .word 0             # dummy value

  .text
main:
    # code to setup the variable mappings
    la $t0, arrayA
    la $t8, count
   
    # code for reading in the user value X
    li $v0, 5
    syscall
    add $t6, $0, $v0  #t6 = user value X

    # code for counting multiples of X in arrayA
    addi $t1, $0, 8  #t1 = limit
    addi $t2, $0, 0  #t2 = loop counter
    addi $t5, $t6, -1  #t5 = mask
    lw $t7, 0($t8)  #t7 = result
loop:
    beq $t2, $t1, end
    lw $t4, 0($t0)    #t4 = arr[0]
    addi $t9, $0, 10
    and $a2, $t5, $t4   #a2 = remainder
    bne $a2, $0, skip
    addi $t7, $t7, 1   #t7++
skip:
    addi $t2, $t2, 1
    addi $t0, $t0, 4
    j loop
end:
    # code for printing result
    li $v0, 1
    addi $a0, $t7, 0
    syscall

    # code for terminating program
    li  $v0, 10
    syscall
