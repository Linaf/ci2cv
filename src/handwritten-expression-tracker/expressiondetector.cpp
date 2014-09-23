#include "expressiondetector.h"
#include <math.h>
ExpressionDetector::ExpressionDetector()
{
    tracker = FACETRACKER::LoadFaceTracker();
    tracker_params= FACETRACKER::LoadFaceTrackerParams();
    xP=-30;
    zP=-40;
    yP=-50;
    //thershold=10;
}
ExpressionDetector::~ExpressionDetector()
{
    delete tracker;
    tracker=0;
    delete tracker_params;
    tracker_params=0;
}
//void ExpressionDetector::getLandmarkLocations()
//{
//    tracker = FACETRACKER::LoadFaceTracker();
//    tracker_params= FACETRACKER::LoadFaceTrackerParams();
//    result= tracker->NewFrame(image, tracker_params);
//    if(result!=tracker->TRACKER_FAILED && result!=tracker->TRACKER_FACE_OUT_OF_FRAME)
//    {
//        shape= tracker->getShape();
//        shape3D= tracker->get3DShape();
//        poseVec= tracker->getPose();
//    }
//    else if(result==tracker->TRACKER_FACE_OUT_OF_FRAME)
//    {
//        tracker->Reset();
//        //Call the FaceTracker out of Frame
//    }
//    else
//    {
//        tracker->Reset();
//        //Call the FaceTracker Failed to come;
//    }
//    delete tracker;
//    delete tracker_params;
//}
void ExpressionDetector::setImage(const std::string &imgLoc)
{
    image= cv::imread(imgLoc,CV_LOAD_IMAGE_GRAYSCALE);
}
std::string ExpressionDetector::getOffset()
{
    if(xP==30)
    {
     zP=zP+10;
     xP=-30;
    }
std::string s= intToString(xP) + " " + intToString(zP) + " " + intToString(yP) +" "+"0 0 ";
xP=xP+10;
return s;
}

void ExpressionDetector::processVideo()
{

    cap >> image;
    if( !vidLoc.empty())
    {
    writer.open(vidLoc,CV_FOURCC('M','J','P','G'), 30, image.size());
    writer.write(image);
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

        //result= tracker->NewFrame(image, tracker_params);

        //image.convertTo(image, -1, 1.1, 30);
        //cv::flip(image, image, 1);
        //tracker->Reset();
        result= tracker->NewFrame(image, tracker_params);

        if(result!=tracker->TRACKER_FAILED && result!=tracker->TRACKER_FACE_OUT_OF_FRAME)
        {
            //Return the value;
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

                //paintOnPicture(image, initialRun48);
                //paintOnPicture(image, initialRun54);

                //paintOnPicture(image, runningMax48);
                //paintOnPicture(image, runningMax54);

                paintOnPicture(image, m,1);
                cv::Point point;
                point.x= image.size().width/2;
                point.y= image.size().height/2;
                //Here call the generateSmiles using the queries for the fucntion;
                if(i==60)
                {
                //cv::Point_<double> m2= shape.at(offset);
                    //Here a check must be placed such that this rect fall inside the rectangle of the image;
         // (0 <= roi.x && 0 <= roi.width && roi.x + roi.width <= m.cols && 0 <= roi.y && 0 <= roi.height && roi.y + roi.height <= m.rows)
         if(point6.x< image.cols && point17.y < image.rows && 0 <= point17.x && 0 <= point28.x -point17.x && point17.x + point28.x -point17.x <= image.cols && 0 <= point17.y  && 0 <=  point28.y - point17.y && point17.y + point28.y - point17.y <= image.rows)
                {
          lEye= cv::Rect(point17.x, point17.y,  point28.x -point17.x, point28.y - point17.y);
         }
         else
         {
             cv::putText(image, "Left Eye Out of Frame", point, cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(255, 0, 0));
         }
      if(point22.x< image.cols && point22.y < image.rows && 0 <= point22.x && 0 <= point28.x -point17.x && point22.x + point28.x -point17.x <= image.cols && 0 <= point22.y && 0 <=  point28.y - point17.y && point22.y + point28.y - point17.y <= image.rows)
      {
          rEye= cv::Rect(point22.x, point22.y, point28.x -point17.x, point28.y - point17.y);
      }
      else
      {
          cv::putText(image, "Right Eye Out of Frame", point, cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(255, 0, 0));
      }
      if(point6.x< image.cols && point51.y < image.rows && 0 <= point6.x && 0 <= point10.x- point6.x&& point6.x + point10.x- point6.x <= image.cols && 0 <= point51.y && 0 <=   point6.y- point14.y && point51.y +  point6.y- point14.y <= image.rows)
      {
                    mouth =cv::Rect(point6.x, point51.y, point10.x- point6.x, point6.y- point14.y);
       }             //std::cout<<"Reached Here"<<std::endl;
      else
      {
          cv::putText(image, "Mouth Out of Frame", point, cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(255, 0, 0));
      }
      detectSmile(mouth, lEye, rEye);
                    //std::cout<<"Reached Here 2"<<std::endl;
                }
            }
            j+=66;
        }
        else if(result==tracker->TRACKER_FACE_OUT_OF_FRAME)
        {
            tracker->Reset();
            //Call the FaceTracker out of Frame
        }
        else
        {
            tracker->Reset();
            //Call the FaceTracker Failed to come;
        }
        viewImage();
        cap >> image;
         if(!vidLoc.empty())
        writer.write(image);
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

    delete tracker;
    tracker=0;
            delete tracker_params;
    tracker_params=0;
}
void ExpressionDetector::setVideoSource()
{
    cap= cv::VideoCapture(0);
    if(!cap.isOpened())
        throw(12346);

    //std::cout<<"IT also reached here"<<std::endl;
}
void ExpressionDetector::setVideoSource(const std::string &videoLoc)
{
    cap= cv::VideoCapture(videoLoc);
    if(!cap.isOpened())
        throw(12345);

}
void ExpressionDetector::setVideoWriteLocation(const std::string &vidLoc)
{
    this->vidLoc= vidLoc;
    /*
    this->vidLoc= vidLoc;
    writer= cv::VideoWriter(vidLoc,CV_FOURCC('M','J','P','G'), 30, image.size());
    if(!writer.isOpened())
        throw(12347);*/

}

bool ExpressionDetector::generateBVH(const std::string &saveLocation)
{
    std::string line="";
    std::string readLine;
    std::ifstream myFile("BlendshapeTemplate (copy).bvh");
    std::string saveLocal= saveLocation;
    saveLocal.append(".bvh");
    std::ofstream myOutFile(saveLocal.c_str());
    int sizeVec= (int)shape.size()/66;

    std::cout<<"Shape Entire "<<shape.size()<<std::endl;
    std::cout<<"Shape Eyes 2 Entire "<<smileFull.size()<<std::endl;
    std::cout<<"Shape Eyes   Entire "<<eyeBlinkR.size()<<std::endl;
    std::cout<<"Shape Mouth Entire "<<eyeBlinkL.size()<<std::endl;
    std::cout<<"Pose "<<poseVec.size()<<std::endl;
    int j=0;
    int offset=0;
    if(myFile.is_open())
    {
        std::string append;
        std::stringstream ss;
        while(getline(myFile,line))
        {

            if(std::string::npos!=line.find("*ROOT"))
            {
                append="\t OFFSET" " 0" " 0"  " 0";
                line.assign(append);
            }
            else if(std::string::npos!=line.find("*NECK"))
            {

                //Here insert the pose Location for the inital head locc as same as it was for the file
                FACETRACKER::Pose p= poseVec.at(0);
                double zRot= p.roll;
                double yRot= p.yaw;
                double xRot= p.pitch;
                append="\t OFFSET " "0" " 0" " 0 " + doubleToString(zRot) +" "+ doubleToString(xRot) + " " + doubleToString(yRot);
                line.assign(append);
            }
            else  if(std::string::npos!=line.find("*ENDSITE"))
            {
                append="\t\t\t OFFSET " "0" " 0"  " 10";
                line.assign(append);
            }
            else if(std::string::npos!=line.find("***"))
            {
                cv::Point_<double> m2= shape.at(offset);
                int x2= (int)m2.x;
                int y2= (int)m2.y;
                initalValueHold[offset]=x2;
                initalValueHold[offset]=y2;

                cv::Point3_<double> m= shape3D.at(offset);
                double x= m.x;
                double y= m.y;
                double z= m.z;
                std::string of= "\t\t\tOFFSET ";

                append= of + doubleToString(x) + " " + doubleToString(y) + " "+doubleToString(z);
                line.assign(append);
                offset++;

                //Iterate form the vector initial here

            }
            else if (std::string::npos!=line.find("*FRAMES"))
            {

                append="FRAMES: " + intToString((int)(shape.size()/66));
                line.assign(append);
                //To Declare the amount of the lines
            }
            else if (std::string::npos!=line.find("*FRAME TIME"))
            {
                append="FRAMES TIME: " "0.033333";
                line.assign(append);//Here add the frame time;
            }
            else if (std::string::npos!=line.find("*JOINT"))
            {
              //  std::cout<<"It indeed got Here"<<std::endl;
                calculateInitalParameter();
                int counter=0;
                int frameNumber=0;
//                int k= (int)shape3D.size();
                append="";
                for (std::vector<cv::Point3_<double> >::iterator i = shape3D.begin();
                                           i != shape3D.end();
                                           ++i)
                {
                    if(counter==0)
                    {
                        //Append the root location and the Neck locations (THUS here will be where the pose will be incorporated)
                        append.append("0 0 0 0 0 0 "); //root offset;
                        FACETRACKER::Pose p= poseVec.at(frameNumber);
                        double zRot= p.roll;
                        double yRot= p.yaw;
                        double xRot= p.pitch;
                        append.append(doubleToString(zRot) +" "+ doubleToString(xRot)+ " " + doubleToString(yRot) +" ");// Neck update from the pose of the funciton;
                    }

                    cv::Point3_<double> m= (*i);

                    double x= m.x;
                    double y= m.y;
                    double z= m.z;

                    append.append(doubleToString(x) + " " + doubleToString(y) + " "+doubleToString(z) + " ");

                    counter++;
                    //This affects the blendshapes only;
                    if(counter==66)
                    {
                    std::cout<<"Frame Number "<<frameNumber<<std::endl;
                        if(frameNumber < sizeVec)
                        {

                            append.append("0 0 0 0 0 0 ");
                            resetOffset();
                            append.append(generateAnimation(frameNumber*66));
                            append.append("\n");
                            counter=0;
                            frameNumber+=1;
                        }
                        }
                }
                line.assign(append);
                //Now here iterate over the array to find the location.
                //Way to iterate over the array such that it breaks at 66;
                //Create the animation array too.
            }
//            else
//                line.append(readLine);
            myOutFile<<line;
            myOutFile<<"\n";


        }
        return true;
    }
    else
        return false;
}
void ExpressionDetector::resetOffset()
{
    xP=-30;
    zP=-40;
    yP=-50;
}

void ExpressionDetector::calculateInitalParameter()
{
//For the brows;
int frameNumber=0;

    brownDownL= (shape.at(frameNumber+37)).y -(shape.at(frameNumber+19)).y;
    brownDownR= (shape.at(frameNumber+44)).y -(shape.at(frameNumber+24)).y;
    brownDownC= (shape.at(frameNumber+27)).y -(shape.at(frameNumber+21)).y;
    mouthArea= generateArea(frameNumber);
    jawLine= (shape.at(frameNumber+27)).x - (shape.at(frameNumber+8)).x;
    lipDistance_L= (shape.at(frameNumber+54)).x - (shape.at(frameNumber+27)).x;
    lipDistance_R= (shape.at(frameNumber+48)).x - (shape.at(frameNumber+27)).x;

    differenceValueInitial[0]= brownDownL;
    differenceValueInitial[1]= brownDownC;
    differenceValueInitial[2]= brownDownR;
    differenceValueInitial[3]= mouthArea;
    differenceValueInitial[4]= jawLine;
    differenceValueInitial[5]= lipDistance_L;
    differenceValueInitial[6]= lipDistance_R;



    differenceValueMax[0]= 0.1;
    differenceValueMax[1]= 0.1;
    differenceValueMax[2]= 0.1;
    differenceValueMax[3]= 0.1;
    differenceValueMax[4]= 0.1;
    differenceValueMax[5]= 0.1;

    differenceValueMin[0]= 0.0;
    differenceValueMin[1]= 0.0;
    differenceValueMin[2]= 0.0;
    differenceValueMin[3]= 0.0;
    differenceValueMin[4]= 0.0;
    differenceValueMin[5]= 0.0;

//Here call the generate Area fucntion;
}
double ExpressionDetector::generateArea(int frameNumber)
{

    //Currently SEt the areas;
    //Set the points for the internal mouth;
double area=0;
    std::vector<cv::Point_<double> > listOfPoints;
    //For the case of the mouth since they are points from the 60 to 65 points
    //copy those data's to the location of the points;
    for (int i=0; i< 6; i++)
    listOfPoints.push_back(shape.at(frameNumber+60 +i));
    int j=4;

    for(int i=0; i< 5; i++)
    {
        area= area+ (listOfPoints.at(j).x + listOfPoints.at(i).x )* (listOfPoints.at(j).y + listOfPoints.at(i).y);
    }
if(area < 0)
    area= area*-1;

return area/2;

}

void ExpressionDetector::calculateDifference(int frameNumber)
{
 //cv::Point_<double> m= shape.at(frameNumber);
    //This above may be needed the following generator doesn't give the task
    //desired.
 if(frameNumber>0)//Now this makes is run fine;
 {
     brownDownL= (shape.at(frameNumber+37)).y -(shape.at(frameNumber+19)).y;
     brownDownR= (shape.at(frameNumber+44)).y -(shape.at(frameNumber+24)).y;
     brownDownC= (shape.at(frameNumber+27)).y -(shape.at(frameNumber+21)).y;
     mouthArea= generateArea(frameNumber);
     jawLine= (shape.at(frameNumber+27)).x - (shape.at(frameNumber+8)).x;
     lipDistance_L= (shape.at(frameNumber+54)).x - (shape.at(frameNumber+27)).x;
     lipDistance_R= (shape.at(frameNumber+48)).x - (shape.at(frameNumber+27)).x;

     brownDownC= brownDownC -differenceValueInitial[1];
     brownDownL= brownDownL -differenceValueInitial[0];
     brownDownR= brownDownR -differenceValueInitial[2];
     mouthArea= mouthArea - differenceValueInitial[3];

     jawLine= jawLine - differenceValueInitial[4];
     lipDistance_L= lipDistance_L - differenceValueInitial[5];//May Be Area is a better choice;
     lipDistance_R= lipDistance_R - differenceValueInitial[6];
     //Set's the difference for the two frame here; Now it's going forward from this definition.
     if(frameNumber==66)
     {
     differenceValueMax[0]= brownDownL;
     differenceValueMax[1]= brownDownC;
     differenceValueMax[2]= brownDownR;
     differenceValueMax[3]= mouthArea;
     differenceValueMax[4]= jawLine;
     differenceValueMax[5]= lipDistance_L;
     differenceValueMax[6]= lipDistance_R;

     differenceValueMin[0]= brownDownL;
     differenceValueMin[1]= brownDownC;
     differenceValueMin[2]= brownDownR;
     differenceValueMin[3]= mouthArea;
     differenceValueMin[4]= jawLine;
     differenceValueMin[5]= lipDistance_L;
     differenceValueMin[6]= lipDistance_R;
    }
     //This things doesn't seem right;
     //Why?
     //Because this run seems that unless it's less than zero it doesn't change the correspoinding values;
     //Then rather than making like that; Use the inital value to set the difference.

             if(brownDownC<0)//Now It Can;
             {
                 if(brownDownC < differenceValueMin[1])
                 {
                     differenceValueMin[1]= brownDownC;
                 }
             }
             else
             {
                 if(brownDownC > differenceValueMax[1])
                 {
                     differenceValueMax[1]= brownDownC;
                 }
             }
             if(brownDownL<=0)
             {
                 if(brownDownL < differenceValueMin[0])
                 {
                     differenceValueMin[1]= brownDownL;
                 }
             }
             else
             {
                 if(brownDownL > differenceValueMax[0])
                 {
                     differenceValueMax[0]= brownDownL;
                 }
             }
             if(brownDownR<0)
             {
                 if(brownDownR < differenceValueMin[2])
                 {
                     differenceValueMin[1]= brownDownR;
                 }
             }
             else
             {
                 if(brownDownR > differenceValueMax[2])
                 {
                     differenceValueMax[2]= brownDownR;
                 }
             }
             //This doesn't have a less than zero;
             //if(mouthArea<0)
             //{
                 //if(mouthArea < differenceValueMin[3])
                 //{
                 //    differenceValueMin[3]= mouthArea;
               //  }
             //}
             //else
             //{
                 if(mouthArea > differenceValueMax[3])
                 {
                     differenceValueMax[3]= mouthArea;
                 }
             //}
             if(jawLine<0)
             {
                 if(jawLine < differenceValueMin[4])
                 {
                     differenceValueMin[4]= jawLine;
                 }
             }
             else
             {
                 if(jawLine > differenceValueMax[4])
                 {
                     differenceValueMax[4]= jawLine;
                 }
             }
             if(lipDistance_L<0)
             {
                 if(lipDistance_L < differenceValueMin[5])
                 {
                     differenceValueMin[5]= lipDistance_L;
                 }
             }
             else
             {
                 if(lipDistance_L > differenceValueMax[5])
                 {
                     differenceValueMax[5]= lipDistance_L;
                 }
             }

             if(lipDistance_R<0)
             {
                 if(lipDistance_R < differenceValueMin[6])
                 {
                     differenceValueMin[5]= lipDistance_R;
                 }
             }
             else
             {
                 if(lipDistance_R > differenceValueMax[6])
                 {
                     differenceValueMax[5]= lipDistance_R;
                 }
             }
}
}

std::string ExpressionDetector::generateAnimation(int frameNumber)
{
    std::string s;
    //Move the location of Blendshapes so they are not overlapping.
    //For the EyeBlink_L
    s= getOffset();
    bool bo=eyeBlinkL.at(frameNumber/66);

            if(!bo)
    {
            s.append("90 ");
}
            else
    {
            s.append("0 ");
}
            s.append(getOffset());
   bo= eyeBlinkR.at(frameNumber/66);
   if(!bo)
   {
       s.append("90 ");
    }
       else
    {
       s.append("0 ");
   }
   //For all the rest eye movements;
   for(int i=0; i<12; i++)
   {
       s.append(getOffset());
       s.append("0 ");
   }
   //Do for the Brows;
   calculateDifference(frameNumber);
   double angle=0;
   s.append(getOffset());
   if(brownDownL<0)//Then the brown is Down; then update This --affect the third down;
   {
       brownDownL= -1* brownDownL;

       angle= brownDownL * 90/ (-1*differenceValueMin[0]);
       //Now the INital Pose Value is zero
       //the minimum is the max; Cris Cross it;

   }

   s.append(doubleToString(angle));
s.append(" ");
   angle=0;
   s.append(getOffset());
   if(brownDownR<0)
   {

       brownDownR= -1* brownDownR;

       angle= brownDownR * 90/ (-1*differenceValueMin[2]);
       //Now the INital Pose Value is zero
       //the minimum is the max; Cris Cross it;

   }
   s.append(doubleToString(angle));
s.append(" ");

//Brow C Up
angle=0;
   s.append(getOffset());
   if(brownDownC>0)
   {
          angle= brownDownC * 90/ (differenceValueMax[1]);
       //Now the Inital Pose Again is Zero
       //The Maximum value is the 90; Now cris cross it;
   }
   s.append(doubleToString(angle));
    s.append(" ");
//Brow L Up
angle=0;
   s.append(getOffset());
   if(brownDownL>0)
   {
          angle= brownDownL * 90/ (-1*differenceValueMin[0]);
       //Now the Inital Pose Again is Zero
       //The Maximum value is the 90; Now cris cross it;
   }
   s.append(doubleToString(angle));
   s.append(" ");
//Brow Left U
angle=0;
    s.append(getOffset());
   if(brownDownR>0)
   {
       angle= brownDownR * 90/ (-1*differenceValueMin[2]);
       //Now the Inital Pose Again is Zero
       //The Maximum value is the 90; Now cris cross it;
   }
   s.append(doubleToString(angle));
   s.append(" ");

   //For Jaw FWD
   s.append(getOffset());
   s.append("0 ");
   //For Jaw Left
   angle=0;
   s.append(getOffset());
   if(jawLine < 0)
   {
    angle= jawLine * 45 / (-1 * differenceValueMin[4]);
   }
   s.append(doubleToString(angle));
   s.append(" ");
   //Jaw Open;
    angle= 0;
    s.append(getOffset());
    if(mouthArea > 0)
    {

        angle= mouthArea * 90 / (differenceValueMax[3]);

    }
     std::cout<<"Area of The Frame Number "<<frameNumber/66<<" - "<<angle<<std::endl;
    s.append(doubleToString(angle));
    s.append(" ");
            //if()
   //Jaw Chew - Zero
   s.append(getOffset());
   s.append("0 ");
   //Jaw Right
   angle=0;
   s.append(getOffset());
   if(jawLine > 0)
   {
       angle= jawLine * 45 /(differenceValueMax[4]);
   }
   s.append(doubleToString(angle));
   s.append(" ");
   //Mouth Left
   s.append(getOffset());
   s.append("0 ");
   //Mouth Right
   s.append(getOffset());
   s.append("0 ");
   //Mouth Frown
   s.append(getOffset());
   s.append("0 ");
   //Mouth Frown
   s.append(getOffset());
   s.append("0 ");
   //Mouth Smile Both done here;
   bo= smileFull.at(frameNumber/66);
   if(bo > 0.2)
   {
       //Right
       s.append(getOffset());
       s.append("90 ");
//Left
       s.append(getOffset());
       s.append("90 ");

   }
   else
   {
       angle=0;
       s.append(getOffset());
        if(lipDistance_L > 0)//Which is always true; less head movement
        {
            angle= lipDistance_L * 45 /(differenceValueMax[5]);
        }
        s.append(doubleToString(angle));
        s.append(" ");
        angle=0;
        s.append(getOffset());
        //The case for the else is for lip pucker
        if(lipDistance_R < 0)// which is alway true; less head movement
        {
        angle= lipDistance_R * 45 /(differenceValueMin[6]);
        angle= std::abs(angle);
        }
        s.append(doubleToString(angle));
        s.append(" ");
   }

   //Mouth dimple Left and Right;
   s.append(getOffset());
   s.append("0 ");
   s.append(getOffset());
   s.append("0 ");
   //Lip Streach for both
   s.append(getOffset());
   s.append("0 ");
   s.append(getOffset());
   s.append("0 ");
   //LIp Uper and Lower Closes;
   s.append(getOffset());
   s.append("0 ");
   s.append(getOffset());
   s.append("0 ");
   //Lip Upper Up and Down
   //This is a combination for the mouth area parameter;
   s.append(getOffset());
   angle=0;

if(mouthArea> 0)
{
     angle= jawLine * 90 /(differenceValueMax[3]);
}
s.append(doubleToString(angle));
s.append(" ");
s.append(getOffset());
angle=0;

if(mouthArea>0)
{
      angle= jawLine * 90 /(differenceValueMax[3]);
}
s.append(doubleToString(angle));
s.append(" ");
   //LIP Upper and Lower OPEN
   s.append(getOffset());
   s.append("0 ");
   s.append(getOffset());
   s.append("0 ");

   //LIP FUNNEL
   s.append(getOffset());
   s.append("0 ");
   //LIP PUCKER
   angle=0;
   s.append(getOffset());
    if(lipDistance_L < 0)
    {
        angle= lipDistance_L * 45 /(differenceValueMin[5]);
    }
    if(lipDistance_R > 0)// which is alway true; less head movement
    {
    angle= std::abs(angle);
    double x;
    x= lipDistance_R * 45 /(differenceValueMax[6]);
    angle= std::abs(angle) + std::abs(x);
    }
    s.append(doubleToString(angle));
    s.append(" ");
   //CHINELOWERRAISE TO CHECK SQUINT_R
   for(int i=0; i< 6; i++)
   {
       s.append(getOffset());
       s.append("0 ");
   }
return s;
}
void ExpressionDetector::viewImage()
{
    cv::namedWindow("Facial Expression Tracker");
    cv::imshow("Facial Expression Tracker", image);
}
//Template It;
std::string ExpressionDetector::intToString(int x)
{
    std::stringstream ss;
    ss.str(std::string());
    ss<<x;
    std::string xLoc= ss.str();
    return xLoc;
}
std::string ExpressionDetector::doubleToString(double x)
{
    std::stringstream ss;
    ss.str(std::string());
    ss<<x;
    std::string xLoc= ss.str();
    return xLoc;
}

void ExpressionDetector::paintOnPicture(cv::Mat &image, cv::Point_<double> point)
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
void ExpressionDetector::paintOnPicture(cv::Mat &image, cv::Point_<double> point, int)
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
void ExpressionDetector::detectSmile(cv::Rect regionMouth, cv::Rect regionEyeL, cv::Rect regionEyeR)
{
    //Here create the ROI of from the image;
    cv::Point point;
    cv::Mat ima2;
    //cv::equalizeHist(image, ima2);
    cv::Mat roi;
    cv::CascadeClassifier smileCascade, eyeCascadeL, eyeCascadeR;
    bool eyeRDetect= false;
    if(image.rows > 0 && image.cols > 0)
    {
        if(regionMouth.size().height < image.size().height && regionMouth.size().width < image.size().width)
        {
            roi= image(regionMouth);
            std::vector<cv::Rect> smiles;
            ///opt/ros/hydro/share/OpenCV/haarcascades/haarcascade_smile.xml
            smileCascade.load("smiled_05.xml");
            smileCascade.detectMultiScale(roi,smiles,1.1,2,0 | CV_HAAR_SCALE_IMAGE, cv::Size(30,30));
            const int smile_neighbors= (int) smiles.size();
            static int max_neighbors=-1;
            static int min_neighbors=-1;
            if(min_neighbors==-1) min_neighbors=smile_neighbors;
            if(smile_neighbors>max_neighbors)
                max_neighbors=smile_neighbors;

            float intensityZeroOne= ((float)smile_neighbors-min_neighbors)/(max_neighbors-min_neighbors+1);
            cv::rectangle(image, regionMouth, cv::Scalar(212, 33, 128));
            //Area to print the message away;
            point.x= image.size().width/2;
            point.y= image.size().height - image.size().height/15;
            //Now Here these Values Since it's
           // std::cout<<intensityZeroOne<<std::endl;
            if(intensityZeroOne>0.2)
            {
                cv::putText(image, "Smile", point, cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(255, 0, 0));
            }
            else
            {
                cv::putText(image, "Not Smile", point, cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(255, 0, 0));
            }
            smileFull.push_back(intensityZeroOne);
        }
        if(regionEyeL.size().height < image.size().height && regionEyeL.size().width < image.size().width)
        {
            bool eyeLDetect= false;
            point.x= image.size().width - 3*image.size().width/4;
            point.y= 10;
            cv::Mat roiEL(image, regionEyeL);

            cv::rectangle(image, regionEyeL, cv::Scalar(212, 33, 128));
            cv::rectangle(image, regionEyeR, cv::Scalar(212, 33, 128));
            std::vector<cv::Rect> eyeL;
            eyeCascadeL.load("haarcascade_eye_tree_eyeglasses.xml");
            eyeCascadeL.detectMultiScale(roiEL, eyeL,1.1,2,0 | CV_HAAR_SCALE_IMAGE, cv::Size(30,30));
            if(eyeL.size()>0)
            {
                eyeLDetect=true;
            }
            if(eyeLDetect)
            {
                cv::putText(image, "Eye Open 1", point, cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(255, 0, 0));
            }
            else
                cv::putText(image, "Eye not Open 1", point, cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(255, 0, 0));
            eyeBlinkL.push_back(eyeLDetect);

        }

        if(regionEyeR.size().height < image.size().height && regionEyeR.size().width < image.size().width)
        {
            cv::Mat roiER(image, regionEyeR);
            //Note here the the change can be needed if the case doesn't reflect on the data;

            std::vector<cv::Rect> eyeR;

            eyeCascadeR.load("haarcascade_eye_tree_eyeglasses.xml");
            eyeCascadeR.detectMultiScale(roiER, eyeR,1.1,2,0 | CV_HAAR_SCALE_IMAGE, cv::Size(30,30));

            if(eyeR.size()>0)
            {
                eyeRDetect=true;
            }
            point.x= image.size().width - image.size().width/2;
            point.y= 10;
            if(eyeRDetect)
            {
                cv::putText(image, "Eye Open 2", point, cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(255, 0, 0));
            }
            else
            {
                cv::putText(image, "Eye not Open 2", point, cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(255, 0, 0));
            }
            eyeBlinkR.push_back(eyeRDetect);
        }

    }


}


