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
	std::string path="./Bed/bed.pbm";
  imgBed=get.getImage(path);
  LibSeek::Bed bedAuto(imgBed,1);
	LibSeek::Bed bedHand(imgBed,0);
}
