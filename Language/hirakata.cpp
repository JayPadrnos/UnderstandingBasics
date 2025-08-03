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
    string romaji;
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
    {"あ", "ア", "a"}, {"い", "イ", "i"}, {"う", "ウ", "u"}, {"え", "エ", "e"}, {"お", "オ", "o"},

    // K consonant
    {"か", "カ", "ka"}, {"き", "キ", "ki"}, {"く", "ク", "ku"}, {"け", "ケ", "ke"}, {"こ", "コ", "ko"},

    // S consonant
    {"さ", "サ", "sa"}, {"し", "シ", "shi"}, {"す", "ス", "su"}, {"せ", "セ", "se"}, {"そ", "ソ", "so"},

    // T consonant
    {"た", "タ", "ta"}, {"ち", "チ", "chi"}, {"つ", "ツ", "tsu"}, {"て", "テ", "te"}, {"と", "ト", "to"},

    // N consonant
    {"な", "ナ", "na"}, {"に", "ニ", "ni"}, {"ぬ", "ヌ", "nu"}, {"ね", "ネ", "ne"}, {"の", "ノ", "no"},

    // H consonant
    {"は", "ハ", "ha"}, {"ひ", "ヒ", "hi"}, {"ふ", "フ", "fu"}, {"へ", "ヘ", "he"}, {"ほ", "ホ", "ho"},

    // M consonant
    {"ま", "マ", "ma"}, {"み", "ミ", "mi"}, {"む", "ム", "mu"}, {"め", "メ", "me"}, {"も", "モ", "mo"},

    // Y consonant
    {"や", "ヤ", "ya"}, {"ゆ", "ユ", "yu"}, {"よ", "ヨ", "yo"},

    // R consonant
    {"ら", "ラ", "ra"}, {"り", "リ", "ri"}, {"る", "ル", "ru"}, {"れ", "レ", "re"}, {"ろ", "ロ", "ro"},

    // W consonant
    {"わ", "ワ", "wa"}, {"を", "ヲ", "wo"},

    // N
    {"ん", "ン", "n"},

    // Small kana for combinations
    {"ゃ", "ャ", "ya (small)"}, {"ゅ", "ュ", "yu (small)"}, {"ょ", "ョ", "yo (small)"},
    {"ぁ", "ァ", "a (small)"}, {"ぃ", "ィ", "i (small)"}, {"ぅ", "ゥ", "u (small)"},
    {"ぇ", "ェ", "e (small)"}, {"ぉ", "ォ", "o (small)"}, {"っ", "ッ", "tsu (small)"},
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

        if (input == card.romaji) {
            if (difficulty == BEGINNER || modes.review)
                cout << "Correct!\n";
            correct++;
        } else {
            if (difficulty == BEGINNER || modes.review)
                cout << "Wrong! Correct answer: " << card.romaji << "\n";
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
