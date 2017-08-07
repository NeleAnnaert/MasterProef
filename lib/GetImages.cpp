/*
 *  Retrieving images saved on the computer
 *  Author: Nele Annaert
 */

#include "GetImages.h"
#include <iostream>

using namespace LibSeek;

cv::Mat GetImages::getImage (std::string path)
{
  cv::Mat img;
  img=cv::imread(path);
  return img;
}
