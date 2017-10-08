#include <iostream>
#include <bitset>

using namespace std;

int main() {
	int t = 4; 
	bitset<400> k(t);
	//k.set(1);
	//k[1] = 3;
	//k<<= 2;
	cout << k[2] <<endl;
}
