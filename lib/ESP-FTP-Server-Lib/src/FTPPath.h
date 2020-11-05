#ifndef FTP_PATH_H_
#define FTP_PATH_H_

#include <Arduino.h>
#include <list>

class FTPPath
{
public:
	FTPPath();
	explicit FTPPath(String path);
	virtual ~FTPPath();

	void changePath(String path);
	void goPathUp();

	String getPath() const;
	String getFilePath(String filename) const;

	static std::list<String> splitPath(String path);
	static String createPath(std::list<String> path);

private:
	std::list<String> _Path;
};

#endif
