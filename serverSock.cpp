#include "main.h"

int serverSocket() {
	WSADATA wsadata;
	WSAStartup(MAKEWORD(2, 2), &wsadata);

	sockaddr_in serverAddress, clientAddress;
	SOCKET sockListen = socket(AF_INET, SOCK_STREAM, 0);

	// invalid socket
	if (sockListen == INVALID_SOCKET) {
		return INV_SOCK;
	}

	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	serverAddress.sin_port = htons(PORT);

	int sockBind = ::bind(sockListen, (sockaddr *)&serverAddress, sizeof(serverAddress));
	if (sockBind == SOCKET_ERROR) {
		return BIND_FAIL;
	}

	sqlite3 *stuDB;
	int retv;
	char *error;
	const char *sqlStr;
	retv = sqlite3_open(":memory:", &stuDB);
	if (retv) {
		sqlite3_close(stuDB);
		return DB_ERROR;
	}

	sqlStr = "CREATE TABLE student_info"
		"(no Integer PRIMARY KEY, name text, id Integer, memo text);";
	if (sqlite3_exec(stuDB, sqlStr, NULL, NULL, &error) != SQLITE_OK) {
		sqlite3_close(stuDB);
		sqlite3_free(error);
		return DB_ERROR;
	}

	SOCKET acceptSock[THREAD];
	int length = sizeof(serverAddress), THREAD_COUNT = 0, status;
	while (true) {
		if (listen(sockListen, ListenQ) == SOCKET_ERROR)
			return LISTEN_FAIL;
		
		acceptSock[THREAD_COUNT] = accept(sockListen, (sockaddr *)&clientAddress, &length);
		
		if (acceptSock[THREAD_COUNT] < 0)
			return ACCEPT_FAIL;
		
		if ((status = createThread(THREAD_COUNT, &acceptSock[THREAD_COUNT], stuDB)) < 0)
			return THREAD_FAIL;

		THREAD_COUNT = (THREAD_COUNT + 1) % THREAD;
	}
}

int createThread(int TID, SOCKET *accept, sqlite3 *DB) {
	printf("[*] TID : %d, RUN!\n", TID);
	thread thisThread(&response, accept, DB);
	thisThread.join();
	return NOTHING;
}
