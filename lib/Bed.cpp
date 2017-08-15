/*
 *  Determine dimentia of the bed
 *  Author: Nele Annaert
 */

#include "Bed.h"

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
  setValues(0,0,0,0,0,0,0,0);
	std::cout<<"Uw bed is nu een punt, vergeet geen setValues, setValuesAuto of setValueImg te doen"<<std::endl;
}


Bed::Bed(int irbx, int irby, int irox, int iroy, int ilox, int iloy, int ilbx, int ilby)
{
	setValues(irbx,irby,irox,iroy,ilox,iloy,ilbx,ilby);
}

Bed::Bed (cv::Mat img, int get)
{
  if (get == 0)
  {
		setValuesImg(img);
  }
  else
  {
		setValuesAuto(img);
  }
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

void Bed::setValuesAuto(cv::Mat img)
{
  cv::Mat oneChannel;
  cv::cvtColor(img,oneChannel,cv::COLOR_RGB2GRAY);
  cv::Mat mask;
	std::vector<cv::Point> hoeken;
  int rows=img.rows;
  int cols=img.cols;
  mask=cv::Mat::zeros(rows,cols,CV_8UC1);
  int THRESHOLD = 80;
	int DISTANCE = 10;
	int max_rij=0;
	int pos_max;
	int min_afstand=5000;
	int max_afstand=0;
	unsigned int pos_min_a, pos_max_a;
  for (int j=0;j<cols;j++)
  {
    for ( int i=0;i<rows;i++)
    {
		  if(oneChannel.at<uchar>(i,j)>THRESHOLD)
			{
				if(hoeken.empty())
				{
					hoeken.push_back(cv::Point(j,i));
				}
				else
				{
					bool foundNew = true;
					for(auto &point : hoeken)
					{
						if((j-point.x)*(j-point.x) + (i-point.y)*(i-point.y) < DISTANCE*DISTANCE)
						{
							foundNew = false;
							break;	
						}
					}
					if(true == foundNew)
					{
						hoeken.push_back(cv::Point(j,i));
					}
				}
			}
		}
	}
	for(unsigned int teller=0;teller<hoeken.size();teller++)
	{
     if(max_rij<hoeken[teller].y)
		{
       pos_max=teller;
			max_rij=hoeken[teller].y;
		}
	}
	for (unsigned int tel=0; tel < hoeken.size() ; tel++)
	{
	  int a=(hoeken[tel].x-hoeken[pos_max].x)*(hoeken[tel].x-hoeken[pos_max].x)+(hoeken[tel].y-hoeken[pos_max].y)*(hoeken[tel].y-hoeken[pos_max].y);
		if(a<min_afstand && a!=0)
		{
			min_afstand=a;
			pos_min_a=tel;
		}
		if(a>max_afstand)
		{
			max_afstand=a;
			pos_max_a=tel;
		}
	}
	for (unsigned int t=0;t<hoeken.size();t++)
	{
		if(t==pos_max_a)
		{
			rbx=hoeken[t].x;
			rby=hoeken[t].y;
			std::cout<<"rechtsboven: "<<std::to_string(rbx)<<" , "<<std::to_string(rby)<<std::endl;
		}
		else if(t==pos_min_a)
		{
			rox=hoeken[t].x;
			roy=hoeken[t].y;
			std::cout<<"rechtsonder: "<<std::to_string(rox)<<" , "<<std::to_string(roy)<<std::endl;
		}
		else if(t==pos_max)
		{
			lox=hoeken[t].x;
			loy=hoeken[t].y;
			std::cout<<"linksonder: "<<std::to_string(lox)<<" , "<<std::to_string(loy)<<std::endl;
		}
		else
		{
			lbx=hoeken[t].x;
			lby=hoeken[t].y;
			std::cout<<"linksboven: "<<std::to_string(lbx)<<" , "<<std::to_string(lby)<<std::endl;
		}
	}
}  
