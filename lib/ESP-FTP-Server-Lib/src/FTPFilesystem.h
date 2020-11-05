#ifndef FTP_FILESYSTEM_H_
#define FTP_FILESYSTEM_H_

#include <map>
#include <FS.h>
#include <FSImpl.h>
#include "FTPPath.h"

class FTPFilesystem
{
public:
	FTPFilesystem();
	virtual ~FTPFilesystem();

	void addFilesystem(String Name, FS * const Filesystem);
	void clearFilesystemList();

	File open(const String & path, const char* mode = FILE_READ);
	bool exists(const String & path);
	bool remove(const String & path);
	bool rename(const String & pathFrom, const String & pathTo);
	bool mkdir(const String & path);
	bool rmdir(const String & path);

	void printFilesystems();

#ifndef UNIT_TEST
private:
#endif
	FS * getFilesystem(String path);
	static String getPathWithoutFS(String path);

	std::map<String, FS *> _Filesystems;
};

class FTPFileImpl : public fs::FileImpl
{
public:
	explicit FTPFileImpl(String name) : _Name(name) {}
	~FTPFileImpl() {}
	size_t write(const uint8_t *buf, size_t size) override { return 0; };
	size_t read(uint8_t* buf, size_t size) override { return 0; };
	void flush() override {};
	bool seek(uint32_t pos, SeekMode mode) override { return false; };
	size_t position() const override { return 0; };
	size_t size() const override { return 0; };
	void close() override {};
	time_t getLastWrite() override { return 0; };
	const char* name() const override { return _Name.c_str(); };
	boolean isDirectory(void) override { return true; };
	fs::FileImplPtr openNextFile(const char* mode) override
	{
		if(_Filesystems.empty())
		{
			return 0;
		}
		String next = _Filesystems.front();
		_Filesystems.pop_front();
		return fs::FileImplPtr(new FTPFileImpl(next));
	}
	void rewindDirectory(void) override {};
	operator bool() override { return false; };

	void addFilesystem(String name) { _Filesystems.push_back(name); }
private:
	String _Name;
	std::list<String> _Filesystems;
};

#endif
