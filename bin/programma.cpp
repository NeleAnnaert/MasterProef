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
  std::string folder_save = "./MovMasks/img";
  std::string folder_saveMask = "./Masks/img";
  std::vector<float> bounds;  
  cv::Mat img_bed, img_current, img_prev, mask, mask_def;
  std::string path;
  path="./Bed/bed.pbm";
  img_bed=get.getImage(path);
  LibSeek::Detect det (img_bed);
  std::string folder_in="./SavedFrames/img";
  std::string result;
  int aantAfbeeldingen = 845;
  for (int tel = 0; tel<=aantAfbeeldingen;tel++)
  {
    path=folder_in+std::to_string(tel)+".pbm";
    img_current = get.getImage(path);
    if (tel>0)
    {
      mask=det.tempDifferenceNew(img_prev, img_current);
      path = folder_save+std::to_string(tel)+".pbm";
      sav.saveImage(mask,path);
      mask_def=det.createMaskNew(mask,img_current);
      path = folder_saveMask+std::to_string(tel)+".pbm";
      sav.saveImage(mask_def,path);
      result = det.checkBed(mask_def);
      std::cout<<result+std::to_string(tel)<<std::endl;
    }
    img_prev=img_current.clone();
  }
}
