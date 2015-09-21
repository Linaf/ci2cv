#ci2cv facedetector for group picture identification
=================
This is a modified version of CSIRO Face Analysis SDK(ci2cv) to detect multiple faces simultaneously with in a single video frame or group picture.


Prerequisites
-------------
###### ci2cv
> CSIRO Face Analysis SDK contains a number of useful components that can extract and utilise the geometry of the face found in video. 
> https://github.com/iCogLabs/face-analysis-sdk
> use the following link for installation instruction
 https://github.com/iCogLabs/face-analysis-sdk/blob/master/doc/documentation.html


###### cmake
> Build management tool; v2.8 or higher recommended.
> http://www.cmake.org/ | cmake

###### opencv
> Opensource computer vision library.
> http://www.samontab.com/web/2014/06/installing-opencv-2-4-9-in-ubuntu-14-04-lts/

######FFMPEG
>  version 1.0.0 or above.
> https://trac.ffmpeg.org/wiki/CompilationGuide/Ubuntu

######QT
> version 4.7 or above 


Build
-----
```sh
$ cd catkin_ws/src/
$ git clone https://github.com/Linaf/ci2cv
## Edit CMakeLists.txt file inside ci2cv and replace CI2CV_LIBRARY and OpenCV_LIBS path by      		respective library paths of your system.
$ cd ..
$ catkin_make 
$ source devel/setup.bash
```

Run group_picture_tracker
-----------
Run ci2cv_node to track multiple faces simultaneously via ci2cv
```sh
$ roscore
$ rosrun usb_cam usb_cam_node
$ rosrun ci2cv ci2cv_node

This node tracks multiple faces simultaneously and publishes the video to a rostopic named "/ci2cv_node/output_video"


