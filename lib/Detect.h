/*
 *  Headerfile Class used for te detection
 *  Author: Nele Annaert
 */

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <string>
#include <vector>

#include "Bed.h"

namespace LibSeek {
/*---------- Decalration of the class and used methods ----------*/
class Detect
{
  LibSeek::Bed bed;
public:
  /*
   *  Constructor
   *  No argtuments
   */
   Detect(cv::Mat img);
  /*
   *  Constructor
   *  8 ints as argument
   */
   Detect(int irbx, int irby, int irox, int iroy, int ilox, int iloy, int ilbx, int ilby);
  /*
   *  Output: Boolean
   *  Input: 2 frames
   *  GOal: check for movement
   */
  bool checkMovement(cv::Mat prev, cv::Mat current);
  /* 
   *  Output: Mask after person detection
   *  Input: Original image
   *  GOal: Detect the person and create mask so person isn't 
      recognisable
   */
   cv::Mat createMask(cv::Mat img);
  /*
   *  Output String met daarin of er een alarm moet gegenereerd worden
   *  Input: Masker
   */
  std::string checkBed(cv::Mat mask);
  /*
   *  Output afbeeling met 255 waar pixel is verandert 
   *  Input: 2 opeenvolgende frames 
   */
  cv::Mat tempDifference(cv::Mat prev, cv::Mat current);
  /*
   *  Output masker 
   *  Input: bewegingsmasker en frame 
   */
  cv::Mat createMaskNew(cv::Mat movementMask, cv::Mat frame);
  /*
   *  Output eraded and dilated picture 
   *  Input: masker 
   */
  cv::Mat erDil(cv::Mat img, int size);
  /*
   *  Output afbeeling met 255 waar pixel is verandert en waarde binnen terhold 
   *  Input: 2 opeenvolgende frames 
   */
  cv::Mat tempDifferenceNew(cv::Mat prev, cv::Mat current);
  /*
   *  Output bool met waarde true als een persoon in bed ligt 
   *  Input:  masker
   */
	bool detectionHead (cv::Mat mask);
}; 	//End of class
}	//End of LibSeek
