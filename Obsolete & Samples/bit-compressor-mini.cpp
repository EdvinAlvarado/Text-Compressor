#include <iostream>
#include <sstream>
#include <string>
#include <bitset>
#include <vector>
using namespace std;


// make a data type agnostic one.
template <class T>
void printvector(vector<T> &v) {
	for (int i = 0; i < v.size(); i++) {
			cout << v[i] << endl;
	}
}

int main () {
	stringstream ss;
	string text_sample = "hello.";
	int l = text_sample.length();
	// cout << "text length: " << l << endl;	
	// filling the string stream with the bit data.
	for (int i = 0; i < l; i++) {
		// ss << hex << (int)text_sample.at(i); 
		ss << hex << bitset<8>((int)text_sample.at(i)); 
	}
	string hexstring = ss.str();
	// cout << "0x" << hexstring << endl;
	// int hexstring_length = hexstring.length();
	cout << "length of hexstring: " << hexstring.length() << endl << endl;	

	// different block sizes
	int num_of_blocks = 1;
	for (int block_size = hexstring.length() / 2; block_size >= 8; block_size /= 2) {
		num_of_blocks *= 2;
		cout << "number of blocks: " << num_of_blocks << endl;
		cout << "block size: " << block_size << endl;

		// prints dynamic even sized blocks of hex string.
		vector<string> blocks;
		for (int n = 0; n < num_of_blocks; n++) {
			// cout << "n = " << n << endl;
			string block_string = hexstring.substr( (block_size * n),  block_size); // substr(location, length)
			// cout << block_string << endl;
			blocks.push_back(block_string);
		}
		// cout << endl;
		printvector<string>(blocks);
		cout << "blocks" << endl << endl;
		// stringstream compressor_ss;
		// compressor_ss << blocks[0];
		for (int i = 0; i < blocks.size()-1; i++) {
			cout << "block i: " << i << "\n" << blocks[i] << endl;			
			for (int j = 1+i; j < blocks.size(); j++) {
				cout << "block j: " << j << "\n" << blocks[j] << endl;		
				if (blocks[i] == blocks[j]) {
					// compressor_ss << "p" << j-i << block_size;
					string coder = "P" + to_string(j-i) + "L" + to_string(block_size);
					blocks[j] = coder;
				}
			}
			// cout << "compressed binary:\n" << compressor_ss.str() << endl << endl;
			// compressor_ss.str("");
			cout << endl << "resulting vector" << endl;
			printvector<string>(blocks);
			cout << endl;
		}
	}
}