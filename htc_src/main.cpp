/* Huffman Text Compression
Course : CS 213, Instructor : Varsha Apte,
prepared by Aman Mangal & Sanket Totala
*/

#include "Huffman.h"
#include <stdio.h>
#include <cstring>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <cassert>
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

int main(){
    //input file
    char in_file[100];
    cout<<"Input file : ";
    cin>>in_file;

    //checking the extension
    string in_ext = extension(in_file);
    assert(in_ext == "txt" || in_ext == "exe");

    //compression
    Huffman H(in_file);
    string concat;
	FILE* oFile;
	FILE* pFile = fopen(in_file, "r");

	//gets the file name
	int length = strlen(in_file);
	string my_ext = "htc";
	for(int count = length - 3; count<length; count++){
        in_file[count] = my_ext[count - length + 3];
	}

	oFile = fopen(in_file, "w+");
	fprintf(oFile, "%d", H.getSize());
	fprintf(oFile, "%c", '\n');
	for(int i = 0; i < 256; i++){
		if((H.getCode(i)).length()>0){
			char chh = i;
			fprintf(oFile, "%c", chh);
			string ss = H.getCode(i) + '\n';
			for(unsigned int j = 0; j < ss.length(); j++){
				char temp = ss[j];
				fprintf (oFile, "%c", temp);
			}
		}
	}

	while(!feof(pFile)){
		unsigned char str;
		fread(&str, 1, 1, pFile);
		if(!feof(pFile)){
			concat += H.getCode(str);
		}

		while(concat.length()>=7 && !feof(pFile)){
			string str2;
			str2=concat.substr(0,7);
			concat.erase(0,7);
			int ascii_decimal=0;
			for(int j=0;j<7;j++){
				char dig=str2[j];
				int digit=atoi(&dig);
				ascii_decimal+=(int)pow(2,j)*digit;
			}
			ascii_decimal+=128;
			char out=(char)ascii_decimal;
			fprintf (oFile, "%c", out);
		}
	}
	for(unsigned int i=0;i<concat.length();i++){
		fprintf (oFile, "%c", concat[i]);
	}
	fprintf (oFile, "%d", 2);
	fclose(oFile);
	fclose(pFile);
	cout<<"File stord in "<<in_file<<endl;
    return 0;
}
