/*
 *  test program seek lib
 *  Saving images recorded by the seek cam
 *  HeaderFile
 *  Author: Nele Annaert 
 */

#include<opencv2/opencv.hpp>
#include<string>

namespace LibSeek {

/*--------- Declaration of the class and used methods ---------*/
class Alarm 
{
	int teller;
	int THRESH;
public:
	/*
	 * Constructor
	 */
	 Alarm();
	 /*
	  *	output None
		* input None
		*/
	void adOne();
	/* output None
   * input None
	 */
	 void timesUp();
	/*
	 * Output None
	 * INput integer 
	 */
	 void setThresh(int t);
	 /*
	  * Output None
		* input None
		*/
		void endAlarm ();
 }; 	//End of the class

} //End of the namespace
