/* Stegnography encryption & Decryption,
Course : CS 213, Instructor : Varsha Apte,
prepared by Aman Mangal & Sanket Totala
Huffman compression
*/

#include "MyHuffman.h"

//Default Constructor
MyHuffman::MyHuffman(){
    //initialize the size
    size = 0;
    //initialize codes array
    for(int i=0;i<256;i++){
        code[i]="";
    }
}

//store the codes for each character for the given tree, if the character is present in the tree
void MyHuffman::storeCode(Fnode *huffman_tree, string pr){
	if(huffman_tree->left == NULL){
		code[huffman_tree->ch] = pr;
		size++;
	}
	else{
		storeCode(huffman_tree->left, pr + "0");
		storeCode(huffman_tree->right, pr + "1");
	}
}

//constructor for the given message file
//this function calculates the tree & stores it into the codes array
MyHuffman::MyHuffman(char* message){
    //initialize the size
    size = 0;
    //initialize the codes array
    for(int i=0;i<256;i++){
        code[i]="";
    }

    //reading the file & calculating the frequency
	unsigned char str;
	FILE * pFile;
	int count[256] = {0};
	pFile = fopen (message,"r");
	int i;
	if (pFile != NULL){
		while(!feof(pFile)){
			fread(&str, 1, 1, pFile);//place of storage, no of elements of size_t, size_t (i.e. no of bytes of reading), pile from which to read
			count[str]++;
		}
		count[str]--;
	}
	fclose (pFile);

    //making the priority queue for the frequency array
	priority_queue<Fnode*, vector <Fnode*>, mycomparison> ascending_frequencies;
	for(i = 0; i < 256; i++){
		if(count[i]>0){
			Fnode* v = new Fnode(i, NULL, NULL, count[i]);
			ascending_frequencies.push(v);
		}
	}

	//creating the huffman tree
	while(ascending_frequencies.size() > 1){
		Fnode* v1 = ascending_frequencies.top();
		ascending_frequencies.pop();
		Fnode* v2 = ascending_frequencies.top();
		ascending_frequencies.pop();
		Fnode* v = new Fnode('\0', v1, v2, v1->freq+v2->freq);
		ascending_frequencies.push(v);
	}
	Fnode* huffman_tree = ascending_frequencies.top();
	storeCode(huffman_tree, "");
}

 //add the code in the array
void MyHuffman::addCode(int index, string c){
    code[index] = c;
}

//return the character whose code is given string or part of it
int MyHuffman::uncompress(string& str){
    unsigned int index;
    for(int count = 0; count < 256; count++){
        string _code = code[count];
        if(_code == "") {continue;}
        for(index = 0; index < _code.length(); index++){
            if(str[index] != _code[index])
                break;
        }
        if(index == _code.length()){
            str = str.substr(index, str.length() - index);
            return count;
        }
    }
    //indicates error
    return -1;
}

//return the size of the huffman tree
int MyHuffman::getSize(){
    return size;
}

 //return the code for the given character
string MyHuffman::getCode(int index){
    return code[index];
}
