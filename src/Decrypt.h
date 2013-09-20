/* Stegnography encryption & Decryption,
Course : CS 213, Instructor : Varsha Apte,
prepared by Aman Mangal & Sanket Totala
Dncryption of images & text
*/

#ifndef DECRYPT_H
#define DECRYPT_H

#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>
#include <cmath>
#include <cassert>
#include <cstring>
#include <string>
#include <cstdlib>
#include "Encryption.h"
#include "Decryption.h"
#include "MyHuffman.h"
using namespace std;
using namespace cv;

extern string extension(char* name);
extern void append(string file, char* name);

class Decrypt{
    private :

    public :
        void decrypt(char* enc_file, string password);
};

#endif //DECRYPT_H
