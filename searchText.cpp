#include "main.h"

// using KMP algorithm
vector<int> getPi(const char *p) {
	int m = strlen(p), j = 0;
	vector<int> pi(m, 0);
	for (int i = 1; i < m; i++) {
		while (j > 0 && p[i] != p[j]) j = pi[j - 1];
		if (p[i] == p[j]) pi[i] = ++j;
	}
	return pi;
}

int KMP_Algorithm(char *s, const char *p) {
	vector<int> pi = getPi(p);
	int n = strlen(s), m = strlen(p), j = 0;
	for (int i = 0; i < n; i++) {
		while (j > 0 && s[i] != p[j]) j = pi[j - 1];
		if (s[i] == p[j]) {
			if (j == m - 1) return i + 3;
			else j++;
		}
	}
	return -1;
}

void searchText(char *text, const char *target, char *result) {
	int p = 0;
	int i = KMP_Algorithm(text, target);
	if (i == -1) return;
	for (; text[i] == ' '; i++);
	for (; text[i] != '\r'; i++)
		result[p++] = text[i];
	result[p] = NULL;
}