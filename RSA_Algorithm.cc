// RSA Assignment for ECE4122/6122 Fall 2015

#include <iostream>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#include "RSA_Algorithm.h"

using namespace std;

// Implement the RSA_Algorithm methods here

// Constructor
RSA_Algorithm::RSA_Algorithm()
  : rng(gmp_randinit_default)
{
  // get a random seed for the random number generator
  int dr = open("/dev/random", O_RDONLY);
  if (dr < 0)
    {
      cout << "Can't open /dev/random, exiting" << endl;
      exit(0);
    }
  unsigned long drValue;
  read(dr, (char*)&drValue, sizeof(drValue));
  //cout << "drValue " << drValue << endl;
  rng.seed(drValue);
// No need to init n, d, or e.
}

// Fill in the remainder of the RSA_Algorithm methods
void RSA_Algorithm::GenerateRandomKeyPair(size_t sz){
  mpz_class p, q;
  int reps = 100;
  bool prime_true = false;
  while(prime_true == false){
    p = rng.get_z_bits(sz); 
    int probab_prime_res_p = mpz_probab_prime_p(p.get_mpz_t(),reps);
    if (probab_prime_res_p != 0){
      prime_true = true;
    }
  }
  prime_true = false;
  while(prime_true == false){
    q = rng.get_z_bits(sz); 
    int probab_prime_res_q = mpz_probab_prime_p(q.get_mpz_t(),reps);
    if (probab_prime_res_q != 0){
      prime_true = true;
    }
  }
  
  n = p*q;
  mpz_class phi = (p-1)*(q-1);
  bool d_less = false;
  bool gcd_1 = false;
  int inv_exist = 0;
  while((d_less == false) || (gcd_1 == false) || (inv_exist == 0)){  
    d = rng.get_z_bits(sz*2);
    if(d < phi){
      d_less = true;
    }
    mpz_class d_phi_gcd;
    mpz_gcd(d_phi_gcd.get_mpz_t(), d.get_mpz_t(), phi.get_mpz_t());
    if (d_phi_gcd == 1){
      gcd_1 = true;
    } 
    inv_exist =  mpz_invert(e.get_mpz_t(), d.get_mpz_t(), phi.get_mpz_t());           
  }
//  cout << "inv_exist " << inv_exist << endl;
//  cout << "p " << p << endl;
//  cout << "q " << q << endl;
//  cout << "phi " << phi << endl;
}


mpz_class RSA_Algorithm::Encrypt(mpz_class M){
 
  mpz_class C;
  mpz_powm( C.get_mpz_t(), M.get_mpz_t(), e.get_mpz_t(), n.get_mpz_t());
  return C;
}

mpz_class RSA_Algorithm::Decrypt(mpz_class C){

  mpz_class M;
  mpz_powm(M.get_mpz_t(), C.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());
  return M;
}


void RSA_Algorithm::PrintND()
{ // Do not change this, right format for the grading script
  cout << "n " << n << " d " << d << endl;
}

void RSA_Algorithm::PrintNE()
{ // Do not change this, right format for the grading script
  cout << "n " << n << " e " << e << endl;
}

void RSA_Algorithm::PrintNDE()
{ // Do not change this, right format for the grading script
  cout << "n " << n << " d " << d << " e " << e << endl;
}

void RSA_Algorithm::PrintM(mpz_class M)
{ // Do not change this, right format for the grading script
  cout << "M " << M << endl;
}

void RSA_Algorithm::PrintC(mpz_class C)
{ // Do not change this, right format for the grading script
  cout << "C " << C << endl;
}




