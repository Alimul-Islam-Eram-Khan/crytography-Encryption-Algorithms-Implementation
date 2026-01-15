
#include <bits/stdc++.h>
using namespace std;

string encryptPolySubstitute(const string& plaintext, const string& key) {
    string ciphertext = "";
    int keyIndex = 0;
    int keyLength = key.length();

    for (char c : plaintext) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            char keyChar = tolower(key[keyIndex % keyLength]);
            ciphertext += (c - base + (keyChar - 'a')) % 26 + base;
            keyIndex++;
        } else {
            ciphertext += c;
        }
    }
    return ciphertext;
}

int main() {
    string plaintext, key;
    cout << "Enter the plaintext to be encrypted: ";
    getline(cin, plaintext);

    cout << "Enter the encryption key (letters only): ";
    cin >> key;


    string encrypted = encryptPolySubstitute(plaintext, key);


    cout << "\nPlaintext:  " << plaintext << endl;
    cout << "Key:        " << key << endl;
    cout << "Encrypted:  " << encrypted << endl;

    return 0;
}


