#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
// #include <bitset>
// #include <vector>
#include <iomanip> // setfill, setw
using namespace std;

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
	int init_hexstr_len = hexstr.length();
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
	cout << endl;
	string compressed_hexstr = "";
	for (int i = 0; i <hexstr.length() - 1; i += 2) {
		cout << "hex: " << hexstr.substr(i, 2);
		int intsubstr;
		istringstream(hexstr.substr(i, 2)) >> std::hex >> intsubstr;
		cout << "\tascii: " << intsubstr;
		cout << "\tchar " << (char)intsubstr << endl;
		compressed_hexstr += (char)intsubstr;
	}
	cout << endl;
	cout << str_sample << endl;
	cout << hexstr << endl;
	cout << compressed_hexstr << endl;
	cout << "hex length before: " << init_hexstr_len << endl;
	cout << "hex lenght after: " << hexstr.length() << endl;
	cout << "compressed hex to char length: " << compressed_hexstr.length() << endl; 
	
	ofstream compar_file;
	compar_file.open("comparison C++.txt");
	compar_file << hexstr << "\n\n" << compressed_hexstr;
	compar_file.close();
	ofstream output_file;
	output_file.open("output C++.txt");
	output_file << compressed_hexstr;
	output_file.close();
}

