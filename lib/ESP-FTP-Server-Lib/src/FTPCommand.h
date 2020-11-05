#ifndef FTP_COMMAND_H_
#define FTP_COMMAND_H_

#include <WiFiClient.h>
#include <Arduino.h>
#include "FTPPath.h"
#include "FTPFilesystem.h"

class FTPCommand
{
public:
	FTPCommand(String Name, int ExpectedArgumentCnt, WiFiClient * const Client, FTPFilesystem * const Filesystem = 0, IPAddress * DataAddress = 0, int * DataPort = 0)
		: _Name(Name), _ExpectedArgumentCnt(ExpectedArgumentCnt),
			_Filesystem(Filesystem),
			_DataAddress(DataAddress), _DataPort(DataPort), _Client(Client), _DataConnection(0) {}
	virtual ~FTPCommand() {}

	String getName() const
	{
		return _Name;
	}

	virtual void run(FTPPath & WorkDirectory, const std::vector<String> & Line) = 0;

	void SendResponse(int Code, String Text)
	{
		_Client->print(Code);
		_Client->print(" ");
		_Client->println(Text);
	}

	bool ConnectDataConnection()
	{
		if(_DataConnection == 0)
		{
			_DataConnection = new WiFiClient();
		}
		if(_DataConnection->connected())
		{
			_DataConnection->stop();
		}
		_DataConnection->connect(*_DataAddress, *_DataPort);
		if(!_DataConnection->connected())
		{
			_DataConnection->stop();
			SendResponse(425, "No data connection");
			return false;
		}
		SendResponse(150, "Accepted data connection");
		return true;
	}

	void data_print(String str)
	{
		if(_DataConnection == 0 || !_DataConnection->connected())
		{
			return;
		}
		_DataConnection->print(str);
	}

	void data_println(String str)
	{
		if(_DataConnection == 0 || !_DataConnection->connected())
		{
			return;
		}
		_DataConnection->println(str);
	}

	void data_send(uint8_t * c, size_t l)
	{
		if(_DataConnection == 0 || !_DataConnection->connected())
		{
			return;
		}
		_DataConnection->write(c, l);
	}

	int data_read(uint8_t * c, size_t l)
	{
		if(_DataConnection == 0 || !_DataConnection->connected())
		{
			return 0;
		}
		return _DataConnection->readBytes(c, l);
	}

	void CloseDataConnection()
	{
		_DataConnection->stop();
	}

protected:
	String _Name;
	int _ExpectedArgumentCnt;
	FTPFilesystem * const _Filesystem;
	IPAddress * const _DataAddress;
	int * const _DataPort;

private:
	WiFiClient * const _Client;
	WiFiClient * _DataConnection;
};

class FTPCommandTransfer : public FTPCommand
{
public:
	FTPCommandTransfer(String Name, int ExpectedArgumentCnt, WiFiClient * const Client, FTPFilesystem * const Filesystem = 0, IPAddress * DataAddress = 0, int * DataPort = 0)
		: FTPCommand(Name, ExpectedArgumentCnt, Client, Filesystem, DataAddress, DataPort) {}

	virtual void workOnData() = 0;

	bool trasferInProgress()
	{
		return _file;
	}

	void abort()
	{
		if(_file)
		{
			CloseDataConnection();
			SendResponse(426, "Transfer aborted");
			_file.close();
		}
	}

protected:
	File _file;
};

#endif
