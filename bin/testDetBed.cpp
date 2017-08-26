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
	int AANTFRAMES = 31;
  std::string path="./Masks/img";
	std::string path_full;
	std::string result;
  cv::Mat img;
	cv::Mat bed = get.getImage("./Bed/bed.pbm");
	LibSeek::Detect det(bed);
	for (teller = 0 ; teller < AANTFRAMES ; teller ++)
	{
  	path_full = path + std::to_string(teller) + ".pbm";
		img=get.getImage(path_full);
		result = det.detectionHead(img);
		std::cout<<" resultaat frame: "<<std::to_string(teller)<<" "<<result<<std::endl;
	}
}
