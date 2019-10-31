#include "func_list.h"

void helloWorld(char* text) {
	memset(text, 0, sizeof(text));
	sprintf(text,
		"HTTP/1.1 200 OK\r\n"
		"Content-Length : 28\r\n"
		"Content-Type : text/html;charset=utf-8\r\n"
		"\r\n"
		"<h3><b>HELLO WORLD!</b></h3>\r\n");
}