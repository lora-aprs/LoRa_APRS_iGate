#ifndef RNFR_H_
#define RNFR_H_

#include <WiFiClient.h>
#include "../FTPCommand.h"

class RNFR_RNTO : public FTPCommand
{
public:
	explicit RNFR_RNTO(WiFiClient * const Client, FTPFilesystem * const Filesystem) : FTPCommand("RN", 1, Client, Filesystem), _fromSet(false) {}

	void run(FTPPath & WorkDirectory, const std::vector<String> & Line) override
	{
		if(Line[0] == "RNFR")
		{
			from(WorkDirectory, Line);
		}
		else if(Line[0] == "RNTO")
		{
			to(WorkDirectory, Line);
		}
	}

	void from(const FTPPath & WorkDirectory, const std::vector<String> & Line)
	{
		String filepath = WorkDirectory.getFilePath(Line[1]);
		if(!_Filesystem->exists(filepath))
		{
			SendResponse(550, "File " + Line[1] + " not found");
			return;
		}
		_fromSet = true;
		_from = filepath;
		SendResponse(350, "RNFR accepted - file exists, ready for destination");
	}

	void to(const FTPPath & WorkDirectory, const std::vector<String> & Line)
	{
		if(!_fromSet)
		{
			SendResponse(503, "Need RNFR before RNTO");
			return;
		}
		String filepath = WorkDirectory.getFilePath(Line[1]);
		if(_Filesystem->exists(filepath))
		{
			SendResponse(553, "File " + Line[1] + " already exists");
			return;
		}
		if(_Filesystem->rename(_from, filepath))
		{
			SendResponse(250, "File successfully renamed or moved");
		}
		else
		{
			SendResponse(451, "Rename/move failure");
		}
		_fromSet = false;
		_from = "";
	}

private:
	bool _fromSet;
	String _from;
};

#endif
