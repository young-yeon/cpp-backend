#include "func_list.h"

void router(REQUEST_HEADER head, sqlite3 *DB, char *result) {
	if (!strcmp(head.Route, "/")) return helloWorld(result);
	if (!strcmp(head.Route, "/nyy")) return nyy(result);
	if (!strcmp(head.Route, "/api")) return api(result, head, DB);
	memset(result, 0, sizeof(result));
	sprintf(result, "HTTP/1.1 404 Notfound\r\n");
}