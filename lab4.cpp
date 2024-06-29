#include <iostream>
#include <bitset>
#include <vector>
#include "DES.h"

using namespace std;

string toUpperString(string str);
vector<string> splitString(const string& str);

int main()
{
	cout << "Enter text: ";
	string text;
	getline(cin, text);
	
	text = toUpperString(text);
	vector<string> asd = splitString(text);
	
	string key;
	string IV;
	
	do
	{
		cout << "Enter key (8 symbols max): ";
		cin >> key;
		if (key.size() <= 8) break;
	} while (true);

	do
	{
		cout << "Enter initial vector (8 symbols max): ";
		cin >> IV;
		if (IV.size() <= 8) break;
	} while (true);

	key = toUpperString(key);
	IV = toUpperString(IV);

	bitset<64> bitTestKey = convertStringToBitset(key);
	vector<bitset<48>> vecBitTestKey = keyGeneration(bitTestKey);
	vector<bitset<64>> textParts;
	vector<bitset<64>> cryptedTextParts;
	vector<bitset<64>> decryptedTextParts;
	
	string decryptedText = "";
	string cryptedText = "";

	cout << endl;

	for (int i = 0; i < asd.size(); ++i)
	{
		textParts.push_back(convertStringToBitset(asd[i]));
	}

	bitset<64> bitIV = convertStringToBitset(IV);
	cryptedTextParts = encrypt_OFB(textParts, bitIV, vecBitTestKey);
	decryptedTextParts = decrypt_OFB(cryptedTextParts, bitIV, vecBitTestKey);

	for (int i = 0; i < cryptedTextParts.size(); ++i)
	{
		cryptedText += bitsetToString(cryptedTextParts[i]);
	}
	for (int i = 0; i < decryptedTextParts.size(); ++i)
	{
		decryptedText += bitsetToString(decryptedTextParts[i]);
	}
	
	cout << endl;
	cout << "crypted text - " << cryptedText << endl << endl;
	cout << "decrypted text - " << decryptedText << endl << endl;

}

string toUpperString(string str)
{
	string newStr = "";
	for (char c : str)
	{
		c = toupper(c);
		newStr.push_back(c);
	}
	return newStr;
}

vector<string> splitString(const string& str) {
	vector<string> result;

	for (size_t i = 0; i < str.size(); i += 8) {
		result.push_back(str.substr(i, 8));
	}

	return result;
}