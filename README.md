## Charlie Conneely - G00348887 - Theory of Algorithms Project 20/21

### **Repo Contents**
* **`/LabExercises`**: Folder containing all C programs illustrating different aspects of the SHA process.
* **`/TestFiles`**: Folder containing all .txt files which are used to test the SHA512 program. 
* **`Makefile`**: File containing all make commands (more info under *Compilation/Test Instructions*).
* **`tests.sh`**: Bash code which loops through the `/TestFiles` directory and processes each file using the `sha512` executable, comparing the resulting hash digest with that of the built-in `sha512sum` function. After each iteration, the result will be echo'd to the command line indicating a *Pass* or *Fail*.   
* **`sha512.c`**: Source code, written in C, which performs all aspects of the SHA512 algorithm on a file which is passed in as a command line argument.  



***
<!-- ## **Compilation/Test Instructions** -->
### **Compilation/Testing:** 
To create the necessary sha512 executable run:
```bash
make
```

To remove all executables from the repository run:
```bash
make clean
```

To test the program against files in the `TestFiles` directory, run:
```bash
make test
```
### **Running the program:** 
After calling `make`, to execute the sha512 algorithm against a file: 
```bash
./sha512 -p path/toFile.txt
```

To caculate the hash digest of multiple files:
```bash
./sha512 -p file1.txt file2.txt pathTo/file3.txt
```

For a more descriptive output, run:
```bash
./sha512 -v -p file.txt
```


***
### **What is the SHA512 algorithm?**
The SHA512 algorithm is a member of a family of cryptographic functions which are designed to protect data. Using *bitwise operations*, *modular additions*, and *compression functions*, the SHA512 algorithm will transform input data into a respective hash. This hash is a collection of bits whose length, in the case of SHA512, is a multiple of 512. <br>
The point of algorithms such as this, is that they are *one way*. For any given hash value, to compute it's respective input (if it is unknown) would be almost impossible and extremely costly. <br>
Hashing algorithms such as SHA512 serve many purposes. For example, passwords are often stored in a database as their hash values, meaning that if someone were to gain access it would be almost impossible to compute the original passwords. Additionaly, since a small change in input can have drastic changes in the respective hash ouput, tampering in files by hackers can easily be detected.        

### **Questions**
1. "*Why can't we reverse the SHA512 algorithm to retrieve the original message from a hash digest?*"<br>
1. "*Can you design an algorithm that, given enough time, will find input messages that give each of the possible 512-bit strings?*"
1. "*How difficult is it to find a hash digest beginning with at least twelve zeros?*"

***
### Resources
* [U.S. Department of Commerce - Secure Hash Standard (SHS)](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf)
* [Brilliant.org](https://brilliant.org/wiki/secure-hashing-algorithms/)
* [Bitwise Operators](https://www.javatpoint.com/bitwise-operator-in-c)
