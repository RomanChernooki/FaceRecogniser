#include <string>
#include <vector>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>

struct Coords
{
	int x1;
	int x2;
	int y1;
	int y2;
	cv::Mat *frame;
};

extern "C++" __declspec(dllexport) std::vector<Coords> detectfaces(const std::string &filename, cv::CascadeClassifier &face_cascade);