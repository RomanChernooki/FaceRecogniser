#include <gtest/gtest.h>
#include <opencv2/objdetect.hpp>
#include <boost/function.hpp>
#include <boost/dll.hpp>
#include "../library_source/Coords.h"


TEST(FaceTest, PositiveTest)
{
	cv::CascadeClassifier face_cascade;
	boost::dll::shared_library lib(R"(face_detector_lib)", boost::dll::load_mode::append_decorations);
	boost::function<ImageCoords(const std::string&, cv::CascadeClassifier&)> detectFacesFunc =
		lib.get<ImageCoords(const std::string&, cv::CascadeClassifier&)>("detectFaces");
	EXPECT_EQ(detectFacesFunc("c:/data/test1.jpg", face_cascade).faceCorrdsVector.size(), 1);
}


int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}