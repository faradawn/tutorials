#include <iostream>
#include <string>

using namespace std;

int main(){
	int n;
	cin>>n;
	for(int i=1; i<=n; i++){
		string str;
		cin>>str;
		if(i%2 != 0){
			cout<<str<<endl;
		}
	}
	return 0;
}

