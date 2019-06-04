#include "FAT.h"

FAT::FAT(FSHandle &fsHandle) : FS(fsHandle)
{
	fsHandle.ReadBytes(0, 512);
	FATRecord *fatRecord = (FATRecord *)fsHandle.GetDataBuffer();
	sectorsPerCluster = fatRecord->SectorsPerCluster;
	bytesPerSector = *((WORD*)fatRecord->BytesPerSector);
	bytesPerCluster = bytesPerSector * sectorsPerCluster;
	fsName = STRING((char *)fatRecord->OEM_ID, 8);
	totalClusters = fatRecord->TotalSectors / sectorsPerCluster;
}

FAT::~FAT()
{

}

STRING FAT::GetFileSystemName()
{
	return STRING("FAT32");
}