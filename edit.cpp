//============================================================================
// Name        : edit_distance_draft.cpp
// Author      : Yifan_Tian 78921267
// Author      : Xufeng Bao 18446359
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi */
#include <math.h>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <list>
#include <cstring>
#include <algorithm>
using namespace std;

string operator*(const string& s, unsigned int n) {
    stringstream out;
    while (n--)
        out << s;
    return out.str();
}

string operator*(unsigned int n, const string& s) { return s * n; }


int edit1 (string filename) {

  cout<<"Input file: "<<filename<<endl;
  ifstream myfile (filename.c_str());
  std::list<char> mylist;                                           // implement linked list
  std::list<char>::iterator it1,it2,itp;

  string line;
  string astr,bstr;
  if (myfile.is_open())
  {
    getline (myfile,line);
    char buffer[256];
    strcpy(buffer, line.c_str());
    int alen = atoi (buffer);
    getline (myfile,line);
    bstr = line;
    getline (myfile,line);
    strcpy(buffer, line.c_str());
    int blen = atoi (buffer);
    getline (myfile,line);
    astr = line;
  }
  else {
    //bstr = "algorithm";
    //astr = "analysis";
    bstr = "electrical engineering";
    astr = "computer science";
  }

	int len2 = bstr.length();  //vertically
	int len1 = astr.length(); //horizontally
	cout<<"len1: "<<len1<<" len2: "<<len2<<endl;
	int table[len1+1][len2+1];
  string optable[100][100];

  for(int i = 0; i<len2; i++){
    mylist.push_back(bstr[i]);
  }
  it1 = it2 = mylist.begin();

  int flag = 1;
  if (len2<100 && len1<100) flag = 0;

  string s;

	for(int i=0; i<=len1;i++){
		for(int j=0;j<=len2;j++){
			table[i][j]=0;
		}
	}

	for(int i=1; i<=len1;i++){
		table[i][0] = i*3;
		string s = "i";
		if (flag == 0) optable[i][0] = s*i;
	}
	for(int i=1; i<=len2; i++){
		table[0][i] = i*2;
		string s = "d";
		if (flag == 0) optable[0][i] = s*i;
	}


	for(int i = 1; i<= len1; i++){
		for(int j = 1; j<= len2; j++){
			int d = 4;
			if (bstr.at(j-1) == astr.at(i-1)){
				d = 0;
			}
			int ir = table[i-1][j-1] + d;
			int op = ir;
			int opid = 1;
			int insert = table[i-1][j]+3;
			if (op > insert) {
				opid = 2;
				op = insert;
			}
			int del = table[i][j-1]+2;
			if (op>del) {
				opid = 3;
				op = del;
			}
			switch(opid){
			case(1):
				if (d==0){
					string s = "r";
					if (flag == 0) optable[i][j] = optable[i-1][j-1]+s;
				} else{
					string s = "c";
					if (flag == 0) optable[i][j] = optable[i-1][j-1]+s;
				}
				break;
			case(2):
				s = "i";
				if (flag == 0) optable[i][j] = optable[i-1][j]+s;
				break;
			case(3):
				s = "d";
				if (flag == 0) optable[i][j] = optable[i][j-1]+s;
				break;
			}
			table[i][j] = op;
		}
	}

  cout<<"cost: "<<table[len1][len2]<<endl;

  if (flag == 0) {
    	string seq = optable[len1][len2];
    	string z = bstr;
      string pz;
    	int i = 0;
      itp = mylist.begin();
    	int sp = len2;
    	int cost = 0;
      cout<<"Oper"<<"\t|"<<" c "<<"| Total |\t"<<"z"<<endl;
      cout<<"initial"<<"\t| "<<0<<" |\t"<<cost<<"  |\t"<<i<<"\t";
      for (it1=mylist.begin(); it1!=mylist.end(); ++it1) cout<<*it1;
      cout<<endl;
      for(int j = 0;j<seq.length(); j++) {
        char op = seq[j];
    		if(op == 'r')
    		{
    			if (i != sp+1){
            i+=1;
            ++itp;
    				cost += 0;
            cout<<"right"<<"\t| "<<0<<" |\t"<<cost<<"  |\t"<<i<<"\t";

            for (it1=mylist.begin(); it1!=itp; ++it1) cout<<*it1;
            cout<<"*";
            for (it1=itp; it1!=mylist.end(); ++it1) cout<<*it1;
            cout<<endl;
            }
    		} else if(op == 'c'){
    			if (i != sp+1){
            mylist.insert (itp,astr.at(i));
            itp = mylist.erase (itp);                              //replace in constant time
    				cost += 4;
    				i+=1;
            cout<<"replace"<<"\t| "<<4<<" |\t"<<cost<<"  |\t"<<i<<"\t";

            for (it1=mylist.begin(); it1!=itp; ++it1) cout<<*it1;
            cout<<"*";
            for (it1=itp; it1!=mylist.end(); ++it1) cout<<*it1;
            cout<<endl;
    			}
    		} else if(op == 'd') {
    			if (i != sp+1){
            itp = mylist.erase (itp);                            //delete in constant time
    				sp -= 1;
    				cost += 2;
            cout<<"delete"<<"\t| "<<2<<" |\t"<<cost<<"  |\t"<<i<<"\t";

            for (it1=mylist.begin(); it1!=itp; ++it1) cout<<*it1;
            cout<<"*";
            for (it1=itp; it1!=mylist.end(); ++it1) cout<<*it1;
            cout<<endl;
    			}
    		} else if(op == 'i') {
          mylist.insert (itp,astr.at(i));                         //insertion in constant time
    			sp += 1;
    			i += 1;
    			cost += 3;
          cout<<"insert"<<"\t| "<<3<<" |\t"<<cost<<"  |\t"<<i<<"\t";

          for (it1=mylist.begin(); it1!=itp; ++it1) cout<<*it1;
          cout<<"*";
          for (it1=itp; it1!=mylist.end(); ++it1) cout<<*it1;
          cout<<endl;

    		}
    	}
    }

	return 0;
}


int main(){

  string filename = "sample.txt";                       //filename string
  cout<<endl;
  edit1(filename);

  filename = "";                                        //filename string
  cout<<endl;
  edit1(filename);

  filename = "input1.txt";                          //filename string
  cout<<endl;
  edit1(filename);

  filename = "input2.txt";                          //filename string
  cout<<endl;
  edit1(filename);

  filename = "input3.txt";                            //filename string
  cout<<endl;
  edit1(filename);

  return 0;
}
