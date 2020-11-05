#ifndef TYPE_H_
#define TYPE_H_

#include <WiFiClient.h>
#include "../FTPCommand.h"

class TYPE : public FTPCommand
{
public:
	explicit TYPE(WiFiClient * const Client) : FTPCommand("TYPE", 1, Client) {}
	
	void run(FTPPath & WorkDirectory, const std::vector<String> & Line) override
	{
		if(Line[1] == "A")
		{
			SendResponse(200, "TYPE is now ASCII");
			return;
		}
		else if(Line[1] == "I")
		{
			SendResponse(200, "TYPE is now 8-bit binary");
			return;
		}
		SendResponse(504, "Unknow TYPE");
	}
};

#endif
