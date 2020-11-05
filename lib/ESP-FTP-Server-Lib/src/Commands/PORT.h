#ifndef PORT_H_
#define PORT_H_

#include <WiFiClient.h>
#include "../FTPCommand.h"
#include "../common.h"

class PORT : public FTPCommand
{
public:
	explicit PORT(WiFiClient * const Client, IPAddress * DataAddress, int * DataPort)
		: FTPCommand("PORT", 1, Client, 0, DataAddress, DataPort)
	{}
	
	void run(FTPPath & WorkDirectory, const std::vector<String> & Line) override
	{
		std::vector<String> connection_details = Split<std::vector<String>>(Line[1], ',');
		for(int i = 0; i < 4; i++)
		{
			(*_DataAddress)[i] = connection_details[i].toInt();
		}
		*_DataPort = connection_details[4].toInt() * 256 + connection_details[5].toInt();
		SendResponse(200, "PORT command successful");
	}
};

#endif
