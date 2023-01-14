#include<iostream>
#include<string>
using namespace std;
 
const int N=25;
string s1,s2,s3,s4;
int x[N],y[N],bx,by,d[N];
int cnt=0;
 
//Part B
void check(int x0,int y0){
	if(x0>=0&&x0<=4000000&&y0>=0&&y0<=4000000){
		bool b=true;
		for(int j=0;j<N;j++)
			if(abs(x[j]-x0)+abs(y[j]-y0)<=d[j])
				b=false;
		if(b){
			cout<< "Found " << x0<<' '<<y0 << endl;
            cout << (long long)x0 * 4000000 + y0 << endl;
			exit(0);
		}
	}
}
 
int main(){
	for(int i=0;i<N;i++){
		cin>>s1>>s1>>s1>>s2>>s3>>s3>>s3>>s3>>s3>>s4;
		x[i]=stoi(s1.substr(2,s1.length()-1));
		y[i]=stoi(s2.substr(2,s2.length()-1));
		bx=stoi(s3.substr(2,s3.length()-1));
		by=stoi(s4.substr(2,s4.length()));
		d[i]=abs(x[i]-bx)+abs(y[i]-by);
	}
	/*
	for(int x0=-10000000;x0<10000000;x0++)
		for(int i=0;i<N;i++)
			if(abs(x[i]-x0)+abs(y[i]-2000000)<=d[i])
				{cnt++; break;}
	cout<<cnt-1;
	*/
	for(int i=0;i<N;i++){
		for(int s=0;s<=d[i]+1;s++){
			check(x[i]+s,y[i]+d[i]+1-s);
			check(x[i]-s,y[i]+d[i]+1-s);
			check(x[i]+s,y[i]-d[i]-1+s);
			check(x[i]-s,y[i]-d[i]-1+s);
		}
	}
	return 0;
}