#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;

enum {
    ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
};

enum Suit {
    CLUBS, DIAMONDS, HEARTS, SPADES
};

struct Card {
    Rank rank;
    Suit suit;
};

class Deck {
    private:
    vector<Card> cards;

    public:
    Deck() {
        for (int s = CLUBS; s <= SPADES; ++s) {
            for (int r = ACE; r <= KING; ++r) {
                cards.push_back({static_cast<Rank>(r), static_cast<Suit>(s)});
            }
        }
        shuffle();
    }

    void shuffle() {
        srand(time(0));
        random_shuffle(cards.begin(), cards.end());
    }

    Card dealCard() {
        Card c = cards.back();
        cards.pop_back();
        return c;
    }
};

class Player {
    protected:
    vector<Card> hand;

    public:
    void addToHand(Card card) {
        hand.push_back(card);
    }

    void clearHand() {
        hand.clear();
    }

    int getHandValue() {
        int value = 0;
        int numAces = 0;
        for (const auto& card : hand) {
            if (card.rank >= TWO && card.rank <= TEN) {
                value += static_cast<int>(card.rank);
            } else if (card.rank >= JACK && card.rank <= KING) {
                value += 10;
            } else if (card.rank == ACE) {
                value += 11; // assume ace as 11 initially
                numAces++;
            }
        }
        // Adjust ace values if necessary
        while (value > 21 && numAces > 0) {
            value -= 10;
            numAces--;
        }
        return value;
    }

    virtual bool isBusted() {
        return getHandValue() > 21;
    }

    void displayHand(bool hideFirstCard = false) {
        for (size_t i = 0; i < hand.size(); ++i) {
            if (hideFirstCard && i == 0) {
                cout << "Hidden Card, ";
            } else {
                cout << cardToString(hand[i]) << ", ";
            }
        }
        cout << "\n";
    }

    string cardToString(const Card& card) {
        string ranks[] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King"};
        string suits[] = {"Clubs", "Diamonds", "Hearts", "Spades"};
        return ranks[card.rank - 1] + " of " + suits[card.suit];
    }
};

class Dealer : public Player {
    public:
    void displayfirstCard() {
        if (!hand.empty()) {
            cout << "Dealer's Hand: ";
            cout << "Hidden Card, ";
            cout << cardToString(hand[1]) << "\n";
        }
    }

    bool shouldHit() {
        return getHandValue() < 17;
    }
};

class BlackJackGame {
    private:
    Deck deck;
    Dealer dealer;
    vector<Player> players;

    public:
    void addPlayer(Player player) {
        players.push_back(player);
    }

    void dealInitialCard() {
        for (int i = 0; i < 2; ++i) {
            for (auto& player : players) {
                player.addToHand(deck.dealCard());
            }
            dealer.addToHand(deck.dealCard());
        }
    }

    void displayTable(bool hideDealerCard = true) {
        dealer.displayFirstCard();
        for (auto& player : players) {
            cout << "Player's Hand: ";
            player.displayHand();
        }
        if (!hideDealerCard) {
            cout << "Dealers Hand: ";
            dealer.displayHand();
        }
    }

    void playRound() {
        dealInitialCards();
        displayTable();

        // Players turn
        for (auto& player : players) {
            while (!player.isBusted()) {
                cout << "Player's Turn - ";
                char choice;
                cout << "Do you want to (h)it or (s)tay? ";
                cin >> choice;
                if (choice == 'h') {
                    player.addToHand(deck.dealCard());
                    cout << "Player's Hand: ";
                    player.displayHand();
                } else if (choice == 's') {
                    break;
                } else {
                    cout << "Invalid choice! Please enter 'h' or 's'. \n";
                }
            }
        }

        // Dealers turn
        while (dealer.shouldHit()) {
            dealer.addToHand(deck.dealCard());
        }

        // Display final table
        displayTable(false);

        // Determine winners
        for (auto& player : players) {
            if (player.isBusted()) {
                cout << "Player busts!\n";
            } else if (dealer.isBusted() || player.getHandValue() > dealer.getHandValue()) {
                cout << "Player wins! \n";
            } else if (player.getHandValue() == dealer.getHandValue()) {
                cout << "Push!\n";
            } else {
                cout << "Dealer Wins!\n";
            }
        }

        // Clear hands for the next round
        for (auto&player : players) {
            player.clearHand();
        }
        dealer.clearHand();
    }
};

int main() {
    BlackJackGame game;

    int numPlayers;
    cout << "Enter the number of players (up to 4): ";
    cin >> numPlayers;

    for (int i = 0; i < numPlayers; ++i) {
        Player player;
        game.addPlayer(player);
    }

    char playAgain = 'y';
    while (playAgain == 'y') {
        game.playRound();
        cout << "Do you want to pay again? (y/n): ";
        cin >> playAgain;
    }

    return 0;
}