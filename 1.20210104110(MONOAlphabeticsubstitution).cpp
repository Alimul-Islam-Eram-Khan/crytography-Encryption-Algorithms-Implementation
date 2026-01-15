#include <bits/stdc++.h>
using namespace std;


string Monoalphabetic_Cipher_Encryption(string message, string key) {
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    unordered_map<char, char> char_map;


    for (int i = 0; i < 26; i++) {
        char_map[alphabet[i]] = key[i];
        char_map[toupper(alphabet[i])] = toupper(key[i]);
    }

    string ency = "";
    for (char c : message) {
        if (isalpha(c)) {
            ency += char_map[c];
        } else {
            ency += c;
        }
    }
    return ency;
}



int main() {
    string key = "FDSAVCXZGHJKLREWQTYUIOPMNB";
    string message;

    cout << "Enter the message to encrypt: ";
    getline(cin, message);


    string encrypted_message = Monoalphabetic_Cipher_Encryption(message, key);
    cout << "Encrypted Message: " << encrypted_message << endl;
    return 0;
}
