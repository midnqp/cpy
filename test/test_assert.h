#ifndef H_STDIO
#include <stdio.h>
#endif

#ifndef H_LIBAR
#include "../libavoidrepitition.h"
#endif




void test_assert()
{
	printf("--TESTING--\n");
	

	printf("--RESULT--\n%s\n", "Sorry! assert() can never pass string. See issue #8.");
}
