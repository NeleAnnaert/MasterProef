/*
 *  Main loop
 *  Author: Nele Annaert
 */

#include "GetImages.h"
#include "Bed.h"

int main (int argc, char** argv)
{
  LibSeek::GetImages get;
  std::string path="./SavedBySeekCam/img0.pbm";
  cv::Mat imgBed;
  imgBed=get.getImage(path);
  LibSeek::Bed bedHand(imgBed,0);
  LibSeek::Bed bedAuto(imgBed,1);
}
