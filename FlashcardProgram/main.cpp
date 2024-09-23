#include "FlashCard.hpp"
#include "Deck.hpp"
#include "UserSession.hpp"
#include <iostream>

void createUserDeck(Deck& deck) {
    int cardCount;
    std::cout << "How many cards would you like to add?: ";
    std::cin >> cardCount;
    std::cin.ignore(); // clear newline from buffer

    for (int i = 0; i < cardCount; ++i) {
        std::string question, answer, hint;
        int difficulty;
        std::cout << "Enter question for card " << i + 1 << ": ";
        std::getline(std::cin, question);
        std::cout << "Enter answer for card " << i + 1 << ": ";
        std::getline(std::cin, answer);
        std::cout << "Enter hint for card " << i + 1 << ": ";
        std::getline(std::cin, hint);
        std::cout << "Enter difficulty level (1 = easy, 2 = medium, 3 = hard): ";
        std::cin >> difficulty;
        std::cin.ignore();

        deck.addCard(FlashCard(question, answer, hint, "", "", difficulty));
    }
}

int main() {
    Deck mathDeck;
    createUserDeck(mathDeck);
    int difficulty;
    std::cout << "Select difficulty level 1 - 3: ";
    std::cin >> difficulty;

    Deck filteredDeck = mathDeck.filterByDifficulty(difficulty);
    UserSession session(filteredDeck, false);
    session.startTimer();

    while (session.hasNextCard()) {
        FlashCard card = session.getCurrentCard();
        std::cout << "Question: " << card.question << std::endl;

        char hintChoice;
        std::cout << "Do you want a hint? (y/n): ";
        std::cin >> hintChoice;

        if (hintChoice == 'y') {
            session.showHint(card);
        }

        std::string userAnswer;
        std::cout << "Your answer: ";
        std::cin >> userAnswer;

        if (userAnswer == card.answer) {
            std::cout << "Correct!\n";
            session.nextCard(true);
        } else {
            std::cout << "Incorrect. The correct answer was: " << card.answer << "\n";
            session.nextCard(false);
        }
    }

    session.displayProgress();
    std::cout << "Time Taken: " << session.endTimer() << "seconds." << std::endl;
    session.reviewIncorrectCards();

    return 0;
}