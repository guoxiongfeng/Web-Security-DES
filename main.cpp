#include<iostream>
#include <bitset>
#include <algorithm>
#include <fstream>
#include "DES.cpp"
using namespace std;

int main() {
	string s_key = "ZXCVBNML";
	Key k(s_key);
	cout << "key: " << bit_form(s_key) << endl;
	Des des(k);
	string raw_msg = "QWERTYUI";
	cout << "raw message:" << raw_msg << endl;
	cout << "raw bit form: "   << bit_form(raw_msg) << endl;
	auto trans_info = des.code(raw_msg);
	cout << "code:" << trans_info << endl;
	bitset<64> decode_msg = des.decode(trans_info);
	cout << "after decode:" << decode_msg << endl;
	cout << "message: " << str(decode_msg) << endl;
}
