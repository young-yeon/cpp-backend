#include "main.h"

REQUEST_HEADER headerParse(char* text) {
	REQUEST_HEADER value;

	int p, vp;
	for (p = 0, vp = 0; text[p] != ' '; p++) value.Method[vp++] = text[p];
	value.Method[vp] = NULL;

	for (p++, vp = 0; text[p] != ' '; p++) value.uri[vp++] = text[p];
	value.uri[vp] = NULL;

	for (p = 0; value.uri[p] != '?' && value.uri[p] != NULL; p++)
		value.Route[p] = value.uri[p];
	value.Route[p] = NULL;

	if (value.uri[p] == '?') p++;
	for (vp = 0; value.uri[p] != NULL; p++)
		value.uri_data[vp++] = value.uri[p];
	value.uri_data[vp] = NULL;

	if (DEBUG_MODE_PRINT_ROUTE)
		printf("[DEBUG_MODE] METHOD :: %s\n"
			"[DEBUG_MODE] ROUTE :: %s\n"
			"[DEBUG_MODE] URI_DATA :: %s\n",
			value.Method, value.Route, value.uri_data);

	char tmp[500];
	for (p = strlen(text) - 1, vp = 0; text[p] != '\n'; p--)
		tmp[vp++] = text[p];
	
	for (vp--, p = 0; vp >= 0; vp--) value.data[p++] = tmp[vp];
	value.data[p] = NULL;

	if (DEBUG_MODE_PRINT_DATA)
		printf("[DEBUG_MODE] DATA :: %s\n", value.data);

	searchText(text, "Host", value.Host);
	searchText(text, "Date", value.Date);
	searchText(text, "Cache-Control", value.CacheControl);
	searchText(text, "Connection", value.Connection);
	searchText(text, "Content-Length", value.ContentLength);
	searchText(text, "Content-Type", value.ContentType);
	searchText(text, "Content-Language", value.ContentLanguage);
	searchText(text, "Content-Encoding", value.ContentEncoding);
	
	if (DEBUG_MODE_PRINT_GENERALHEADER) {
		printf("[DEBUG_MODE] GENERAL HEADER\n\n");
		printf("HOST :: %s, ALLOW :: %s\n",
			value.Host, hostChecker(value.Host) ? "PASS" : "FAIL");
		printf("DATE :: %s\n", value.Date);
		printf("Cache-Control :: %s\n", value.CacheControl);
		printf("Connection :: %s\n", value.Connection);
		printf("Content-Length :: %s\n", value.ContentLength);
		printf("Content-Type :: %s\n", value.ContentType);
		printf("Content-Language :: %s\n", value.ContentLanguage);
		printf("Content-Encoding :: %s\n\n", value.ContentEncoding);
		printf("[DEBUG_MODE] END\n");
	}

	searchText(text, "Sec-Fetch-Mode", value.SecFetchMode);
	searchText(text, "User-Agent", value.UserAgent);
	searchText(text, "Cookie", value.Cookie);
	searchText(text, "Referer", value.Referer);
	searchText(text, "Authorization", value.Authorization);
	searchText(text, "Origin", value.Origin);
	searchText(text, "Accept", value.Accept);
	searchText(text, "Accept-Charset", value.AcceptCharset);
	searchText(text, "Accept-Encoding", value.AcceptEncoding);
	searchText(text, "Acceot-Language", value.AcceptLanguage);

	if (DEBUG_MODE_PRINT_GENERALHEADER) {
		printf("[DEBUG_MODE] REQUEST HEADER\n\n");
		printf("Sec-Fetch-Mode :: %s\n", value.SecFetchMode);
		printf("User-Agent :: %s\n", value.UserAgent);
		printf("Cookie :: %s\n", value.Cookie);
		printf("Referer :: %s\n", value.Referer);
		printf("Authorization :: %s\n", value.Authorization);
		printf("Origin :: %s\n", value.Origin);
		printf("Accept :: %s\n", value.Accept);
		printf("Accept-Charset :: %s\n", value.AcceptCharset);
		printf("Accept-Encoding :: %s\n", value.AcceptEncoding);
		printf("Accept-Language :: %s\n\n", value.AcceptLanguage);
		printf("[DEBUG_MODE] END\n");
	}

	return value;
}