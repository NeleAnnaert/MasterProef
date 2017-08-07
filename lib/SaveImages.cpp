/*
 *  Fuction File Saving Images 
 *  Saving images recorded by the seek cam
 *  Author: Nele Annaert 
 */
 
#include "SaveImages.h"
#include <string>
#include <iostream>

using namespace LibSeek;
std::string DIRECTORY="./SavedPics/";
std::vector<int> compression_params;
bool testWrite;

void SaveImages::saveImage (cv::Mat frame,std::string pad)
{
  compression_params.push_back(CV_IMWRITE_PXM_BINARY);
  compression_params.push_back(100);
  testWrite=cv::imwrite(pad,frame,compression_params);
}

