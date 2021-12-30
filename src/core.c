#include "../include/cpy.h"

void cpyErr(const char* e_msg, bool crash) {
	print("libcpy error: ", e_msg);
	if (crash) exit(-1);
}
