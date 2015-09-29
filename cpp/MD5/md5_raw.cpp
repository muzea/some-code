#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
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

string md5_file(char* file){
	char table[] = "0123456789ABCDEF";
	unsigned int h[] = { 0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476 };
	unsigned int r[64] = { 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
		5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20, 5, 9, 14, 20,
		4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
		6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21 };
	unsigned int k[64];
	char read_buffer[64];
	ifstream fileStream(file,ios::in|ios::binary);
	for (size_t i = 0; i < 64; i++)
	{
		k[i] = floor(abs(sin(i + 1)) * (1ull << 32));
	}
	size_t len = 0;
	unsigned long long chunkSize = 0;
	bool end = false;
	unsigned long long bitlen = 0;
	while (!end)
	{
		fileStream.read(read_buffer, 64);
		chunkSize = fileStream.gcount();
		bitlen += chunkSize * 8ull;
		int loop = 1;
		if (chunkSize < 56){
			*(read_buffer + chunkSize) = 0x80;
			chunkSize++;
			memset(read_buffer + chunkSize, 0, 56 - chunkSize);
			*((unsigned long long*)(read_buffer + 56)) = bitlen;
			end = true;
		}
		else if (chunkSize != 64){
			*(read_buffer + chunkSize) = 0x80;
			chunkSize++;
			memset(read_buffer + chunkSize, 0, 64 - chunkSize);
			loop = 2;
		}
		while (loop)
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
				b = leftrotate((a + f + k[i] + *((unsigned int*)(read_buffer + 4 * g))), r[i]) + b;
				a = temp;
			}
			h[0] = h[0] + a;
			h[1] = h[1] + b;
			h[2] = h[2] + c;
			h[3] = h[3] + d;

			if (loop == 2){
				memset(read_buffer, 0, 56);
				*((unsigned long long*)(read_buffer + 56)) = bitlen;
				end = true;
				loop = 1;
			}
			else{
				loop = 0;
			}
		}
	}
	fileStream.close();
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
	cout << md5_file("test.txt") << endl;
	return 0;
}