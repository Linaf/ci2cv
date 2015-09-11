#include "GroupPicture.h"
//#include "/home/lina/catkin_ws/src/ci2cv/src/utils/utils.h"
#include "utils/utils.h"
//#include </home/lina/setup/ffmpeg-2.7.2/compat/aix/math.h>
#include <math.h>
#include <boost/filesystem.hpp>
#include "tracker/FaceTracker.hpp"
#include <sstream>
using namespace FACETRACKER;



GroupPicture::GroupPicture()
            : it_(nh_)
             {
				tracker = FACETRACKER::LoadFaceTracker();
				tracker_params= FACETRACKER::LoadFaceTrackerParams();
				Utils::Init();
                image_sub_ = it_.subscribe("/usb_cam/image_raw", 1,
                &GroupPicture::imageCb, this);
				pub_= it_.advertise("ci2cv_node/output_video", 1);

			}
GroupPicture::~GroupPicture()
{
     delete tracker;
     tracker=0;
     delete tracker_params;
     tracker_params=0;
}
void GroupPicture::setImage(const std::string &imgLoc)
{
image= cv::imread(imgLoc,CV_LOAD_IMAGE_GRAYSCALE);
}

void GroupPicture::processVideo()
{
   // image=GroupPicture::imageCb();
    cap >> image;

    faces = Utils::detectFaces(image);

    if( !vidLoc.empty())
    {
     for (int i = 0; i < (int)faces.size(); i++){
    writer.open(vidLoc,CV_FOURCC('M','J','P','G'), 30, image.size());
    writer.write(image);
          }
    }

    cv::Point_<double> initialRun48;
    initialRun48.x=-1;
    cv::Point_<double> initialRun54;
    initialRun54.x=-1;

    cv::Point_<double> runningMax48;
    runningMax48.x=0;
    cv::Point_<double> runningMax54;
    runningMax54.x=0;

    cv::Point_<double> point6;
    cv::Point_<double> point10;
    cv::Point_<double> point14;
    cv::Point_<double> point17;//For the left eye;
    cv::Point_<double> point22;//For the right eye;
    cv::Point_<double> point28;
    cv::Point_<double> point51;
    cv::Point_<double> point48;//For the mouth;

    char key;
    int j=0;
    while(image.size().width>0 && image.size().height>0)
    {


          if((int)faces.size()>=0) {

                         std::cout<<"there are faces"<<endl;

                        j=0;
                        shape.clear();
                        shape3D.clear();
                        poseVec.clear();
                        if(!vidLoc.empty())
                        writer.open(vidLoc,CV_FOURCC('M','J','P','G'), 30, image.size());
                        tracker->Reset();


                 result= tracker->NewFrame(image, tracker_params);

                 if(result!=tracker->TRACKER_FAILED && result!=tracker->TRACKER_FACE_OUT_OF_FRAME)
                 {
                     std::vector<cv::Point_<double> > shapeAdditional;
                     FACETRACKER::Pose pose;
                     std::vector<cv::Point3_<double> > shape3DAdditional;
                     shapeAdditional= tracker->getShape();
                     shape3DAdditional= tracker->get3DShape();
                     pose= tracker->getPose();

                     shape.insert(shape.end(),shapeAdditional.begin(), shapeAdditional.end());
                     shape3D.insert(shape3D.end(), shape3DAdditional.begin(), shape3DAdditional.end());
                     poseVec.insert(poseVec.end(), pose);
                     for(int i=0; i<66; i++)
                     {
                         cv::Point_<double> m= shape.at(i+j);
                         if(i==48)
                         {
                             point48= m;
                             if(initialRun48.x==-1)
                             {
                                 initialRun48= m;
                             }
                             if(runningMax48.x<m.x)
                             {
                                 runningMax48= m;
                             }
                         }
                         if(i==54)
                         {
                             if(initialRun54.x==-1)
                             {
                                 initialRun48= m;
                             }
                             if(runningMax54.x<m.x)
                             {
                                 runningMax54= m;
                             }
                         }
                         if(i==6)
                         {
                             point6= m;
                         }
                         if(i==10)
                         {
                             point10= m;
                         }
                         if(i==14)
                         {
                             point14=m;
                         }
                         if(i==17)
                         {
                             point17=m;
                         }
                         if(i==22)
                         {
                             point22=m;
                         }
                         if(i==30)
                         {
                             point28=m;
                         }
                         if(i==33)
                         {
                             point51=m;
                         }


                         paintOnPicture(image, m,1);
                         cv::Point point;
                         point.x= image.size().width/2;
                         point.y= image.size().height/2;
             msg = cv_bridge::CvImage(std_msgs::Header(), "bgr8", image).toImageMsg();
             pub_.publish(msg);
			 cv::waitKey(1);
                         if(i==60)
                         {
                 std::cout<<"Reached Here 2"<<std::endl;
                         }
                     }
                     j+=66;
                   for(int b=0; b<(int)faces.size();b++){

                          viewImage(image);
                          cap >> image;
                          if(!vidLoc.empty())
                         writer.write(image);
                     }


                 }
                 else if(result==tracker->TRACKER_FACE_OUT_OF_FRAME)
                 {
                     tracker->Reset();
                     //Call the FaceTracker out of Frame
                     for(int b=0; b<(int)faces.size();b++){

                            viewImage(image);
                            cap >> image;
                            viewImage();
                            if(!vidLoc.empty())
                           writer.write(image);
                       }

                 }
                 else
                 {
                     tracker->Reset();
                     //Call the FaceTracker Failed to come;
                     for(int b=0; b<(int)faces.size();b++){

                            viewImage(image);
                            cap >> image;
                            viewImage();
                            if(!vidLoc.empty())
                           writer.write(image);
                       }

                 }


                 key = (char) cv::waitKey(20);
                 if(key==27)
                     break;
                 else if(key==82 || key== 114)//press R or r to reset the tracking;
                 {
                     j=0;
                     shape.clear();
                     shape3D.clear();
                     poseVec.clear();
                     if(!vidLoc.empty())
                     writer.open(vidLoc,CV_FOURCC('M','J','P','G'), 30, image.size());
                     tracker->Reset();
                 }




                         }
          else{
                             std::cout<<"no faces"<<endl;
                         }



}
    delete tracker;
    tracker=0;
    delete tracker_params;
    tracker_params=0;

}
void GroupPicture::setVideoSource()
{
cap= cv::VideoCapture(0);
if(!cap.isOpened())
throw(12346);
}
void GroupPicture::setVideoSource(const std::string &videoLoc)
{
cap= cv::VideoCapture(videoLoc);
if(!cap.isOpened())
throw(12345);
}

void GroupPicture::viewImage()
{
    cv::namedWindow("Facial Expression Tracker");
    cv::imshow("Facial Expression Tracker", image);
}
void GroupPicture::viewImage(cv::Mat image1)
{
    cv::namedWindow("Facial Expression Tracker1", CV_WINDOW_NORMAL);
    cv::imshow("Facial Expression Tracker1", image1);
}
void GroupPicture::viewImage(std::vector<cv::Mat> images)
{

    for(int i=0; i<(int)images.size(); i++){
        cv::namedWindow("Facial Expression Tracker1");
        viewImage(images[i]);
    }

}
std::string GroupPicture::intToString(int x)
{
    std::stringstream ss;
    ss.str(std::string());
    ss<<x;
    std::string xLoc= ss.str();
    return xLoc;
}
std::string GroupPicture::doubleToString(double x)
{
    std::stringstream ss;
    ss.str(std::string());
    ss<<x;
    std::string xLoc= ss.str();
    return xLoc;
}
void GroupPicture::paintOnPicture(cv::Mat &image, cv::Point_<double> point)
{
    int x=(int)point.y;
    int y=(int)point.x;
    image.at<cv::Vec3b>(x,y)[0]=0;
    image.at<cv::Vec3b>(x,y)[1]=255;
    image.at<cv::Vec3b>(x,y)[2]=0;

    image.at<cv::Vec3b>(x+1,y+1)[0]=0;      image.at<cv::Vec3b>(x-1,y-1)[0]=0;
    image.at<cv::Vec3b>(x+1,y+1)[1]=255;    image.at<cv::Vec3b>(x-1,y-1)[1]=255;
    image.at<cv::Vec3b>(x+1,y+1)[2]=0;      image.at<cv::Vec3b>(x-1,y-1)[2]=0;

    image.at<cv::Vec3b>(x+1,y-1)[0]=0;      image.at<cv::Vec3b>(x-1,y+1)[0]=0;
    image.at<cv::Vec3b>(x+1,y-1)[1]=255;    image.at<cv::Vec3b>(x-1,y+1)[0]=255;
    image.at<cv::Vec3b>(x+1,y-1)[2]=0;      image.at<cv::Vec3b>(x-1,y+1)[0]=0;
}
void GroupPicture::paintOnPicture(cv::Mat &image, cv::Point_<double> point, int)
{
    int x=(int)point.y;
    int y=(int)point.x;
    image.at<cv::Vec3b>(x,y)[0]=255;
    image.at<cv::Vec3b>(x,y)[1]=255;
    image.at<cv::Vec3b>(x,y)[2]=255;

    image.at<cv::Vec3b>(x+1,y+1)[0]=255;    image.at<cv::Vec3b>(x-1,y-1)[0]=255;
    image.at<cv::Vec3b>(x+1,y+1)[1]=255;    image.at<cv::Vec3b>(x-1,y-1)[1]=255;
    image.at<cv::Vec3b>(x+1,y+1)[2]=255;    image.at<cv::Vec3b>(x-1,y-1)[2]=255;

    image.at<cv::Vec3b>(x+1,y-1)[0]=255;    image.at<cv::Vec3b>(x-1,y+1)[0]=255;
    image.at<cv::Vec3b>(x+1,y-1)[1]=255;    image.at<cv::Vec3b>(x-1,y+1)[0]=255;
    image.at<cv::Vec3b>(x+1,y-1)[2]=255;    image.at<cv::Vec3b>(x-1,y+1)[0]=255;
}
void GroupPicture::setVideoWriteLocation(const std::string &vidLoc)
{
    this->vidLoc= vidLoc;


}

void GroupPicture::imageCb(const sensor_msgs::ImageConstPtr& msg)
{
      cv_bridge::CvImagePtr cv_ptr;
    try
     {
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
      }
     catch (cv_bridge::Exception& e)
     {
       ROS_ERROR("cv_bridge exception: %s", e.what());
        return;
       }
 
}

