/*
	프로젝트명	: C/C++을 이용한 경량 웹서버 제작
	제작자		: 나영연
	제작 기간	: 2019.08.16 ~
*/

#pragma once

// Default settings for SERVER
#define IP_ADDRESS "127.0.0.1"
#define PORT 80
#define DEBUG_MODE_PRINT_ALLBUF false
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
	char Host[50] = " ";
	char Date[50] = " ";
	char CacheControl[50] = " ";
	char Connection[50] = " ";
	char ContentLength[5] = " ";
	char ContentType[50] = " ";
	char ContentLanguage[50] = " ";
	char ContentEncoding[30] = " ";
	
	// Request Header
	char SecFetchMode[30] = " ";
	char UserAgent[150] = " ";
	char Cookie[200] = " ";
	char Referer[50] = " ";
	char Authorization[50] = " ";
	char Origin[50] = " ";
	char Accept[150] = " ";
	char AcceptCharset[15] = " ";
	char AcceptEncoding[15] = " ";
	char AcceptLanguage[15] = " ";

	// Method
	char Method[10] = " ";

	// Route
	char uri[500] = " ";
	char Route[50] = " ";
	char uri_data[450] = " ";

	// Content
	char data[500] = " ";
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