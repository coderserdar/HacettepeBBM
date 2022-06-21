#ifndef OPS_H
#define OPS_H

#define MAXFACTOR 50

struct factor_s {
    int base, power;
};
typedef struct factor_s factor_t;

void factorize(int x, factor_t factors[], int &n);
int gcd(int number1, int number2);
int lcm(int number1, int number2);

#endif
