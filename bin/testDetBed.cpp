/*
 *  Main loop
 *  Author: Nele Annaert
 */

#include "GetImages.h"
#include "Bed.h"

int main (int argc, char** argv)
{
  LibSeek::GetImages get;
  std::vector<float> bounds;  
  std::string path="./SavedBySeekCam/img0.pbm";
  cv::Mat img;
  img=get.getImage(path);
  LibSeek::Bed bed(img);
  bounds = bed.sidesOfBed();
}
