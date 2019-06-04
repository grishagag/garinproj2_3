#include "exFAT.h"

ULONGLONG step(DWORD base, DWORD exp)
{
	ULONGLONG result = 1;
	for (;;)
	{
		if (exp & 1)
			result *= base;
		exp >>= 1;
		if (!exp)
			break;
		base *= base;
	}
	return result;
}

exFAT::exFAT(FSHandle &fsHandle) : FS(fsHandle)
{
	fsHandle.ReadBytes(0, 512);
	EXFATRecord *exFATRecord = (EXFATRecord *)fsHandle.GetDataBuffer();
	totalClusters = exFATRecord->TotalClusters;
	fsName = STRING((char *)exFATRecord->OEM_ID, 8);
	bytesPerSector = step(2, exFATRecord->SectorFactor);
	sectorsPerCluster = step(2, exFATRecord->ClusterFactor);
	bytesPerCluster = bytesPerSector * sectorsPerCluster;
}

exFAT::~exFAT()
{

}

STRING exFAT::GetFileSystemName()
{
	return STRING("exFAT");
}
