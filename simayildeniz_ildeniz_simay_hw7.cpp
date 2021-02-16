# include <iostream>
# include <string>
# include <vector>
# include <cmath>
using namespace std;

string extendKey(const string & key, const string & plaintext)
{
	if (plaintext.length() > key.length())
	{
		string tempKey = key;
		for (int i = 0; i < (plaintext.length()-key.length()); i++)
		{
			tempKey += key[(i % (key.length()))];
		}
		return tempKey;
	}
	return key;	
}

void permuteAndEncrypt(unsigned char & ch,const unsigned char & chKey)  // ch of plain text 
{
	unsigned char index1 = ch & 0x01;  // 2^0 = 1 = 0x01
	index1 = index1 << 2;              // shifted 2 right
	unsigned char index2 = ch & 0x02;  // 2^1 = 2 = 0x02
	index2 = index2 >> 1;              // shifted 1 left
	unsigned char index3 = ch & 0x04;   // 2^2 = 4 = 0x04
	index3 = index3 << 1;               // shifted 1 right
	unsigned char index4 = ch & 0x08;   // 2^3 = 8 = 0x08
	index4 = index4 >> 2;               // shifted 2 left
	unsigned char index5 = ch & 0x10;   // 2^4 = 16 = 0x10
	index5 = index5 << 2;               // shifted 2 right
	unsigned char index6 = ch & 0x20;   // 2^5 = 32 = 0x20
	index6 = index6 >> 1;               // shifted 1 left
	unsigned char index7 = ch & 0x40;   // 2^6 = 64 = 0x40
	index7 = index7 << 1;               // shifted 1 right
	unsigned char index8 = ch & 0x80;   // 2 ^7 = 128 = 0x80
	index8 = index8 >> 2;               // shifted 2 right
	unsigned char encryptedMes = index1 | index2 | index3 | index4 | index5 |index6 |index7 | index8;
	encryptedMes = chKey ^ encryptedMes;
	cout << hex << (int) encryptedMes;
}

int main()
{
	string key, plaintext;
	cout << "*** Welcome to the Simple Data Encryption Application ***" << endl;
	cout << "Please enter the encryption key: ";
	getline(cin,key);
	cout << "Please enter the plaintext to be encrypted: ";
	while (getline(cin,plaintext))
	{
		string extKey = extendKey(key,plaintext);
		int index = 0; // loop variable
		vector <unsigned char> vecOfPlainChars; // includes chars of the plain text
		vector <unsigned char> vecOfKeyChars;  // includes chars of the extended key
		while (index != plaintext.length())  // to fill the vectors:
		{
			unsigned char charPlain = plaintext[index];  
			unsigned char charKey = extKey[index];
			vecOfKeyChars.push_back(charKey);
			vecOfPlainChars.push_back(charPlain);
			index++;
		}
		cout << "Ciphertext: ";
		for (int i = 0; i < vecOfPlainChars.size(); i++)
		{
			permuteAndEncrypt(vecOfPlainChars[i],vecOfKeyChars[i]);  // also displays the encrypted message 
		}
		cout << endl; cout << endl;
		cout << "Please enter the plaintext to be encrypted: ";
	}
	return 0;
}