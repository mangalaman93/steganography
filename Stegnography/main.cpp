/* Stegnography encryption & Decryption of text & images,
Course : CS 213, Instructor : Varsha Apte,
prepared by Aman Mangal & Sanket Totala,
Encryption & Decryption of text & images
*/

#include <iostream>
#include <cassert>
#include "EncryptImage.h"
#include "EncryptText.h"
#include "Decrypt.h"
using namespace std;

//function to find out the extension of the given file
string extension(char* name){
    int count = 0;
    string ext = "";
    char c = name[count];
    //serach for the '.' & get the extension
    while(c != '\0'){
        if(c == '.')
            ext = "";
        else
             ext += c;
        count++;
        c = name[count];
    }
    return ext;
}

//coyying the file name into a char* variable
void append(string file, char* name){
    //copying the file name
    unsigned int count;
    for(count = 0; count < file.length(); count++){
        name[count] = file[count];
    }
    name[count] = '\0';
}

int main(){
    char stegnography;
    cout<<"'e' for encryption & 'd' for retrieving the message : ";
    cin>>stegnography;

    //For Encryption
    if(stegnography == 'e'){
        char cover_file[100], message_file[100];
        string passwd, out_file;
        cout<<"Cover File : ";
        cin>>cover_file;
        cout<<"Message File : ";
        cin>>message_file;
        cout<<"Secret Password : ";
        cin>>passwd;
        cout<<"Output File name (without extension) : ";
        cin>>out_file;
        string message_ext = extension(message_file);

        //text encryption
        if(message_ext == "txt"){
            EncryptText ET;
            cout<<"initializing encryption of text in cover image....."<<endl;
            ET.encryptText(cover_file, message_file, passwd, out_file);
        }

        //image encryption
        else if(message_ext == "png" || message_ext == "tiff" || message_ext == "bmp" || message_ext == "jpeg" || message_ext == "jpg"){
            EncryptImage EI;
            cout<<"initializing encryption of image in cover image....."<<endl;
            EI.encryptImage(cover_file, message_file, passwd, out_file);
        }

        //invalid input file
        else{
            cout<<"please enter a valid input file"<<endl;
            assert(0);
            return 0;
        }
    }

    //For Decryption
    else if(stegnography == 'd'){
        char encrypted_file[100];
        string passwd;
        cout<<"Encrypted File : ";
        cin>>encrypted_file;
        cout<<"Secret Password : ";
        cin>>passwd;
        Decrypt DT;
        DT.decrypt(encrypted_file, passwd);
    }

    //For invalid input
    else{
        cout<<"Sorry! wrong input. try again"<<endl;
        assert(0);
        return 0;
    }
    return 0;
}
