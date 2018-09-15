#include <iostream>

using namespace std;

class A{
public:
	int a[5];
};

void up(A& o){
	int temp1 = 1;
	int temp2 = 1;
	o.a[0] = temp1;
	o.a[1] = temp2;
}
int main()
{
	A o;
	int x =2;
	int y = 3;
	o.a[0] = x;
	o.a[1] = y;
	up(o);
	cout<<o.a[0]<<" "<<o.a[1]<<"\n";
	return 0;

}