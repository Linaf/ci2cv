/* 
 * File:   utils.cpp
 * Author: ss
 */

#include "utils.h"
using namespace std;
CascadeClassifier Utils::face_cascade;

void Utils::Init() {
	std::cout<<"\nthe code reached here";
    Utils::face_cascade.load("/usr/share/opencv/haarcascades/haarcascade_frontalface_alt.xml");
	std::cout<<"\nthe code reached here 2";
}

    vector<Rect> Utils::detectFaces(Mat frame) {
    vector<Rect> faces;
    Mat buffer_mat;
    cvtColor(frame, buffer_mat, COLOR_BGR2GRAY);
    equalizeHist(buffer_mat, buffer_mat);
    face_cascade.detectMultiScale(buffer_mat, faces, 1.1, 2, 0 | CV_HAAR_SCALE_IMAGE, Size(30, 30));
    return faces;
}

