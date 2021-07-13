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
	//Tries to gain access of a shared memory block that exist
	HANDLE fileHandle = OpenFileMapping(FILE_MAP_ALL_ACCESS, false, L"MySharedMemory");

	//If the file found nothing
	if (fileHandle == nullptr)
	{
		//Write message and print out the last error
		std::cout << "could not create file mapping object: " << GetLastError() << std::endl;

		//Return 1 meaing there was an error
		return 1;
	}

	//Maps the merory from the share block to a pointer that can be manipulated
	//It takes in the handle to the virtual file, next is access to read and write controls,
	//The last part is how many bytes needed to access with the pointers
	MyData* data = (MyData*)MapViewOfFile(fileHandle, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(MyData));

	//If the data equal 
	if (data == nullptr)
	{
		//Write message and print out the last error
		std::cout << "could not map view of file: " << GetLastError() << std::endl;

		//Closes the file that was open
		CloseHandle(fileHandle);

		//Return 1 meaing there was an error
		return 1;
	}

	//Prints out how the data will be shown in the console
	std::cout << "MyData = {";
	std::cout << data->i << ",";
	std::cout << data->f << ",";
	std::cout << data->c << ",";
	std::cout << data->b << ",";
	std::cout << data->d << " ";
	std::cout << " }:" << std::endl;

	//Waits for a key pressed before moving on
	_getch();

	//Unmap the data memory bloack
	UnmapViewOfFile(data);

	//cloases the file
	CloseHandle(fileHandle);

	return 0;
}