#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Define structure to represent a Hiragana character
struct Hiragana {
    string character;
    string pronunciation;
};

int main() {
    // Create a vector of Hiragana characters and their pronunciations
    vector<Hiragana> hiraganaAlphabet = {
        {"あ", "a"}, {"い", "i"}, {"う", "u"}, {"え", "e"}, {"お", "o"},
        {"か", "ka"}, {"き", "ki"}, {"く", "ku"}, {"け", "ke"}, {"こ", "ko"},
        {"さ", "sa"}, {"し", "shi"}, {"す", "su"}, {"せ", "se"}, {"そ", "so"},
        {"た", "ta"}, {"ち", "chi"}, {"つ", "tsu"}, {"て", "te"}, {"と", "to"},
        {"な", "na"}, {"に", "ni"}, {"ぬ", "nu"}, {"ね", "ne"}, {"の", "no"},
        {"は", "ha"}, {"ひ", "hi"}, {"ふ", "fu"}, {"へ", "he"}, {"ほ", "ho"},
        {"ま", "ma"}, {"み", "mi"}, {"む", "mu"}, {"め", "me"}, {"も", "mo"},
        {"や", "ya"}, {"ゆ", "yu"}, {"よ", "yo"},
        {"ら", "ra"}, {"り", "ri"}, {"る", "ru"}, {"れ", "re"}, {"ろ", "ro"},
        {"わ", "wa"}, {"を", "wo"}, {"ん", "n"}
    };

    // Display the Hiragana alphabet and pronunciation
    cout << "Hiragana Alphabet Practice" << "\n";

    for (const Hiragana& h : hiraganaAlphabet) {
        cout << h.character << " (" << h.pronunciation << ") "
    }

    cout << endl;

    // Quiz the user on Hiragana characters
    cout << "Let's practice! Type the pronunciation for each character." << "\n";

    int score = 0;

    for (const Hiragana& h : hiraganaAlphabet) {
        string userAnswer;
        cout << "What is the pronunciation of " << h.character << "? ";
        cin >> userAnswer;

        if (userAnswer == h.pronunciation) {
            cout << "Correct!" << "\n";
            score++;
        } else {
            cout << "Incorrect. The correct answer is " << h.pronunciation << ".\n";
        }
    }

    cout << "Quiz complete. Your score is " << score << "out of " << hiraganaAlphabet.size() << ".\n";

    return 0;
}    
