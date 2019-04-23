#include <iostream>
#include <sstream>
#include <string>
#include <bitset>
#include <vector>
#include <iomanip> // setfill, setw
using namespace std;


// make a data type agnostic one.
template <class T>
void printvector(vector<T> &v) {
	for (int i = 0; i < v.size(); i++) {
			cout << v[i] << endl;
	}
}
// printvector<string>(blocks);

template <typename T>
std::string bin_to_hex( T i ) {
  std::stringstream stream;
  stream //<< "0x" 
         << std::setfill ('0') << std::setw(sizeof(T)/4) 
         << std::hex << i;
  return stream.str();
}

template <typename T>
std::string int_to_hex( T i ) {
  std::stringstream stream;
  stream //<< "0x" 
         << std::setfill ('0') << std::setw(2) 
         << std::hex << i;
  return stream.str();
}

int starting_size(int length) {
	int size;
	if (length < 65636) {
		if ((length > 2) && (length % 2 == 0)) {
			size = length / 2;
		} else if ((length > 2) && (length % 2 != 0)) {
			size = (length - 1) / 2;
		}
	} else if (length >= 65636) {
		size = 65636;
	} else {
		cerr << "Wrong hexstr length\n";
	}
	return size;
}

int main () {
	string str_sample = "HHHHHHHHHHHHHHHHHHHHHHH";
	string hexstr = "";
	for (const int& c : str_sample)
		hexstr.append(bin_to_hex(c));
	cout << hexstr << endl;
	for (int block = starting_size(hexstr.length()); block > 6; block--) {
		cout << "\n" << "block size: " << block << endl;

		for (int i = block; i < hexstr.length() - 6; i++) {
			if (hexstr.substr(i, block).length() == block) {
				// cout << hexstr.substr(i, block) << endl;
				cout << "i = " << i << "\nposition = " << i - block + 1 << "\n" << hexstr.substr(0, block) <<"\n" << hexstr.substr(i, block) << endl; 
				if (hexstr.substr(0, block) == hexstr.substr(i, block)) {
					cout << "MATCH" << endl;
					cout << hexstr.substr(0, i) << endl;
					cout << "FF" << int_to_hex(i - block + 1) << int_to_hex(block) << endl;
					cout << hexstr.substr(i + block, string::npos) << endl;
					hexstr = hexstr.substr(0, i) + "FF" + int_to_hex(i - block + 1) + int_to_hex(block) + hexstr.substr(i + block, string::npos);
					cout << hexstr << endl;
				}
			}
		}
	}
	string compressed_hexstr = "";
	for (int i = 0; hexstr.length() - 1; i += 2) {
		
	}
}

