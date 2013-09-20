/* Stegnography encryption & Decryption,
Course : CS 213, Instructor : Varsha Apte,
prepared by Aman Mangal & Sanket Totala
Encryption of images
*/

/*order of encryption --
    length of password
    password
    1
    length of the extension
    extension
    length of the height => height
    length of the width => width
    secret image
*/

#include "EncryptImage.h"

void EncryptImage::encryptImage(char* c_file, char* m_file, string paswd, string o_file){
    //Encryption
    int val, flength, width, height;

    //input file image
    IplImage *in_img = cvLoadImage(c_file, -1);  //-1 is defalut number of channels
    width = in_img->width;
    height = in_img->height;

    //creates the final output image
    IplImage * out_image = cvCreateImage(cvSize(width,height), IPL_DEPTH_8U, 3);
    out_image = in_img;

    //message image
    Encryption E(out_image);
	IplImage *hidden = cvLoadImage(m_file, -1);

    //storing the length of the password
    int lpasswd = paswd.length();
    val = lpasswd;
    E.encryptPixel(val);

    //storing the password
    for(int count=0; count<lpasswd; count++){
        val = paswd[count];
        E.encryptPixel(val);
    }

    //Stores the flag that output is a image file
    E.encryptBit(1);

    //storing length of the extension of the file
    string m_ext  = extension(m_file);
    int m_length = m_ext.length();
    E.encryptPixel(m_length);

    //storing the extension of the file
    for(int count = 0; count < m_length; count++){
        val = m_ext[count];
        E.encryptPixel(val);
    }

	//store length of height
    flength = hidden->height;
    val = log(flength)/log(256) + 1;
    E.encryptPixel(val);

    //stores the height
    while(flength > 0){
        val = flength%256;
        flength = flength/256;
        E.encryptPixel(val);
    }

	//store length of width
	flength = hidden->width;
    val = log(flength)/log(256) + 1;
    E.encryptPixel(val);

    //stores the width
    while(flength > 0){
        val = flength%256;
        flength = flength/256;
        E.encryptPixel(val);
    }

	//store the image to be hidden
	int h = hidden->height, w = hidden->width;
	for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			CvScalar cv_hid = cvGet2D(hidden, i, j);
			for(int k = 0; k < 3; k++){
                val = cv_hid.val[k]; E.encryptPixel(val);
			}
		}
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
    cout<<"The final image is stored in the file named : "<<o_file<<endl;
}
