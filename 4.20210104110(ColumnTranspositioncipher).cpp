#include <bits/stdc++.h>
using namespace std;
bool validate_key(const string& key) {
    for (char c : key) {
        if (!isdigit(c)) return false;
    }
    set<char> unique_chars(key.begin(), key.end());
    return key.length() == unique_chars.size();
}
vector<vector<char>> create_encryption_matrix(const string& message, int rows, int cols) {
    vector<vector<char>> matrix(rows, vector<char>(cols, 'X'));
    int index = 0;


    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (index < message.length()) {
                matrix[i][j] = message[index++];
            }
        }
    }
    return matrix;
}

void display_matrix(const vector<vector<char>>& matrix, const string& label) {
    cout << "\n" << label << ":\n";
    for (const auto& row : matrix) {
        for (char c : row) {
            cout << c << " ";
        }
        cout << endl;
    }
}


string column_transposition_encrypt(const string& message, const string& key) {
    int cols = key.length();
    int rows = (message.length() + cols - 1) / cols;


    vector<vector<char>> matrix = create_encryption_matrix(message, rows, cols);


    display_matrix(matrix, "Matrix (Row-wise Fill)");

    vector<int> column_order(cols);
    iota(column_order.begin(), column_order.end(), 0);
    sort(column_order.begin(), column_order.end(), [&](int a, int b) {
        return key[a] < key[b];
    });


    string encrypted_message;
    for (int col : column_order) {
        for (int row = 0; row < rows; ++row) {
            encrypted_message += matrix[row][col];
        }
    }


    vector<vector<char>> transformed_matrix(rows, vector<char>(cols));
    for (int col = 0; col < cols; ++col) {
        for (int row = 0; row < rows; ++row) {
            transformed_matrix[row][col] = matrix[row][column_order[col]];
        }
    }
    display_matrix(transformed_matrix, "Transformed Matrix (Reordered Columns)");

    return encrypted_message;
}


string column_transposition_decrypt(const string& encrypted_message, const string& key) {
    int cols = key.length();
    int rows = (encrypted_message.length() + cols - 1) / cols;


    vector<int> column_order(cols);
    iota(column_order.begin(), column_order.end(), 0);
    sort(column_order.begin(), column_order.end(), [&](int a, int b) {
        return key[a] < key[b];
    });


    vector<vector<char>> matrix(rows, vector<char>(cols, 'X'));
    int index = 0;
    for (int col : column_order) {
        for (int row = 0; row < rows; ++row) {
            if (index < encrypted_message.length()) {
                matrix[row][col] = encrypted_message[index++];
            }
        }
    }


    display_matrix(matrix, "Matrix Reconstructed from Encrypted Message");


    string decrypted_message;
    for (const auto& row : matrix) {
        for (char c : row) {
            decrypted_message += c;
        }
    }
    return decrypted_message;
}

int main() {
    string message, key;


    cout << "Enter the message (plaintext): ";
    getline(cin, message);


    cout << "Enter the key (e.g., '31542'): ";
    cin >> key;


    if (!validate_key(key)) {
        cerr << "Invalid key: Ensure the key contains only unique digits." << endl;
        return 1;
    }
    string encrypted_message = column_transposition_encrypt(message, key);
    cout << "\nEncrypted Message: " << encrypted_message << endl;



    return 0;
}
