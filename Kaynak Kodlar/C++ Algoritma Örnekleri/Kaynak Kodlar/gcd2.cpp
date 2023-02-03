#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS
#include <math.h>               // pow

#define min(x, y) (x) < (y) ? (x) : (y)

using namespace std;

struct factor_s {
    int base, power;
    struct factor_s *next;
};
typedef struct factor_s factor_t;

factor_t *factorize(int x);
factor_t *gcd_factors(factor_t *factors1, factor_t *factors2);
void delete_factors(factor_t *head);

int main(void)
{
    int number1, number2;
    factor_t *factors1 = NULL, *factors2 = NULL, *factors3 = NULL;
    long int gcd = 1L;
    factor_t *f = NULL;

    cout << "Sayýlarý yazýnýz: ";
    cin >> number1 >> number2;
    factors1 = factorize(number1);
    factors2 = factorize(number2);
    factors3 = gcd_factors(factors1, factors2);
    for (f = factors3; f != NULL; f = f->next)
        gcd = gcd * (long int) pow((double) f->base,
                                   (double) f->power);
    delete_factors(factors1);
    delete_factors(factors2);
    delete_factors(factors3);
    cout << "En büyük ortak bölen: " << gcd << endl;
    return EXIT_SUCCESS;
}

bool is_prime(int cand)
{
    int count;

    if (cand == 2)
        return true;
    if (cand % 2 == 0)
        return false;
    for (count = 3; count * count <= cand; count += 2) {
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

factor_t *factorize(int x)
{
    factor_t *head = NULL, *tail = NULL, *f = NULL;
    int factor = 2;

    while (x > 1) {
        if (x % factor == 0) {
            f = new factor_t;
            f->base = factor;
            f->power = 0;
            while (x % factor == 0) {
                f->power++;
                x = x / factor;
            }
            f->next = NULL;
            if (head == NULL)
                head = f;
            if (tail != NULL)
                tail->next = f;
            tail = f;
        }
        factor = next_prime(factor);
    }
    return head;
}

factor_t *gcd_factors(factor_t *factors1, factor_t *factors2)
{
    factor_t *factors = NULL, *head = NULL, *tail = NULL;

    while ((factors1 != NULL) && (factors2 != NULL)) {
        if (factors1->base < factors2->base)
            factors1 = factors1->next;
        else if (factors1->base > factors2->base)
            factors2 = factors2->next;
        else {
            factors = new factor_t;
            factors->base = factors1->base;
            factors->power = min(factors1->power, factors2->power);
            factors->next = NULL;
            if (head == NULL)
                head = factors;
            if (tail != NULL)
                tail->next = factors;
            tail = factors;
            factors1 = factors1->next;
            factors2 = factors2->next;
        }
    }
    return head;
}

void delete_factors(factor_t *head)
{
    factor_t *p = NULL;

    while (head != NULL) {
        p = head->next;
        delete head;
        head = p;
    }
}
