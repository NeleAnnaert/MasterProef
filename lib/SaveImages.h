/*
 *  test program seek lib
 *  Saving images recorded by the seek cam
 *  HeaderFile
 *  Author: Nele Annaert 
 */

#include<opencv2/opencv.hpp>
#include<string>

namespace LibSeek {

/*--------- Declaration of the class and used methods ---------*/
class SaveImages
{
public:
  /*
  *   Output: None
  *   Input: Frame that should be saved and path
  *   Goal: Saving the frames
  */
  void saveImage(cv::Mat frame, std::string path);
/*--------------- Declaration of used variables ---------------*/
cv::Mat frame;
int aant;
 }; 	//End of the class

} //End of the namespace
