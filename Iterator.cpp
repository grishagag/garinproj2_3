#include "Iterator.h"

Iterator::Iterator(FS *pFileSystem)
{
	this->pFileSystem = pFileSystem;
	currentState = 0;
}

Iterator::Iterator()
{

}

void Iterator::First()
{
	currentState = 0;
}

void Iterator::Next()
{
	currentState++;
}

bool Iterator::IsDone()
{
	return (currentState < (pFileSystem->GetTotalClusters() + 1));
}

ULONGLONG Iterator::GetState()
{
	return currentState;
}

void Iterator::GetData()
{
	BYTE *Cluster = pFileSystem->GetClusters(currentState, 1);
	for(DWORD i = 0; i < pFileSystem->GetBytesPerCluster(); i++)
		std::cout << std::hex << (DWORD)Cluster[i] << " ";
}