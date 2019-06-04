#pragma once
#include <windows.h>
#include <iostream>
#include <string>
typedef std::string STRING;

class FSHandle
{
protected:
	HANDLE fileSystemHandle;
	BYTE *dataBuffer;
public:
	FSHandle(HANDLE fsHandle);
	FSHandle(FSHandle &fsHandle);
	void ReadBytes(ULONGLONG readOffset, ULONGLONG numberOfBytes);
	void Destroy();
	BYTE *GetDataBuffer();
	~FSHandle();
};

class FS
{
protected:
	FSHandle fileSystemHandle;
	STRING fsName;
	DWORD bytesPerSector;
	DWORD sectorsPerCluster;
	DWORD bytesPerCluster;
	DWORD totalClusters;
public:
	FS(FSHandle &fsHandle);
	DWORD GetBytesPerCluster();
	DWORD GetTotalClusters();
	BYTE *GetClusters(ULONGLONG readOffset, ULONGLONG numberOfClusters);
	void Info();
	virtual STRING GetFileSystemName() = 0;
	virtual ~FS();
};