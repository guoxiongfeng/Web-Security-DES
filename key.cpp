#include <bitset>
#include <algorithm>
#include<iostream> 
#include "helper.cpp"
using namespace std;

class Key{
	public :
		bitset<48> k[16];
		Key() {
			
		}
		Key(string & s) {
			getSubKey(bit_form(s));
			isreversed = false;
		}
		void Reverse() {
			// Used for decode.
			for (int i = 0; i < 8; ++i) {
				swap(k[i], k[15 - i]);
			}
			isreversed = !isreversed;
		}
		bool isreversed;
	private:
		bitset<56> PC_1Hash(bitset<64> &key) {

             bitset<56> ans;
             for (int i = 0; i < 56; ++i) {
             	ans[i] = key[PC_1[i] - 1];//diff, -1是因为从0开始计数的。 
			 }
			 return ans;
		}
		bitset<48> PC_2Hash(bitset<56> &key) {

             bitset<48> ans;
             
             for (int i = 0; i < 48; ++i) {
             	ans[i] = key[PC_2[i] - 1];	
			 }
			 return ans;
		}
		void leftShift(bitset<28> &i, int n) {
			i = (i << n) | (i >> 28 - n); //
		}
		void getSubKey(bitset<64> init_key) {
			// 64bit 原始key
			bitset<56> valid_key;
			int j = 0;
			valid_key = PC_1Hash(init_key);
			bitset<28> C, D;
			for (int i = 0; i < 28; ++i) {
				C[i] = valid_key[i];//C[i]高位 
				D[i] = valid_key[i + 28];
			}
			for(int i = 0; i < 16; ++i) {
				if (i + 1 == 1 || i + 1 == 2 || i + 1 == 9 || i + 1 == 16) {
					leftShift(C, 1);
					leftShift(D, 1);	
				}
				else {
					leftShift(C, 2);
					leftShift(D, 2);
				}
				//concat Ci, Di
				bitset<56>tmp;
				for (int j = 0; j < 28; ++j) {
					tmp[j] = C[j];
					tmp[28 + j] = D[j];
				}
				k[i] = PC_2Hash(tmp);
			}
		}
};
