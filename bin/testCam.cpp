/*
 *  Test program seek lib
 *  Author: Maarten Vandersteegen
 */
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

#include "seek.h"
#include "Detect.h"
#include "GetImages.h"
#include "SaveImages.h"

int main(int argc, char** argv)
{
    LibSeek::SeekThermal seek;
    LibSeek::GetImages get;
    LibSeek::SaveImages save;
    std::string result;
    cv::Mat frame,img_bed, mask, movementMask, prev, current;
    std::string path = "./SavedBySeekCam/img0.pbm";
    img_bed=get.getImage(path);
    LibSeek::Detect det (img_bed);
    if (!seek.open()) {
        std::cout << "failed to open seek cam" << std::endl;
        return -1;
    }

    int counter = 0;
    while(1) {
        if (!seek.grab()) {
            std::cout << "no more LWIR img" << endl;
            return -1;
        }

        seek.retrieve(frame);
        cv::normalize(frame, frame, 0, 65535, cv::NORM_MINMAX);
        cv::imshow("LWIR", frame);
        char c = cv::waitKey(10);
        if (c == 's') {
          cv::waitKey(0);
        }
        path="./SavedFrames/img"+std::to_string(counter)+".pbm";
        save.saveImage(frame,path);
        current = get.getImage(path); 
        if (counter>0)
        {
          movementMask = det.tempDifference(prev,current);
          path="./SavedMovement/img"+std::to_string(counter)+".pbm";
          save.saveImage(movementMask,path);
          mask = det.createMaskNew(movementMask, current);
          path="./SavedMasks/img"+std::to_string(counter)+".pbm";
          save.saveImage(mask,path);
          result = det.checkBed (mask);
          std::cout<<result<<std::endl;
        }
        prev=current.clone();
        counter++;
    }
}
