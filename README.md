# RSA Criptography
This is an implementation of the RSA algorithm. It is an 
amateur implementation, so there maybe some errors.

This project originated as the final work for the discipline 
of Discretes Mathematics in the University of São Paulo and, 
so, it is based on the description given by the UFRJ's 
professor S. C. Coutinho in his book "Números Inteiros e 
Criptografia RSA" (In a free translation, "Integers Numbers 
and RSA Criptography").

I have chosen to write this program in C++ because I wanted to 
learn how to deal with big integers in this language and for 
its speed.

## How it works?
Well, the book by professor Coutinho is dedicated to explain 
how the RSA Criptography works, but I will try to describe it
here briefly.

The RSA critography is a process of public key criptography, it
means that the key to criptograph a message is known by anyone
who wants it and to decrypt the message is still impossible. 
The public key pair is composed by n, a large number that is 
the result of the multiplication of two large primes p and q, 
and e, that is a prime relatively to phi(n), that is the 
numbers up to n that are primes relatively to n.

It is also composed by the private key. It is formed by d, the
multiplicative inverse of e, calculated by the euclidian 
algorithm, and n. 

## Why it works?
The safety in the RSA Criptography is based on the process of 
fatoration of a number, since to calculate both e and n it is 
need to know phi(n), that by its own is only fast calculated 
knowing the two primes p and q. Any process that could break 
the security of the RSA criptography is, in a way, a process 
to discover the factors of n.

## Farewell and good luck!