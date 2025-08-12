// flashcardbase.cpp

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <chrono>

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// Flashcard structure
struct Flashcard {
    string hiragana;
    string katakana;
    string romaji;      // full name for display (may include " (small)")
    string quizRomaji;  // simplified input for quiz
};

// Enum for difficulty
enum Difficulty {
    BEGINNER,
    INTERMEDIATE,
    DAILY
};

// Struct to hold program modes
struct Modes {
    bool timed = false;
    bool review = false;
};

// Global constants for flashcards
vector<Flashcard> flashcards = {
    // Vowels
    {"あ", "ア", "a", "a"}, {"い", "イ", "i", "i"}, {"う", "ウ", "u", "u"}, {"え", "エ", "e", "e"}, {"お", "オ", "o", "o"},

    // K consonant
    {"か", "カ", "ka", "ka"}, {"き", "キ", "ki", "ki"}, {"く", "ク", "ku", "ku"}, {"け", "ケ", "ke", "ke"}, {"こ", "コ", "ko", "ko"},

    // S consonant
    {"さ", "サ", "sa", "sa"}, {"し", "シ", "shi", "shi"}, {"す", "ス", "su", "su"}, {"せ", "セ", "se", "se"}, {"そ", "ソ", "so", "so"},

    // T consonant
    {"た", "タ", "ta", "ta"}, {"ち", "チ", "chi", "chi"}, {"つ", "ツ", "tsu", "tsu"}, {"て", "テ", "te", "te"}, {"と", "ト", "to", "to"},

    // N consonant
    {"な", "ナ", "na", "na"}, {"に", "ニ", "ni", "ni"}, {"ぬ", "ヌ", "nu", "nu"}, {"ね", "ネ", "ne", "ne"}, {"の", "ノ", "no", "no"},

    // H consonant
    {"は", "ハ", "ha", "ha"}, {"ひ", "ヒ", "hi", "hi"}, {"ふ", "フ", "fu", "fu"}, {"へ", "ヘ", "he", "he"}, {"ほ", "ホ", "ho", "ho"},

    // M consonant
    {"ま", "マ", "ma", "ma"}, {"み", "ミ", "mi", "mi"}, {"む", "ム", "mu", "mu"}, {"め", "メ", "me", "me"}, {"も", "モ", "mo", "mo"},

    // Y consonant
    {"や", "ヤ", "ya", "ya"}, {"ゆ", "ユ", "yu", "yu"}, {"よ", "ヨ", "yo", "yo"},

    // R consonant
    {"ら", "ラ", "ra", "ra"}, {"り", "リ", "ri", "ri"}, {"る", "ル", "ru", "ru"}, {"れ", "レ", "re", "re"}, {"ろ", "ロ", "ro", "ro"},

    // W consonant
    {"わ", "ワ", "wa", "wa"}, {"を", "ヲ", "wo", "wo"},

    // N
    {"ん", "ン", "n", "n"},

    // Small kana for combinations
    {"ゃ", "ャ", "ya (small)", "ya"}, {"ゅ", "ュ", "yu (small)", "yu"}, {"ょ", "ョ", "yo (small)", "yo"},
    {"ぁ", "ァ", "a (small)", "a"}, {"ぃ", "ィ", "i (small)", "i"}, {"ぅ", "ゥ", "u (small)", "u"},
    {"ぇ", "ェ", "e (small)", "e"}, {"ぉ", "ォ", "o (small)", "o"}, {"っ", "ッ", "tsu (small)", "tsu"},
};

// Time records
unordered_map<string, vector<double>> topTimes;

// Function declarations
void showMainMenu();
void showSettingsMenu(Modes &modes);
void showKanaList();
void startQuiz(Difficulty difficulty, const Modes &modes);
void recordTime(double timeTaken, Difficulty difficulty);
void showTopTimes();

int main() {
#ifdef _WIN32
    // Enable UTF-8 output on Windows console
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    Modes modes;
    while (true) {
        showMainMenu();
        cout << "\nSelect an option: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                startQuiz(BEGINNER, modes);
                break;
            case 2:
                startQuiz(INTERMEDIATE, modes);
                break;
            case 3:
                startQuiz(DAILY, modes);
                break;
            case 4:
                showKanaList();
                break;
            case 5:
                showTopTimes();
                break;
            case 6:
                showSettingsMenu(modes);
                break;
            case 0:
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
    return 0;
}

void showMainMenu() {
    cout << "\n===== Kana Flashcard Menu =====\n";
    cout << "1. Beginner Quiz\n";
    cout << "2. Intermediate Quiz\n";
    cout << "3. Daily Quick Run (5-10 Cards)\n";
    cout << "4. View Full Kana List\n";
    cout << "5. View Top Times\n";
    cout << "6. Settings\n";
    cout << "0. Exit\n";
}

void showSettingsMenu(Modes &modes) {
    int input;
    while (true) {
        cout << "\n===== Settings =====\n";
        cout << "1. Toggle Timed Mode (Currently " << (modes.timed ? "ON" : "OFF") << ")\n";
        cout << "2. Toggle Review Mode (Currently " << (modes.review ? "ON" : "OFF") << ")\n";
        cout << "0. Return to Main Menu\n";
        cout << "Choose an option: ";
        cin >> input;

        switch (input) {
            case 1:
                modes.timed = !modes.timed;
                break;
            case 2:
                modes.review = !modes.review;
                break;
            case 0:
                return;
            default:
                cout << "Invalid input. Try again.\n";
        }
    }
}

void showKanaList() {
    cout << "\n==== Kana List ====" << endl;
    for (const auto& card : flashcards) {
        cout << "H: " << card.hiragana << "\tK: " << card.katakana << "\tR: " << card.romaji << endl;
    }
}

void startQuiz(Difficulty difficulty, const Modes &modes) {
    vector<Flashcard> cards = flashcards;
    if (difficulty == DAILY && flashcards.size() > 10)
        cards.resize(10);

    random_shuffle(cards.begin(), cards.end());
    int correct = 0;
    auto start = chrono::high_resolution_clock::now();

    for (const auto& card : cards) {
        cout << "Kana: " << card.hiragana << " / " << card.katakana << "\nRomaji: ";
        string input;
        getline(cin, input);

        if (input == card.quizRomaji) {
            if (difficulty == BEGINNER || modes.review)
                cout << "Correct!\n";
            correct++;
        } else {
            if (difficulty == BEGINNER || modes.review)
                cout << "Wrong! Correct answer: " << card.quizRomaji << "\n";
        }
    }

    auto end = chrono::high_resolution_clock::now();
    double timeTaken = chrono::duration<double>(end - start).count();

    if (modes.timed) {
        cout << "\nTime taken: " << timeTaken << " seconds\n";
        recordTime(timeTaken, difficulty);
    }

    if (difficulty == INTERMEDIATE && !modes.review) {
        cout << "\nCorrect answers: " << correct << " / " << cards.size() << endl;
    }
}

void recordTime(double timeTaken, Difficulty difficulty) {
    string key = (difficulty == BEGINNER ? "Beginner" : difficulty == INTERMEDIATE ? "Intermediate" : "Daily");
    topTimes[key].push_back(timeTaken);
    sort(topTimes[key].begin(), topTimes[key].end());
    if (topTimes[key].size() > 3) topTimes[key].resize(3);
}

void showTopTimes() {
    cout << "\n==== Top 3 Times per Mode ====" << endl;
    for (const auto& [mode, times] : topTimes) {
        cout << mode << " mode:\n";
        for (size_t i = 0; i < times.size(); ++i) {
            cout << "  " << i + 1 << ". " << times[i] << " seconds\n";
        }
    }
}
