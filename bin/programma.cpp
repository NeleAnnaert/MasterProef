/*
 *  Main loop
 *  Author: Nele Annaert
 */

#include "GetImages.h"
#include "Detect.h"
#include "seek.h"
#include "SaveImages.h"

int main (int argc, char** argv)
{
	LibSeek::SeekThermal seek;
  LibSeek::GetImages get;
  LibSeek::SaveImages sav;
  std::string folder_saveMovMasks = "./MovMasks/img";
  std::string folder_saveMask = "./Masks/img";
	std::string folder_save = "./SavedFrames/img";
	std::string result;
  std::vector<float> bounds;  
  cv::Mat img_bed, img_current, img_prev, mask, mask_def, frame, frame_n;
  std::string path;
  path="./Bed/bed.pbm";
  img_bed=get.getImage(path);
  LibSeek::Detect det (img_bed);
	int aant,counter;
	int NUMFRAMES=5;

	if (!seek.open())
	{
		std::cout<< "Failed to open seek cam" <<std::endl;
		return -1;
	}
	aant = 0;
	counter = 0;
	while (1)
	{
    if (!seek.grab())
		{
		  std::cout<< "no mare LWIR img" <<endl;
			return -1;
		}

		if (0 == aant)
		{
		  seek.retrieve(frame);
	    cv::normalize(frame, frame_n, 0, 65535, cv::NORM_MINMAX);
			aant ++;
			counter ++;
			path=folder_save+std::to_string(counter)+".pbm";
			sav.saveImage(frame_n,path);
			img_current=get.getImage(path);
    	if(counter>1)
    	{
      	mask=det.tempDifferenceNew(img_prev, img_current);
      	path = folder_saveMovMasks+std::to_string(counter)+".pbm";
      	sav.saveImage(mask,path);
      	mask_def=det.createMaskNew(mask,img_current);
      	path = folder_saveMask+std::to_string(counter)+".pbm";
      	sav.saveImage(mask_def,path);
      	result = det.checkBed(mask_def);
      	std::cout<<result+std::to_string(counter)<<std::endl;
    	}
    	img_prev=img_current.clone();
		}
		else if ( NUMFRAMES == aant)
		{
      aant=0;
	  }
		else
		{
		  aant++;
		}
  }
}
