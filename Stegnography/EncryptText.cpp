/* Stegnography encryption & Decryption,
Course : CS 213, Instructor : Varsha Apte,
prepared by Aman Mangal & Sanket Totala
Encryption of text
*/

/*order of encryption --
    length of password
    password
    0
    length of the tree
    tree => length of the code => code
    length of the length of the message
    length of message
    message => codes
*/

#include "EncryptText.h"

void EncryptText::encryptText(char* c_file, char* m_file, string paswd, string o_file){
    int val, flength, width, height;

    //reading input cover image
    IplImage *cover_img = cvLoadImage(c_file, -1);  //-1 is defalut number of channels
    if(cover_img == 0){
        cout<< "cannot find the file " << c_file << endl;
    }
    assert(cover_img != 0);
    width = cover_img->width;
    height = cover_img->height;

    //creates the final output image
    IplImage * out_image = cvCreateImage(cvSize(width,height), IPL_DEPTH_8U, 3);
    out_image = cover_img;

    //constructors
    Encryption E(out_image);
    MyHuffman H(m_file);

    //reading the message file
    ifstream message(m_file, ifstream::in);
    if(message == NULL){
        cout<<"cannot find the file "<<m_file<<endl;
    }
    assert(message != NULL);

    //STORing the length of the password
    int lpasswd = paswd.length();
    E.encryptPixel(lpasswd);

    //STORing the password
    for(int count=0; count<lpasswd; count++){
        val = paswd[count];
        E.encryptPixel(val);
    }

    //Stores flag showing that the message is in the text file
    E.encryptBit(0);

    //STORES the length of the tree
    E.encryptPixel(H.getSize());

    //storing the tree
    for(int count = 0; count<256; count++){
        if(H.getCode(count) != ""){
            E.encryptPixel(count);
            E.encryptCode(H.getCode(count));
        }
    }

    //STORES the length of length the text
    message.seekg(0,ios::end);
    flength = message.tellg();
    message.seekg(0,ios::beg);
    val = log(flength)/log(256) + 1;
    E.encryptPixel(val);

    //STORES the length of the text
    while(flength > 0){
        val = flength%256;
        flength = flength/256;
        E.encryptPixel(val);
    }

    //stores the secret text
    while(message.good()){
        unsigned char in_ch = message.get();
        unsigned int val = (int)in_ch;
        string v = H.getCode(val);
        E.encryptPixel(v);
    }
    cout<<"encryption done !"<<endl;

    //save the final image
    string c_ext = extension(c_file), o_ext;
    if(c_ext == "jpeg" || c_ext == "jpg")
        o_ext = ".png";
    else
        o_ext = "." + c_ext;
    o_file = o_file.append(o_ext);
    char file[110];
    append(o_file, file);
    E.saveImage(file);
    message.close();
    cout<<"The final image is stored in the file named : "<<o_file<<endl;
}
