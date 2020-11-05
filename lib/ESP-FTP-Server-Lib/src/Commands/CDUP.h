#ifndef CDUP_H_
#define CDUP_H_

#include <WiFiClient.h>
#include "../FTPCommand.h"

class CDUP : public FTPCommand
{
public:
	explicit CDUP(WiFiClient * const Client) : FTPCommand("CDUP", 0, Client) {}
	
	void run(FTPPath & WorkDirectory, const std::vector<String> & Line) override
	{
		WorkDirectory.goPathUp();
		SendResponse(250, "Ok. Current directory is " + WorkDirectory.getPath());
	}
};

#endif
