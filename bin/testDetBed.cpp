/*
 *  Main loop
 *  Author: Nele Annaert
 */

#include "GetImages.h"
#include "Detect.h"


int main (int argc, char** argv)
{
  LibSeek::GetImages get;
	int teller;
	int AANTFRAMES = 232;
  std::string path="./Masks/img";
	std::string path_full;
	bool result;
  cv::Mat img;
	cv::Mat bed = get.getImage("./Bed/bed.pbm");
	LibSeek::Detect det(bed);
	for (teller = 0 ; teller < AANTFRAMES ; teller ++)
	{
  	path_full = path + std::to_string(teller) + ".pbm";
		img=get.getImage(path_full);
		result = det.detectionHead(img);
	}
}
