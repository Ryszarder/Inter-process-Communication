#include <Windows.h>
#include <iostream>
#include <conio.h>

//Stores the data into a struct
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
	//Initialize the values for the data in the struct
	MyData myData = { 10, 3.8f, 'C', false, 70.52 };

	//Open a named shared memoty block, that checks to see if there is an exising file or not, access control to read/write 
	//with the file, the size of the memory block, and gives the name for the file mapping
	HANDLE fileHandle = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(MyData), L"MySharedMemory");

	//If file can't be found
	if (fileHandle == nullptr)
	{
		//Writes out the message and gives the last error
		std::cout << "Could not create file mapping object: " << GetLastError() << std::endl;
		//Return 1 meaing there was an error
		return 1;
	}

	//Maps the merory from the share block to a pointer that can be manipulated
	//It takes in the handle to the virtual file, next is access to read and write controls,
	//The last part is how many bytes needed to access with the pointers
	MyData* data = (MyData*)MapViewOfFile(fileHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(MyData));

	//If Data equals nullprt
	if (data == nullptr)
	{
		//Write message with the last error
		std::cout << "could not map view of file: " << GetLastError() << std::endl;
		//Since the file was open it's needs to be closed
		CloseHandle(fileHandle);
		//Return 1 meaing there was an error
		return 1;
	}

	//Writes to the memory block
	*data = myData;

	//Pauses the console so it will show the data till a key is pressed
	_getch();

	//Unmaps the memory block
	UnmapViewOfFile(data);

	//Since the file was open it's needs to be closed
	CloseHandle(fileHandle);

	return 0;
}