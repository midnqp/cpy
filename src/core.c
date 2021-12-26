#include "cpy.h"

void cpy_error(const char* e_msg, bool crash) {
	print("libcpy error: ", e_msg);
	if (crash) exit(-1);
}
