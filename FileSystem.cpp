#include "FileSystemProducer.h"
#include "Decorator.h"

int main()
{
	WCHAR volumeCharacter;
	std::wcout << "Specify first volume character:";
	std::wcin.get(volumeCharacter);
	FS *fileSystem = FSProducer::ProduceFileSystem(&volumeCharacter);
	if (fileSystem == NULL) {
		std::cout << "Could not create filesystem of specified volume...";
		exit(GetLastError());
	}
	fileSystem->Info();
	Iterator iterator(fileSystem);
	Decorator decorator(&iterator);
	int step = 0;
	for (decorator.First(); decorator.GetState() <= 6; decorator.Next(step))
	{
		std::cout << "\nCluster Number:" << (int)decorator.GetState() << std::endl;
		decorator.GetData();
		step++;
	}
	//BYTE *dataBuffer = fileSystem->GetClusters(0, 1);
	//std::cout << "First cluster in hexadecimal:" << std::endl;
	//for (int i = 0; i < fileSystem->GetBytesPerCluster(); i++)
	//	std::cout << std::hex << (int)dataBuffer[i] << " ";
	//delete fileSystem;
	system("pause");
}
