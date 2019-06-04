#pragma once
#include "AbstractFileSystem.h"

class Iterator
{
protected:
	FS *pFileSystem;
	ULONGLONG currentState;
public:
	Iterator(FS *pFileSystem);
	Iterator();
	void First();
	void Next();
	bool IsDone();
	ULONGLONG GetState();
	void GetData();
};