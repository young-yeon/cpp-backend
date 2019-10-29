#include "main.h"

bool strChecker(const char *target, const char *allow) {
	for (int i = 0; target[i] != NULL && allow[i] != NULL; i++)
		if (target[i] != allow[i]) return false;
	return true;
}

bool hostChecker(const char *target_host) {
	if (!strcmp(ALLOW_HOSTS[0], "*")) return true;
	for (int i = 0; ALLOW_HOSTS[i][0] != NULL; i++)
		if (strChecker(target_host, ALLOW_HOSTS[i]))
			return true;
	return false;
}