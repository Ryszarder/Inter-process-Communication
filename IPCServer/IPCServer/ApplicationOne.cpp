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
	MyData myData = { 10, 3.8f, 'C', false, 70.52 };

	HANDLE fileHandle = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(MyData), L"MySharedMemory");

	if (fileHandle == nullptr)
	{
		std::cout << "Could not create file mapping object: " << GetLastError() << std::endl;
		return 1;
	}

	MyData* data = (MyData*)MapViewOfFile(fileHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(MyData));

	if (data == nullptr)
	{
		std::cout << "could not map view of file: " << GetLastError() << std::endl;
		CloseHandle(fileHandle);
		return 1;
	}

	*data = myData;

	_getch();

	UnmapViewOfFile(data);

	CloseHandle(fileHandle);

	return 0;
}