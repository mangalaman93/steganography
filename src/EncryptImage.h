/* Stegnography encryption & Decryption,
Course : CS 213, Instructor : Varsha Apte,
prepared by Aman Mangal & Sanket Totala
Encryption of images
*/

#ifndef ENCRYPTIMAGE_H
#define ENCRYPTIMAGE_H

#include <cstring>
#include <fstream>
#include <cstdlib>
#include <string>
#include "Encryption.h"
#include "Decryption.h"
using namespace std;

extern string extension(char* name);
extern void append(string file, char* name);

class EncryptImage{
    private :

    public :
        void encryptImage(char* c_file, char* m_file, string paswd, string o_file);
};

#endif //ENCRYPTIMAGE_H
