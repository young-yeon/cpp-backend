#include "func_list.h"

void nyy(char *text) {
	memset(text, 0, sizeof(text));
	sprintf(text,
		"HTTP/1.1 200 OK\r\n"
		"Content-Length: 35\r\n"
		"Content-Type: text/html;charset=utf-8\r\n"
		"\r\n"
		"{\"name\":\"youngyeon\",\"text\":\"TEST!\"}\r\n");
}