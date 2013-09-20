/* Stegnography encryption & Decryption,
Course : CS 213, Instructor : Varsha Apte,
prepared by Aman Mangal & Sanket Totala
Huffman compression
*/

#ifndef MYHUFFMAN_H
#define MYHUFFMAN_H

#include <stdio.h>
#include <queue>
#include <cstring>
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <cmath>
using namespace std;

//struct tree node
struct Fnode{
	public:
		unsigned char ch;
		int freq;
		Fnode* left;
		Fnode* right;
		//default constructor
		Fnode(char c='\0',Fnode* l=NULL, Fnode* r=NULL, int f=0)
            :ch(c), left(l), right(r) {
            freq=f;
        }
};

//class for the priority queue for comparison
class mycomparison{
    private :
        bool reverse;

    public:
        //constructor
        mycomparison(const bool& revparam=false){
            {reverse=revparam;}
        }

        //operator overloading
        bool operator() (Fnode* lhs, Fnode* rhs) {
            if (reverse) return (lhs->freq<rhs->freq);
            else return (lhs->freq>rhs->freq);
        }
};

class MyHuffman{
    private:
        //stores code for all the 256 possible character
        string code[256];
        //number of character whose code is defined
        int size;
        //store the codes for each character for the given tree, if the character is present in the tree
        void storeCode(Fnode *huffman_tree, string pr);

    public:
        // Default constructor (while decryption)
        MyHuffman();
        //constructor for the given message file (while encryption)
        MyHuffman(char* message);
        //return the size of the huffman tree
        int getSize();
        //add the code in the array
        void addCode(int index, string c);
        //return the code for the given character
        string getCode(int index);
        //return the character whose code is given string or part of it
        int uncompress(string& str);
};

#endif // MyHuffman_H
