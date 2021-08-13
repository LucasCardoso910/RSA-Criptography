#include <iostream>
#include <gmp.h>

int main() {
    mpz_t a; // This is the type defined for GMP for integers
    mpz_t b; // It is a pointer to the internals of the GMP integer data structures
    mpz_t result1;
    mpz_t result2;
    mpz_t result3;

    // To initialize the number
    mpz_init(a);
    mpz_init(b);
    mpz_init(result1);
    mpz_init(result2);
    mpz_init(result3);

    // Setting its values with strings as a base 10 number
    mpz_set_str(a, "314159265358979323846264338327950288", 10);
    mpz_set_str(b, "1000000000000000", 10);
    
    // To print a number
    std::cout << "a = ";
    mpz_out_str(stdout, 10, a);
    std::cout << "\n";

    std::cout << "b = ";
    mpz_out_str(stdout, 10, b);
    std::cout << "\n";

    // Comparisons
    int relation;

    relation = mpz_cmp(a, b); // Comparison between two mpz ints
    std::cout << "The comparison between a and b returned " << relation << "\n";
    relation = mpz_cmp_d(a, 3.14159265); // Comparison between a mpz int and a double
    std::cout << "The comparison between a and pi returned " << relation << "\n";
    relation = mpz_cmp_si(b, -1000000000000001); // Comparison between a mpz int and a signed long
    std::cout << "The comparison between b and -(b + 1) returned " << relation << "\n";
    relation = mpz_cmp_ui(b, 1000000000000001); // Comparison between a mpz int and a unsigned long
    std::cout << "The comparisson between b and (b + 1) returned " << relation << "\n";

    // Comparisons returns:
    // a negative number if the first number is less than the second
    // zero if the first number is equal to the second
    // a positive number if the first number is bigger than the second

    // Addition
    mpz_add_ui(result1, b, 1); // result1 = b + 1
    mpz_add(result2, a, b); // result2 = a + b

    std::cout << "b + 1 = "; // Showing result 1
    mpz_out_str(stdout, 10, result1);
    std::cout << "\n";

    std::cout << "a + b = "; // Showing result 2
    mpz_out_str(stdout, 10, result2);
    std::cout << "\n";

    // Subtraction
    mpz_sub_ui(result1, b, 1); // result1 = b - 1
    mpz_sub(result2, a, b); // result2 = a - b
    mpz_sub(result3, b, a); // result3 = b - a

    std::cout << "b - 1 = "; // Showing result 1
    mpz_out_str(stdout, 10, result1);
    std::cout << "\n";

    std::cout << "a - b = "; // Showing result 2
    mpz_out_str(stdout, 10, result2);
    std::cout << "\n";

    std::cout << "b - a = "; // Showing result 3
    mpz_out_str(stdout, 10, result3);
    std::cout << "\n";

    // Multiplication
    mpz_mul_ui(result1, a, 2); // result1 = a * 2
    mpz_mul(result2, a, b); // result2 = a * b

    std::cout << "b * 2 = "; // Showing result 1
    mpz_out_str(stdout, 10, result1);
    std::cout << "\n";

    std::cout << "a * b = "; // Showing result 2
    mpz_out_str(stdout, 10, result2);
    std::cout << "\n";

    // Division
    // n / d = q
    // n % d = r
    // n = (q * d) + r

    // Division quocient
    // Quocient divisions (represented by the letter q) can be of three types:
    // c: the result is rounded up towards +infinity (c is from ceil)
    // f: the result is rounded down towards -infinity (f is from floor)
    // t: the result is rounded towards zero (t is from truncate)
    mpz_tdiv_q_ui(result1, a, 2); // result1 = a / 2
    mpz_tdiv_q(result2, a, b); // result2 = a / b
    mpz_tdiv_q(result3, b, a); // result3 = b / a

    std::cout << "a / 2 = "; // Showing result 1
    mpz_out_str(stdout, 10, result1);
    std::cout << "\n";

    std::cout << "a / b = "; // Showing result 2
    mpz_out_str(stdout, 10, result2);
    std::cout << "\n";

    std::cout << "b / a = "; // Showing result 3
    mpz_out_str(stdout, 10, result3);
    std::cout << "\n";

    // Division remainder
    // Remainder divisions (represented by the letter r) can be of three types:
    // c: r will have the opposite sign to d
    // f: r will have the same sign as d
    // t: r will have the same sign as n
    mpz_tdiv_r_ui(result1, a, 2); // result1 = a % 2
    mpz_tdiv_r(result2, a, b); // result2 = a % b
    mpz_tdiv_r(result3, b, a); // result3 = b % a 

    std::cout << "a % 2 = "; // Showing result 1
    mpz_out_str(stdout, 10, result1);
    std::cout << "\n";

    std::cout << "a % b = "; // Showing result 2
    mpz_out_str(stdout, 10, result2);
    std::cout << "\n";

    std::cout << "b % a = "; // Showing result 3
    mpz_out_str(stdout, 10, result3);
    std::cout << "\n";

    // Square
    mpz_mul(result1, a, a); // result1 = a * a
    mpz_mul(result2, b, b); // result2 = b * b

    std::cout << "a * a = "; // Showing result 1
    mpz_out_str(stdout, 10, result1);
    std::cout << "\n";

    std::cout << "b * b = "; // Showing result 2
    mpz_out_str(stdout, 10, result2);
    std::cout << "\n";

    // Clearing the use of memory
    mpz_clear(a);
    mpz_clear(b);
    mpz_clear(result1);
    mpz_clear(result2);
    mpz_clear(result3);
}