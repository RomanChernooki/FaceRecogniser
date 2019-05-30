#include "FaceRecogniser.h"
#include "../library_source/FaceDetector.h"
#include <boost/property_tree/json_parser.hpp>
#include <boost/dll/import.hpp> 
#include <boost/dll/shared_library.hpp>
#include <boost/function.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <regex>
#include <vector>

using namespace cv;

FaceRecogniser::FaceRecogniser()
{
}


FaceRecogniser::~FaceRecogniser()
{
}


void FaceRecogniser::readDirectory(const std::string& name)
{
	boost::filesystem::path rootPath(name);
	if (!exists(rootPath))
	{ 
		std::cout << name << " is unexisting path.";
		return;
	};
	if (!boost::filesystem::is_directory(rootPath))
	{
		std::cout << name << " isn't directory.";
		return;
	}
	boost::filesystem::path outputPathDirectory = boost::filesystem::path(outputDirectory);
	if (!exists(outputPathDirectory))
	{
		create_directory(outputPathDirectory);
	}
	readDirectoryPath(rootPath);
	std::ofstream jsonFile;
	jsonFile.open(rootPath.string() + "\\result.json");
	boost::property_tree::write_json(jsonFile, root);
	jsonFile.close();
}


void FaceRecogniser::readDirectoryPath(const boost::filesystem::path &path)
{
	boost::filesystem::directory_iterator start(path);
	boost::filesystem::directory_iterator end;
	for (auto& pathIterator : boost::filesystem::directory_iterator(path))
	{
		std::cout << pathIterator.path() << '\n';
		if (boost::filesystem::is_directory(pathIterator))
		{
			readDirectoryPath(pathIterator.path());
		}
		std::regex isImage(R"(\.(?:jpg|png))", std::regex_constants::icase);
		if (std::regex_search(pathIterator.path().string(), isImage))
		{
			scanImage(pathIterator.path());
		}
	}
}


void FaceRecogniser::scanImage(const boost::filesystem::path &path)
{
	boost::dll::shared_library lib(R"(face_detector_lib)", boost::dll::load_mode::append_decorations);
	if (!lib.is_loaded())
	{
		std::cout << "Cant't find face_detector_lib!" << std::endl;
		return;
	}
	boost::function<ImageCoords(const std::string&, cv::CascadeClassifier&)> detectFacesFunc = 
		lib.get<ImageCoords(const std::string&, cv::CascadeClassifier&)>("detectFaces"); 
	if (!detectFacesFunc)
	{
		std::cout << "Cant't find detectFacesFunc" << std::endl;
		return;
	}
	ImageCoords image = detectFacesFunc(path.string(), this->face_cascade);
	boost::property_tree::ptree imageNode;
	imageNode.put("Result", (this->outputDirectory + path.stem().string() + ".jpg"));
	cv::resize(image.imageFrame, image.imageFrame, cv::Size(), 0.5, 0.5);
	if (image.faceCorrdsVector.size())
	{
		for (int i = 0; i < image.faceCorrdsVector.size(); i++)
		{
			boost::property_tree::ptree coordsNode;
			coordsNode.put("x1", image.faceCorrdsVector[i].x1);
			coordsNode.put("x2", image.faceCorrdsVector[i].x2);
			coordsNode.put("y1", image.faceCorrdsVector[i].y1);
			coordsNode.put("y2", image.faceCorrdsVector[i].y2);
			imageNode.push_back(std::make_pair("FaceCoords", coordsNode));
			cv::Rect region(
				image.faceCorrdsVector[i].x1 / 2,
				image.faceCorrdsVector[i].y1 / 2,
				(image.faceCorrdsVector[i].x2 - image.faceCorrdsVector[i].x1) / 2,
				(image.faceCorrdsVector[i].y2 - image.faceCorrdsVector[i].y1) / 2);
			cv::GaussianBlur(image.imageFrame(region), image.imageFrame(region), Size(0, 0), 4);
		}
	}

	imwrite(outputDirectory + path.stem().string() + ".jpg", image.imageFrame);
	root.push_back(std::make_pair("Image", imageNode));
	std::cout << image.faceCorrdsVector.size() << std::endl;

}
