#include "AbstractFileSystem.h"

FSHandle::FSHandle(HANDLE fsHandle)
{
	fileSystemHandle = fsHandle;
	dataBuffer = NULL;
}

FSHandle::FSHandle(FSHandle &fsHandle) : 
						fileSystemHandle(fsHandle.fileSystemHandle), dataBuffer(fsHandle.dataBuffer)
{

}

void FSHandle::ReadBytes(ULONGLONG readOffset, ULONGLONG numberOfBytes)
{
	delete[] dataBuffer;
	dataBuffer = new BYTE[numberOfBytes];
	LARGE_INTEGER sectorOffset;
	DWORD numberOfReadBytes;
	sectorOffset.QuadPart = readOffset;
	ULONGLONG currentPosition = SetFilePointer(fileSystemHandle, sectorOffset.LowPart, &sectorOffset.HighPart, FILE_BEGIN);
	if (currentPosition != sectorOffset.LowPart) {;
		exit(GetLastError());
	}
	bool readResult = ReadFile(fileSystemHandle, dataBuffer, numberOfBytes, &numberOfReadBytes, NULL);
	if (!readResult || numberOfReadBytes != numberOfBytes) {
		exit(GetLastError());
	}
}

void FSHandle::Destroy()
{
	CloseHandle(fileSystemHandle);
	delete dataBuffer;
}

BYTE *FSHandle::GetDataBuffer()
{
	return dataBuffer;
}

FSHandle::~FSHandle()
{

}

FS::FS(FSHandle &fsHandle) : fileSystemHandle(fsHandle)
{

}

DWORD FS::GetBytesPerCluster()
{
	return bytesPerCluster;
}

DWORD FS::GetTotalClusters()
{
	return totalClusters;
}

BYTE *FS::GetClusters(ULONGLONG readOffset, ULONGLONG numberOfClusters)
{
	ULONGLONG bytesToRead = numberOfClusters *bytesPerCluster;
	ULONGLONG clusterOffset = this->bytesPerCluster * readOffset;
	fileSystemHandle.ReadBytes(clusterOffset, bytesToRead);
	return fileSystemHandle.GetDataBuffer();
}

void FS::Info()
{
	std::cout << "Filesystem name:" << this->GetFileSystemName() << std::endl;
	std::cout << "Bytes per cluster:" << this->GetBytesPerCluster() << std::endl;
	std::cout << "Total clusters:" << this->GetTotalClusters() << std::endl;
}

FS::~FS()
{
	fileSystemHandle.Destroy();
}
