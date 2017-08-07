/*
 *  Main loop
 *  Author: Nele Annaert
 */
 
#include "Bed.h"

int main (int argc, char** argv)
{
   std::vector<float> bounds;
   LibSeek::Bed bed (1,2,3,4,5,6,7,8);
   bounds=bed.sidesOfBed();
}
