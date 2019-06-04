#include "Decorator.h"

Decorator::Decorator(Iterator *it) : iterator(it)
{
}

void Decorator::First()
{
	iterator->First();
}

void Decorator::Next(DWORD stepSize)
{
	for (DWORD i = 0; i < stepSize; i++)
		iterator->Next();
}
bool Decorator::IsDone()
{
	return iterator->IsDone();
}

ULONGLONG Decorator::GetState()
{
	return iterator->GetState();
}

void Decorator::GetData()
{
	iterator->GetData();
}