#pragma once

#include "main.h"

// METHOD PARSER
map<string, string> parser(const string& route);

/*
* 
* get (insert)	: params
* post (insert)	: x-www-form-urlencoded
* put (update)	: x-www-form-urlencoded
* delete (drop)	: x-www-form-urlencoded
*
* --------------- ROUTE ---------------
*   /				helloWorld
*   /nyy			nyy
*   /insert			insert <GET, POST>
* -------------------------------------
*
*/

void helloWorld(char *text);
void nyy(char *text);
void insert(char *text, REQUEST_HEADER head, sqlite3 *DB);
