#pragma once

#include <boost/filesystem.hpp>
#include <boost/property_tree/ptree.hpp>
#include <opencv2/objdetect.hpp>
#include <vector>

#define MAX_THREAD_COUNT 7

class FaceRecogniser
{
public:
	FaceRecogniser();
	~FaceRecogniser();
	void readDirectory(const std::string& name);

private:
	cv::CascadeClassifier face_cascade;
	boost::filesystem::path *rootPath;
	boost::property_tree::ptree root;
#ifdef _WIN32
	const std::string outputDirectory = R"(C:\output\)"; 
#elif __linux__
	const std::string outputDirectory = R"(/home/output/)";
#endif

	void scanImage(const boost::filesystem::path& path);
	void readDirectoryPath(const boost::filesystem::path& path);
};

