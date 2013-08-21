/* Stegnography decryption, Course : CS 213,
Instructor : Varsha Apte, prepared by Aman & Sanket
Class : Decryption - This class retrieves the message
from the encrypted image. The public function returns
a char value of whatever is stored in the image.
*/

#ifndef DECRYPTION_H
#define DECRYPTION_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
using namespace std;
using namespace cv;

class Decryption{
	private:
		int height, width, current[2];
		IplImage *img;
		//return the next position where the value is to be hidden
        void next();

    public:
        //Default constructor
        Decryption(IplImage *image);
        //retreives the value hidden in the given 8 pixels & return it
        int decryptPixcel();
        //retreives the single pixel value
        int decryptBit();
        //returns the code...It first calculate the length of the code
        //then retrives the code
        string decryptCode();

};

#endif // DECRYPTION_H
