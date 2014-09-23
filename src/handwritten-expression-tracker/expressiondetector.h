#ifndef EXPRESSIONDETECTOR_H
#define EXPRESSIONDETECTOR_H

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
  What is the aim for this class?
  This class is class i desire to process all the ci2cv stuff.
  This includes the detection part from the image; The entry point from the webcam videos;
  Also the handwritten codes for the expression tracker; This function also is the one in which we use
  to generate the BVH file.
  */
class ExpressionDetector
{
public:
       ExpressionDetector();
//       void getLandmarkLocations();

bool generateBVH(const std::string &saveLocatio);


       void setImage(const std::string &imgLoc);
       void viewImage();
       void processVideo();
       void calculateInitalParameter();
       void detectSmile(cv::Rect, cv::Rect, cv::Rect);
       void paintOnPicture(cv::Mat &image, cv::Point_<double> point);
       void paintOnPicture(cv::Mat &image, cv::Point_<double> point, int);
       //For Setting Either the camera or Video for source
       void setVideoSource();
       void setVideoSource(const std::string &videoLoc);
       void calculateDifference(int frameNumber);
       void resetOffset();
       void setVideoWriteLocation(const std::string &vidLoc);

       void generateLength(int frameNumber);

       double generateArea(int frameNumber);
       std::vector<cv::Point_<double> > get2dShape();
       std::vector<cv::Point3_<double> > get3dShape();
       std::string generateAnimation(int frameNumber);
       std::string intToString(int x);
       std::string doubleToString(double x);
       std::string getOffset();

       ~ExpressionDetector();
private:


       //Here are the list of inital Difference values for the inital value;
       double brownDownL;//Covers both values either Up or Down
       double brownDownR;
       double brownDownC;
       double mouthArea;
       double jawLine;
       double lipDistance_L;
       double lipDistance_R;
       double initalValueHold[122];

       double differenceValueInitial[7];
       double differenceValueMax[7];
       double differenceValueMin[7];
       //If the value is less than zero then i would assign it to the minmum; Thus change the value to positive
       //To Evalue using cris cros; That is after check it's not less than that of the inital difference;


       //int thershold;

       int xP;
       int zP;
       int yP;


       //Declare all relevant parameters here
       std::vector<bool> eyeBlinkL;
       std::vector<bool> eyeBlinkR;
       std::vector<float> smileFull;

       std::vector<cv::Point_<double> > shape;
       std::vector<cv::Point3_<double> > shape3D;
       std::vector<FACETRACKER::Pose> poseVec;

       //CV::RECT to hold the ROI for the Mat;
       cv::Rect lEye;
       cv::Rect rEye;
       cv::Rect mouth;
       int result;

       cv::VideoCapture cap;
       cv::Mat image;
       cv::VideoWriter writer;
       std::string vidLoc;

       FACETRACKER::FaceTracker *tracker;
       FACETRACKER::FaceTrackerParams *tracker_params ;
};

#endif // EXPRESSIONDETECTOR_H
