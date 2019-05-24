// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "FaceRecogniser.h"
#include <iostream>

int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		std::cout << "Give path to a folder as an first argument, please." << std::endl;
		return -1;
	}
	FaceRecogniser recogniser;
	recogniser.readDirectory(argv[1]);
}

