/*
 *  Main loop
 *  Author: Nele Annaert
 */

#include "GetImages.h"
#include "Bed.h"

int main (int argc, char** argv)
{
  LibSeek::GetImages get;
  cv::Mat imgBed;
	std::string path="./SavedBySeekCam/img0.pbm";
  imgBed=get.getImage(path);
  LibSeek::Bed bedAuto(imgBed,1);
}
