/* Stegnography decryption, Course : CS 213,
Instructor : Varsha Apte, prepared by Aman & Sanket
Class : Decryption - This class retrieves the message
from the encrypted image. The public function returns
a char value of whatever is stored in the image.
*/

#include "Decryption.h"

//Default Constructor
Decryption::Decryption(IplImage *image){
    img = image;
	width = img->width;
	height = img->height;
	current[0] = 0;
	current[1] = 0;
}

//retreives the single pixel value
int Decryption::decryptBit(){
    CvScalar cv1 = cvGet2D(img, current[0], current[1]);
    int val = cv1.val[0];
	next();
	return val%2;
}

//retreives the value hidden in the given pixel & return it
int Decryption::decryptPixcel(){
        int val[8],i;
        //retrieves the value from rgb pixel
        for(i = 0; i < 8; i++){
            val[i] = decryptBit();
        }
		//calculate the hidden value
        int ascii = 0;
		for(i = 0; i < 8; i++){
			ascii = ascii* 2 + val[7-i];
		}
        return ascii;
}

 //returns the code...It first calculate the length of the code
//then retrives the code
string Decryption::decryptCode(){
    int size = decryptPixcel();
    string str = "";
    for(int count = 0; count<size; count++){
        char ch;
        int temp = decryptBit();
        itoa(temp, &ch, 10);
        str += ch;
    }
    return str;
}

//return the next position where the value is to be hidden
void Decryption::next(){
    current[0]++;
    if(current[0] >= height){
        int m = current[0];
        current[0] = m % height;
        current[1] = current[1] + (m/height);
    }
}
