#include <math.h>                       // sqrt,pow
#include "ops.h"                        // struct factor_s

#define max(x, y) (x) > (y) ? (x) : (y)
#define min(x, y) (x) > (y) ? (x) : (y)

void gcd_factors(const factor_t factors1[], int n1,
                 const factor_t factors2[], int n2,
                 factor_t factors[], int &n);
void lcm_factors(const factor_t factors1[], int n1,
                 const factor_t factors2[], int n2,
                 factor_t factors[], int &n);

int gcd(int number1, int number2)
{
    factor_t factors1[MAXFACTOR], factors2[MAXFACTOR], factors3[MAXFACTOR];
    int n1, n2, n3;
    long int result = 1L;
    int i;

    factorize(number1, factors1, n1);
    factorize(number2, factors2, n2);
    gcd_factors(factors1, n1, factors2, n2, factors3, n3);
    for (i = 0; i < n3; i++)
        result *= (long int) pow(factors3[i].base, factors3[i].power);
    return result;
}

int lcm(int number1, int number2)
{
    factor_t factors1[MAXFACTOR], factors2[MAXFACTOR], factors3[MAXFACTOR];
    int n1, n2, n3;
    long int result = 1L;
    int i;

    factorize(number1, factors1, n1);
    factorize(number2, factors2, n2);
    lcm_factors(factors1, n1, factors2, n2, factors3, n3);
    for (i = 0; i < n3; i++)
        result *= (long int) pow(factors3[i].base, factors3[i].power);
    return result;
}

bool is_prime(int cand)
{
    int count;

    if (cand == 2)
        return true;
    if (cand % 2 == 0)
        return false;
    for (count = 3; count <= sqrt(cand); count += 2) {
        if (cand % count == 0)
            return false;
    }
    return true;
}

int next_prime(int prime)
{
    int cand = (prime % 2 == 0) ? prime + 1 : prime + 2;

    while (!is_prime(cand))
        cand += 2;
    return cand;
}

void factorize(int x, factor_t factors[], int &n)
{
    int factor = 2;

    n = 0;
    while (x > 1) {
        if (x % factor == 0) {
            factors[n].base = factor;
            factors[n].power = 0;
            while (x % factor == 0) {
                factors[n].power++;
                x /= factor;
            }
            n++;
        }
        factor = next_prime(factor);
    }
}

void gcd_factors(const factor_t factors1[], int n1,
                 const factor_t factors2[], int n2,
                 factor_t factors[], int &n)
{
    int i1 = 0, i2 = 0;

    n = 0;
    while ((i1 < n1) && (i2 < n2)) {
        if (factors1[i1].base < factors2[i2].base)
            i1++;
        else if (factors1[i1].base > factors2[i2].base)
            i2++;
        else {
            factors[n].base = factors1[i1].base;
            factors[n].power = min(factors1[i1].power, factors2[i2].power);
            i1++;
            i2++;
            n++;
        }
    }
}

void lcm_factors(const factor_t factors1[], int n1,
                 const factor_t factors2[], int n2,
                 factor_t factors[], int &n)
{
    int i1 = 0, i2 = 0, i;

    n = 0;
    while ((i1 < n1) && (i2 < n2)) {
        if (factors1[i1].base < factors2[i2].base) {
            factors[n] = factors1[i1];
            i1++;
        } else if (factors1[i1].base > factors2[i2].base) {
            factors[n] = factors2[i2];
            i2++;
        } else {
            factors[n].base = factors1[i1].base;
            factors[n].power = max(factors1[i1].power, factors2[i2].power);
            i1++;
            i2++;
        }
        n++;
    }
    if (i1 == n1) {
        for (i = i2; i < n2; i++, n++)
            factors[n] = factors2[i];
    } else {
        for (i = i1; i < n1; i++, n++)
            factors[n] = factors1[i];
    }
}
