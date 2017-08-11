/*
 *  Headerfile Class used for retrieving images from computer
 *  Author: Nele Annaert
 */  

#include <opencv2/opencv.hpp>
#include <string>

namespace LibSeek {

/* ---------- Declaration of hte class and used methods ----------*/
class GetImages
{
public:
  /*  
   *  Output: The image you wanted to retrieve
   *  Input: path to the iamge
   *  Goal: retreving image and return it
   */
  cv::Mat getImage(std::string path);
};	//end of class
}	//end of libseek
