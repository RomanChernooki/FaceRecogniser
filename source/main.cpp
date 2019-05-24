// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "FaceRecogniser.h"
#include <iostream>

int main()
{
	FaceRecogniser recogniser;
	recogniser.readDirectory(R"(E:\projects\face_detector\data)");
    std::cout << "Hello World!\n"; 
}

