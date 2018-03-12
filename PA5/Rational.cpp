/*
 * Rational.cpp
 *
 *  Created on: Feb 17, 2018
 *      Author: dmcdonough
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cstdlib>
#include <string>
#include <stack>
#include <iomanip>
#include "Rational.h"

using namespace std;


ifstream in;

Rational normalize(long long TOP,long long BOT){
	if(BOT<0)TOP*=-1,BOT*=-1;	//multiplies numerator by -1 if denom is negative

	long long gc=__gcd(abs(TOP),abs(BOT));	   //  __gcd(x,y)  is a built-in function in #include<algorithm>
									// which finds greatest common divisor of x and y using euclid algorithm

	TOP/=gc;
	BOT/=gc;

	return Rational(TOP,BOT);
}// end normalize

Rational::~Rational() {

}// end destructor

Rational::Rational() {
	top = 0;
	bot = 1;
}// end default constructor

Rational::Rational(const int num, const int denom) {
	top = num;bot = denom;
	if(bot<0)top*=-1,bot*=-1;//multiplies numerator by -1 if denom is negative
	int gc=__gcd(abs(top),abs(bot));
	top/=gc;bot/=gc;
}// end Rational(const int num, const int denom)

Rational::Rational(const int wholeNumber) {
	top = wholeNumber;
	bot = 1;
}// end Rational(const int wholeNumber)

Rational::Rational(const Rational &a) {
	top = a.top;
	bot = a.bot;
} // end Rational(const Rational &a)

ostream& operator<<(ostream& out, const Rational& rat) {
	out << rat.top << '/' << rat.bot;
	return out;
}// end ostream
int k=0;
istream& operator>>(istream& in,Rational& rat) {
	string s;

	in>>s;

	int ind=s.find('/');

	if(ind==-1){                // if ind==-1 then there is not / in rational number
		rat.top=atoi(s.c_str());// so we assign the given number to the top
		rat.bot=1; 				// and 1 to the bot
		return in;
	}

	int TOP=0,BOT=0;

	int sign=1;
	if(s[0]=='-'){sign=-1;s[0]='0';} // checks for the negative sign and stores in sign
									// s[0]='0' because "037" will still be converted to 37

	for(int i=0;i<ind;i++){
		TOP=TOP*10+s[i]-'0';     // gets the numerator from the string of numbers
	}


	if(ind+1<int(s.size()) && s[ind+1]=='-'){sign*=-1;s[ind+1]='0';}
								// checks for the negative sign and stores in sign

	for(int i=ind+1;i<int(s.size());i++){
		BOT=BOT*10+s[i]-'0';    // gets the denominator from the string of numbers
	}
	Rational et=normalize(TOP,BOT);
	rat=et;

	rat.top*=sign;

	return in;
}// end istream

Rational Rational::operator+(const Rational &rat){
	int TOP=bot*rat.top+top*rat.bot;
	int BOT=bot*rat.bot;

	return normalize(TOP,BOT);
}// end +
Rational Rational::operator-(const Rational &rat){

	Rational x(-rat.top,rat.bot);
	return (*this+x);
}// end -
Rational Rational::operator*(const Rational &rat) {
	long long TOP = top * rat.top;
	long long BOT = bot * rat.bot;

	return normalize(TOP, BOT);
}// end *
Rational Rational::operator/(const Rational &rat){
	long long TOP = top * rat.bot;
	long long BOT = bot * rat.top;

	return normalize(TOP, BOT);
}// end /
int Rational::operator==(const Rational &rat) {
	return (top == rat.top && bot == rat.bot);
}// end ==
int Rational::operator!=(const Rational &rat) {
	return (top != rat.top || bot != rat.bot);
}// end !=
int Rational::operator>(const Rational &rat) {
	return (top*rat.bot > bot*rat.top);
}// end >
int Rational::operator<(const Rational &rat) {
	return (top*rat.bot < bot*rat.top);
}// end <
int Rational::operator>=(const Rational &rat) {
	return ((*this==rat) || (*this>rat));
}// end >=
int Rational::operator<=(const Rational &rat) {
	return ((*this==rat) || (*this<rat));
}// end <=
void Rational::operator=(Rational &rat){
	top=rat.top;
	bot=rat.bot;
}// end =

// extra credit functions

Rational Rational::operator+=(Rational &rat){
	Rational x=(*this)+rat;

	top=x.top;
	bot=x.bot;

	return (*this);
}// end +=
Rational Rational::operator-=(Rational &rat){
	Rational x=(*this)-rat;

	top=x.top;
	bot=x.bot;

	return (*this);
}// end -=
Rational Rational::operator/=(Rational &rat){
	Rational x=(*this)/rat;

	top=x.top;
	bot=x.bot;

	return (*this);
}// end /=
Rational Rational::operator*=(Rational &rat){
	Rational x=(*this)*rat;

	top=x.top;
	bot=x.bot;

	return (*this);
}// end *=

// end extra credit functions

double toDouble(const Rational &rat) {
	return (double)(rat.top)/(double)(rat.bot);
}// end toDouble

void solve(string s){

	Rational rat;
	stack<Rational>st;
	//cout<<s<<endl;

	int flag=0;
	for(int i=0;i<int(s.size());i++){	// checks string
		if('a'<=s[i] && s[i]<='z')flag=1;	// checks for lower case letters, sets flag if any
		if('A'<=s[i] && s[i]<='Z')flag=1;	// checks for upper case letters, sets flag if any
	}

	int ind=0;
	int compare=0;

	if(flag)  goto err;  // if flag==1 then we had a character which is an error
	if(s.size()==0)goto empty_line; // if empty throws an empty line error

	while(ind<int(s.size())){	// performs mathematics actions


		int n_ind=s.size();
		for(int j=ind;j<int(s.size());j++){	// checks for white space
			if(s[j]==' '){n_ind=j;break;}
		}

		string ne="";
		for(int j=ind;j<n_ind;j++){	// adds s[j] to ne
			ne+=s[j];
		}

		stringstream ss;
		ss<<ne;

		if(('0'<=ne[0] && ne[0]<='9') ||
				(ne[0]=='-' && ne.size()>1 && ('0'<=ne[1] && ne[1]<='9'))){
			ss>>rat;

			if(rat.bot==0){
				goto err;
			}

			st.push(rat);
		}else{
			if(st.size()<2){
				goto err;
			}

			if(compare==1)goto err; // if we already have comparison it should have been the last
					// so we print error

			Rational a1=st.top();st.pop();
			Rational a2=st.top();st.pop();


			if(s[ind]=='+')st.push(a1+a2);else
			if(s[ind]=='-')st.push(a2-a1);else
			if(s[ind]=='*')st.push(a1*a2);else
			if(s[ind]=='/' && a1.top!=0)st.push(a2/a1);else
			{
				compare++;                            	        // we count the number of comparisons

				if(ind+1<int(s.size()) || s[ind+1]=='='){      // s[ind+1]=='=' so we dont check it anymore
					if(s[ind]=='=')st.push(a2==a1);else
					if(s[ind]=='>')st.push(a2>=a1);else
					if(s[ind]=='<')st.push(a2<=a1);else
					if(s[ind]=='!')st.push(a2!=a1);else
					goto err;
				}else
				if(s[ind]=='>')st.push(a2>a1);else
				if(s[ind]=='<')st.push(a2<a1);else
				goto err;
			}
		}

		ind=n_ind;
		while(ind<int(s.size()) && (s[ind]==' ' || s[ind]=='\n' || s[ind]=='\0'))ind++;// increments ind every space or new line
	}// end while
	if(st.size()!=1)goto err;


	for(int i=25-int(s.size());i>=0;i--)s+=' ';// sets spacing for result
	if(compare==1){
		if(st.top().top==0)cout<<s<<" : false"<<endl;else
			cout<<s<<" : true"<<endl;
	}else{
		cout<<s<<" : "<<st.top();
		cout<<fixed<<setprecision(6)<<" (double "<<toDouble(st.top())<<")"<<endl;
	}


	return;


	err:
	for(int i=25-int(s.size());i>=0;i--)s+=' ';// sets spacing for result
		cout<<s<<" : error"<<endl;return;

	empty_line:
		cout<<"empty line"<<endl;return;
}// end solve

int main(int argc, char *argv[]){


	for(int i = 1; i < argc; i++) {// goes through the args
		string S;
		in.open(argv[i]);
		if(in.is_open()) {
			cout<<argv[i]<<" was successfully opened."<<endl;
		}
		else {
			cout<<argv[i]<<" was not opened successfully."<<endl;
		}
		while(getline(in,S)){// opens each given file
			solve(S);
		}
		in.close();

	}


	return 0;
}// end main
