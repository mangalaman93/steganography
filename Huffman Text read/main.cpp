#include<stdio.h>
#include<cstring>
#include<string>
#include<iostream>
#include <cstdlib>
using namespace std;



string code[256]={""};
int noo=0;

int main (){
	string str;
	char ch[3],c1[100];
	unsigned char c='\n';
	char file[100];
	FILE* pFile;
	FILE* oFile;
	cout<<"Enter file to be decompressed : ";
	cin>>file;
	pFile=fopen(file,"r");
	cout<<"Enter file name of the decompressed file : ";
	cin>>file;
	oFile=fopen(file,"w+");
	fgets(ch, 100, pFile);
	int a=(int)atoi(ch);
	for(int i=0;i<a;i++){
		c=fgetc(pFile);
		fgets(c1, 100, pFile);
		int j=0;
		while(c1[j]!='\n'){
			j++;
		}
		c1[j]='\0';
		code[c]=c1;
	}
	int max_len=0;
	for(int i=0;i<256;i++){
		if(code[i]!=""){
			if(code[i].length()>max_len){
				max_len=code[i].length();
			}
			noo++;
		}
	}
	str="";
	int flag=0;
	while(!feof(pFile)){
		while(!feof(pFile) && str.length()<max_len && flag==0){
			c=fgetc(pFile);
			unsigned int ascii_decimal=0;
			ascii_decimal=(int)c;
			if(c=='2'){
				flag=2;
				break;
			}
			if(c=='0'){
				str+="0";
				flag=1;
				break;
			}
			else if(c=='1'){
				str+="1";
				flag=1;
				break;
			}
			else{
				ascii_decimal-=128;
				int arr[7];
				for(int k=0;k<7;k++){
					arr[k]=ascii_decimal%2;
					ascii_decimal/=2;
					if(arr[k]==0){
						str+="0";
					}
					else{
						str+="1";
					}
				}
			}
		}
		if(flag==2){
			break;
		}
		while(!feof(pFile) && flag==1){
			c=fgetc(pFile);
			if(c=='0'){
				str+="0";
			}
			else if(c=='1'){
				str+="1";
			}
		}
		int k;
		for(k=0;k<256;k++){
			int l=0;
			for(l=0;l<code[k].length();l++){
				if(code[k][l]!=str[l]){
					break;
				}
			}
			if(code[k].length() && l==code[k].length()){
				break;
			}
		}
		if(k==256){
			cout<<"ERROR!!\n";
			return 1;
		}
		str.erase(0,code[k].length());
		fprintf (oFile, "%c", (char)k);
	}
	while(str.length()>0){
		int k;
		for(k=0;k<256;k++){
			int l=0;
			for(l=0;l<code[k].length();l++){
				if(code[k][l]!=str[l]){
					break;
				}
			}
			if(code[k].length() && l==code[k].length()){
				break;
			}
		}
		if(k==256){
			cout<<"ERROR!!\n";
			return 1;
		}
		str.erase(0,code[k].length());
		fprintf (oFile, "%c", (char)k);
	}
	cout<<str;
	fclose(pFile);
	fclose(oFile);
	return 0;
}
