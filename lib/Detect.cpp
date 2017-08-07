/*
 * Detect people in bed and see when they step out
 * Author: Nele Annaert
 */

#include "Detect.h"

using namespace LibSeek;

Detect::Detect(cv::Mat img)
{
  bed.setValuesImg(img);
}

Detect::Detect (int irbx, int irby, int irox, int iroy, int ilox, int iloy, int ilbx, int ilby)
{
  bed.setValues (irbx, irby, irox, iroy, ilox, iloy, ilbx, irby);
}

bool Detect::checkMovement(cv::Mat prev, cv::Mat current)
{
  int dif, i, j, rows,cols, TRESH;
  bool move;
  dif=0;
  TRESH=150;
  rows=prev.rows;
  cols=prev.cols;
  for (j=0;j<cols;j++)
  {
    for (i=0;i<rows;i++)
    {
      if(current.at<uchar>(i,j)!=prev.at<uchar>(i,j))
      {
        dif++;
      }
    }
  }
  std::cout<<std::to_string(dif)<<std::endl;
  if (dif<TRESH)
    move=false;
  else
    move=true;
  return move;
}

cv::Mat Detect::createMask(cv::Mat img)
{
  cv::Mat oneChannel;
  cv::cvtColor(img,oneChannel,cv::COLOR_RGB2GRAY);
  cv::Mat mask;
  int rows=img.rows;
  int cols=img.cols;
  mask=cv::Mat::zeros(rows,cols,CV_8UC1);
  int tresh = 180;
  for (int j=0;j<cols;j++)
  {
    for ( int i=0;i<rows;i++)
    {
      mask.at<uchar>(i,j) = oneChannel.at<uchar>(i,j)>tresh?255:0;
    }
   }
  mask=erDil(mask,1);
  return mask;
}

std::string Detect::checkBed(cv::Mat frame)
{
  int i,j,rows,cols;
  float xLeft, xRight;
  bool found;
  std::vector<float> bounds;
  std::string outBed;
  outBed="none";		//We nemen aan dat er niets uit het bed steekt
  found=false;
  bounds=bed.sidesOfBed();
  rows=frame.rows;
  cols=frame.cols;
  cv::Mat mask=cv::Mat::zeros(rows,cols,CV_8UC1);
  for (j=0;j<cols && !found;j++)
  {
    for (i=0;i<rows;i++)
    {
      if(frame.at<uchar>(i,j)==255)
      {
        //xLeft=(i-bounds[0])/bounds[1];
        xLeft=bounds[0]*j+bounds[1];
        //xRight=(i-bounds[2])/bounds[3];
        xRight=bounds[2]*j+bounds[3];
        if(i>xLeft)
        {
          outBed="left";
          found=true;
          break;
        }
        else if(i<xRight)
        {
          outBed="right";
          found=true;
          break;
        }
      }
    }
  } 
  return outBed;
}
cv::Mat Detect::tempDifference(cv::Mat prev, cv::Mat current)
{
  int i, j, rows,cols;
  cv::Mat movementMask;
  cv::Mat oneChannel_current, oneChannel_prev;
  cv::cvtColor(prev,oneChannel_prev,cv::COLOR_RGB2GRAY);
  cv::cvtColor(current,oneChannel_current,cv::COLOR_RGB2GRAY);
  rows=prev.rows;
  cols=prev.cols;
  movementMask=cv::Mat::zeros(rows,cols,CV_8UC1);
  for (j=0;j<cols;j++)
  {
    for (i=0;i<rows;i++)
    {
      if(oneChannel_current.at<uchar>(i,j)!=oneChannel_prev.at<uchar>(i,j))
      {
        movementMask.at<uchar>(i,j)=255;
      }
    }
  }
  return movementMask;
}

cv::Mat Detect::createMaskNew(cv::Mat movementMask,cv::Mat frame)
{
  cv::Mat oneChannel;
  cv::cvtColor(frame,oneChannel,cv::COLOR_RGB2GRAY);
  cv::Mat mask, mask_open;
  int rows=frame.rows;
  int cols=frame.cols;
  mask=cv::Mat::zeros(rows,cols,CV_8UC1);
  int tresh = 180;
  for (int j=0;j<cols;j++)
  {
    for ( int i=0;i<rows;i++)
    {
      if(movementMask.at<uchar>(i,j)==255)
      {
        mask.at<uchar>(i,j) = oneChannel.at<uchar>(i,j)>tresh?255:0;
      }
    }
  }
  mask_open=Detect::erDil(mask,1);
  return mask_open;
}

cv::Mat Detect::erDil(cv::Mat img, int size)
{
  cv::Mat element, img_eroded, img_dilated;
  element = getStructuringElement(cv::MORPH_CROSS,cv::Size(2*size + 1,2*size + 1),cv::Point(size,size));
  erode(img,img_eroded,element);
  dilate(img_eroded,img_dilated,element);
  return img_dilated;
}

cv::Mat Detect::tempDifferenceNew(cv::Mat prev, cv::Mat current)
{
  int i, j, rows,cols;
  int TRESH = 5;
  cv::Mat movementMask;
  cv::Mat oneChannel_current, oneChannel_prev;
  cv::cvtColor(prev,oneChannel_prev,cv::COLOR_RGB2GRAY);
  cv::cvtColor(current,oneChannel_current,cv::COLOR_RGB2GRAY);
  rows=prev.rows;
  cols=prev.cols;
  movementMask=cv::Mat::zeros(rows,cols,CV_8UC1);
  for (j=0;j<cols;j++)
  {
    for (i=0;i<rows;i++)
    {
      if(oneChannel_prev.at<uchar>(i,j) - oneChannel_current.at<uchar>(i,j) > 5)
      {
        movementMask.at<uchar>(i,j)=255;
      }
    }
  }
  return movementMask;
}
