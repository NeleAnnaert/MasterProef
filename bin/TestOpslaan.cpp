/*
 *  main looop 
 *  Author: Nele Annaert 
 */
#include <opencv2/highgui/highgui.hpp>
#include "seek.h"
#include "SaveImages.h"
#include <iostream>

int main(int argc, char** argv)
{
    LibSeek::SeekThermal seek;
    LibSeek::SaveImages save;
    cv::Mat frame;
    int aant,counter;
    int NUMFRAMES= 5; 
    std::string pad;

    if (!seek.open()) {
        std::cout << "failed to open seek cam" << std::endl;
        return -1;
    }

    aant=0;
    while(1) {
        if (!seek.grab()) {
            std::cout << "no more LWIR img" << endl;
            return -1;
        }
				if (counter == 0)
				{
        	seek.retrieve(frame);
        	cv::normalize(frame, frame, 0, 65535, cv::NORM_MINMAX);
					counter++;
        	pad="./SavedFrames/img"+std::to_string(aant)+".pbm";
        	save.saveImage(frame,pad);	//Opslaan van de afbeelding
	  			aant++;
        	cv::imshow("LWIR", frame); 	//Weergeven van het frame
			  }
				else if (counter == NUMFRAMES)
				{
				  counter = 0;
				}
				else
				{
				  counter ++;
				}
    }
}
