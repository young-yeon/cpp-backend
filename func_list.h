#pragma once

#include "main.h"

// METHOD PARSER
map<string, string> parser(const string& route);

/*
* 
* get (select)		: nothing
* post (insert)		: x-www-form-urlencoded
* put (update)		: uri-data (/api?no=<int>) / x-www-form-urlencoded
* delete (delete)	: uri-data (/api?no=<int>)
*
* --------------- ROUTE ---------------
*   /		helloWorld
*   /nyy	nyy
*   /api	insert <GET, POST, PUT, DELETE>
* -------------------------------------
*
*/

void helloWorld(char *text);
void nyy(char *text);
void api(char *text, REQUEST_HEADER head, sqlite3 *DB);
