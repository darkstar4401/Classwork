#include <iostream>
#include <stdlib.h>

using namespace std;

class A4p2
{
protected: int var;

public:
	void func()
	{
		int t=var;
		cout<<t<<"\t";
		while(t!=1)
		{
		if(t%2)
			t=3*t+1;
		else
			t=t/2;
		cout<<t<<"\t";
		}
		cout<<endl;
	}
	A4p2(int v) {var = v;}
};

void usage(char *s){
	cerr<<"usage: "<<s<<" <integer>\n";
	exit(0);
}

int main(int argc, char *argv[]){
	int v;
	if(argc!=2) usage(argv[0]);
	v=atoi(argv[1]);
	if(v<=26 || v>40) {cerr<<"<integer> should be between 1 & 50\n"; exit(0);}
	A4p2 val(v);
	val.func();
	return 0;
}
