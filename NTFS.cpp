#include "NTFS.h"

NTFS::NTFS(FSHandle &fsHandle) : FS(fsHandle)
{
	fsHandle.ReadBytes(0, 512);
	NTFSRecord *ntfsRecord = (NTFSRecord *)fsHandle.GetDataBuffer();
	bytesPerSector = *((WORD*)ntfsRecord->BytesPerSector);
	sectorsPerCluster = ntfsRecord->SectorsPerCluster;
	bytesPerCluster = bytesPerSector * sectorsPerCluster;
	totalClusters = ntfsRecord->TotalSectors / sectorsPerCluster;
	fsName = STRING((char *)ntfsRecord->OEM_ID, 8);
}

NTFS::~NTFS()
{

}

STRING NTFS::GetFileSystemName()
{
	return STRING("NTFS");
}
