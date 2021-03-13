/* This script is a template for testing and 
 * proving the implementations of "libavoidrepitition.h".
 *
 * 
 * This script aims to test any update to any
 * implementation.
 * 
 * Usage: Add your test at the end.
 *        Remember, a tester's work is to break the program.
 */

#include <stdio.h>
#include "libavoidrepitition.h"

// To-do: 
// 		- functions for all the implemented builtins.
//		- taking input differently for different functions.



int main() {	
	printf("Unit Testing of libavoidrepitition.h:\n\n");

	char implemented[20][128]=
	 {	
			"[1] assert(expression)        :: True | False",
			"[2] file_read(char* filename) :: File's content",
			"[3] int_str(int)              :: Converts int to str",
			"[4] len(array)                :: Length of the array",
			"[5] substr(str, substr)       :: substr (up to matched)",
			"[6] sum(array, len(array))    :: Sum of the array of numbers",
			"[7] typeof(variable name)     :: Integer corresponding to a type",
	
	};
	for (int i=0; i < len(implemented); i++) {
		printf("%s\n", implemented[i]);
	}


	// To-do:
	// switch-case in order to be able to specify the tests.
	// then just invoke the functions.
	
	return 0;
}
