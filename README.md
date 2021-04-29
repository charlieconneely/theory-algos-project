## Charlie Conneely - G00348887 - Theory of Algorithms Project 20/21
This repository contains a C program which can peform the SHA-512 algorithm on a file and output it's message digest. 
### **Contents**
- **`/LabExercises`**: Folder containing all C programs illustrating different aspects of the SHA process.
- **`/TestFiles`**: Folder containing all .txt files which are used to test the sha512 executable. 
- **`Makefile`**: File containing all make commands (more info under _Compilation/Test Instructions_).
- **`tests.sh`**: Bash code which loops through the `/TestFiles` directory and processes each file using the `sha512` executable, comparing the resulting hash digest with that of the built-in `sha512sum` function. After each iteration, the result will be echo'd to the command line indicating a _Pass_ or _Fail_.   
- **`sha512.c`**: Source code, written in C, which performs all aspects of the SHA-512 algorithm on a file which is passed in as a command line argument.  

***
### **Compilation/Testing:** 
To create the necessary sha512 executable, run:
```
make
```

To test the program against files in the `TestFiles` directory, run:
```
make test
```

To remove all executables from the repository, run:
```
make clean
```
### **Running the program:** 
After calling `make`, to execute the sha512 algorithm against a file: 
```
./sha512 -p path/toFile.txt
```

To calculate the hash digest of multiple files:
```
./sha512 -p file1.txt file2.txt pathTo/file3.txt
```

For a more descriptive output, run:
```
./sha512 -v -p file.txt
```


***


### **What is the SHA512 algorithm?**
The SHA-512 algorithm is a member of a larger family of cryptographic which use variations of the S.H.A (Secure Hash Algorithm). Using _bitwise operations_, _modular additions_, and _compression functions_, the SHA algorithm will protect data by transforming it into a fixed-length hash. This hash, in the case of SHA-512, is 512 bits in length. <br>
The most important feature of the Secure Hash Algorithm is that it is _one way_. For any given hash value, to compute it's respective input (if it is unknown) would be almost impossible and extremely costly. <br>
The general procedure of the Secure Hash Algorithm remains the same across most variations (SHA-1, SHA-256, SHA-512, etc.) However, there are a few elements of the SHA-512 algorithm which differ: 
- The maximum length of an input message is 2^128, with a fixed output length of 512 bits. 
- Where other algorithms require constant arrays of 32 bit words, SHA-512 requires constant arrays of 64 bit words.   
- Bitwise operations such as _SIG-0_ are calculated using different integer values. Also, the _rotate left_ bit operation is not used anywhere in SHA-512.

### **How does SHA-512 work?** 
There are two main stages in SHA-512. I will briefly describe both stages here, as putting the entire process into perspective will make it easier to answer particular questions later on.   
**Stage 1: Preprocessing** 
* **Padding the message**: 
This initial step involves converting the input file into binary form and ensuring that the message length in bits is a mulitple of 1024. First, the end of the binary equivalent message is appended with the bit "1", followed by the bit length of the original message. To ensure that the final message length is a multiple of 1024, the necessary number of "0" bits is padded between the initial "1" and the original message length at the end. 
* **Parsing the message**:
At this stage, the message, along with it's padding, is parsed into _N_ 1024 bit blocks denoted as M1, M2... MN. These message blocks are then subclassified further into sixteen 64-bit words denoted as M0(i), M1(i)... M15(i), where _i_ represents a 1024 bit message block.  
* **Setting the initial hash value**:
Next, the initial value of _H_ (an array of eight 64-bit words) must be set in hex. These eight words represent the "first sixty-four bits of the fractional parts of the square roots of the first eight prime numbers" [1], and after the computation in stage 2, will represent our final message digest.

**Stage 2: Hash Computation** 

### **Why is it important?**
Hashing algorithms such as SHA-512 serve many purposes. For example, passwords are often stored in a database as their hash values, meaning that if someone were to gain access to the database, it would be almost impossible to compute the original passwords. Additionaly, since a small change in input can have drastic changes in the respective hash ouput, tampering in files can easily be detected. [2] <br>
- Faster on 64 bit machines. 
- Early SHA algorithms were eventually deemed insecure. The same hasn't happened for SHA-256, but it's better to keep developing more secure algorithms rather than waiting for that to happen.  

***
### **Questions**
1. "_Why can't we reverse the SHA512 algorithm to retrieve the original message from a hash digest?_"<br>

1. "_Can you design an algorithm that, given enough time, will find input messages that give each of the possible 512-bit strings?_"
1. "_How difficult is it to find a hash digest beginning with at least twelve zeros?_"

***
### **Resources**
1. [U.S. Department of Commerce - Secure Hash Standard (SHS)](https://nvlpubs.nist.gov/nistpubs/FIPS/NIST.FIPS.180-4.pdf)
1. [Brilliant.org](https://brilliant.org/wiki/secure-hashing-algorithms/)
1. [Bitwise Operators](https://www.javatpoint.com/bitwise-operator-in-c)
