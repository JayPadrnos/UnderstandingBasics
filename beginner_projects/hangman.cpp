#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    // Seed the random number gen
    srand(static_cast<unsigned int>(time(0)));

    // Words to guess
    vector<string> words;
    words.push_back("program");
    words.push_back("hangman");
    words.push_back("computer");
    words.push_back("science");
    words.push_back("opening");

    // Select a random word from the vector
    const string word = words[rand() % words.size()];

    // Track the number of incorrect guesses and the guessed letters
    int incorrectGuesses = 0;
    string guessedLetters;

    // Creaate a string with underscores to represent the hidden word
    string hiddenWord(word.length(), '_');

    // Game loop
    while (incorrectGuesses < 7 && hiddenWord != word) {
        // Print the hangman ASCII art
        cout << "Incorrect guesses: " << incorrectGuesses << endl;
        cout << "Guessed letters: " << guessedLetters << endl;
        cout << "Hidden word: " << hiddenWord << endl;

        // Prompt  the users for a guess
        cout << "Guess a letter: ";
        char guess;
        cin >> guess;

        // Check if the letters has already been guessed
        if (guessedLetters.find(guess) != string::npos) {
            cout << "You already guessed that letter: " << endl;
            continue;
        }

        // Add a guessed letter to the list
        guessedLetters += guess;

        // Check if the letter is in the word
        if (word.find(guess) != string::npos) {
            // Update the hidden word with the correct guesses
            for (size_t i = 0; i < word.length(); ++i) {
                if (word[i] == guess) {
                    hiddenWord[i] = guess;
                }
            }
        } else {
            // Incorrect guess
            ++incorrectGuesses;
        }
    }

    // Game over
    if (hiddenWord == word) {
        cout << "Congratulations! You guessed the correct word: " << word << endl;
    } else {
        cout << "Sorry, you ran out of guesses. The word was: " << endl;
    }

    return 0;
}