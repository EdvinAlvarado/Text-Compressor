#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <sstream> // stringstream
using namespace std;

int main () {
	string line;
	stringstream ss;
	string binstr = "";
	ifstream myfile ("repeatingtest.txt");
	if (myfile.is_open()) {
		while (getline(myfile, line)) {
			cout << line << endl;
			cout << "Size of text file is " << line.size() << " bytes." << endl;
			cout << "Length of text file " << line.length() << endl;
			int l = line.length();

			for (int i = 0; i < l; i++) {
				ss << std::hex << (int)line.at(i) << std::dec; // writing directly to a hexadecimal string.
				bitset<8> bitchar(line.at(i)); //bitset<8> is the data type.
				cout << "binary " << bitchar << "\tdecimal " << bitchar.to_ulong() << "\thex " << std::hex << bitchar.to_ulong() << std::dec << endl; // hex gives them back as str. to_ulong as int.
				binstr.append(bitchar.to_string());
			}
			cout << binstr << endl;

			binstr.append(bitset<8>(0xa).to_string());
			cout << "added newline in binary " << bitset<8>(0xa) << endl;
			
		}
		myfile.close();
		cout << ss.str() << endl; //string hexadecximal string
	}

}




// int bin = line.at(0); // gets you the decimal ascci code of the char.
// cout << bin << endl;