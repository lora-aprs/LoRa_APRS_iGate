#ifndef RMD_H_
#define RMD_H_

#include <WiFiClient.h>
#include "../FTPCommand.h"

class RMD : public FTPCommand
{
public:
	explicit RMD(WiFiClient * const Client, FTPFilesystem * const Filesystem) : FTPCommand("RMD", 1, Client, Filesystem) {}

	void run(FTPPath & WorkDirectory, const std::vector<String> & Line) override
	{
		String filepath = WorkDirectory.getFilePath(Line[1]);
		if(!_Filesystem->exists(filepath))
		{
			SendResponse(550, "Folder " + filepath + " not found");
			return;
		}
		if(_Filesystem->rmdir(filepath))
		{
			SendResponse(250, " Deleted \"" + filepath + "\"");
		}
		else
		{
			SendResponse(450, "Can't delete \"" + filepath + "\"");
		}
	}
};

#endif
