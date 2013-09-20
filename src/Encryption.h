/* Stegnography encryption, Course : CS 213,
Instructor : Varsha Apte, prepared by Aman & Sanket
Class : Encryption - encrypt the secret message into
the cover image. The public function of the class can
encrypt the a integer(char), a string. It also can
store a string with its length(1 byte) just before it.
*/

#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <cmath>
#include <cassert>
#include <cstring>
#include <string>
#include <cstdlib>
using namespace std;
using namespace cv;

class Encryption{
    private :
        int height, width;
        IplImage *image;
        //stores the current pixel position where secret message is stored
        int current[2];
        //To calculate the next pixel position of cover image where the message to be hidden
        void next();

    public:
        //Default constructor
        Encryption(IplImage* &img);
        //function takes a binary value & store it into the pixel.
		void encryptBit(int val);
		//function takes a char value & store it into the pixel.
		void encryptPixel(int val);
		//function takes a binary string & store it into the pixel.
		void encryptPixel(string val);
		//function takes binary string & store it into the given pixel. It also stores the length of the given string just before it
		//length -> 1byte & then the real string
		void encryptCode(string val);
		//saves the final image
		void saveImage(char* pfile);
};

#endif  //ENCRYPTION_H
