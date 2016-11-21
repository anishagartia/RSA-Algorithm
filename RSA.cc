// ECE4122/6122 RSA Encryption/Decryption assignment
// Fall Semester 2015

#include <iostream>
#include "RSA_Algorithm.h"

using namespace std;

int main()
{
  // Instantiate the one and only RSA_Algorithm object
  RSA_Algorithm RSA;
  
  // Loop from sz = 32 to 1024 inclusive
  // for each size choose 100 different key pairs
  // For each key pair choose 100 differnt plaintext 
  // messages making sure it is smaller than n.
  // If not smaller then n then choose another
  // For eacm message encrypt it using the public key (n,e).
  // After encryption, decrypt the ciphertext using the private
  // key (n,d) and verify it matches the original message.

  // your code here
  size_t max_sz = 1024;
  size_t sz = 32;
  int reps = 100;
  while(sz <= max_sz){
    // 100 keppairs per size
    for (int i=0; i<reps; i++){
      RSA.GenerateRandomKeyPair(sz);
      RSA.PrintNDE();
      // 100 messages per keypair
      for (int j=0; j<reps; j++){
        bool msg_lessn = false;
        mpz_class msg;
        while(msg_lessn == false){
          msg = RSA.rng.get_z_bits(sz);
          if (msg < RSA.n){
            msg_lessn = true;
          }
        }
        mpz_class crypted_msg = RSA.Encrypt(msg);
        mpz_class decrypt_msg = RSA.Decrypt(crypted_msg);      
        RSA.PrintM(msg);
        RSA.PrintC(crypted_msg);
   //     RSA.PrintM(decrypt_msg);
       
        // Break
        

      }
    }
  sz = sz*2;
  }

   
}
  
