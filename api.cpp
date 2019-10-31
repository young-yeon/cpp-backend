#include "func_list.h"

struct apiData {
	char no[20] = " ";
	char name[50] = " ";
	char id[10] = " ";
	char memo[500] = " ";
};

int no = 1; // PRIMARY KEY

int callback(void* list, int count, char** data, char** columns) {
	vector<apiData>* result = static_cast<vector<apiData>*>(list);
	apiData tmp;
	for (int i = 0; i < count; i++) {
		if (!strcmp(columns[i], "no")) sprintf(tmp.no, data[i]);
		if (!strcmp(columns[i], "name")) sprintf(tmp.name, data[i]);
		if (!strcmp(columns[i], "id")) sprintf(tmp.id, data[i]);
		if (!strcmp(columns[i], "memo")) sprintf(tmp.memo, data[i]);
	}
	result->push_back(tmp);
	return 0;
}

void api(char *text, REQUEST_HEADER head, sqlite3 *DB) {
	// GET METHOD
	if (!strcmp(head.Method, "GET")) {
		char* errmsg;
		vector<apiData> data;
		const char* query = "SELECT * FROM student_info;";
		int rc = sqlite3_exec(DB, query, callback, &data, &errmsg);

		if (rc != SQLITE_OK) {
			printf("[!] SQL ERROR : %s", errmsg);
			sqlite3_free(errmsg);
			sprintf(text, "HTTP/1.1 403 Forbidden\r\n");
		}

		stringstream table_result;
		table_result << "{ \"data\" : { ";
		for (auto it = data.begin(); it != data.end(); it++) {
			table_result << it->no << " : ";
			table_result << "{\"name\" : \"" << it->name << "\", ";
			table_result << "\"id\" : " << it->id << ", ";
			table_result << "\"memo\" : \"" << it->memo << "\"}";
			if ((it + 1) != data.end()) table_result << ", ";
		}
		table_result << " } }";
		string tmp = table_result.str();

		memset(text, 0, sizeof(text));
		sprintf(text,
			"HTTP/1.1 200 OK\r\n"
			"Content-Length : %d\r\n"
			"Content-Type : application/json;charset=utf-8\r\n"
			"\r\n"
			"%s\r\n",
			tmp.size(), tmp.c_str());
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
			sprintf(tmp, "{ %d : { \"name\" : \"%s\", \"id\" : %s, \"memo\" : \"%s\"} }",
				no, name, id, memo);
			sprintf(text,
				"HTTP/1.1 200 OK\r\n"
				"Content-Length : %d\r\n"
				"Content-Type : application/json;charset=utf-8\r\n"
				"\r\n"
				"%s\r\n",
				strlen(tmp), tmp);

			char insert[1000];
			char* errmsg;
			sprintf(insert, "INSERT INTO student_info VALUES (%d, '%s', %s, '%s');",
				no++, name, id, memo);
			int rc = sqlite3_exec(DB, insert, NULL, NULL, &errmsg);

			if (rc != SQLITE_OK) {
				printf("[!] SQL ERROR : %s", errmsg);
				sqlite3_free(errmsg);
				sprintf(text, "HTTP/1.1 403 Forbidden\r\n");
			}
		}
		else {
			sprintf(text, "HTTP/1.1 400 Bad Request\r\n");
		}
	}

	// PUT METHOD
	if (!strcmp(head.Method, "PUT")) {
		string udata(head.uri_data);
		map<string, string> ndata = parser(udata);
		const char* noo = "no";
		bool check_no = true;

		for (auto it = ndata.begin(); it != ndata.end(); it++) {
			if (!strcmp((it->first).c_str(), "no") && check_no) {
				noo = (it->second).c_str();
				check_no = false;
			}
		}

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

		if (check_no && check_name && check_id && check_memo) {
			sprintf(text, "HTTP/1.1 400 Bad Request\r\n");
		}
		else {
			char tmp[1024];
			char* err;
			sprintf(tmp, "UPDATE student_info "
				"SET name = '%s', id = %s, memo = '%s' "
				"WHERE no = %s;",
				name, id, memo, noo);

			if (sqlite3_exec(DB, tmp, NULL, NULL, &err) != SQLITE_OK) {
				printf("[!] SQL ERROR : %s", err);
				sqlite3_free(err);
				sprintf(text, "HTTP/1.1 403 Forbidden\r\n");
			}
			
			sprintf(tmp, "{ %s : { \"name\" : \"%s\", \"id\" : %s, \"memo\" : \"%s\"",
				noo, name, id, memo);

			sprintf(text,
				"HTTP/1.1 200 OK\r\n"
				"Content-Length : %d\r\n"
				"Content-Type : application/json;charset=utf-8\r\n"
				"\r\n"
				"%s\r\n",
				strlen(tmp), tmp);
		}
	}

	// DELETE METHOD
	if (!strcmp(head.Method, "DELETE")) {
		string udata(head.uri_data);
		map<string, string> ndata = parser(udata);
		const char* noo = "no";
		bool check_no = true;

		for (auto it = ndata.begin(); it != ndata.end(); it++) {
			if (!strcmp((it->first).c_str(), "no") && check_no) {
				noo = (it->second).c_str();
				check_no = false;
			}
		}
		
		if (check_no) {
			sprintf(text, "HTTP/1.1 400 Bad Request\r\n");
		}
		else {
			char tmp[1024];
			char* err;
			sprintf(tmp, "DELETE FROM student_info WHERE no = %s;", noo);
			if (sqlite3_exec(DB, tmp, NULL, NULL, &err) != SQLITE_OK) {
				printf("[!] SQL ERROR : %s", err);
				sqlite3_free(err);
				sprintf(text, "HTTP/1.1 403 Forbidden\r\n");
			}
			else {
				sprintf(text, "HTTP/1.1 204 OK\r\n");
			}
		}
	}
}