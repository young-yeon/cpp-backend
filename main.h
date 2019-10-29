/*
	프로젝트명	: C/C++을 이용한 경량 웹서버 제작
	제작자		: 나영연
	제작 기간	: 2019.08.16 ~
*/

#pragma once

// Default settings for SERVER
#define IP_ADDRESS "127.0.0.1"
#define PORT 80
#define DEBUG_MODE_PRINT_ALLBUF true
#define DEBUG_MODE_PRINT_ROUTE false
#define DEBUG_MODE_PRINT_DATA false
#define DEBUG_MODE_PRINT_GENERALHEADER false
#define DEBUG_MODE_PRINT_REQUESTHEADER false
#define BUF_SIZE 2048
#define THREAD 10
#define ListenQ 10
#define _CRT_SECURE_NO_WARNINGS true

#define HOST_NLEN 30
#define HOST_MCNT 10

// SIGNALS
#define USER_QUIT 0
#define INV_SOCK -1
#define LISTEN_FAIL -2
#define ACCEPT_FAIL -3
#define THREAD_FAIL -4
#define BIND_FAIL -5
#define DB_ERROR -6

#define NOTHING 1
#define NONE 0

// ALLOW HOSTS
const char ALLOW_HOSTS[HOST_NLEN][HOST_MCNT] = {
	"*"
	// "localhost",
	// "127.0.0.1",
	// "*" ALLOW ALL HOSTS
};

// HEADERS
#include <iostream>
#include <map>
#include <vector>
#include <thread>
#include <iterator>
#include <sstream>
#include <WinSock2.h>
#include <conio.h>
#include <windows.h>
// SQLite3 DB
#include "sqlite3/sqlite3.h"
#pragma comment(lib, "sqlite3/sqlite3.lib")

using namespace std;

// STRUCTURES
struct REQUEST_HEADER {
	// General Header
	char Host[50] = "NULL";
	char Date[50] = "NULL";
	char CacheControl[50] = "NULL";
	char Connection[50] = "NULL";
	char ContentLength[5] = "NULL";
	char ContentType[50] = "NULL";
	char ContentLanguage[50] = "NULL";
	char ContentEncoding[30] = "NULL";
	
	// Request Header
	char SecFetchMode[30] = "NULL";
	char UserAgent[150] = "NULL";
	char Cookie[200] = "NULL";
	char Referer[50] = "NULL";
	char Authorization[50] = "NULL";
	char Origin[50] = "NULL";
	char Accept[150] = "NULL";
	char AcceptCharset[15] = "NULL";
	char AcceptEncoding[15] = "NULL";
	char AcceptLanguage[15] = "NULL";

	// Method
	char Method[10] = "NULL";

	// Route
	char uri[500] = "NULL";
	char Route[50] = "NULL";
	char uri_data[450] = "NULL";

	// Content
	char data[500] = "NULL";
};

// FUNCTIONS
void response(SOCKET *accept, sqlite3 *DB);
void clean();
void seeOptions();
int createThread(int TID, SOCKET *accept, sqlite3 *DB);
int serverSocket();
REQUEST_HEADER headerParse(char *text);
void searchText(char *text, const char *target, char *result);
bool hostChecker(const char *target);
void router(REQUEST_HEADER head, sqlite3 *DB, char *result);