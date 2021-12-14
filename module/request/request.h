#ifndef REQUEST_H
#define REQUEST_H




#include <curl/curl.h>
#include "cpy/cpy.h"

extern bool REQUEST_OK;



char* request_post(const char* URL, const char* PostData);




#endif // #ifndef REQUEST_H
