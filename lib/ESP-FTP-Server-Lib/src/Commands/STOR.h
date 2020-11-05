#ifndef STOR_H_
#define STOR_H_

#include <WiFiClient.h>
#include "../FTPCommand.h"
#include "../common.h"

#define FTP_BUF_SIZE 4096

class STOR : public FTPCommandTransfer
{
public:
	explicit STOR(WiFiClient * const Client, FTPFilesystem * const Filesystem, IPAddress * DataAddress, int * DataPort)
		: FTPCommandTransfer("STOR", 1, Client, Filesystem, DataAddress, DataPort)
	{}
	
	void run(FTPPath & WorkDirectory, const std::vector<String> & Line) override
	{
		if(trasferInProgress())
		{
			return;
		}
		if(!ConnectDataConnection())
		{
			return;
		}
		String path = WorkDirectory.getFilePath(Line[1]);
		_file = _Filesystem->open(path, "w");
		if(!_file)
		{
			CloseDataConnection();
			SendResponse(451, "Can't open/create " + path);
			return;
		}
		workOnData();
	}

	void workOnData() override
	{
		uint8_t buffer[FTP_BUF_SIZE];
		int nb = data_read(buffer, FTP_BUF_SIZE);
		if(nb > 0)
		{
			_file.write(buffer, nb);
			return;
		}
		CloseDataConnection();
		SendResponse(226, "File successfully transferred");
		_file.close();
	}

private:
};

#endif
