#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Generate key table for Playfair cipher
void generateKeyTable(string key, vector<vector<char>>& keyTable) {
    vector<bool> used(26, false);
    key.erase(remove(key.begin(), key.end(), 'j'), key.end()); // Remove 'j'
    
    int idx = 0;
    for (char c : key) {
        if (!used[c - 'a']) {
            keyTable[idx / 5][idx % 5] = c;
            used[c - 'a'] = true;
            idx++;
        }
    }

    for (char c = 'a'; c <= 'z'; c++) {
        if (c != 'j' && !used[c - 'a']) {
            keyTable[idx / 5][idx % 5] = c;
            idx++;
        }
    }
}

// Find the position of a character in the key table
pair<int, int> findPosition(vector<vector<char>>& keyTable, char c) {
    if (c == 'j') c = 'i';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (keyTable[i][j] == c)
                return {i, j};
        }
    }
    return {-1, -1};
}

// Playfair encryption function
string playfairEncrypt(string plaintext, vector<vector<char>>& keyTable) {
    string ciphertext = "";

    // Preprocessing: Insert 'x' between repeating letters
    for (int i = 0; i < plaintext.size(); i += 2) {
        if (i + 1 == plaintext.size() || plaintext[i] == plaintext[i + 1]) {
            plaintext.insert(i + 1, 1, 'x');
        }
    }

    // Encrypting pairs of characters
    for (int i = 0; i < plaintext.size(); i += 2) {
        pair<int, int> pos1 = findPosition(keyTable, plaintext[i]);
        pair<int, int> pos2 = findPosition(keyTable, plaintext[i + 1]);

        if (pos1.first == pos2.first) {
            // Same row
            ciphertext += keyTable[pos1.first][(pos1.second + 1) % 5];
            ciphertext += keyTable[pos2.first][(pos2.second + 1) % 5];
        } else if (pos1.second == pos2.second) {
            // Same column
            ciphertext += keyTable[(pos1.first + 1) % 5][pos1.second];
            ciphertext += keyTable[(pos2.first + 1) % 5][pos2.second];
        } else {
            // Rectangle swap
            ciphertext += keyTable[pos1.first][pos2.second];
            ciphertext += keyTable[pos2.first][pos1.second];
        }
    }

    return ciphertext;
}

// Playfair decryption function
string playfairDecrypt(string ciphertext, vector<vector<char>>& keyTable) {
    string plaintext = "";

    // Decrypting pairs of characters
    for (int i = 0; i < ciphertext.size(); i += 2) {
        pair<int, int> pos1 = findPosition(keyTable, ciphertext[i]);
        pair<int, int> pos2 = findPosition(keyTable, ciphertext[i + 1]);

        if (pos1.first == pos2.first) {
            // Same row
            plaintext += keyTable[pos1.first][(pos1.second + 4) % 5];
            plaintext += keyTable[pos2.first][(pos2.second + 4) % 5];
        } else if (pos1.second == pos2.second) {
            // Same column
            plaintext += keyTable[(pos1.first + 4) % 5][pos1.second];
            plaintext += keyTable[(pos2.first + 4) % 5][pos2.second];
        } else {
            // Rectangle swap
            plaintext += keyTable[pos1.first][pos2.second];
            plaintext += keyTable[pos2.first][pos1.second];
        }
    }

    // Remove padding 'x'
    for (int i = 1; i < plaintext.size(); i++) {
        if (plaintext[i] == 'x' && plaintext[i - 1] == plaintext[i + 1]) {
            plaintext.erase(i, 1);
        }
    }

    return plaintext;
}

int main() {
    string key, plaintext, ciphertext;

    cout << "Enter key: ";
    cin >> key;
    cout << "Enter plaintext: ";
    cin >> plaintext;

    vector<vector<char>> keyTable(5, vector<char>(5));
    generateKeyTable(key, keyTable);

    ciphertext = playfairEncrypt(plaintext, keyTable);
    cout << "Ciphertext: " << ciphertext << endl;

    string decryptedText = playfairDecrypt(ciphertext, keyTable);
    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
