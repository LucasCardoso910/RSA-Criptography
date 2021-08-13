#include "rsa_criptography.hpp"

int main() {
    std::vector<std::string> primes = find_two_large_primes();
    std::vector<std::string> crypt;
    std::string phi;
    std::string n;
    std::string e;
    std::string d;
    std::string msg;

    std::cout << "primes: " << primes[0] << " and " << primes[1] << std::endl;
    n = get_n(primes[0], primes[1]);
    std::cout << "n: " << n << std::endl;
    phi = phi_n(primes[0], primes[1]);
    std::cout << "phi: " << phi << std::endl;
    e = find_e(primes[0], primes[1]);
    std::cout << "e: " << e << std::endl;
    d = find_d(phi, e);
    std::cout << "d: " << d << std::endl;
    msg = get_message();
    std::cout << msg << std::endl;

    crypt = pre_encoding(msg, n); // Generates the string as numbers
    print_vector_string(crypt);
    crypt = codify(crypt, e, n); // Applies the criptography algorithm
    print_vector_string(crypt);
    crypt = decodify(crypt, d, n); // Decodifies the message
    print_vector_string(crypt);
    msg = pos_decoding(crypt); // Generates the original message again
    std::cout << msg << std::endl;

    return 0;
}