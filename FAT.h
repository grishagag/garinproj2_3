#pragma once
#include "AbstractFileSystem.h"

typedef struct
{
	BYTE Padding1[3];
	BYTE OEM_ID[8];
	BYTE BytesPerSector[2];
	BYTE SectorsPerCluster;
	BYTE ReservedSectors[2];
	BYTE Padding2[16];
	ULONGLONG TotalSectors;
} FATRecord;

class FAT : public FS
{
public:
	FAT(FSHandle &fsHandle);
	virtual ~FAT();
	virtual STRING GetFileSystemName();
};
