#include <iostream>             // cin,cout,endl
#include <stdlib.h>             // EXIT_SUCCESS,srand,rand
#include <time.h>               // time

using namespace std;

enum status_e { GAME_CONTINUES, PLAYER_WINS, PLAYER_LOSES };
typedef enum status_e status_t;

int main(void)
{
    int die1, die2, sum, point;
    status_t game_status = GAME_CONTINUES;

    srand(time(NULL));
    die1 = 1 + rand() % 6;
    die2 = 1 + rand() % 6;
    sum = die1 + die2;
    cout << "Zarlar: " << die1 << " + " << die2 << " = " << sum << endl;
    switch (sum) {
        case  7:
        case 11: game_status = PLAYER_WINS; break;
        case  2:
        case  3:
        case 12: game_status = PLAYER_LOSES; break;
        default: game_status = GAME_CONTINUES;
                 point = sum;
                 cout << "Sayý: " << point << endl;
                 break;
    }

    while (game_status == GAME_CONTINUES) {
        die1 = 1 + rand() % 6;
        die2 = 1 + rand() % 6;
        sum = die1 + die2;
        cout << "Zarlar: " << die1 << " + " << die2 << " = " << sum << endl;
        if (sum == point)
            game_status = PLAYER_WINS;
        else {
            if (sum == 7)
                game_status = PLAYER_LOSES;
        }
    }

    if (game_status == PLAYER_WINS)
      cout << "Oyuncu kazanýr." << endl;
    else
      cout << "Oyuncu kaybeder." << endl;

    return EXIT_SUCCESS;
}
