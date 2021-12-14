#include "request.h"



bool REQUEST_OK = true;



struct string {
	char* str; 
	size_t len;
};




size_t curl_writefunc_callback(void* p, size_t size, size_t count, struct string* cResp) {
	size_t newLen = cResp->len + size * count;
	cResp->str = (char*)realloc(cResp->str, newLen + 1);

	if (cResp->str == NULL) { 
		printf("request.h :: curl_writefunc() failed - realloc\n"); 
		exit(1); 
	}
	
	memcpy(cResp->str + cResp->len, p, size * count);
	cResp->str[newLen] = '\0';
	cResp->len = newLen;

	return size * count;
}




void str_init(struct string* string) {
	string->len = 0;
	string->str = new(char*, 1);
	if (string->str == NULL) { 
		printf("request.h :: str_init() failed - malloc\n"); exit(1); 
	}
	strcpy(string->str, "");
}




char* request_post(const char* URL, const char* PostData) {
	curl_global_init(CURL_GLOBAL_DEFAULT);
	CURL* curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, URL);
	curl_easy_setopt(curl, CURLOPT_POST, 1L);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, PostData);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);	
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_writefunc_callback);
	struct string cwfResp; //curl write func : response
	str_init(&cwfResp);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &cwfResp);


	CURLcode rescode = curl_easy_perform(curl);
	if (rescode != CURLE_OK) 
		REQUEST_OK = false;

	curl_easy_cleanup(curl);
	curl_global_cleanup();

	char* rawResp = new(char*, strlen(cwfResp.str));
	strcpy(rawResp, cwfResp.str);
	free(cwfResp.str);
	return rawResp;
}
