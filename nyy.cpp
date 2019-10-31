#include "func_list.h"

void nyy(char *text) {
	memset(text, 0, sizeof(text));
	sprintf(text,
		"HTTP/1.1 200 OK\r\n"
		"Content-Length: 45\r\n"
		"Content-Type: application/json;charset=utf-8\r\n"
		"\r\n"
		"{\"name\":\"youngyeon\",\"id\":2608,\"text\":\"TEST!\"}\r\n");
}