#ifndef FUCK_ResponseEntity_H
#define FUCK_ResponseEntity_H
#include <cpprest/http_client.h>

struct ResponseEntity
{
	bool success;
	web::json::value  result;
	utility::string_t  code;
	int status;
	utility::string_t message;
};

#endif