// CS2100 Computer Organisation
// AY2025/2026 Semester 1
// National University of Singapore.
// Assignment 1 Question 1.
// All rights reserved.
//
// Start by filling in the following variables which main() will print out so as to identify yourself.
// Failure to full in the details correctly will be penalised.
//

const char *student_number = "A0308974N";
const char *student_name = "Ng Jun Hao";
const char *student_tut_grp = "28";

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

/**
 * @brief Checks if the input string is valid in the base given.
 *
 *        For simplicity, we shall only use lower case alphabets for digits beyound '9'.
 *
 * @param str      A NULL terminated C string.
 * @param base     The base of the digits in str.
 *
 * @returns        1 if the string is valid in the base, 0 otherwise
 * 
 * @note           Know your ASCII table. The ASCII value for the character '0' is not the value 0.
 *
 */
int check_inpstr(const char *str, int base)
{
	//loop over string until \0
    while(*str != '\0') {
		//if char is between 0 to 9
		if ('0' <= *str && *str <= '9') {
			//if its ascii value - 0's ascii value, which gives the number,
			//is greater or = the base, it is invalid
			if (*str - '0' >= base) {
				return 0;
			}
		//if char is between a to f	       
		} else if ('a' <= *str && *str <= 'f') {
			//if its ascii value - a's ascii value, which gives the its relative
			//position from a, is greater or = the base - 10, which gives
			//the bases relative position from 10, it is invalid
            if (*str - 'a' >= base - 10) {
                return 0;
            }
		//if the char not between 0 to 9 or a to f its is immediately invalid.
        } else {
            return 0;
        }
		//increment the pointer to check the next char of the string
		str++;
    }
	//after going through all chars if its not invalid then returns valid.
    return 1;
}

int char_to_val(char c) {
	//by this point all values are already checked to be in the
	//correct base. This just maps them to their number value.
	switch(c) {
		case '0': return 0;
		case '1': return 1;
		case '2': return 2;
		case '3': return 3;
		case '4': return 4;
		case '5': return 5;
		case '6': return 6;
		case '7': return 7;
		case '8': return 8;
		case '9': return 9;
		case 'a': return 10;
		case 'b': return 11;
		case 'c': return 12;
		case 'd': return 13;
		case 'e': return 14;
		case 'f': return 15;
		default: return 0;
	}
}

char val_to_char(int val) {
	//convert a value to its respective char
	switch(val) {
		case 0: return '0';
		case 1: return '1';
		case 2: return '2';
		case 3: return '3';
		case 4: return '4';
		case 5: return '5';
		case 6: return '6';
		case 7: return '7';
		case 8: return '8';
		case 9: return '9';
		case 10: return 'a';
		case 11: return 'b';
		case 12: return 'c';
		case 13: return 'd';
		case 14: return 'e';
		case 15: return 'f';
		default: return '0';
	}
}

uint64_t to_base_10(const char *number, int base) {
	//initialise the result variable
	uint64_t result = 0;
	 	//loop through the number's string until \0
        while(*number != '\0') {
				//multiply current result by base
                result *= base;
				//add the next digit
                result += char_to_val(*number);
				//increment number pointer to go to next char
				number++;
        }
        return result;
}

int to_new_base(uint64_t number, int base, int *arr, int size) {
	//initialise a counter and remainder to 0
	int counter = 0;
	int remainder = 0;
	//loops while the number is greater than 0, uses the method in the lecture
	while (number > 0) {
		//gets the remainder
		remainder = number % base;
		//divides the number by the base
		number /= base;
		//store in the array the remainder then increments the counter
		arr[counter++] = remainder;
		//if counter is bigger than max_outputlen - 1 theres not enough space for \0, returns error
		if (counter >= size - 1) {
			printf("Error, output max length exceeded");
			exit(-1);
		}
	}
	//currently we have the remainders stored from LSB to MSB
	//for loop to swap the order, method from the tutorial
	for (int i = 0; i < counter / 2; i++) {
        int tmp = arr[i];
        arr[i] = arr[counter - 1 - i];
        arr[counter - 1 - i] = tmp;
    }

	//returns the number of digits to be used later
	return counter;

}

void int_array_to_string(int *arr, int size, char *output) {
	//initialise a result pointer to point to output
	char *result = output;
	//for loop over the tempArray and converting each number to a char and storing in output
	for (int i = 0;  i < size; i++) {
		result[i] = val_to_char(arr[i]);
	}
	//adds \0 to the end of the string to signify the end
	result[size] = '\0';
}



/**
 * @brief Performs unsigned addition using 64-bit data type uint64_t.
 *
 * This function performs the addition of the two numbers given by the user in their
 * respective bases, and outputs the result as a printable string in the base 
 * desired by the user.
 *
 * @param output        Pointer to the output string.
 * @param output_maxlen The maximum number of characters in 'output'. This strictly must not
 *                      be exceeded.
 * @param r_out         Desired base of the output.
 * @param src1          The first operand in the form of a string of digits in the base of
 *                      given by the user.
 * @param r_src1        The base of the digits in src1.
 * @param src2          The first operand in the form of a string of digits in the base of
 *                      given by the user.
 * @param r_src2        The base of the digits in src2.
 *
 * @returns             None. This is a void function.
 *
 * @note Use uint64_t for your internal operations as the sum may exceed what 32 bits can represent.
 *
 * @note Watch out for how the MSB is handled when converting to and from uint64_t.
 *
 **/
void perform_u64_addition(char *output, int output_maxlen, int r_out, 
		          const char *src1, int r_src1, const char *src2, int r_src2)
{
	//converts both src into base 10 uint64_t
	uint64_t src1Value = to_base_10(src1, r_src1);
	uint64_t src2Value = to_base_10(src2, r_src2);

	//initialise a temp array that will be used to store the integer version of the final result
	int tempArray[output_maxlen];

	//add the values in base 10
	uint64_t totalValue = src1Value + src2Value;

	//if result is 0 immediately set output to 0 and return
	if (totalValue == 0) {
		if (output_maxlen < 2) {
			exit(-1);
		}
		output[0] = '0';
		output[1] = '\0';
		return;
	}

	//converts totalValue to the new base storing it in tempArray and having size number of digits
	int size = to_new_base(totalValue, r_out, tempArray, output_maxlen);

	//takes the tempArray and converts it into a string and stores it in ouput
	int_array_to_string(tempArray, size, output);
}


