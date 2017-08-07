/*
 *  Determine dimentia of the bed
 *  Author: Nele Annaert
 */

#include "Bed.h"
#include <string>
#include <iostream>

//using namespace cv;
using namespace LibSeek;

void LibSeek::mouseCallBack(int event, int x, int y , int flags, void* userdata)
{
  std::vector<cv::Point>* collection = (std::vector<cv::Point>*)userdata;
  cv::Point pt = cv::Point (x,y);
  if (event==cv::EVENT_LBUTTONDOWN)
  {
    std::cout<<"left button is clicked-Postion(" << x <<" , "<< y <<" )" <<std::endl;
  collection->push_back(pt);
  }
  else if (event==cv::EVENT_RBUTTONDOWN)
  {
    std::cout<<"Right button is clicked, the last point is removed" <<std::endl;
    if (collection->size()==0)
    {
      std::cout<<"There are no points in the vector so can't remove one"<<std::endl;
    }
    else
    {
      collection->pop_back();
    }
  }
}
Bed::Bed()
{
  rbx = 0;
  rby = 0;
  rox = 0;
  roy = 0;
  lox = 0;
  loy = 0;
  lbx = 0;
  lby = 0;
  std::cout<<"Uw bed is nu een punt, vergeet geen setValue of setValueImg te doen"<<std::endl;
}


Bed::Bed(int irbx, int irby, int irox, int iroy, int ilox, int iloy, int ilbx, int ilby)
{
  rbx = irbx;
  rby = irby;
  rox = irox;
  roy = iroy;
  lox = ilox;
  loy = iloy;
  lbx = ilbx;
  lby = ilby;
}

Bed::Bed (cv::Mat img)
{
  std::cout<<"Druk met de linkermuisknop op de hoekpunten van het bed in wijzerzin beginnende met de rechterbovenhoek"<<std::endl;
  std::vector<cv::Point> hoeken;
  cv::namedWindow("Constructor",1);
  cv::setMouseCallback("Constructor",mouseCallBack, (void*) (&hoeken));
  imshow("Constructor",img);
  cv::waitKey(0);
  rbx = hoeken[0].x;
  rby = hoeken[0].y;
  rox = hoeken[1].x;
  roy = hoeken[1].y;
  lox = hoeken[2].x; 
  loy = hoeken[2].y;
  lbx = hoeken[3].x;
  lby = hoeken[3].y;
  std::cout<< "rb ( "<<rbx<<" , "<<rby<<") ro ( "<<rox<<" , "<<roy<<" )"<<std::endl;
}  

void Bed::setValues(int irbx, int irby, int irox, int iroy, int ilox, int iloy, int ilbx, int ilby)
{
  rbx = irbx;
  rby = irby;
  rox = irox;
  roy = iroy;
  lox = ilox;
  loy = iloy;
  lbx = ilbx;
  lby = ilby;
}

void Bed::setValuesImg (cv::Mat img)
{
  std::cout<<"Druk met de linkermuisknop op de hoekpunten van het bed in wijzerzin beginnende met de rechterbovenhoek"<<std::endl;
  std::vector<cv::Point> hoeken;
  cv::namedWindow("Constructor",1);
  cv::setMouseCallback("Constructor",mouseCallBack, (void*) (&hoeken));
  imshow("Constructor",img);
  cv::waitKey(0);
  rbx = hoeken[0].x;
  rby = hoeken[0].y;
  rox = hoeken[1].x;
  roy = hoeken[1].y;
  lox = hoeken[2].x; 
  loy = hoeken[2].y;
  lbx = hoeken[3].x;
  lby = hoeken[3].y;
}  

std::vector<float> Bed::sidesOfBed()
{
  std::vector<float> bounds;
  float rico, trans;
  rico = (float) (loy-lby)/(lox-lbx);
  bounds.push_back(rico);
  std::cout<<"rico links"<<std::to_string(rico)<<std::endl;
  trans=-rico*lbx+lby;
  std::cout<<"trans link"<<std::to_string(trans)<<std::endl;
  bounds.push_back(trans);
  rico = (float) (roy-rby)/(rox-rbx);
  std::cout<<"rico rechts"<<std::to_string(rico)<<std::endl;
  bounds.push_back(rico);
  trans=-rico*rbx+rby;
  std::cout<<"trans rechts"<<std::to_string(trans)<<std::endl;
  bounds.push_back(trans);
  return bounds; 
}
