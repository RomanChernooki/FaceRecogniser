#include "FaceRecogniser.h"
#include "FaceDetector.h"
#include <boost/property_tree/json_parser.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <regex>
#include <vector>

using namespace cv;


FaceRecogniser::FaceRecogniser()
{
	this->rootPath = 0;
}


FaceRecogniser::~FaceRecogniser()
{
}


void FaceRecogniser::readDirectory(const std::string& name)
{
	boost::filesystem::path path(name);
	if (!exists(path))
	{ 
		std::cout << name << " is unexisting path.";
		return;
	};
	if (!boost::filesystem::is_directory(path))
	{
		std::cout << name << " isn't directory.";
		return;
	}
	this->rootPath = &path;
	boost::filesystem::path outputPathDirectory = boost::filesystem::path(outputDirectory);
	if (!exists(outputPathDirectory))
	{
		create_directory(outputPathDirectory);
	}
	readDirectoryPath(path);
	std::ofstream jsonFile;
	jsonFile.open(rootPath->string() + "\\result.json");
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
	std::vector<Coords> coords = detectfaces(path.string(), this->face_cascade);
	boost::property_tree::ptree imageNode;
	imageNode.put("Result", (this->outputDirectory + path.stem().string() + ".jpg"));
	cv::resize(*coords[0].frame, *coords[0].frame, cv::Size(), 0.5, 0.5);
	if (coords.size() && (coords[0].x2 - coords[0].x1))
	{
		for (int i = 0; i < coords.size(); i++)
		{
			boost::property_tree::ptree coordsNode;
			coordsNode.put("x1", coords[i].x1);
			coordsNode.put("x2", coords[i].x2);
			coordsNode.put("y1", coords[i].y1);
			coordsNode.put("y2", coords[i].y2);
			imageNode.push_back(std::make_pair("FaceCoords", coordsNode));
			cv::Rect region(coords[i].x1 / 2, coords[i].y1 / 2, (coords[i].x2 - coords[i].x1) / 2, (coords[i].y2 - coords[i].y1) / 2);
			cv::GaussianBlur((*(coords[0].frame))(region), (*(coords[0].frame))(region), Size(0, 0), 4);
		}
	}

	imwrite(outputDirectory + path.stem().string() + ".jpg", *coords[0].frame);
	delete coords[0].frame;
	root.push_back(std::make_pair("Image", imageNode));
	std::cout << coords.size() << std::endl;
}
