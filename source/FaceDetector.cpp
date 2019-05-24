#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "FaceDetector.h"

using namespace cv;



std::vector<Coords> detectfaces(const std::string &filename, cv::CascadeClassifier &face_cascade)
{
	std::vector<Coords> faceCorrdinatesArray;
	if (face_cascade.empty())
	{
		if (!face_cascade.load(R"(data\haarcascades\haarcascade_frontalface_alt.xml)"))
		{
			std::cout << R"(data\haarcascades\haarcascade_frontalface_alt.xml is missing!)" << std::endl;
			return faceCorrdinatesArray;
		}
	}
	Mat *frame = new Mat(imread(filename, 1));
	Mat frame_gray;
	cvtColor(*frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	//-- Detect faces
	std::vector<Rect> faces;
	face_cascade.detectMultiScale(frame_gray, faces);

	if (!faces.size())
	{
		Coords faceCorrdinates;
		faceCorrdinates.x1 = 0;
		faceCorrdinates.y1 = 0;
		faceCorrdinates.x2 = 0 + 0;
		faceCorrdinates.y2 = 0 + 0;
		faceCorrdinates.frame = frame;
		faceCorrdinatesArray.push_back(faceCorrdinates);
		std::cout << "Found faces: " << 0 << std::endl;
	}
	else
	{
		for (size_t i = 0; i < faces.size(); i++)
		{
			Coords faceCorrdinates;
			faceCorrdinates.x1 = faces[i].x;
			faceCorrdinates.y1 = faces[i].y;
			faceCorrdinates.x2 = faces[i].x + faces[i].width;
			faceCorrdinates.y2 = faces[i].y + faces[i].height;
			faceCorrdinates.frame = frame;
			faceCorrdinatesArray.push_back(faceCorrdinates);
		}
		std::cout << "Found faces: " << faceCorrdinatesArray.size() << std::endl;
	}
	std::cout << "At path:" << filename << std::endl << std::endl;
	return faceCorrdinatesArray;
}