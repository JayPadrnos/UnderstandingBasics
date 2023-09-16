#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to perform XOR encryption or decryption
void xorCrypt(string inputFile, string outputFile, string key) {
    ifstream inFile(inputFile,  ios::binary);
    ofstream outFile(outputFile, ios::binary);

    if (!inFile || !outFile) {
        cerr << "Error opening files." << endl;
        return;
    }

    size_t keyIndex = 0;
    char byte;

    while (inFile.get(byte)) {
        // XOR the byte with the key character
        byte ^= key[keyIndex];
        outFile.put(byte);

        // Move to the next character in the key
        keyIndex = (keyIndex + 1) % key.length();
    }

    inFile.close();
    outFile.close();
}

int main() {
    string inputFile = "input.txt";
    string encryptedFile = "encrypted.txt";
    string decryptedFile = "decrypted.txt";
    string key = "MySecretKey"; // Key can change

    // Encrypt the file
    xorCrypt(inputFile, encryptedFile, key);
    cout << "File encrypted." << endl;

    // Decrypt the file
    xorCrypt(encryptedFile, decryptedFile, key);
    cout << "File decrypted." << endl;

    return 0;
}