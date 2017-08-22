/*
 *  Main loop
 *  Author: Nele Annaert
 */

#include "GetImages.h"
#include "Bed.h"


int main (int argc, char** argv)
{
  LibSeek::GetImages get;
	LibSeek::Bed bed;
	int teller;
	int AANTFRAMES = 231;
  std::string path="./SavedFrames/img";
	std::string path_full;
  cv::Mat img;
  std::vector<cv::Point> hoeken;
	for (teller = 116; teller < AANTFRAMES ; teller ++)
	{
  	path_full = path + std::to_string(teller) + ".pbm";
		img=get.getImage(path_full);
		bed.setValuesImg(img);
	}
}
