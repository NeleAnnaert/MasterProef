/*
 *  Headerfile Class used for determine dimentia of the bed
 *  Author: Nele Annaert
 */

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <iostream>
#include <string>

namespace LibSeek  {
/*---------- Declaration of the class and used methods ----------*/
//For creating an object off this class yuou insert the location of the 4 corners
class Bed
{
  int rbx, rby, rox, roy, lox, loy, lbx, lby; 
public:
  /*
   *  Constructor
   */
  Bed();
  /* 
   *  Constructor
   *  Input 8 int, these are the coordinats of the corners of the bed
   */
  Bed (int irbx, int irby, int irox, int iroy, int ilox, int iloy, int ilbx, int ilby);
  /*
   *  Constructor
   *  Input an image, to select the corners of the bed
   */
  Bed(cv::Mat img);
  /* 
   *  Output: None
   *  Input: The values for the points of the corners
   */
  void setValues (int irbx, int irby, int irox, int iroy, int ilox, int iloy, int ilbx, int ilby);
  /* 
   *  Output: None
   *  Input: image to determin the values for the points of the corners
   */
  void setValuesImg (cv::Mat img);
  /*
   *  Output: Vector with coefficients of the lines (side of the bed)
   *  Input: None
   */
   std::vector<float> sidesOfBed();
};	//End of the class
  /*
   *  Output: None
   *  Input: event, coordinats of the click, int flags and the vector
   */
  void mouseCallBack(int event, int x, int y, int flags, void* userdata);
} 	//End of the namespace
