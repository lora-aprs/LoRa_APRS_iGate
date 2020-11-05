#include "FTPPath.h"
#include "common.h"

FTPPath::FTPPath()
{
}

FTPPath::FTPPath(String path)
{
	changePath(path);
}

FTPPath::~FTPPath()
{
}

void FTPPath::changePath(String path)
{
	std::list<String> p = splitPath(path);
	std::copy(p.begin(), p.end(), std::back_inserter(_Path));
}

void FTPPath::goPathUp()
{
	_Path.pop_back();
}

String FTPPath::getPath() const
{
	return createPath(_Path);
}

String FTPPath::getFilePath(String filename) const
{
	if(*filename.begin() == '/')
	{
		return filename;
	}
	if(_Path.size() == 0)
	{
		return "/" + filename;
	}
	return getPath() + "/" + filename;
}

std::list<String> FTPPath::splitPath(String path)
{
	std::list<String> p = Split<std::list<String>>(path, '/');
	p.erase(
		std::remove_if(p.begin(), p.end(), [](const String & s)
			{
				if(s.isEmpty())
				{
					return true;
				}
				return false;
			}),
		p.end());
	return p;
}

String FTPPath::createPath(std::list<String> path)
{
	if(path.size() == 0)
	{
		return "/";
	}
	String new_path;
	for(const String & p: path)
	{
		new_path += "/";
		new_path += p;
	}
	return new_path;
}
