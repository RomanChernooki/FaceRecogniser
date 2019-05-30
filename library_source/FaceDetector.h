#include <string>
#include <vector>
#include <boost/config.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/objdetect.hpp>
#include "Coords.h"


extern "C" BOOST_SYMBOL_EXPORT ImageCoords detectFaces(const std::string &filename, cv::CascadeClassifier &face_cascade);