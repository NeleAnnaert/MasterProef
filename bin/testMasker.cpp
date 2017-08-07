/*
 *  Main loop
 *  Author: Nele Annaert
 */

#include "GetImages.h"
#include "Detect.h"
#include "SaveImages.h"

int main (int argc, char** argv)
{
  LibSeek::GetImages get;
  LibSeek::SaveImages save;
  std::string path="./SavedBySeekCam/img0.pbm";
  cv::Mat img;
  cv::Mat vorig_img;
  cv::Mat mask;
  bool move;
  img=get.getImage(path);
  LibSeek::Detect det (img);
  path="./SavedPics/img3.pbm";
  vorig_img=get.getImage(path);
  path="./SavedPics/img4.pbm";
  img=get.getImage(path);
  move = det.checkMovement (img,vorig_img);
  std::cout<<std::boolalpha;
  std::cout<<move<<std::endl;
  mask=det.createMask(img);
  path= "./SavedBySeekCam/img91.pbm";
  save.saveImage(mask,path);
}
