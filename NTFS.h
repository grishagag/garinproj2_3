#pragma once
#include "AbstractFileSystem.h"

typedef struct
{
	BYTE Padding1[3];
	BYTE OEM_ID[8];
	BYTE BytesPerSector[2];
	BYTE SectorsPerCluster;
	BYTE Padding2[26];
	ULONGLONG TotalSectors;
} NTFSRecord;

class NTFS : public FS
{
public:
	NTFS(FSHandle &fsHandle);
	virtual ~NTFS();
	virtual STRING GetFileSystemName();

};