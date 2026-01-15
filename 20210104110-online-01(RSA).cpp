#include<bits/stdc++.h>
using namespace std;

// Check if the nth number is prime
bool isPrime(int n) {
    if (n % 2 == 0) return n == 2;
    if (n % 3 == 0) return n == 3;
    int step = 4, m = (int)pow(n, 0.5) + 1;
    for (int i = 5; i < m; step = 6 - step, i += step) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

// Extended Euclidean Algorithm
int gcdExtended(int a, int b, int *x, int *y) {
    if (a == 0) {
        *x = 0, *y = 1;
        return b;
    }
    int x1, y1;
    int gcd = gcdExtended(b % a, a, &x1, &y1);
    *x = y1 - (b / a) * x1;
    *y = x1;
    return gcd;
}

// Compute GCD
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Modular multiplicative inverse
int modInverse(int a, int m) {
    int x, y;
    int g = gcdExtended(a, m, &x, &y);
    if (g != 1)
        return -1;
    else {
        return (x % m + m) % m;
    }
}

// Modular exponentiation a^b % c
unsigned long long emod(unsigned long long a, unsigned long long b, unsigned long long c) {
    if (b == 0) {
        return 1;
    } else if (b % 2 == 0) {
        unsigned long long d = emod(a, b / 2, c);
        return (d * d) % c;
    } else {
        return ((a % c) * emod(a, b - 1, c)) % c;
    }
}

// Encrypt or decrypt the message
template<class T>
vector<unsigned long long> encrypt_decrypt(vector<T> msgV, unsigned long long n_or_d, unsigned long long e) {
    vector<unsigned long long> c;
    for (auto it = msgV.begin(); it != msgV.end(); ++it) {
        unsigned long long v = emod(*it, e, n_or_d);
        c.push_back(v);
    }
    return c;
}

// Function to display vector contents
template<class T>
void iterateAndDisplay(vector<T> aVector, int incrementValue) {
    for (auto it = aVector.begin(); it != aVector.end(); it += incrementValue) {
        cout << "'" << *it << "' ";
    }
}

int main() {
    string message;
    vector<int> msgVectorN;
    vector<char> msgVectorC;
    vector<unsigned long long> msgBlocks;
    vector<int> recoveredMsg;

    cout << "Enter a message: ";
    getline(cin, message);

    for (char ch : message) {
        msgVectorC.push_back(ch);
        if (ch != ' ') {
            msgVectorN.push_back(int(ch - 65));
        } else {
            msgVectorN.push_back(26);
        }
    }

    cout << "Message:              ";
    iterateAndDisplay(msgVectorC, 1);
    cout << endl;

    cout << "Number values:         ";
    iterateAndDisplay(msgVectorN, 1);
    cout << endl;

    if (msgVectorN.size() % 2 == 0) {
        for (auto it = msgVectorN.begin(); it != msgVectorN.end(); it += 2) {
            msgBlocks.push_back(*it * 100 + (*(it + 1)));
        }
    } else {
        auto it = msgVectorN.begin();
        for (; it != msgVectorN.end() - 1; it += 2) {
            msgBlocks.push_back(*it * 100 + (*(it + 1)));
        }
        msgBlocks.push_back(*it * 100);
    }

    cout << "Message Blocks:        ";
    iterateAndDisplay(msgBlocks, 1);
    cout << endl;

    int p, q;
    cout << "Enter a prime number p: ";
    cin >> p;
    cout << "Enter a prime number q: ";
    cin >> q;

    unsigned long long n = p * q;
    unsigned long long totient = (p - 1) * (q - 1);

    // Generate e automatically
    int e_coPrime;
    for (e_coPrime = 2; e_coPrime < totient; ++e_coPrime) {=
        if (gcd(e_coPrime, totient) == 1) {
            break;
        }
    }

    unsigned long long d = modInverse(e_coPrime, totient);

    cout << "Public Key  (e , n):   (" << e_coPrime << " , " << n << " )" << endl;
    cout << "Private Key (d , n):   (" << d << " , " << n << " )" << endl;

    vector<unsigned long long> encryptedMsg = encrypt_decrypt(msgBlocks, n, e_coPrime);

    cout << "Encrypted Message:     ";
    iterateAndDisplay(encryptedMsg, 1);
    cout << endl;

    vector<unsigned long long> decryptedMsg = encrypt_decrypt(encryptedMsg, n, d);

    cout << "Decrypted Message:     ";
    iterateAndDisplay(decryptedMsg, 1);
    cout << endl;

    for (auto block : decryptedMsg) {
        if (block > 99) {
            recoveredMsg.push_back(block / 100);
            int secondValue = block % 100;
            if (secondValue != 0) {
                recoveredMsg.push_back(secondValue);
            }
        } else {
            recoveredMsg.push_back(block);
        }
    }

    cout << "Number values:         ";
    iterateAndDisplay(recoveredMsg, 1);
    cout << endl;

    cout << "Message:               ";
    for (int num : recoveredMsg) {
        if (num == 26) {
            cout << "' ' ";
        } else {
            cout << "'" << char(num + 65) << "' ";
        }
    }
    cout << endl;

    //-------1.Computing hashed value h
    int k;
    cout << "Enter a random number k: ";
    cin >> k;

    unsigned long long h = (emod(e_coPrime, k, totient) + d) % totient;


    cout << "Hashed Value (h):      " << h << endl;


    //----2. Verifying  h
    if (gcd(h, totient) == 1) {

        cout << "Hash is valid and satisfies gcd = 1" << endl;
    } else {

        cout << "Invalid Hash" << endl;
    }

    return 0;
}

