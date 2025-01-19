#include <iostream>
#include <fstream>
#include <openssl/sha.h>  // For SHA-256 hashing (requires OpenSSL)
#include <sstream>
#include <iomanip>

using namespace std;

// Function to calculate the SHA-256 hash of a file
string calculateFileHash(const string &fileName) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    ifstream file(fileName, ios::binary);
    if (!file.is_open()) {
        cerr << "Error opening file: " << fileName << endl;
        return "";
    }

    char buffer[1024];
    while (file.read(buffer, sizeof(buffer))) {
        SHA256_Update(&sha256, buffer, file.gcount());
    }
    SHA256_Final(hash, &sha256);

    // Convert hash to hexadecimal string
    stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        ss << hex << setw(2) << setfill('0') << (int)hash[i];
    }

    return ss.str();
}

// Function to save the file hash to a file
void saveHashToFile(const string &fileName, const string &hash) {
    ofstream outFile(fileName);
    if (!outFile.is_open()) {
        cerr << "Error opening hash file for writing." << endl;
        return;
    }
    outFile << hash;
    outFile.close();
}

// Function to read the saved hash from a file
string readHashFromFile(const string &fileName) {
    ifstream inFile(fileName);
    if (!inFile.is_open()) {
        cerr << "Error opening hash file for reading." << endl;
        return "";
    }

    string savedHash;
    inFile >> savedHash;
    inFile.close();
    return savedHash;
}

int main() {
    string fileToCheck, hashFile;

    // Ask the user to input the file to check and the location to store the hash
    cout << "Enter the path of the file you want to check: ";
    cin >> fileToCheck;

    cout << "Enter the location where you want to store the hash (e.g., hash.txt): ";
    cin >> hashFile;

    // Check if the hash file exists
    string savedHash = readHashFromFile(hashFile);
    
    if (savedHash.empty()) {
        // If no hash file exists, calculate and save the hash
        string currentHash = calculateFileHash(fileToCheck);
        if (!currentHash.empty()) {
            saveHashToFile(hashFile, currentHash);
            cout << "Hash saved for file: " << fileToCheck << endl;
        }
    } else {
        // If hash file exists, compare the hashes
        string currentHash = calculateFileHash(fileToCheck);
        if (!currentHash.empty()) {
            if (savedHash == currentHash) {
                cout << "File integrity is intact. No changes detected." << endl;
            } else {
                cout << "WARNING: File has been modified!" << endl;
            }
        }
    }

    return 0;
}

