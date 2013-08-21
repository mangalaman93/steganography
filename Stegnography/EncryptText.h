/* Stegnography encryption & Decryption,
Course : CS 213, Instructor : Varsha Apte,
prepared by Aman Mangal & Sanket Totala
Encryption of text
*/

#ifndef ENCRYPTTEXT_H
#define ENCRYPTTEXT_H

#include <cstring>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include "Encryption.h"
#include "MyHuffman.h"
using namespace std;

extern string extension(char* name);
extern void append(string file, char* name);

class EncryptText{
    private :

    public :
        void encryptText(char* c_file, char* m_file, string paswd, string o_file);
};

#endif //ENCRYPTTEXT_H
