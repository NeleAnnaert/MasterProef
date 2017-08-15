/*
 *  Programma voor het opslagen van de calibratieafbeelding van het bed
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
		std::string path="./Bed/bed.pbm";

    if (!seek.open()) {
        std::cout << "failed to open seek cam" << std::endl;
        return -1;
    }
    if (!seek.grab()) {
        std::cout << "no more LWIR img" << endl;
        return -1;
    }
    seek.retrieve(frame);
    cv::normalize(frame, frame, 0, 65535, cv::NORM_MINMAX);
		save.saveImage(frame,path);
    cv::imshow("BED", frame);
    cv::waitKey(0);
}
