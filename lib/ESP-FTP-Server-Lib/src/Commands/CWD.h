#ifndef CWD_H_
#define CWD_H_

#include <WiFiClient.h>
#include "../FTPCommand.h"

class CWD : public FTPCommand
{
public:
	explicit CWD(WiFiClient * const Client, FTPFilesystem * const Filesystem) : FTPCommand("CWD", 1, Client, Filesystem) {}

	void run(FTPPath & WorkDirectory, const std::vector<String> & Line) override
	{
		FTPPath path = WorkDirectory;
		Serial.println(Line[1]);
		if(Line[1] == "..")
		{
			path.goPathUp();
		}
		else
		{
			path.changePath(Line[1]);
		}
		File dir = _Filesystem->open(path.getPath());
		if(dir.isDirectory())
		{
			WorkDirectory = path;
			SendResponse(250, "Ok. Current directory is " + WorkDirectory.getPath());
		}
		else
		{
			SendResponse(550, "Directory does not exist");
		}
	}
};

#endif
