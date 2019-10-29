#include "func_list.h"

void insert(char *text, REQUEST_HEADER head, sqlite3 *DB) {
	// GET METHOD
	if (!strcmp(head.Method, "GET")) {
		string udata(head.uri_data);
		map<string, string> data = parser(udata);

		const char *name = "name", *id = "id", *memo = "memo";
		bool check_name = true, check_id = true, check_memo = true;

		for (auto it = data.begin(); it != data.end(); it++) {
			if (!strcmp((it->first).c_str(), "name") && check_name) {
				name = (it->second).c_str();
				check_name = false;
			}
			if (!strcmp((it->first).c_str(), "id") && check_id) {
				id = (it->second).c_str();
				check_id = false;
				for (int i = 0; i < strlen(id); i++)
					if (!('0' <= id[i] && id[i] <= '9')) check_id = true;
			}
			if (!strcmp((it->first).c_str(), "memo") && check_memo) {
				memo = (it->second).c_str();
				check_memo = false;
			}
		}

		memset(text, 0, sizeof(text));
		if ((!check_name) && (!check_id) && (!check_memo)) {
			char tmp[1024];
			sprintf(tmp, "{\"name\":\"%s\",\"id\":%s,\"memo\":\"%s\"}",
				name, id, memo);
			sprintf(text,
				"HTTP/1.1 200 OK\r\n"
				"Content-Length : %d\r\n"
				"Content-Type : text/html;charset=utf-8\r\n"
				"\r\n"
				"%s\r\n",
				strlen(tmp), tmp);

			char insert[1000];
			char *errmsg;
			sprintf(insert, "INSERT INTO student_info VALUES ('%s', %s, '%s');",
				name, id, memo);
			int rc = sqlite3_exec(DB, insert, NULL, NULL, &errmsg);

			if (rc != SQLITE_OK) {
				printf("[!] SQL ERROR : %s", errmsg);
				sqlite3_free(errmsg);
			}
		}
		else {
			sprintf(text, "HTTP/1.1 404 Notfound\r\n");
		}
		
	}

	// POST METHOD
	if (!strcmp(head.Method, "POST")) {
		string tdata(head.data);
		map<string, string> data = parser(tdata);
		const char* name = "name", * id = "id", * memo = "memo";
		bool check_name = true, check_id = true, check_memo = true;

		for (auto it = data.begin(); it != data.end(); it++) {
			if (!strcmp((it->first).c_str(), "name") && check_name) {
				name = (it->second).c_str();
				check_name = false;
			}
			if (!strcmp((it->first).c_str(), "id") && check_id) {
				id = (it->second).c_str();
				check_id = false;
				for (int i = 0; i < strlen(id); i++)
					if (!('0' <= id[i] && id[i] <= '9')) check_id = true;
			}
			if (!strcmp((it->first).c_str(), "memo") && check_memo) {
				memo = (it->second).c_str();
				check_memo = false;
			}
		}

		memset(text, 0, sizeof(text));
		if ((!check_name) && (!check_id) && (!check_memo)) {
			char tmp[1024];
			sprintf(tmp, "{\"name\":\"%s\",\"id\":%s,\"memo\":\"%s\"}",
				name, id, memo);
			sprintf(text,
				"HTTP/1.1 200 OK\r\n"
				"Content-Length : %d\r\n"
				"Content-Type : text/html;charset=utf-8\r\n"
				"\r\n"
				"%s\r\n",
				strlen(tmp), tmp);

			char insert[1000];
			char* errmsg;
			sprintf(insert, "INSERT INTO student_info VALUES ('%s', %s, '%s');",
				name, id, memo);
			int rc = sqlite3_exec(DB, insert, NULL, NULL, &errmsg);

			if (rc != SQLITE_OK) {
				printf("[!] SQL ERROR : %s", errmsg);
				sqlite3_free(errmsg);
			}
		}
		else {
			sprintf(text, "HTTP/1.1 404 Notfound\r\n");
		}
	}
}