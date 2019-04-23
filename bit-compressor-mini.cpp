#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
// #include <bitset>
// #include <vector>
#include <iomanip> // setfill, setw
using namespace std;

// Returns hex number string of binary int.
// Have not validated for numbers greater than 0xFF.
template <typename T>
std::string bin_to_hex( T i ) {
  std::stringstream stream;
  stream //<< "0x" 
         << std::setfill ('0') << std::setw(sizeof(T)/4) 
         << std::hex << i;
  return stream.str();
}

// Return hex number string of a dec int.
// Same validation as the former function.
template <typename T>
std::string int_to_hex( T i ) {
  std::stringstream stream;
  stream //<< "0x" 
         << std::setfill ('0') << std::setw(2) 
         << std::hex << i;
  return stream.str();
}

// Gives the first block size that can divide the hexstr into at least 2 equal length strings.
// Capped at 65636 as that is 16^4 and that's the farthest index distance that the FFXXYY marker can hold.
// Realistically, the farthest would be 15^2 as the FFXXYY marker values haven't been offset to account for the unused 0x00.
// Other limits that have not been accounted for is that the largest block size is 16^2=256 (if offseted).
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
	// Writing the hexstr with the Hexadecimals of the ascii codes of the string. 
	for (const int& c : str_sample)
		hexstr.append(bin_to_hex(c));
	cout << hexstr << endl;
	// Record the initial hexstr length so it can be compared to the marked one later.
	int init_hexstr_len = hexstr.length();
	// Starts going through all potential block sizes that could be marked and compressed.
	for (int block = starting_size(hexstr.length()); block > 6; block--) {
		cout << "\n" << "block size: " << block << endl;
		// Once a block size is chosen,  it will run through all the indexes except for the last. This is because there is no purpose of getting a string of block size 6 or less as it can't be compressed with FFXXYY.
		// This will run through all possible block-sized substrs to see if it fits with the initial block.
		for (int i = block; i < hexstr.length() - 6; i++) {
			// Verify that the current chosen substr is the same size as the chosen block size.
			if (hexstr.substr(i, block).length() == block) {
				// cout << hexstr.substr(i, block) << endl;
				cout << "i = " << i << "\nposition = " << i - block + 1 << "\n" << hexstr.substr(0, block) <<"\n" << hexstr.substr(i, block) << endl; 
				// If the first block-size substr is equal to one of the other block-size substr (while not being in the same indexes), then a match is declared, shown, and compressed.
				if (hexstr.substr(0, block) == hexstr.substr(i, block)) {
					cout << "MATCH" << endl;
					cout << hexstr.substr(0, i) << endl;
					cout << "FF" << int_to_hex(i - block + 1) << int_to_hex(block) << endl;
					cout << hexstr.substr(i + block, string::npos) << endl;
					// I need to write on how the FFXXYY marker works in the README.
					hexstr = hexstr.substr(0, i) + "FF" + int_to_hex(i - block + 1) + int_to_hex(block) + hexstr.substr(i + block, string::npos);
					cout << hexstr << endl;
				}
			}
		}
	}
	cout << endl;
	// Now that all possible repeating patterns have been substituted with the marker, The hexstr is compressed to their equivalent char. Depending on which text editor is used you might or might no see different symbols, as not all hexadecimal have a char counterpart. This is because the classic ASCII table goes from 0x00 to 0x7F. Many computers have extended ASCII tables so it's possible values over 0x7F will be represented with actual char or something. If the table doesn't have anything for that char, you'll either see a box as a placeholder or <0xXX> instead with "XX" substituted with the hexadecimal. The good thing is that either way any text editor will read it as one char so it will still be compressed even if not that human readable.
	string compressed_hexstr = "";
	for (int i = 0; i <hexstr.length() - 1; i += 2) {
		cout << "hex: " << hexstr.substr(i, 2);
		int intsubstr;
		istringstream(hexstr.substr(i, 2)) >> std::hex >> intsubstr;
		cout << "\tascii: " << intsubstr;
		cout << "\tchar " << (char)intsubstr << endl;
		compressed_hexstr += (char)intsubstr;
	}
	// Print out the results of the compressor.
	cout << endl;
	cout << str_sample << endl;
	cout << hexstr << endl;
	cout << compressed_hexstr << endl;
	cout << "hex length before: " << init_hexstr_len << endl;
	cout << "hex lenght after: " << hexstr.length() << endl;
	cout << "compressed hex to char length: " << compressed_hexstr.length() << endl; 
	
	// Write into two files the output alone and a comparison respectively.
	ofstream compar_file;
	compar_file.open("comparison C++.txt");
	compar_file << hexstr << "\n\n" << compressed_hexstr;
	compar_file.close();
	ofstream output_file;
	output_file.open("output C++.txt");
	output_file << compressed_hexstr;
	output_file.close();
}