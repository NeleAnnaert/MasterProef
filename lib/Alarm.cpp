/*
 *  Fuction File Saving Images 
 *  Saving images recorded by the seek cam
 *  Author: Nele Annaert 
 */
 
#include "Alarm.h"
#include <string>
#include <iostream>

using namespace LibSeek;

Alarm::Alarm()
{
	teller = 0;
	THRESH = 30;
}

void Alarm::adOne()
{
	teller ++;
	if (teller >= THRESH)
	{
		timesUp();
		
	}
}

void Alarm::timesUp()
{
	std::cout<<"AALLAARRMM" <<std::endl;
}

void Alarm::setThresh(int t)
{
	THRESH = t;
}

void Alarm::endAlarm()
{
  teller = 0;
}
