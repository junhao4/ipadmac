// YOU ARE NOT TO SUBMIT THIS FILE. 
// 
// It is strictly for testing your code.             
// Also, as we are doing string matching for grading, make sure any new "printf()" that you may
// have introduced for debugging is *REMOVED* before submission.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern const char *student_number, *student_name, *student_tut_grp;

// Length limit of inputs according to their bases.
// This is to make sure that the output is not too long.
const int lenLimit[17] = {
	0,  // base 0 - invalid
	0,  // base 1 - invalid
	31, // base 2
	20, // base 3
	10, // base 4
	10, // base 5
	10, // base 6
	10, // base 7
	10, // base 8
	10, // base 9
	10, // base 10 
	8,  // base 11 
	8,  // base 12 
	8,  // base 13 
	8,  // base 14
	8,  // base 15
	8   // base 16
};

// This is what you need to work on and it's definition should be in Assg1.c.
extern int check_inpstr(const char *src1, int r_src1);

extern void perform_u64_addition(char *res, int maxlen, int r_res, 
		                 const char *src1, int r_src1, const char *src2, int r_src2);

int read_base(const char *descr)
{
    int r;
    char inp[100];
    
    printf("What is the base of the %s [2-16]? ", descr);

    if (fgets(inp, sizeof(inp), stdin)) {
        r = atoi(inp);

	if ((r < 2) || (r > 16)) {
           inp[strlen(inp)-1] = 0;
           printf("What you entered '%s' is NOT acceptable. It must be a number between 2 and 16 (inclusive). Aborting...\n", inp);
	   exit(-1);
	}
    } else {
        printf("Error reading input. Aborting...\n");
	exit(-1);
    }

    return r;
}

int main(int argc, char *argv[])
{
    int r_src1, r_src2, r_res, i;
    char src1[100], src2[100], res[100];

    printf("CS2100 Assignment 1 Question 1\n");
    printf("------------------------------\n");
    printf("Unsigned addition in any base submission by:\n\n");
    printf("Student name: %s\n", student_name);
    printf("Student number: %s\n", student_number);
    printf("Tutorial group: %s\n", student_tut_grp);
    printf("======================================\n\n");

    // Read in first number's base
    r_src1 = read_base("FIRST input");
    printf("\n\n");

    // Read in second number's base
    r_src2 = read_base("SECOND input");
    printf("\n\n");

    // Read in result's base
    r_res = read_base("RESULT");
    printf("\n\n===================================\n\n");

    // Read and check first input
    printf("What is the FIRST input (in base %d)? ", r_src1);

    if (fgets(src1, sizeof(src1), stdin)) {
        // Remove the newline
	src1[strlen(src1)-1] = 0;

        if (!check_inpstr(src1, r_src1))
	{
           printf("'%s' is NOT valid in base %d. Aborting....\n", src1, r_src1);
	   exit(-1);
	}

	// Check if it exceeds the length limit
	if ((strlen(src1) == 0) || (strlen(src1) > lenLimit[r_src1])) {
           printf("\nUnfortunately, your input '%s' exceeds the base %d string length limit of %d digits. Aborting...\n", src1, r_src1, lenLimit[r_src1]);
	   exit(-1);
	}

    } else {
        printf("Error reading input. Aborting...\n");
	exit(-1);
    }

    // Read and check second input
    printf("\n\nWhat is the SECOND input (in base %d)? ", r_src2);

    if (fgets(src2, sizeof(src2), stdin)) {
        // Remove the newline
	src2[strlen(src2)-1] = 0;

        if (!check_inpstr(src2, r_src2))
	{
           printf("'%s' is NOT valid in base %d. Aborting...\n", src2, r_src2);
	   exit(-1);
	}
	//
	// Check if it exceeds the length limit
	if ((strlen(src2) == 0) || (strlen(src2) > lenLimit[r_src2])) {
           printf("\nUnfortunately, your input '%s' exceeds the base %d string length limit of %d digits. Aborting...\n", src2, r_src2, lenLimit[r_src2]);
	   exit(-1);
	}

    } else {
        printf("Error reading input. Aborting...\n");
	exit(-1);
    }

    // Now the fun begins
    perform_u64_addition(res, 20, r_res, src1, r_src1, src2, r_src2);

    printf("\n\n           >>> %s (base %d) + %s (base %d) = %s (base %d)\n", src1, r_src1, src2, r_src2, res, r_res);
}
