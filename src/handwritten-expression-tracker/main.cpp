#include "expressiondetector.h"
#include <time.h>
int main(int argc, char* argv[])
{
 time_t rawtime;
   ExpressionDetector e;
   try
   {
       if(argc==1)
    {
           std::cout<<"Using Camera"<<std::endl;
           time(&rawtime);
           e.setVideoWriteLocation(ctime(&rawtime));
           e.setVideoSource();
    }
       else if(argc==2)
       {
           //I have to change this function to the one in which the webcam video can also be
           //saved to the data form.
           std::cout<<"Using File"<<argv[1];
           e.setVideoSource(argv[1]);
       }
       e.processVideo();
       time(&rawtime);
       //std::cout<<"Trying to Save to File output_currentTime.BVH"<<std::endl;
       bool sucess=e.generateBVH(ctime(&rawtime));
       if (sucess)
           std::cout<<"Saving Sucessfull"<<std::endl;
       else
           std::cout<<"Saving Unsucessful"<<std::endl;
   }
   catch(int n)
   {
       if (n==12345)
       {
           std::cout<<"File Not Found"<<std::endl;
       }
       else
       std::cout<<"Camera Not Found"<<std::endl;
   }
   catch(cv::Exception e)
   {
       std::cout<<"opencv"<<std::endl;
   }

}
