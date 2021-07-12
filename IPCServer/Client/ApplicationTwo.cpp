#include <Windows.h>
#include <iostream>
#include <conio.h>

struct MyData
{
	int i;
	float f;
	char c;
	bool b;
	double d;
};

int main()
{
	HANDLE fileHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, false, L"MySharedMemory");

	if (fileHandle == nullptr)
	{
		std::cout << "could not create file mapping object: " << GetLastError() << std::endl;

		return 1;
	}

	MyData* data = (MyData*)MapViewOfFile(fileHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(MyData));

	if (data == nullptr)
	{
		std::cout << "could not map view of file: " << GetLastError() << std::endl;
		CloseHandle(fileHandle);
		return 1;
	}

	std::cout << "MyData = {";
	std::cout << data->i << ",";
	std::cout << data->f << ",";
	std::cout << data->c << ",";
	std::cout << data->b << ",";
	std::cout << data->d << " ";
	std::cout << " }:" << std::endl;

	_getch();

	UnmapViewOfFile(data);

	CloseHandle(fileHandle);

	return 0;
}