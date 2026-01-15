#include <bits/stdc++.h>
using namespace std;

vector<vector<char>> create_matrix(const string& message, int rows, int cols) {
    vector<vector<char>> matrix(rows, vector<char>(cols, 'X'));
    int index = 0;


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (index < message.length()) {
                matrix[i][j] = message[index++];
            }
        }
    }
    return matrix;
}
vector<vector<char>> transpose_matrix(const vector<vector<char>>& matrix, const string& key) {
    int cols = key.length();
    vector<int> column_order(cols);


    iota(column_order.begin(), column_order.end(), 0);
    sort(column_order.begin(), column_order.end(), [&](int a, int b) {
        return key[a] < key[b];
    });


    vector<vector<char>> transposed(matrix.size(), vector<char>(cols));
    for (int j = 0; j < cols; j++) {
        int column_index = column_order[j];
        for (int i = 0; i < matrix.size(); i++) {
            transposed[i][j] = matrix[i][column_index];
        }
    }
    return transposed;
}

string extract_encrypted_message(const vector<vector<char>>& matrix) {
    string encrypted_message;
    for (const auto& row : matrix) {
        for (char c : row) {
            encrypted_message += c;
        }
    }
    return encrypted_message;
}

int main() {
    string message, key;

    cout << "Enter the message: ";
    getline(cin, message);


    cout << "Enter the key (e.g., '31542'): ";
    cin >> key;

    int cols = key.length();
    int rows = (message.length() + cols - 1) / cols;

    vector<vector<char>> matrix = create_matrix(message, rows, cols);

    cout << "\nInitial Matrix (Row-wise):\n";
    for (const auto& row : matrix) {
        for (char c : row) {
            cout << c << " ";
        }
        cout << endl;
    }


    vector<vector<char>> transposed = transpose_matrix(matrix, key);

    cout << "\nTransformed Matrix (Columns reordered based on key):\n";
    for (const auto& row : transposed) {
        for (char c : row) {
            cout << c << " ";
        }
        cout << endl;
    }
    string encrypted_message = extract_encrypted_message(transposed);

    cout << "\nEncrypted Message: " << encrypted_message << endl;

    return 0;
}
