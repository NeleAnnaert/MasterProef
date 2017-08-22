/*
 *  Main loop
 *  Author: Nele Annaert
 */

#include "GetImages.h"
#include "DetectNotNormalized.h"
#include "SaveImages.h"
#include "seek.h"

int main (int argc, char** argv)
{
  LibSeek::SeekThermal seek;
  LibSeek::GetImages get;
  LibSeek::SaveImages save;
  std::string path="./Bed/bed.pbm";
  cv::Mat img;
  cv::Mat img_save;
  cv::Mat mask;
  img=get.getImage(path);
  LibSeek::DetectNotNormalized det (img);
  int aant,counter;
	int NUMFRAMES = 5;

	if(!seek.open())
	{
	  std::cout<< "Failed to open seek cam" <<std::endl;
		return -1;
	}
	aant = 0;
	counter = 0;
	while(1)
	{
	  if (!seek.grab())
		{
		  std::cout<< "no more LWIR img" <<std::endl;
			return -1;
		}
		if (0==aant)
		{
		  seek.retrieve(img);
		  cv::normalize(img,img_save, 0, 65535, cv::NORM_MINMAX);
		  aant ++;
			counter ++;
			path="./SavedFrames/img"+std::to_string(counter)+".pbm";
			save.saveImage(img_save,path);
      mask = det.createMask(img);
      path= "./Masks/img"+std::to_string(counter)+".pbm";
      save.saveImage(mask,path);
	  }
		else if (NUMFRAMES == aant)
		{
		  aant = 0;
	  }
		else
		{
		  aant ++;
	  }
	}
	
}
