#include <iostream>
#include <string>
#include <cmath>
using namespace std;

inline unsigned int leftrotate(unsigned int data,int bit){
	return ((data << bit) | (data >> (32 - bit)));
}

string md5(char* p){
	char table[] = "0123456789ABCDEF";
	unsigned int h[] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476 };
	unsigned int r[64] = { 7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
						   5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
						   4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
						   6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21 };
	unsigned int k[64];
	for (size_t i = 0; i < 64; i++)
	{
		k[i] = floor(abs(sin(i + 1)) * (1ull<< 32));
	}
	size_t len = strlen(p);
	unsigned long long bitlen = len * 8;
	*(p + len) = 0x80;
	len++;
	memset(p + len, 0, 56 - (len % 64));
	len += (56 - (len % 64));
	unsigned long long* _p = (unsigned long long*)(p + len);
	*_p = bitlen;
	len += 8;
	size_t chunk = len / 64;
	size_t index = 0;
	while (index != chunk)
	{
		unsigned int f, g;
		unsigned int a = h[0], b = h[1], c = h[2], d = h[3];
		for (size_t i = 0; i < 64; i++)
		{
			if (i < 16){
				f = (b & c) | ((~b) & d);
				g = i;
			}
			
			else if (i < 32)
			{
				f = (d & b) | ((~d) & c);
				g = (5 * i + 1) % 16;
			}
			else if (i < 48){
				f = b ^ c ^ d;
				g = (3 * i + 5) % 16;
			}
			else{
				f = c ^ (b | (~d));
				g = (7 * i) % 16;
			}
			unsigned int temp = d;
			d = c;
			c = b;
			b = leftrotate((a + f + k[i] + *( (unsigned int*)(p + index * 64 + 4 * g) ) ), r[i]) + b;
			a = temp;
		}
		h[0] = h[0] + a;
		h[1] = h[1] + b;
		h[2] = h[2] + c;
		h[3] = h[3] + d;
		++index;
	}
	string ret;
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			ret += table[((h[i] >> (8 * j)) & 0xf0) >> 4];
			ret += table[((h[i] >> (8 * j)) & 0xf)];
		}
	}
	return ret;
}


int main(int argc,char* argv[]){
	char str[70] = "The quick brown fox jumps over the lazy dog";
	cout << md5(str) << endl;
	return 0;
}