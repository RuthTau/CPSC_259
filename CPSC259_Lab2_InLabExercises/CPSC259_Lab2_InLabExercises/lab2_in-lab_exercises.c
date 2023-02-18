/*
 File:				lab2_in-lab_exercises.c
 Purpose:			Implementation of functions for lab 2 in-lab exercises
 Author:       Ruth Tau and Tessa Clement
 Student Numbers: 37100518 and 61619698
 CS Accounts:     tyy and tessa42
 Date:            29 Sep 2022
*/


#include "lab2_in-lab_exercises.h"
#include <stdlib.h>
#include <string.h>

/*
 * Let's start with something easy.  There are 3 unit tests
 * for this function.
 *
 * Swaps the contents of two integer variables using pointers
 *
 * PARAM:     first_int is a pointer to an int
 * PARAM:     second_int is a pointer to an int
 * PRE:       both pointers are valid pointers to int
 * POST:      the contents of two integer variables are swapped
 * RETURN:    VOID
 */
void swap_ints(int* first_int, int* second_int)
{
  int temp;
  temp = *first_int;
  *first_int = *second_int;
  *second_int = temp;
}

/*
 * Now let's try something a little more challenging.
 *
 * Reverses the contents of the string passed to the
 * function.  Does not move the terminating null '\0'
 * character.
 *
 * PARAM:     string is a pointer to an array of char (a string)
 * PRE:       the array of char terminates with a null '\0'
 * POST:      the char array has been reversed
 * RETURN:    VOID
 */
void reverse_string(char* string)
{
	int length_scan = 0;

	length_scan = strlen(string);

	char * begin, * end;

	begin = string;
	end = string+ length_scan-1 ;

	for (int i = 0; i < (length_scan / 2); i++) {

		// swap use char type

		char temp;
		temp = *begin; //with &* is the value inside the variable
		*begin = *end;
		*end = temp;

		begin++;
		end--;
	}
	
}





/*
 * Let's see how well you read the lab document.
 *
 * Determines if candidate contains sample, and returns
 * 1 if  it does, and 0 if it does not.
 *
 * PARAM:     candidate is a pointer to an array of char (a string)
 * PARAM:     sample is a pointer to an array of char (a string)
 * PRE:       the arrays of char terminate with a null '\0'
 * PRE:       candidate != NULL; sample != NULL
 * POST:      N/A
 * RETURN:    IF candidate contains sample THEN 1
 *            ELSE 0.
 */
int contains_sample(char* candidate, char* sample)
{
	char* result = NULL;
	if (candidate != NULL & sample != NULL) {
		result = strstr(candidate, sample);
		if (result != NULL) {
			return 1;
		}
	}
	else return 0;
}

/*
 * Returns the first index where sample is located inside the
 * candidate.  For example:
 * IF candidate = "Hello", sample = "Hello", RETURNS 0
 * IF candidate = "soupspoon", sample = "spoon", RETURNS 4
 * IF candidate = "ACGTACGTA", sample = "CGT", RETURNS 1
 * IF candidate = "CGTACGTA", sample = "CGTT", returns -1
 *
 * PARAM:     candidate is a pointer to an array of char (a string)
 * PARAM:     sample is a pointer to an array of char (a string)
 * PRE:       the arrays of char terminate with a null '\0'
 * POST:      N/A
 * RETURN:    IF candidate contains sample
 *            THEN the index where the first letter of sample is inside candidate
 *            ELSE -1.
 */
int find_index(char* candidate, char* sample)
{
	char* result = NULL;
	int index = -1;
	result = strstr(candidate, sample);
	if (result != NULL) {
		for (index = 0; candidate < result; index++)
			candidate++;
	}
	return index;
}