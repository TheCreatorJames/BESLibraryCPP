# BESLibraryCPP
After designing and implementing the [Basyl Encryption Library in C#](https://github.com/TheCreatorJames/BESLibrary), I ported the algorithm to C++. It is completely compatible with the [C# version](https://github.com/TheCreatorJames/BESLibrary) of the library. 


### What is the Basyl Encryption Standard?
It is a collection of encryption algorithms designed by Jesse Mitchell. These algorithms are different from many other widely used encryption algorithms like AES and Triple DES, which use Fiestel networks to encrypt files. 

Fiestel Networks have restricted key sizes, and can not dynamically be redesigned. The Basyl Encryption Standard is designed to be mathematically comparable in strength to the One-Time Pad. Using a carefully designed and unpredictable PRNG, the Basyl Encryption standard uses key generators in various ways to encrypt your files.

Two main variants exist. 

##### Standard BES

This version of the algorithm XORs against the original file to encrypt. The proper usage of BES uses some sort of hash of the original file as a part of the seed for the original file. This guarantees no two files will ever get the same encryption scheme, even with the same password. An additional 8 bytes of salt are added for extra randomness, so even the same file will never be encrypted the same way twice.

Standard BES has a small known plaintext attack that will allow an attacker to modify bytes in the file. However, because of the hashing step, this is easily detected.

Standard BES has the advantage of being able to skip ahead in the file for decryption. (Semi-Random Access).

##### BES Cipher Mode

In order to prevent all kinds of attacks, including a known plaintext attack, BES Cipher Mode uses an internal shuffle cipher. This uses the key generator to shuffle around bytes in a cipher similar to the Enigma (but of course, way stronger than the Enigma).

BES Cipher must be decrypted as a whole up to the point you are trying to access, so that is it's one disadvantage to standard BES.
### Features

1) Secure Encryption

2) No Keysize Limit

3) Easily and Dynamically Adjustable

### How to Use


### Todo

The BasylPseudoAdaptor class has been successfully implemented, however, is not included in the utility file encryption class. This needs to be implemented. 
