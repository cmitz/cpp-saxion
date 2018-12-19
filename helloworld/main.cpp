#include <iostream>
#include <random>
#include "io.h"

using namespace std;

int randomNumber() {
    // Use Mersenne Twister Engine for Random Number Generation
    mt19937 rng;
    rng.seed(random_device()());
    uniform_int_distribution<mt19937::result_type> dist100(1,100);
    return dist100(rng);
}

int main() {
    string guessedNumber;

    int answer = randomNumber();
    int input;
    int attempt = 0;
    bool finished = false;

    cout << "Let's play a game.  I'm thinking of a number." << endl;
    cout << "You have 7 tries to guess what it is." << endl;

    do {
        cout << "Guess #" << ++attempt << ": ";

        input = readNumber();
        bool correct = writeResponse(answer, input);

        if (correct || attempt == 7) {
            if (attempt == 7) {
                cout << "Sorry, you lose.  The correct number was " << answer << "." << endl;
            }

            char again;
            bool notYN = true;

            do {
                cout << "Would you like to play again (y/n)? ";
                cin >> again;

                if (again == 'y') {
                    attempt = 0;
                    answer = randomNumber();
                    notYN = false;
                } else if (again == 'n') {
                    finished = true;
                    notYN = false;
                }
            } while (notYN);
        }

    } while (!finished);

    return 0;
}