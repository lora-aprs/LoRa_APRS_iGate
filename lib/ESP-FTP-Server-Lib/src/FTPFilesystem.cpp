#include "FTPFilesystem.h"
#include "common.h"

FTPFilesystem::FTPFilesystem()
{
}

FTPFilesystem::~FTPFilesystem()
{
}

void FTPFilesystem::addFilesystem(String Name, FS * const Filesystem)
{
	_Filesystems[Name] = Filesystem;
}

void FTPFilesystem::clearFilesystemList()
{
	_Filesystems.clear();
}

File FTPFilesystem::open(const String & path, const char* mode)
{
	if(path == "/")
	{
		std::shared_ptr<FTPFileImpl> root = std::shared_ptr<FTPFileImpl>(new FTPFileImpl("/"));
		for(auto const & f: _Filesystems)
		{
			root->addFilesystem(f.first);
		}
		return File(root);
	}
	FS * fs = getFilesystem(path);
	return fs->open(getPathWithoutFS(path), mode);
}

bool FTPFilesystem::exists(const String & path)
{
	FS * fs = getFilesystem(path);
	if(fs == 0)
	{
		return false;
	}
	return fs->exists(getPathWithoutFS(path));
}

bool FTPFilesystem::remove(const String & path)
{
	FS * fs = getFilesystem(path);
	if(fs == 0)
	{
		return false;
	}
	return fs->remove(getPathWithoutFS(path));
}

bool FTPFilesystem::rename(const String & pathFrom, const String & pathTo)
{
	FS * fsFrom = getFilesystem(pathFrom);
	FS * fsTo = getFilesystem(pathTo);
	if(fsFrom == 0 || fsTo == 0)
	{
		return false;
	}
	if(fsFrom != fsTo)
	{
		// cant move/rename from one filesystem to another one!
		return false;
	}
	return fsFrom->rename(getPathWithoutFS(pathFrom), getPathWithoutFS(pathTo));
}

bool FTPFilesystem::mkdir(const String & path)
{
	FS * fs = getFilesystem(path);
	if(fs == 0)
	{
		return false;
	}
	return fs->mkdir(getPathWithoutFS(path));
}

bool FTPFilesystem::rmdir(const String & path)
{
	FS * fs = getFilesystem(path);
	if(fs == 0)
	{
		return false;
	}
	return fs->rmdir(getPathWithoutFS(path));
}

void FTPFilesystem::printFilesystems()
{
	for (auto const & fs: _Filesystems)
	{
		Serial.println(fs.first);
	}
}

FS * FTPFilesystem::getFilesystem(String path)
{
	std::list<String> splitted = FTPPath::splitPath(path);
	String name = *(splitted.begin());
	std::map<String, fs::FS *>::iterator iter = _Filesystems.find(name);
	if(iter == _Filesystems.end())
	{
		Serial.println("[ERROR] Filesystem not found!");
		return 0;
	}
	return iter->second;
}

String FTPFilesystem::getPathWithoutFS(String path)
{
	std::list<String> splitted = FTPPath::splitPath(path);
	splitted.pop_front();
	String path_without = FTPPath::createPath(splitted);
	return path_without;
}
