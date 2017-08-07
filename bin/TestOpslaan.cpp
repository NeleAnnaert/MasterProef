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
    int NUMFRAMES= 50; 
    std::string pad;

    if (!seek.open()) {
        std::cout << "failed to open seek cam" << std::endl;
        return -1;
    }

    aant=0;
    counter=0;
    while(1) {
        if (!seek.grab()) {
            std::cout << "no more LWIR img" << endl;
            return -1;
        }

        seek.retrieve(frame);
        cv::normalize(frame, frame, 0, 65535, cv::NORM_MINMAX);
	counter++;
        if (counter==NUMFRAMES){
          pad="./SavedByCam/img"+std::to_string(aant)+".bpm";
          save.saveImage(frame,pad);	//Opslaan van de afbeelding
	  aant++;
          counter=0;
        }
        cv::imshow("LWIR", frame); 	//Weergeven van het frame

        char c = cv::waitKey(10);
        if (c == 's') {
            cv::waitKey(0);
        }
    }
}
