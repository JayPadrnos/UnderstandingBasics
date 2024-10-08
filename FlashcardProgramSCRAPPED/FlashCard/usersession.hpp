#pragma once
#include "deck.hpp"
#include <algorithm>
#include <random>
#include <iostream>

class UserSession {
    private:
        Deck* deck;
        std::vector<int> cardIndices;

        void displayCard(const Card& card) {
            std::cout << card.getQuestion() << std::endl;
            std::cout << "Served in a " << card.getGlass() << std::endl;

            std::cout << "Ingredients:" << std::endl;
            for (const auto& ing : card.getIngredients()) {
                std::cout << " " << ing.second << " " << ing.first << std::endl;
            }

            std::cout << "Garnish: " << card.getGarnish() << std::endl;

            std::cout << "Variations:" << std::endl;
            for (const auto& var : card.getVariations()) {
                std::cout << " " << var.first << ": " var.second << std::endl;
            }

            std::cout << "Preparation: " << card.getPreparation() << std::endl;
        }

    public:
        UserSession(Deck* d) : deck(d) {
            cardIndices.resize(deck->size());
            std::iota(cardIndices.begin(), cardIndices.end(), 0);
        }

        void startSession(bool randomMode) {
            if (randomMode) {
                std::shuffle(cardIndices.begin(), cardIndices.end(), std::mt19937{std::random_device{}()});
            }

            for (int index : cardIndices) {
                const Card& card = deck->getCard(index);
                displayCard(card);

                std::cout << "\nPress Enter to flip to the next card...";
                std::cin.get();
            }
        }
};