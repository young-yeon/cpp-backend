#include "main.h"

void response(SOCKET *accept, sqlite3 *DB) {
	SOCKET acceptSock = *accept;
	char szBuf[BUF_SIZE], szInBuf[BUF_SIZE];

	memset(szInBuf, NULL, sizeof(szInBuf));
	recv(acceptSock, szInBuf, sizeof(szInBuf), 0);
	
	if (strlen(szInBuf) > NOTHING)
		printf("[*] RECV : SUCCESS!\n");
	else {
		printf("[!] NOTHING RECEVED!\n");
		closesocket(acceptSock);
		return;
	}

	if (DEBUG_MODE_PRINT_ALLBUF) {
		printf("[DEBUG_MODE] RECV CONTENTS\n\n"
			"%s\n[DEBUG_MODE] END\n", szInBuf);
	}

	REQUEST_HEADER header = headerParse(szInBuf);
	
	if (!hostChecker(header.Host)) {
		printf("[!] HOST NOT ALLOW!\n");
		memset(szBuf, 0, sizeof(szBuf));
		sprintf(szBuf, "HTTP/1.1 403 Forbidden\r\n");
		send(acceptSock, szBuf, (int)strlen(szBuf), 0);
		closesocket(acceptSock);
		return;
	}
	
	router(header, DB, szBuf);

	send(acceptSock, szBuf, (int)strlen(szBuf), 0);

	printf("[*] SEND DATA...\n");

	closesocket(acceptSock);
}