#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "FaceDetector.h"

using namespace cv;



ImageCoords detectFaces(const std::string &filename, cv::CascadeClassifier &face_cascade)
{
	ImageCoords image;
	if (face_cascade.empty())
	{
		if (!face_cascade.load(R"(data\haarcascades\haarcascade_frontalface_alt.xml)"))
		{
			std::cout << R"(data\haarcascades\haarcascade_frontalface_alt.xml is missing!)" << std::endl;
			return image;
		}
	}
	Mat frame = Mat(imread(filename, 1));
	Mat frame_gray;
	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	equalizeHist(frame_gray, frame_gray);
	//-- Detect faces
	std::vector<Rect> faces;
	face_cascade.detectMultiScale(frame_gray, faces);

	for (size_t i = 0; i < faces.size(); i++)
	{
		Coords faceCorrdinates;
		faceCorrdinates.x1 = faces[i].x;
		faceCorrdinates.y1 = faces[i].y;
		faceCorrdinates.x2 = faces[i].x + faces[i].width;
		faceCorrdinates.y2 = faces[i].y + faces[i].height;
		image.faceCorrdsVector.push_back(faceCorrdinates);
	}
	image.imageFrame = frame;
	std::cout << "Found faces: " << image.faceCorrdsVector.size() << std::endl;
	std::cout << "At path:" << filename << std::endl << std::endl;
	return image;
}