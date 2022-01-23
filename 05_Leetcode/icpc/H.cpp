#include <iostream>
using namespace std;

int main(){
	int n;
	cin>>n;
    int start;
    cin>>start;
    int c;
	for(int i=2; i<=n; i++){
        cin>>c;
		if(c%start == 0){
            cout<<c<<endl;
            cin>>start;
            i++;
		}
	}
	return 0;
}