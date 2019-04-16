#include <iostream>
#include <sstream>
#include <string>
#include <bitset>
#include <vector>
using namespace std;

int main () {
	stringstream ss;
	string text_sample = "How are you, Jon?";
	int l = text_sample.length();
	cout << "text length: " << l << endl;	
	for (int i = 0; i < l; i++) {
		// ss << hex << (int)text_sample.at(i); 
		ss << hex << bitset<8>((int)text_sample.at(i)); 
	}
	string hexstring = ss.str();
	cout << "0x" << hexstring << endl;
	int hexstring_length = hexstring.length();
	cout << "length of hexstring: " << hexstring_length << endl << endl;
	int num_of_blocks = 1;
	for (int block_size = hexstring_length / 2; block_size >= 4; block_size /= 2) {
		num_of_blocks *= 2;
		cout << "number of blocks: " << num_of_blocks << endl;
		cout << "block size: " << block_size << endl;


		// prints dynamic even sized blocks of hex string.
		vector <string> blocks;
		for (int n = 0; n < num_of_blocks; n++) {
			// cout << "n = " << n << endl;
			string block_string = hexstring.substr( (block_size * n),  block_size); // substr(location, length)
			cout << block_string << endl;
			blocks.push_back(block_string);
		}
		cout << endl;
	}
}