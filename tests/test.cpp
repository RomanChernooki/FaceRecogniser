#include <gtest/gtest.h>
#include <opencv2/objdetect.hpp>
#include "../source/FaceDetector.h"


TEST(FaceTest, PositiveTest)
{
	cv::CascadeClassifier face_cascade;
	EXPECT_EQ(detectfaces("c:/data/test1.jpg", face_cascade).size(), 1);
}


int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}