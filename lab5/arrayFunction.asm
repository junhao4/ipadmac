# arrayFunction.asm
       .data 
array: .word 8, 2, 1, 6, 9, 7, 3, 5, 0, 4
newl:  .asciiz "\n"

       .text
main:
	# Print the original content of array
	# setup the parameter(s)

	la $a0, array
	addi $a1, $0, 10

	# call the printArray function
	
	jal printArray	

	# Ask the user for two indices
	li   $v0, 5         	# System call code for read_int
	syscall           
	addi $t0, $v0, 0    	# first user input in $t0
 
	li   $v0, 5         	# System call code for read_int
	syscall           
	addi $t1, $v0, 0    	# second user input in $t1

	# Call the findMin function
	# setup the parameter(s)

	la $a0, array
	sll $t0, $t0, 2
	add $a0, $a0, $t0
	sll $t1, $t1, 2
	add $a1, $a0, $t1

	# call the function

	jal findMin

	# Print the min item
	# place the min item in $t3	for printing
	addi $t3, $a0 ,0

	# Print an integer followed by a newline
	li   $v0, 1   		# system call code for print_int
    addi $a0, $t3, 0    # print $t3
    syscall       		# make system call

	li   $v0, 4   		# system call code for print_string
    la   $a0, newl    	# 
    syscall       		# print newline

	#Calculate and print the index of min item
	
	# Place the min index in $t3 for printing	
	addi $t3, $a1, 0

	# Print the min index
	# Print an integer followed by a newline
	li   $v0, 1   		# system call code for print_int
    addi $a0, $t3, 0    # print $t3
    syscall       		# make system call
	
	li   $v0, 4   		# system call code for print_string
    la   $a0, newl    	# 
    syscall       		# print newline
	
	# End of main, make a syscall to "exit"
	li   $v0, 10   		# system call code for exit
	syscall	       		# terminate program
	

#######################################################################
###   Function printArray   ### 
#Input: Array Address in $a0, Number of elements in $a1
#Output: None
#Purpose: Print array elements
#Registers used: $t0, $t1, $t2, $t3
#Assumption: Array element is word size (4-byte)
printArray:
	addi $t1, $a0, 0	# $t1 is the pointer to the item
	sll  $t2, $a1, 2	# $t2 is the offset beyond the last item
	add  $t2, $a0, $t2 	# $t2 is pointing beyond the last item
l1:	
	beq  $t1, $t2, e1
	lw   $t3, 0($t1)	# $t3 is the current item
	li   $v0, 1   		# system call code for print_int
    addi $a0, $t3, 0   	# integer to print
    syscall       		# print it
	addi $t1, $t1, 4
	j    l1				# Another iteration
e1:
	li   $v0, 4   		# system call code for print_string
    la   $a0, newl    	# 
    syscall       		# print newline
	jr   $ra			# return from this function


#######################################################################
###   Student Function findMin   ### 
#Input: Lower Array Pointer in $a0, Higher Array Pointer in $a1
#Output: $v0 contains the address of min item 
#Purpose: Find and return the minimum item 
#              between $a0 and $a1 (inclusive)
#Registers used: <Fill in with your register usage>
#Assumption: Array element is word size (4-byte), $a0 <= $a1
findMin:
	lw $t0, 0($a0)     #t0 = min
	addi $a0, $a0, 4
	addi $t4, $0, 0    #t4 = res indx
	addi $t5, $0, 1    #t5 = loop i
loop:
	beq $a0, $a1, exit
	lw $t1, 0($a0)    #t1 = arr[i]
	slt $t2, $t1, $t0
	beq $t2, $0, skip
	addi $t0, $t1, 0
	addi $t4, $t5, 0
skip:
	addi $a0, $a0, 4
	addi $t5, $t5, 1
	j loop
	
exit:
	addi $a0, $t0, 0
	addi $a1, $t4, 0
	jr $ra			# return from this function
