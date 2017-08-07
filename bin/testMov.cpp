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
  LibSeek::SaveImages sav;
  int aantAfbeeldingen = 10;
  std::string folder_save = "./Masks/img";
  std::vector<float> bounds;  
  cv::Mat img_bed, img_current, img_prev, mask, mask_def;
  std::string path;
  path="./SavedBySeekCam/img0.pbm";
  img_bed=get.getImage(path);
  LibSeek::Detect det (img_bed);
  //path="/home/nele/Desktop/img0_uint8.png";
  std::string folder_in="./SavedPics/img";
  std::string result;
  for (int tel = 0; tel<=aantAfbeeldingen;tel++)
  {
    path=folder_in+std::to_string(tel)+".pbm";
    img_current = get.getImage(path);
    if (tel>0)
    {
      mask=det.tempDifference(img_prev, img_current);
      path = folder_save+std::to_string(tel)+".pbm";
      sav.saveImage(mask,path);
      mask_def=det.createMaskNew(mask,img_current);
      path = folder_save+std::to_string(tel+50)+".pbm";
      sav.saveImage(mask_def,path);
      result = det.checkBed(mask_def);
      std::cout<<result+std::to_string(tel)<<std::endl;
    }
    img_prev=img_current.clone();
  }
}
