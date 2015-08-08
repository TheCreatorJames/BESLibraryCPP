# BESLibraryCPP
After designing and implementing the [Basyl Encryption Library in C#](https://github.com/TheCreatorJames/BESLibrary), I ported the algorithm to C++. It is completely compatible with the [C# version](https://github.com/TheCreatorJames/BESLibrary) of the library. 


### What is the Basyl Encryption Standard?
It is a collection of encryption algorithms designed by Jesse Mitchell. These algorithms are different from many other widely used encryption algorithms like [AES](https://en.wikipedia.org/wiki/Advanced_Encryption_Standard) and [Triple DES](https://en.wikipedia.org/wiki/Triple_DES), which use [Fiestel networks](https://en.wikipedia.org/wiki/Feistel_cipher) to encrypt files. 

[Fiestel networks](https://en.wikipedia.org/wiki/Feistel_cipher) have restricted key sizes, and can not dynamically be redesigned. The Basyl Encryption Standard is designed to be mathematically comparable in strength to the [One-Time Pad](https://en.wikipedia.org/wiki/One-time_pad). Using a carefully designed and unpredictable PRNG, the Basyl Encryption standard uses key generators in various ways to encrypt your files.

Two main variants exist. 

##### Standard BES

This version of the algorithm [XORs](https://en.wikipedia.org/wiki/Exclusive_or) against the original file to encrypt. The proper usage of BES uses some sort of hash of the original file as a part of the seed for the original file. This guarantees no two files will ever get the same encryption scheme, even with the same password. An additional 8 bytes of salt are added for extra randomness, so even the same file will never be encrypted the same way twice.

Standard BES has a small known plaintext attack that will allow an attacker to modify bytes in the file. However, because of the hashing step, this is easily detected.

Standard BES has the advantage of being able to skip ahead in the file for decryption. (Semi-Random Access).

To Use: 

Create a Key Generator
```
BasylKeyGenerator keyGen("Jesse"); 
byte buf[1024]; //or a string works too
//You will need to export the seed data at some point before encrypting though, to recreate the key generator.
//Read below for how.
keyGen.Encrypt(buf, 1024); //string doesn't need the size parameter.
```

Since decryption is the same as encryption, just call the encrypt method again, after recreating the key generator. 

There are several ways to export key gen info.

Using the BasylWriter to Export
```
BasylWriter writer(stream, keyGen, true);
```


Exporting the Key Generator Seed Info Manually
```
//You determine how to export/save these
//To get the 32 byte hash,
keyGen.Hash(); 

//You can optionally encrypt the first "key" seed.
keyGen.GetEncryptedKey1Random();
//If you don't care, you could just use
keyGen.Key1Random();

//Second "key" seed.
keyGen.Key2Random();
```

How the BasylWriter does it
```
        for (int i = 0; i < keyGen->Hash().size(); i++)
        {
            (*output) << (byte) keyGen->Hash()[i];
        }

        for (int i = 0; i < keyGen->Key2Random().size(); i++)
            (*output) << (byte) keyGen->Key2Random()[i];

        BasylArray<byte>    enc = keyGen->EncryptedKey1Random();
        for (int i = 0; i < enc.size(); i++) (*output) << (byte) enc[i];
```



##### BES Cipher Mode

In order to prevent all kinds of attacks, including a known plaintext attack, BES Cipher Mode uses an internal shuffle cipher. This uses the key generator to shuffle around bytes in a cipher similar to the [Enigma](https://en.wikipedia.org/wiki/Enigma_machine) or shuffling a deck of cards continuously.

BES Cipher must be decrypted as a whole up to the point you are trying to access, so that is it's one disadvantage to standard BES.

You should export the key generator in one of the ways specified above.

Then you create a Cipher by using 
```
BESCipher c(keyGen);
c.EncryptRight(buf, 1024); // encrypts right
```

To Decrypt
```
BESCipher d(keyGen);
d.EncryptLeft(buf, 1024); // encrypts left
```
You could encrypt left first then right too, but to reverse, you need to perform the opposite operation.

### Features

1) Secure Encryption

2) No Keysize Limit

3) Easily and Dynamically Adjustable

### How to Use

Read about the modes above. They will provide descriptions for how to use the algorithm.

### Todo

The BasylPseudoAdaptor class has been successfully implemented, however, is not included in the utility file encryption class. This needs to be implemented. 


### Related Projects
