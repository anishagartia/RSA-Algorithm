# RSA-Algorithm

In this project we will use the GNU multi-precision arithmetic library to implement the well- known public-key encryption algorithm known as Rivest-Shamir-Adelman (RSA). Our program will choose appropriate public/private key pairs, choose random messages, encrypt the random message with the public key, decrypt the random messagse with the private key, and verify that the decrypted message matches the original messages.

## Choosing the RSA public/private key pair. 
To select the public key (n, d) and private key (n, e), we do the following.

1. Create a variable of type gmp randclass to generate randomd numbers.
2. Select two random prime numbers p and q of size sz bits. (Note we will vary sz as described below). The gmp randclass object has a method called get z bits which returns a random value of the specified size. The GNU multi-precision library has a function mpz probab prime p to determine if a given number is “likely” to be prime. For this assignment, use 100 iterations of the primality testing algorithm (the second parameter on the mpz probab prime p function).
3. Compute n = p∗q.
4. Compute φ(n)=(p−1)∗(q−1)
5. Choose a random d of sizes z*2 and with d<φ(n). Note that d does not have to be prime.
6. Insure that the greatest common divisor of d and φ(n) is exactly 1. If not, choose another d. The GMP library has a function mpz gcd to compute the greatest common divisor.
7. Finally, compute e as the multiplicative inverse of d modulo φ(n). Use the GMP function mpz invert for this.

At this point the pair (n, e) is the public key, and (n, d) is the private key (although this is arbitrary, we could use (n, e) as the private key and (n, d) as the public).

Performing the Encryption and Decryption. Given a key (either public or private) (n, d), and a plaintext message m, the RSA encryption algorithm is simple. Just compute the ciphertext message c as c = m^d (mod n). The GMP function mpz powm does this for us.

## Specific program details.

1. We start with sz as 32 bits, and double the size for each iteration up to and including 1024 bits. Recall that sz is the size of p and q, and n is p ∗ q, so n has twice as many bits.
2. For each value of sz, compute 100 different public/private key pairs as described above.
3. For each public/private key pair compute 100 random messages of size less than n bits. Again, you can use the get z bits function of the GMP random nubmer generator to do this.
4. For each random message, compute the ciphertext (using the RSA algorithm), and then decrypt the ciphertext message (again using the RSA algorithm) and verify the decrypted message is identical to the original plaintext message.
