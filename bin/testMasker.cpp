/*
 *  Main loop
 *  Author: Nele Annaert
 */

#include "GetImages.h"
#include "Detect.h"
#include "SaveImages.h"
#include "seek.h"

int main (int argc, char** argv)
{
  LibSeek::SeekThermal seek;
  LibSeek::GetImages get;
  LibSeek::SaveImages save;
  std::string path="./Bed/bed.pbm";
	std::string path_save;
  cv::Mat img;
  cv::Mat img_save;
  cv::Mat mask;
  img=get.getImage(path);
  LibSeek::Detect det(img);
	int AANTFRAMES = 231;
	for (int i = 0; i < AANTFRAMES ; i++)
	{
	  path="./SavedFrames/img";
		path+=std::to_string(i);
		path +=".pbm";
		img = get.getImage(path);
		mask = det.createMask(img);
		imshow("masker",mask);
		cv::waitKey(0);
		path_save="./Masks/img"+std::to_string(i)+".pbm";
		save.saveImage(mask,path_save);
	}
}
