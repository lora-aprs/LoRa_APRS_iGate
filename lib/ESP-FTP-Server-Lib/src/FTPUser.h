#ifndef FTP_USER_H_
#define FTP_USER_H_

#include <Arduino.h>

class FTPUser
{
public:
	FTPUser(const String & username, const String & password) : Username(username), Password(password) {}
	const String Username;
	const String Password;
};

#endif
