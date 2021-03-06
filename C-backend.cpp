#include "main.h"

int main() {
	printf("[   :: Project C-Backend ::   ]\n");
	printf("[ SERVER : %s:%d ]\n", IP_ADDRESS, PORT);
	printf("[ THREAD COUNT : %d ]\n\n", THREAD);
	printf("<< press 'o' to see options >>\n");
	printf("<< press 'q' to close >>\n\n");

	thread killSIG(&clean);
	thread option(&seeOptions);

	int ERROR_CODE = serverSocket();
	switch (ERROR_CODE) {
		case INV_SOCK:
			printf("[!] INVALID SOCKET!\n"); break;
		case BIND_FAIL:
			printf("[!] CANNOT BIND SOCKET!\n"); break;
		case LISTEN_FAIL:
			printf("[!] LISTEN FAIL!\n"); break;
		case ACCEPT_FAIL:
			printf("[!] ACCEPT FAIL!\n"); break;
		case THREAD_FAIL:
			printf("[!] THREAD KILLED!\n"); break;
		case DB_ERROR:
			printf("[!] DB OPEN FAIL!\n"); break;
	}
	WSACleanup();
    return 0;
}

void clean() {
	while (true)
		if (_kbhit() && _getch() == 'q') break;
	WSACleanup();
	printf("[!] SERVER CLOSE\n");
	exit(0);
}

void seeOptions() {
	while (true) {
		while (true)
			if (_kbhit() && _getch() == 'o') break;
		printf("[*] ===== OPTIONS =====\n\n");
		printf(" SERVER ADDR : %s:%d\n\n", IP_ADDRESS, PORT);
		printf(" DEBUG MODES -----\n");
		if (DEBUG_MODE_PRINT_ALLBUF)
			printf("\t PRINT ALL BUFFER\n");
		if (DEBUG_MODE_PRINT_ROUTE)
			printf("\t PRINT METHOD & ROUTE\n");
		if (DEBUG_MODE_PRINT_DATA)
			printf("\t PRINT RECVED DATA\n");
		if (DEBUG_MODE_PRINT_GENERALHEADER)
			printf("\t PRINT GENERAL HEADERS\n");
		if (DEBUG_MODE_PRINT_REQUESTHEADER)
			printf("\t PRINT REQUEST HEADERS\n");
		printf(" BUFFER SIZE : %dbyte\n\n", BUF_SIZE);
		printf(" THREADS : %d\tListenQ : %d\n\n", THREAD, ListenQ);
		printf(" ALLOW HOSTS -----\n");
		if (ALLOW_HOSTS[0] == "*") printf("\t ALL\n");
		else for (int i = 0; ALLOW_HOSTS[i][0] != NULL; i++)
			printf("\t (%d) %s\n", i + 1, ALLOW_HOSTS[i]);
		printf("\n[*] ===================\n");
	}
}