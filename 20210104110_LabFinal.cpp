#include <bits/stdc++.h>
using namespace std;


const char cipherKey[26][3] =
{
    {'X', 'Y', 'Z'}, // A
    {'M', 'N', 'O'}, // B
    {'P', 'Q', 'R'}, // C
    {'S', 'T', 'U'}, // D
    {'L', 'M', 'N'}, // E
    {'A', 'B', 'C'}, // F
    {'D', 'E', 'F'}, // G
    {'G', 'H', 'I'}, // H
    {'J', 'K', 'L'}, // I
    {'O', 'P', 'Q'}, // J
    {'R', 'S', 'T'}, // K
    {'V', 'W', 'X'}, // L
    {'Y', 'Z', 'A'}, // M
    {'B', 'C', 'D'}, // N
    {'F', 'G', 'H'}, // O
    {'I', 'J', 'K'}, // P
    {'L', 'M', 'N'}, // Q
    {'O', 'P', 'Q'}, // R
    {'R', 'S', 'T'}, // S
    {'U', 'V', 'W'}, // T
    {'X', 'Y', 'Z'}, // U
    {'A', 'B', 'C'}, // V
    {'D', 'E', 'F'}, // W
    {'G', 'H', 'I'}, // X
    {'J', 'K', 'L'}, // Y
    {'M', 'N', 'O'}  // Z
};

// encrypting plaintext
string encrypt(const string& plaintext)
{
    string ciphertext = "";
    for (char c : plaintext)
    {
        int index = c - 'A';
        int randChoice = rand() % 3;
        ciphertext += cipherKey[index][randChoice];
    }
    return ciphertext;
}

// decrypting ciphertext
string decrypt(const string& ciphertext)
{
    string plaintext = "";
    for (char c : ciphertext)
    {
        //seaching for matching match
        for (int i = 0; i < 26; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (cipherKey[i][j] == c)
                {
                    plaintext += (char)('A' + i);
                    break;
                }
            }
        }
    }
    return plaintext;
}

int main()
{
    srand(time(0));

    string plaintext;
    cout << "Enter plaintext (uppercase letters A-Z only): ";
    getline(cin, plaintext);
    string ciphertext = encrypt(plaintext);
    cout << "Encrypted text: " << ciphertext << endl;
    string decrypted = decrypt(ciphertext);
    cout << "Decrypted text: " << decrypted << endl;

    return 0;
}
