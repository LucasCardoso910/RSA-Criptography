#include "miller_rabin_by_cslarsen.hpp"
#include <cstring>
#include <cstdlib>
#include <vector>
#include <cmath>
#include <ctime>
#include <gmp.h>

const int TAM_STRING = 256;
const int GCD = 0;
const int X = 1;
const int Y = 2;

std::vector<std::string> euclidian_algorithm(mpz_t a, mpz_t b) {
    // This function can be found in pages 28-32 in the Coutinho's book.

    char return_value[TAM_STRING];
    char x_value[TAM_STRING];
    char y_value[TAM_STRING];
    std::vector<std::string> return_vector;

    mpz_t remainder1; mpz_init_set(remainder1, a); // remainder1 = a
    mpz_t remainder2; mpz_init_set(remainder2, b); // remainder2 = b 
    mpz_t x1; mpz_init_set_ui(x1, 1); // x1 = 1
    mpz_t y1; mpz_init_set_ui(y1, 0); // y1 = 0
    mpz_t x2; mpz_init_set_ui(x2, 0); // x2 = 0
    mpz_t y2; mpz_init_set_ui(y2, 1); // y2 = 1
    
    while (mpz_cmp_ui(remainder2, 0) > 0) {
        mpz_t quocient; mpz_init(quocient);
        mpz_t remainder; mpz_init(remainder);
        mpz_t x; mpz_init(x);
        mpz_t y; mpz_init(y);
        mpz_t q_t_x2; mpz_init(q_t_x2); // quocient times x2
        mpz_t q_t_y2; mpz_init(q_t_y2); // quocient times y2

        mpz_tdiv_q(quocient, remainder1, remainder2); // quocient = remainder1 / remainder2
        mpz_tdiv_r(remainder, remainder1, remainder2); // remainder = remainder1 % remainder2
        mpz_mul(q_t_x2, quocient, x2); // q_t_x2 = quocient % x2
        mpz_mul(q_t_y2, quocient, y2); // q_t_y2 = quocient % y2
        mpz_sub(x, x1, q_t_x2); // x = x1 - q_t_x2
        mpz_sub(y, y1, q_t_y2); // y = y1 - q_t_y2

        if (mpz_cmp_ui(remainder, 0) > 0) {
            mpz_set(x1, x2); // x1 = x2
            mpz_set(x2, x); // x2 = x
            mpz_set(y1, y2); // y1 = y2
            mpz_set(y2, y); // y2 = y
        }

        mpz_set(remainder1, remainder2); // remainder1 = remainder2
        mpz_set(remainder2, remainder);  // remainder2 = remainder
    }

    mpz_t a_t_x2; mpz_init(a_t_x2); // a times x2
    mpz_t b_t_y2; mpz_init(b_t_y2); // b times y2
    mpz_t sum; mpz_init(sum); // sum of a_t_x2 and b_t_y2

    mpz_mul(a_t_x2, a, x2); // a_t_x2 = a * y2
    mpz_mul(b_t_y2, b, y2); // b_t_y2 = b * y2
    mpz_add(sum, a_t_x2, b_t_y2); // sum = a_t_x2 + b_t_y2

    // Gets the return_value as a string
    mpz_get_str(return_value, 10, sum);
    std::string return_string(return_value);
    return_vector.push_back(return_string);

    // Gets the x_value as a string
    mpz_get_str(x_value, 10, x2);
    std::string x_string(x_value);
    return_vector.push_back(x_string);

    // Gets the y value as a string
    mpz_get_str(y_value, 10, y2);
    std::string y_string(y_value);
    return_vector.push_back(y_string);

    return return_vector;
}

std::string phi_n(std::string p_string, std::string q_string) {
    // The value of Euler's totient function, or the value of phi(n), that represents
    // all the numbers  up to n that are relatively primes with n
    // According to Coutinho's book, given a number n that is the result of the
    // multiplication of p and q, phi(n) can be calculated as (p - 1) * (q - 1).

    char return_char[TAM_STRING];
    mpz_t return_value; mpz_init(return_value);
    mpz_t p; mpz_init_set_str(p, p_string.c_str(), 10);
    mpz_t q; mpz_init_set_str(q, q_string.c_str(), 10);

    mpz_sub_ui(p, p, 1); // p = p - 1
    mpz_sub_ui(q, q, 1); // q = q - 1

    mpz_mul(return_value, p, q); // return_value = p * q
    mpz_get_str(return_char, 10, return_value);

    std::string return_string(return_char);
    return return_string;
}

std::vector<int> sieve_of_eratosthenes(int n) {
    // Implementation of the Sieve of Eratosthenes algorithm.

    std::vector<int> numbers;
    std::vector<int> primes;
    int max = floor(sqrt(n));
    int prime;
    int i = 0;

    // First, we fill the vector with all the numbers between 2 and n
    for (int i = 2; i < n; i++) {
        numbers.push_back(i);
    }
    prime = numbers[i]; // First number in the vector is 2 which is a prime

    while (prime <= max) {
        if (prime != 0) { // If the prime isn't currently a number that was a multiple
            for (int j = i + prime; j < n; j += prime) {
                numbers[j] = 0;
                // If the number is a multiple of a prime, it will turn into zero
            }
        }

        i++;
        prime = numbers[i];
    }

    for (int j = 0; j < n; j++) {
        // Creates a vector with all the numbers in the vector numbers that
        // are not zeroes.
        if (numbers[j] != 0) {
            primes.push_back(numbers[j]);
        }
    }

    return primes;
}

std::string generate_random_number(const int bits) {
    // Generate a random binary number with the given parameter bits

    std::string random_number = "1";
    // To guarantee that the number has all the digits with meaning, the first
    // digit must be a 1

    for (int i = 1; i < (bits - 1); i++) {
        // Problem: not real random number
        // TODO: See what it can be done in C++ to deal with it
        random_number += std::to_string(rand() % 2); 
        // Appends to the string a random number: 1 or 0
    }
    random_number += std::to_string(1);
    // To confirm that the number is an odd number, the last digit must be 1

    return random_number;
}

const std::vector<int> five_k_primes = sieve_of_eratosthenes(5000);
// Generates all the primes less than 5000

bool is_not_prime(mpz_t possible_prime) {
    // To make sure that a big number is a prime, it isn't effective to just check
    // all numbers less than the possible prime to see if the remainder is 0 or
    // not, so we will do just as it is said in Coutinho's book, using three
    // different methods to make sure that the number is a prime

    // First we will test the remainder in divisions by all the first five 
    // thousands primes, generated using the sieve of Eratosthenes.
    for (int i = 0; i < five_k_primes.size(); i++) {
        if (mpz_cmp_ui(possible_prime, five_k_primes[i]) > 0) {
            mpz_t remainder; mpz_init(remainder);
            mpz_tdiv_r_ui(remainder, possible_prime, five_k_primes[i]);

            if (mpz_cmp_ui(remainder, 0) == 0) {
                return true;
            }
        }
    }

    // Then we will use the Miller test. It is a probabilistic test, so it is not
    // 100% sure, but in combination with the other methods it is very effective.
    // The implementation of this algorithm was found on GitHub, by cslarsen and
    // added in this program just because it was not the focus of my learning
    mpz_class miller_possible_prime(possible_prime);
    if (!prob_prime(miller_possible_prime, 10)) {
        return true;
    }

    // TODO: Add the thirt method. All numbers generated so far are really primes
    // checking in the internet, but to make sure all the times will be, it is
    // interesting to add the last method.

    return false;
}

