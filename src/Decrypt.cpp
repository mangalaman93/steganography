/* Stegnography encryption & Decryption,
Course : CS 213, Instructor : Varsha Apte,
prepared by Aman Mangal & Sanket Totala
Dncryption of images & text
*/

/*
Decryption =>
    length of the password
    password
    text(0) =>                                  image(1) =>
        length of the tree                          length of the extension
        tree => length of the code => code          extension
        length of the length of the message         length of the height => height
        length of message                           length of the width => width
        message => codes                            secret image(each pixel)
*/

#include "Decrypt.h"

void Decrypt::decrypt(char* enc_file, string password){
	//encrypted image
	int val, length, lol = 0;
	unsigned int max_length = 0;
	char ch;
	string str;
    IplImage* img = cvLoadImage(enc_file, -1);
	Decryption D(img);

    //read length of password
    length = D.decryptPixcel();
    //cout<<"Length of the password is : "<<l<<endl;

    //read password
    str = "";
    for(int i = 0; i < length; i++){
        ch = D.decryptPixcel();
        str += ch;
    }

	//check password
    if(str != password){
        cout<<"Passwords dont match!!\n";
        assert(0);
        return;
    }

	//if password matches then open out filE
	cout<<"Output File (without extension) : ";
	string o_file;
	cin>>o_file;

    val = D.decryptBit();
    if(val == 0){
        //text decryption
        MyHuffman H;

        //retrieves the length of the tree
        length = D.decryptPixcel();

        //retrieves the tree(codes)
        for(int count = 0; count<length; count++){
            int val = D.decryptPixcel();
            //cout<<"val\t"<<val;
            str = D.decryptCode();
            //cout<<"\tcode\t"<<d<<endl;
            if(str.length() > max_length) {max_length = str.length();}
            H.addCode(val, str);
        }

        //calculate length of length of file
        lol = D.decryptPixcel();

        //calculate length of file
        length = 0;
        for(int i = 0; i < lol; i++){
            val = D.decryptPixcel();
            length += val * pow(256, i);
        }

        //retrieving the message
        char file[100];
        o_file = o_file.append(".txt");
        append(o_file, file);
        cout<<file<<endl;
        FILE* p_file = fopen(file, "w+");
        string str = "";
        for(int i = 0; i < length; i++){
            for(unsigned int count = str.length(); count < max_length; count++){
                val = D.decryptBit();
                itoa(val, &ch, 10);
                str += ch;
            }
            int temp = H.uncompress(str);
            assert(temp != -1);
            fprintf(p_file, "%c", (char)temp);
        }
        fclose(p_file);
        cout<<"decryption done !"<<endl;
        cout<<"The secret message is stored in "<<o_file<<endl;
    }

    //Image decryption
    else{
        //retrieves the length of the extension
        length = D.decryptPixcel();
        int height, width;

        string o_ext;
        //retrieves the extension
        for(int i = 0; i < length; i++){
            ch = D.decryptPixcel();
            o_ext += ch;
        }

        //retrieves length of height
        lol = D.decryptPixcel();
        length = 0;
        //calculate height
        for(int i = 0; i < lol ;i++){
            val = D.decryptPixcel();
            length += val * pow(256, i);
        }
        height = length;

        //calculate length of width
        lol = D.decryptPixcel();

        //calculate width
        length = 0;
        for(int i = 0; i < lol; i++){
            val = D.decryptPixcel();
            length += val * pow(256, i);
        }
        width = length;

        //retrieving the image file
        IplImage * out_image = cvCreateImage(cvSize(width, height), IPL_DEPTH_8U, 3);
        for(int i = 0; i < height; i++){
            for(int j = 0; j < width; j++){
                CvScalar cv_hid = cvGet2D(out_image, i, j);
                for(int k = 0; k<3; k++){
                    val = D.decryptPixcel();
                    cv_hid.val[k] = val;
                }
                cvSet2D(out_image, i, j, cv_hid);
            }
		}
        //save out file
        char file[100];
        o_ext = "." + o_ext;
        o_file = o_file.append(o_ext);
        append(o_file, file);
        cvSaveImage(file, out_image);
    }
    return;
}
