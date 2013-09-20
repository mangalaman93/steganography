/* Stegnography encryption, Course : CS 213,
Instructor : Varsha Apte, prepared by Aman & Sanket
Class : Encryption - encrypt the secret message into
the cover image. The public function of the class can
encrypt the a integer(char), a string. It also can
store a string with its length(1 byte) just before it.
*/

#include "Encryption.h"

//Default constructor
Encryption::Encryption(IplImage* &img){
    image = img;
    height = image->height;
    width = image->width;
    current[0] = 0;
    current[1] = 0;
}

//To calculate the next pixel position of cover image where the message to be hidden
//fills the value vertically in rows
void Encryption::next(){
    int pos[2];
    //go to next pixel
    pos[0] = ++current[0];
    pos[1] = current[1];
    //if it crosses the height of the image
    if(pos[0] >= height){
        int d = pos[0]/height;
        int m = pos[0]%height;
        pos[0] = m;
        pos[1] = pos[1] + d;
    }
    if(pos[1] >= width){
        cout<<"cover image is too small to store the secret message !"<<endl;
    }
    assert(pos[1] < width);
    current[0] = pos[0];
    current[1] = pos[1];
}
//function takes a binary value & store it into the pixel.
void Encryption::encryptBit(int val){
    CvScalar pix;
    pix = cvGet2D(image, current[0], current[1]);
    //calculating the final pixel value
    int temp = pix.val[0];
    temp = temp/2;
    temp = temp*2 + pow(2, val) - 1;
    pix.val[0] = temp;
    //stores the pixel
    cvSet2D(image, current[0], current[1], pix);
    next();
}

//function takes a char value & store it into the pixel.
void Encryption::encryptPixel(int val){
    int sec;
    for(int count = 0; count<8; count++){
        sec = val%2;
        val = val/2;
        encryptBit(sec);
    }
}

//function takes a string of binaries & store it into the pixel.
void Encryption::encryptPixel(string val){
    int sec;
    for(unsigned int count = 0; count<val.length(); count++){
        char ch = val[count];
        sec = atoi(&ch);
        encryptBit(sec);
    }
}

//function takes string & store it into the given pixel. It also stores the length of the given string just before it
//length -> 1byte & then the real string
void Encryption::encryptCode(string val){
    int length = val.length();
    encryptPixel(length);
    encryptPixel(val);
}

//saves the final image
void Encryption::saveImage(char *pfile){
    cvSaveImage(pfile, image);
}
