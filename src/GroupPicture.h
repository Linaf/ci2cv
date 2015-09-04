#ifndef GROUPPICTUR_H
#define GROUPPICTUR_H
#include "tracker/FaceTracker.hpp"
#include "utils/helpers.hpp"
#include "utils/command-line-arguments.hpp"
#include "qt-gui/command-line-configuration.hpp"
#include "utils/points.hpp"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <fstream>
#include <iostream>
#include <utils/helpers.hpp>

/**
This class is created inorder to allow ci2cv face tracker with group picture detection.
*/
class GroupPicture
{
public:
GroupPicture();
void setImage(const std::string &imgLoc);
void viewImage();
void viewImage(cv::Mat image1);
void viewImage(std::vector<cv::Mat> images);
void processVideo();
void paintOnPicture(cv::Mat &image, cv::Point_<double> point);
void paintOnPicture(cv::Mat &image, cv::Point_<double> point, int);
void setVideoSource();
void setVideoSource(const std::string &videoLoc);
void setVideoWriteLocation(const std::string &vidLoc);
void generateLength(int frameNumber);
double generateArea(int frameNumber);
std::vector<cv::Point_<double> > get2dShape();
std::vector<cv::Point3_<double> > get3dShape();
std::string intToString(int x);
std::string doubleToString(double x);
~GroupPicture();
private:

//Declare all relevant parameters here
std::vector<cv::Point_<double> > shape;
std::vector<cv::Point3_<double> > shape3D;
std::vector<FACETRACKER::Pose> poseVec;
cv::Rect lEye;
      cv::Rect rEye;
      cv::Rect mouth;
      int result;
cv::VideoCapture cap;
cv::Mat image;
const cv::Mat imageadd;
std::vector<cv::Rect> faces;
cv::VideoWriter writer;
std::string vidLoc;
std::vector<cv::Mat> images;
FACETRACKER::FaceTracker *tracker;
FACETRACKER::FaceTrackerParams *tracker_params ;
//FACETRACKER::FaceTracke<FACETRACKER::FaceTracker> *trackers;
//FACETRACKER::FaceTrackerParams<FACETRACKER::FaceTracker>  *trackers_params ;
};
#endif // GROUPPICTUR_H
