# File-Integrity-Monitor
This project calculates the SHA-256 hash of a file and stores it in a specified location. It then compares the stored hash with the current file hash to detect any changes, ensuring file integrity.

Overview
The File Integrity Checker project is designed to monitor the integrity of files by calculating their cryptographic hash values and comparing them to a stored value. This process ensures that the file has not been altered, modified, or corrupted. The main way this file works is through the use of a hash function, specifically SHA-256, to generate a unique string of characters (a hash) that represents the contents of the file. Even a small change in the file will result in a completely different hash value, allowing users to detect any unauthorized modifications.

Step 1: User Input for File Paths

When the program runs, it prompts the user for two essential inputs:

The file to monitor: The user provides the path to the file whose integrity is to be checked.
The location to store the hash: The user specifies where to store the hash of the file (for example, a text file like file_hash.txt). This location will store the hash value generated when the file is first checked.
These inputs allow the program to adapt to different file locations and ensure flexibility for the user. Once the paths are provided, the program moves forward with the hash calculation.

Step 2: Calculating the File’s SHA-256 Hash

The program reads the contents of the specified file in binary mode and calculates the SHA-256 hash using the OpenSSL library. SHA-256 is a cryptographic hash function that generates a fixed-length (256-bit) hash value, which is unique to the content of the file. The file is read in chunks, which are processed using the SHA256_Update function, and the final hash is obtained using SHA256_Final. The hash is then converted into a hexadecimal string for easy storage and comparison.

Step 3: Storing the Hash

If the specified location for the hash file doesn’t already exist, the program creates a new file and stores the generated hash value in it. This is accomplished through simple file I/O operations. The hash is saved in a plain text file, ensuring it can be retrieved later for comparison.

Step 4: Comparing the Hashes

Upon subsequent executions of the program, the user can check the integrity of the file again. The program reads the previously stored hash from the file and recalculates the hash of the current version of the monitored file. If the stored hash and the newly calculated hash match, the program confirms that the file's integrity is intact and no changes have occurred. If the hashes do not match, it indicates that the file has been modified, and the program issues a warning to inform the user.

Conclusion

The program allows for easy interaction, as it asks the user for file paths at runtime. It works with any file type, and the user can monitor multiple files by repeating the process. The stored hash file can also be kept in any directory of the user’s choice. This approach is useful for a variety of scenarios, such as ensuring the integrity of important documents, software files, or system configurations. By calculating and comparing hashes, the tool provides a simple yet effective way to monitor and verify file integrity over time, making it a great for cybersecurity purposes.
