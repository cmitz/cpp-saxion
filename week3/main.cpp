#include <iostream>
#include <vector>

#include <random>
#include <ctime>

std::mt19937 mersenne(static_cast<unsigned int>(std::time(nullptr)));
std::uniform_int_distribution<> generator(0, 51);
int randomNumber() { return generator(mersenne); }

enum class Rank {
    TWO,
    THREE,
    FOUR,
    VIFE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN,
    JACK,
    QUEEN,
    KING,
    ACE
};

int rankToValue(Rank rank) {
    switch (rank) {
        case Rank::TWO:
            return 2;
        case Rank::THREE:
            return 3;
        case Rank::FOUR:
            return 4;
        case Rank::VIFE:
            return 5;
        case Rank::SIX:
            return 6;
        case Rank::SEVEN:
            return 7;
        case Rank::EIGHT:
            return 8;
        case Rank::NINE:
            return 9;
        case Rank::TEN:
            return 10;
        case Rank::JACK:
            return 10;
        case Rank::QUEEN:
            return 10;
        case Rank::KING:
            return 10;
        case Rank::ACE:
            return 11;
    }
}

std::string rankToString(Rank rank) {
    switch (rank) {
        case Rank::TWO:
            return "2";
        case Rank::THREE:
            return "3";
        case Rank::FOUR:
            return "4";
        case Rank::VIFE:
            return "5";
        case Rank::SIX:
            return "6";
        case Rank::SEVEN:
            return "7";
        case Rank::EIGHT:
            return "8";
        case Rank::NINE:
            return "9";
        case Rank::TEN:
            return "10";
        case Rank::JACK:
            return "J";
        case Rank::QUEEN:
            return "Q";
        case Rank::KING:
            return "K";
        case Rank::ACE:
            return "A";
    }
}

enum class Suit {
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};


std::string suitToString(Suit suit) {
    switch (suit) {
        case Suit::CLUBS:
            return "C";
        case Suit::DIAMONDS:
            return "D";
        case Suit::HEARTS:
            return "H";
        case Suit::SPADES:
            return "S";
    }
}

struct Card {
    Rank rank;
    Suit suit;
};

void printCard(Card card) {
    std::cout << rankToString(card.rank) << suitToString(card.suit) << " ";
}

void printDeck(std::vector<Card> const &deck) {
    for (Card const &card: deck)
        printCard(card);
    std::cout << std::endl;
}

/**
 * Swaps the values of two cards
 * @param a
 * @param b
 */
void swapCard(std::vector<Card> &deck, int a, int b) {
    Card tempCard = deck.at(a);

    deck.at(a) = deck.at(b);
    deck.at(b) = tempCard;
}

/**
 * Shuffle a deck (vector)
 * @param deck
 */
void shuffleDeck(std::vector<Card> &deck) {
    for (int i = 0; i < deck.size(); i++)
        swapCard(deck, i, randomNumber());
}

/**
 * Get the card value from a card
 * @param card
 * @return
 */
int getCardValue(Card card) {
    return rankToValue(card.rank);
}

/**
 * Print the given hand (vector)
 * @param hand
 * @param playerName
 * @param pointsRef
 */
void printHand(std::vector<Card> const &hand, std::string const playerName, int &pointsRef) {
    // Print hand
    std::cout << playerName << "'s hand: ";
    int points(0);
    for (Card const &card: hand) {
        printCard(card);
        points = points + getCardValue(card);
    }
    std::cout << "; points: " << points << std::endl;

    pointsRef = points;
}

/**
 * Ask for input, escapes bad input or answers that weren't an option
 * @param question
 * @param option_a
 * @param option_b
 * @return input
 */
std::string askChoice(std::string question, std::string option_a, std::string option_b) {
    std::string choice;
    do {
        std::cout << question << "[" << option_a << " | " << option_b << "]" << std::endl;
        while (!(std::cin >> choice)) {// prevent failed state
            std::cout << "Bad input - try again: ";
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n'); // NB: preferred method for flushing cin
        }
    } while (!(choice == option_a || choice == option_b));
    return choice;
}


int main() {
    std::vector<Card> deck {};
    deck.resize(52);

    // Instantite deck, sorted
    for (int i = 0; i < 4; i++ ) { // Iterate over suits
        for (int j = 0; j < 13; j++) { // Iterate over ranks
            Card tempCard;
            tempCard.suit = Suit(i);
            tempCard.rank = Rank(j);

            // determine position of the deck
            int x = (i * 13) + j;

            deck.at(x) = tempCard;
        }
    }
    // Shuffle deck
    shuffleDeck(deck);

    std::cout << "Blackjack!" << std::endl;

    // Cards can be dealt multiple times, for now
    bool playing = true;
    while (playing) {
        std::cout << "Playing a game!" << std::endl;

        int points_dealer(0);
        int points_player(0);

        // Dealing first cards --> game setup
        std::cout << "The dealer deals one card to the house" << std::endl;
        std::vector<Card> hand_dealer;
        hand_dealer.push_back(deck.back());
        deck.pop_back();

        std::cout << "The player is dealt two cards" << std::endl;
        std::vector<Card> hand_player;
        hand_player.push_back(deck.back());
        deck.pop_back();
        hand_player.push_back(deck.back());
        deck.pop_back();


        // Print hands
        printHand(hand_player, "Player", points_player);
        printHand(hand_dealer, "Dealer", points_dealer);

        bool gameOver = false;
        while (!gameOver) {
            // Get the players choice
            std::string choice = askChoice("Do you want to take a hit or stand?", "hit", "stand");

            if (choice == "hit") {
                hand_player.push_back(deck.back());
                // Print players hand
                printHand(hand_player, "Player", points_player);

                // Check bust
                if (points_player > 21) {
                    std::cout << "Busted!" << std::endl;
                    gameOver = true;
                } else {

                    // Dealers turn; only hits when <17
                    if (points_dealer < 17) {
                        std::cout << "Dealer hits." << std::endl;
                        hand_dealer.push_back(deck.back());
                        printHand(hand_dealer, "Dealer", points_dealer);

                        // Check bust
                        if (points_dealer > 21) {
                            std::cout << "Dealer busted!" << std::endl;
                            gameOver = true;
                        }
                    } else {
                        std::cout << "Dealer stands." << std::endl;
                    }
                }
            } else if (choice == "stand") {
                gameOver = true;
            } else {
                // PANIC, YOU FOUND A BUG!!
            }
        }

        std::cout << "You are game over." << std::endl;
        printHand(hand_dealer, "Dealer", points_dealer);
        printHand(hand_player, "Player", points_player);
        std::cout << "You " << ((points_player <= 21 && points_player > points_dealer) ? "won" : "lost") << "!" << std::endl;

        std::string again = askChoice("Do you want to play again?", "yes", "no");
        if (again == "no") {
            playing = false;
        }
    }

    return 0;
}