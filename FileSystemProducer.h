#pragma once
#include "NTFS.h"
#include "FAT.h"
#include "exFAT.h"
typedef struct
{
	BYTE Padding[3];
	BYTE OEM_ID[8];
} FSRecord;
class FSProducer
{
public:
	static FS *ProduceFileSystem(WCHAR *fileName);
};
