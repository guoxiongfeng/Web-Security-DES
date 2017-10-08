#include "key.cpp"
#include <iostream>
class Des {
	public: 
		Des(Key k) {
			this->key = k;
		}
		bitset<64> code(string s) {
			
			if (key.isreversed) key.Reverse();
			return process(bit_form(s));
		}
		bitset<64> decode(bitset<64> c) {
			if (!key.isreversed) key.Reverse();
			return process(c);
		}
	private:
		bitset<64> process(bitset<64> s) {
			//Init Permutation.
			bitset<64> init = IP(s);
			//Iteration.
			//swap L16R16 -> R16L16
			bitset<64> it = Iter(init);
			
			//Init Permutaion Inverse.
			return IP_Inv(it);
		}
		bitset<48> E_expand(bitset<32> & R) {

	        bitset<48> ans;
	        for (int i = 0; i < 48; ++i) {
	        	ans[i] = R[E[i] - 1];
			}
			return ans;
		}
		bitset<32> PHash(bitset<32> s) {

          	bitset<32> ans; 
			for (int i = 0; i < 32; ++i) {
				ans[i] = s[P[i] - 1];
			}
			return ans;
		}
		bitset<4> S_Box(bitset<6> s, int i) {
			int row = s[0] * 2 + s[5], col = s[1] * 8 + s[2] * 4 + s[3] * 2 + s[4];// row = s0s5, col = s1s2s3s4
			return bitset<4>(S_BOX[i][row][col]);
		} 
		bitset<32> S_Box_Transform(bitset<48> s) {
			bitset<32> ans;
			for (int i = 0; i < 8; ++i) {
				bitset<6> tmp;
				//得到分组 
				for (int j = 0; j < 6; ++j) {
					tmp[j] = s[i * 6 + j];
				}
				//对每组转换 
				bitset<4> t = S_Box(tmp, i);
				//写入输出bitset 
				for (int j = 0; j < 4; ++j) {
					ans[4 * i + j] = t[j]; 
				}
			}
			return ans;
		}
		bitset<32> Feistal(bitset<32> R, bitset<48> k) {
			bitset<48> exR = E_expand(R);
			bitset<48> ans = exR ^ k;
			//分组， 64转换。合并。
			return PHash(S_Box_Transform(ans));//S_BOX 之后再用P_置换打乱。 
		}
		bitset<64> IP(bitset<64> &s) {
            bitset<64> ans;
            int IP[] = {58, 50, 42, 34, 26, 18, 10, 2,
            60, 52, 44, 36, 28, 20, 12, 4,
            62, 54, 46, 38, 30, 22, 14, 6,
            64, 56, 48, 40, 32, 24, 16, 8,
            57, 49, 41, 33, 25, 17, 9,  1,
            59, 51, 43, 35, 27, 19, 11, 3,
            61, 53, 45, 37, 29, 21, 13, 5,
            63, 55, 47, 39, 31, 23, 15, 7
            };
            for (int i = 0; i < 64; ++i) {
           		ans[i] = s[IP[i] - 1];
		    }
		    //cout << "IP transform: " << ans << endl;
		    return ans;
		}
		bitset<64> Iter(bitset<64> &s) {
			bitset<32> L, R;
			//get L0, R0.
			for (int i = 0; i < 32; ++i) {
				L[i] = s[i];
				R[i] = s[i + 32];
			}
			//Iter main process
			for (int i = 0; i < 16; ++i) {
				bitset<32>tmp = R;
				R = L ^ Feistal(R, key.k[i]);
				L = tmp;
				
			}
			bitset<64> ans;
			//这里，反向。 
			for (int i = 0; i < 32; ++i) {
				ans[i] = R[i];
				ans[i + 32] = L[i];
			}
			return ans;
		}
		bitset<64> IP_Inv(bitset<64> & s) {
            bitset<64> ans;
            int IP_Inv[] = {40, 8, 48, 16, 56, 24, 64, 32,
              39, 7, 47, 15, 55, 23, 63, 31,
              38, 6, 46, 14, 54, 22, 62, 30,
              37, 5, 45, 13, 53, 21, 61, 29,
              36, 4, 44, 12, 52, 20, 60, 28,
              35, 3, 43, 11, 51, 19, 59, 27,
              34, 2, 42, 10, 50, 18, 58, 26,
              33, 1, 41,  9, 49, 17, 57, 25
             };
            for (int i = 0; i < 64; ++i) {
           		ans[i] = s[IP_Inv[i] - 1];
		    }
		    return ans;
		}
		Key key;
};
