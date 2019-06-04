#include "FileSystemProducer.h"

FS *FSProducer::ProduceFileSystem(WCHAR *fileName)
{
	WCHAR volumeName[8] = { '\\', '\\', '.', '\\', ' ', ':'};
	volumeName[4] = *fileName;
	HANDLE fileHandle = CreateFileW(volumeName,
									GENERIC_READ, 
									FILE_SHARE_READ | FILE_SHARE_WRITE, 
									NULL, 
									OPEN_EXISTING, 
									FILE_ATTRIBUTE_NORMAL, 
									NULL);
	if (fileHandle == INVALID_HANDLE_VALUE) {
		exit(GetLastError());
	}
	FSHandle FS(fileHandle);
	FS.ReadBytes(0, 512);
	BYTE *dataBuffer = FS.GetDataBuffer();
	FSRecord * dataRecord = (FSRecord *) dataBuffer;
	STRING OEM((char*)dataRecord->OEM_ID, 8);
	if (!OEM.compare("MSDOS5.0"))
		return new FAT(FS);
	if (!OEM.compare("NTFS    "))
		return new NTFS(FS);
	if (!OEM.compare("EXFAT   "))
		return new exFAT(FS);
	else
		return NULL;
}
