/*
 *  Test program determing values in frame
 *  Author: Nele Annaert
 */
#include "seek.h"

#include <opencv2/highgui/highgui.hpp>
#include <iostream>

int main(int argc, char** argv)
{
    LibSeek::SeekThermal seek;
		LibSeek::SeekThermal save;
    cv::Mat frame,img;
		int min = 50000;
		int max = 0;
		long  som = 0;
    int aantPix, avg;
		int rows,cols;
		int aant_max = 0;
		int aant_min=0;

    if (!seek.open()) {
        std::cout << "failed to open seek cam" << std::endl;
        return -1;
    }
    if (!seek.grab()) {
        std::cout << "no more LWIR img" << endl;
        return -1;
    }

    seek.retrieve(frame);
    cv::imshow("LWIR", frame);

    char c = cv::waitKey(10);
    if (c == 's') {
        cv::waitKey(0);
    }

		rows=frame.rows;
		std::cout<<"aantal rijen: "<<std::to_string(rows)<<std::endl;
		cols=frame.cols;
		std::cout<<"aantal kolommen: " <<std::to_string(cols)<<std::endl;
		aantPix = cols * rows;
		for (int j=0; j<cols; j++)
		{
		  for (int i=0;i<rows; i++)
			{
				int waarde = frame.at<uchar>(i,j);
				som += waarde;
				if (waarde < min)
				{
				  min = waarde;
					aant_min = 1;
				}
				else if (waarde ==min)
				{
				  aant_min++;
				}
				if (waarde > max)
				{
				  max = waarde;
					aant_max = 1;
				}
				else if (waarde == max)
				{
								aant_max++;
				}
			}
		}
		avg= som/aantPix;
		std::cout<<"maximale pixelwaarde: "<<std::to_string (max)<<std::endl;
		std::cout<<"minimale pixelwaarde: "<<std::to_string(min)<<std::endl;
		std::cout<<"gemmiddelde pixelwaarde: " <<std::to_string(avg)<<std::endl;
		std::cout<<"aant max: " <<std::to_string(aant_max)<<std::endl;
		std::cout<<"aant min:" <<std::to_string(aant_min)<<std::endl;
}
