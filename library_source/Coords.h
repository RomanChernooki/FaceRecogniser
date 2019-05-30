#pragma once
#include <opencv2/imgproc.hpp>
#include <vector> 


struct Coords
{
	int x1;
	int x2;
	int y1;
	int y2;
};


struct ImageCoords
{
	std::vector<Coords> faceCorrdsVector;
	cv::Mat imageFrame;
};