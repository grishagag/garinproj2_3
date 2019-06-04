#pragma once
#include "Iterator.h"

class Decorator : public Iterator
{
private:
	Iterator *iterator;
public:
	Decorator(Iterator *it);
	void First();
	void Next(DWORD stepSize);
	bool IsDone();
	ULONGLONG GetState();
	void GetData();
};