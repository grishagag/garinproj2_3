#pragma once
#include "AbstractFileSystem.h"

typedef struct
{
	BYTE Padding1[3];
	BYTE OEM_ID[8];
	BYTE Padding2[61];
	ULONGLONG TotalSectors;
	DWORD FATStartSector;
	DWORD FATSizeInSectors;
	DWORD ClusterOffset;
	DWORD TotalClusters;
	DWORD RootDirCluster;
	BYTE Padding3[8];
	BYTE SectorFactor;
	BYTE ClusterFactor;
} EXFATRecord;

class exFAT : public FS
{
public:
	exFAT(FSHandle &fsHandle);
	virtual ~exFAT();
	virtual STRING GetFileSystemName();
};