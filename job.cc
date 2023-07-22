// Buid instructions, motivation, ...:
// https://github.com/Hermann-SW/9383761-digit-prime#readme
//
// (cpplinted and cppchecked)
//
#include <gmpxx.h>
#include <fstream>
#include <cassert>

    // https://t5k.org/primes/lists/all.txt
    // rank  description                      digits  who   year
#if !defined(TEST)
    //    9  10223*2^31172165+1               9383761 SB12  2016
    //               31172163 == 3 * 11 * 337 * 2803
    const int loops = 3*11*337;
    const int sqspl = 2803;
    const int fact  = 10223;
    const int expo  = 31172165;
#else
    // 5065  1705*2^906110+1                   272770 L3174 2012
    //              906108 == 2^2 * 3 * 7^2 * 23 * 67
    const int loops = 2*7*23;
    const int sqspl = 2*3*7*67;
    const int fact  = 1705;
    const int expo  = 906110;
#endif


void job(mpz_class& t, int j) {
    char *buf = new char[10000000];

    assert(buf);
    std::ifstream f(std::to_string(j) + ".job");
    f >> buf;
    assert(!f.eof());            // assert full number read via terminating "\n"
    f.close();
    t = mpz_class(buf);

    delete buf;
}

void create_birth(std::ofstream& f, int i) {
    f.open(std::to_string(i) + ".job");
    f.flush();                   // trigger stat Birth
}

void write_close(std::ofstream& f, mpz_class& v) {
    f << v << "\n";              // "\n" allows for full number read assertion
    f.close();                   // calls "flush()", triggers stat Modify
}


int main(int argc, char *argv[]) {
    mpz_class a, b, c, p;
    std::ofstream f;

    assert(argc == 2);

    mpz_ui_pow_ui(p.get_mpz_t(), 2, expo);
    p *= mpz_class(fact);
    p += 1;

    int j = atoi(argv[1]);
    job(b, j);

    mpz_ui_pow_ui(c.get_mpz_t(), 2, sqspl);


    for (; j < loops; ++j) {
        create_birth(f, j+1);
        mpz_powm(a.get_mpz_t(), b.get_mpz_t(), c.get_mpz_t(), p.get_mpz_t());
        write_close(f, a);
        b = a;
    }


    create_birth(f, loops + 1);

    c = mpz_class(fact);
    mpz_powm(a.get_mpz_t(), b.get_mpz_t(), c.get_mpz_t(), p.get_mpz_t());

    assert(a * a % p == p - 1);

    write_close(f, a);           // only after "sqrt(-1) (mod p)" asserted


    return 0;
}
