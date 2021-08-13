#include "number_theory.hpp"
#include <iostream>
#include <string>

std::vector<std::string> find_two_large_primes() {
    // Generates a vector with two random large primes

    std::vector<std::string> primes;

    srand((unsigned) time(0)); // Sets the seed of the random numbers generator
    for (int i = 0; i < 2; i++) {
        mpz_t possible_prime; 
        char prime_char[TAM_STRING];

        mpz_init_set_str(possible_prime, generate_random_number(256).c_str(), 2);
        // Sets the possible_prime variable as a random number of 256 bits
        while (is_not_prime(possible_prime)) {
            // Jumps to the next odd number until it is, in fact, a prime number
            mpz_add_ui(possible_prime, possible_prime, 2);
        }

        // Gets the prime as a string
        mpz_get_str(prime_char, 10, possible_prime);
        std::string prime_string(prime_char);
        primes.push_back(prime_string);
    }

    return primes;
}

std::string get_n(std::string p_string, std::string q_string) {
    // Gets the number n, that is the result of p * q

    mpz_t p; mpz_init_set_str(p, p_string.c_str(), 10);
    mpz_t q; mpz_init_set_str(q, q_string.c_str(), 10);
    mpz_t n; mpz_init(n);
    char n_char_string[TAM_STRING];

    mpz_mul(n, p, q); // n = p * q
    
    // Gets the value of n as a string
    mpz_get_str(n_char_string, 10, n); 
    std::string n_string(n_char_string);
    return n_string;
}

std::string lower_string (std::string message) {
    // Gets a string and returns it in all lowercase

    for (int i = 0; i < message.length(); i++) {
        message[i] = tolower(message[i]);
    }

    return message;
}

std::string get_message() {
    // Gets a message to encript
    char message[5000];

    std::cout << "\n";
    std::cout << "Type a message to encrypt!" << std::endl;
    std::cin.getline(message, sizeof(message));
    std::cout << "\n";

    return lower_string(message);
}

std::vector<std::string> separate(std::string translated_msg, std::string n_string) {
    // Gets the message translated to numbers and the number n, result of a 
    // multiplication of two primes, and separates the message in blocks of
    // numbers that are lesser than the number n.
    // This process unrelates the blocks of letters into structures that have
    // no relation to actual linguistic structures, thus not allowing the use 
    // of the method of counting letter frequency, as described by Al-Kindi.

    std::vector<std::string> pre_encoded_msg;
    mpz_t n; mpz_init_set_str(n, n_string.c_str(), 10);

    for (int i = 0; i < translated_msg.length(); i++) {
        std::string next_number(1, translated_msg[i]);
        // Creates a string with the next letter in the message

        mpz_t possible_number; mpz_init(possible_number);
        mpz_set_str(possible_number, (next_number + translated_msg[i + 1]).c_str(), 10); 
        // possible_number = next_number + translated_msg[i + 1]

        while (
            mpz_cmp(possible_number, n) < 0 // std::stoi(nex_number + translate_msg[i + 1]) < n
            // If the string formed with the current string and the next letter
            // is a number less than n
            and i < (translated_msg.length() - 1)
            // and if i is pointing until the penultimate letter
            // Why? Since the code in this loop will increment i and check
            // for the next letter, it causes a problem if the loop is 
            // already in the last letter because it will check a letter that
            // doesn't exist.
        ) {
            next_number += translated_msg[++i];
            mpz_set_str(possible_number, (next_number + translated_msg[i + 1]).c_str(), 10); 
            // possible_number = next_number + translated_msg[i + 1]
        }

        if (translated_msg[i + 1] == '0') {
            // If the next block would start with a 0, it will start with the
            // last number in this block
            next_number.pop_back();
            i--;
        }

        pre_encoded_msg.push_back(next_number);
    }

    return pre_encoded_msg;
}

std::vector<std::string> pre_encoding(std::string message, std::string n_string) {
    // Converts all letters in a message that are alphabetical or a blank space
    // to a number composed by two digits and breaks the giant number formed 
    // into several different blocks

    std::string translated_msg;

    for (int i = 0; i < message.length(); i++) {
        if (isalpha(message[i])) {
            std::string converted_letter = std::to_string((int) message[i] - 87);
            translated_msg += converted_letter;
        }
        else if (message[i] == ' ') {
            // In this convertion, the blank space is a 99
            translated_msg += "99";
        }
    }

    return separate(translated_msg, n_string);
}

std::string find_e(std::string p_string, std::string q_string) {
    // Generates the variable e, based on the best answer in this link
    // https://crypto.stackexchange.com/questions/13166/method-to-calculating-e-in-rsa
    // Basically, it will return the first prime bigger than the bigger prime
    // used to generate n. e is one of the public keys of the RSA criptography

    mpz_t p; mpz_init_set_str(p, p_string.c_str(), 10);
    mpz_t q; mpz_init_set_str(q, q_string.c_str(), 10);
    mpz_t e; mpz_init(e);
    char e_char[TAM_STRING];

    // Sets e as the biggest value between p and q
    if (mpz_cmp(p, q) > 0) {
        mpz_set(e, p); // e = p
    }
    else {
        mpz_set(e, q); // e = q
    }
    mpz_add_ui(e, e, 2); // e += 2

    // Search for the first prime bigger than the value in e
    while (is_not_prime(e)) {
       mpz_add_ui(e, e, 2); // e += 2
    }

    // Returns the value in e as a string
    mpz_get_str(e_char, 10, e);
    std::string e_string(e_char);
    return e_string;
}

std::string find_d(std::string phi_string, std::string e_string) {
    // Find the value of the private key d.
    // It is calculated using the euclidian algorithm between e and phi(n)

    char return_char[TAM_STRING];
    std::vector<std::string> euclidian_return;
    mpz_t e; mpz_init_set_str(e, e_string.c_str(), 10);
    mpz_t phi; mpz_init_set_str(phi, phi_string.c_str(), 10);
    mpz_t d; mpz_init(d);

    euclidian_return = euclidian_algorithm(e, phi);
    mpz_set_str(d, euclidian_return[X].c_str(), 10);

    if (mpz_cmp_ui(d, 0) < 0) {
        mpz_add(d, d, phi); // d = d + phi
    }

    // Gets the value of d as a string
    mpz_get_str(return_char, 10, d);
    std::string return_string(return_char);

    return return_string;
}

std::vector<std::string> codify(std::vector<std::string> pre_encoded_msg, std::string e_string, std::string n_string) {
    // Given the blocks of the original message and the pair of public keys, it
    // returns the criptographed blocks 

    std::vector<std::string> encrypted_msg;
    mpz_t e; mpz_init_set_str(e, e_string.c_str(), 10);
    mpz_t n; mpz_init_set_str(n, n_string.c_str(), 10);

    for (int i = 0; i < pre_encoded_msg.size(); i++) {
        char block_char[TAM_STRING];
        mpz_t block; mpz_init(block);
        
        mpz_set_str(block, pre_encoded_msg[i].c_str(), 10); // block = pre_encoded_msg
        mpz_powm(block, block, e, n); // block = (block ^ e) (mod n)
        
        // Appends to the final vector the value of the criptographed block as a string
        mpz_get_str(block_char, 10, block);
        std::string block_string(block_char);
        encrypted_msg.push_back(block_string);
    }

    return encrypted_msg;
}

std::vector<std::string> decodify(std::vector<std::string> coded_msg, std::string d_string, std::string n_string) {
    // Given the blocks of the criptographed message and the pair of private keys,
    // it returns the original blocks.

    std::vector<std::string> decrypted_msg;
    mpz_t d; mpz_init_set_str(d, d_string.c_str(), 10);
    mpz_t n; mpz_init_set_str(n, n_string.c_str(), 10);

    for (int i = 0; i < coded_msg.size(); i++) {
        int block_as_int;
        mpz_t block; mpz_init(block);
        char block_as_char_string[TAM_STRING];

        mpz_set_str(block, coded_msg[i].c_str(), 10); // block = coded_msg[i]
        mpz_powm(block, block, d, n); // block = (block ^ d) (mod n)
        mpz_get_str(block_as_char_string, 10, block);
        
        std::string block_as_string(block_as_char_string);
        decrypted_msg.push_back(block_as_string);
    }

    return decrypted_msg;
}

std::string pos_decoding(std::vector<std::string> decoded_msg_vector) {
    // Gets the giant number string decoded by the algorithm and generates again
    // a string formed with actual letters

    std::string decoded_msg;
    std::string text_msg;

    // Gets all the digits in the blocks as a single string
    decoded_msg = decoded_msg_vector[0];
    for (int i = 1; i < decoded_msg_vector.size(); i++) {
        decoded_msg += decoded_msg_vector[i];
    }

    for (int i = 0; i < decoded_msg.size(); i += 2) {
        std::string number_string;
        int number;

        // Separates the string in groups of two
        number_string.push_back(decoded_msg[i]);
        number_string.push_back(decoded_msg[i + 1]);
        number = std::stoi(number_string);

        if (number == 99) {
            text_msg.push_back(' '); // Appends the ASCII code of the blank space
        }
        else {
            text_msg.push_back(number + 87); // Appends the ASCII code of the letter
        }
    }

    return text_msg;
}

void print_vector_string(std::vector<std::string> a_vector) {
    // Prints all the strings in a vector with a blank space between them

    for (int i = 0; i < a_vector.size(); i++) {
        std::cout << a_vector[i] << " ";
    }
    std::cout << std::endl;
}