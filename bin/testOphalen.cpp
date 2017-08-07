/*
 *  Main loop
 *  Author: Nele Annaert
 */

#include "GetImages.h"
#include "Bed.h"

int main (int argc, char** argv)
{
  LibSeek::GetImages get;
  LibSeek::Bed bed(1,2,3,4,5,6,7,8);
  std::vector<float> bounds;  
  std::string path="./SavedBySeekCam/img0.pbm";
  cv::Mat img;
  img=get.getImage(path);
  bounds = bed.sidesOfBed();
}
