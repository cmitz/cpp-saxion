#include <iostream>

//
// Created by Casper Smits on 21/11/2018.
//

using namespace std;

int readNumber() {
    int intGuessedNumber;

    while (!(cin >> intGuessedNumber)) // failed state
    {
        cout << "Bad input - try again: ";
        cin.clear();
        cin.ignore(INT_MAX, '\n'); // NB: preferred method for flushing cin
    }

    return intGuessedNumber;
}

bool writeResponse(int answer, int input){
    if (input < answer) {
        cout << "Your guess is too low" << endl;
        return false;
    } else if (input > answer) {
        cout << "Your guess is too high" << endl;
        return false;
    } else if (input == answer){
        cout << "Correct! You win!" << endl;
        return true;
    }
    return false;
}