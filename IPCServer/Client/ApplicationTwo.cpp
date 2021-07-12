#include <Windows.h>

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
	HANDLE fileHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, false, L"MySharedMemoty");

	CloseHandle(fileHandle);
}