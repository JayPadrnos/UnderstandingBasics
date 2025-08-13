// flashcardbase.cpp
// Upgraded Kana Flashcard Program with ESC universal exit, accurate countdown timer,
// robust file I/O, whitespace trimming, exception handling, and more.

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <limits>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <cctype>
#include <random>
#include <ctime>

#ifdef _WIN32
  #include <windows.h>
  #include <conio.h>      // _getch, _kbhit
#else
  #include <termios.h>
  #include <unistd.h>
  #include <sys/select.h>
#endif

using namespace std;

// ====== Structures ======
struct Flashcard {
    string hiragana;
    string katakana;
    string romaji;      // Display name (may include "(small)")
    string quizRomaji;  // Simplified romaji for checking
};

enum Difficulty {
    BEGINNER,
    INTERMEDIATE,
    DAILY
};

struct Modes {
    bool timed = false;
    bool review = false;
    bool reverse = false;     // show romaji -> expect kana
    bool expert = false;      // show only one script (random per card)
    bool onlyHira = false;    // show only hiragana (if true)
    bool onlyKata = false;    // show only katakana (if true)
    bool countdown = false;   // countdown timer enabled
    int countdownSeconds = 30;
};

// ====== Globals ======
vector<Flashcard> flashcards = {
    // Vowels
    {"あ", "ア", "a", "a"}, {"い", "イ", "i", "i"}, {"う", "ウ", "u", "u"}, {"え", "エ", "e", "e"}, {"お", "オ", "o", "o"},

    // K consonant + voiced
    {"か", "カ", "ka", "ka"}, {"き", "キ", "ki", "ki"}, {"く", "ク", "ku", "ku"}, {"け", "ケ", "ke", "ke"}, {"こ", "コ", "ko", "ko"},
    {"が", "ガ", "ga", "ga"}, {"ぎ", "ギ", "gi", "gi"}, {"ぐ", "グ", "gu", "gu"}, {"げ", "ゲ", "ge", "ge"}, {"ご", "ゴ", "go", "go"},

    // S consonant + voiced
    {"さ", "サ", "sa", "sa"}, {"し", "シ", "shi", "shi"}, {"す", "ス", "su", "su"}, {"せ", "セ", "se", "se"}, {"そ", "ソ", "so", "so"},
    {"ざ", "ザ", "za", "za"}, {"じ", "ジ", "ji", "ji"}, {"ず", "ズ", "zu", "zu"}, {"ぜ", "ゼ", "ze", "ze"}, {"ぞ", "ゾ", "zo", "zo"},

    // T consonant + voiced
    {"た", "タ", "ta", "ta"}, {"ち", "チ", "chi", "chi"}, {"つ", "ツ", "tsu", "tsu"}, {"て", "テ", "te", "te"}, {"と", "ト", "to", "to"},
    {"だ", "ダ", "da", "da"}, {"ぢ", "ヂ", "ji", "ji"}, {"づ", "ヅ", "zu", "zu"}, {"で", "デ", "de", "de"}, {"ど", "ド", "do", "do"},

    // N consonant
    {"な", "ナ", "na", "na"}, {"に", "ニ", "ni", "ni"}, {"ぬ", "ヌ", "nu", "nu"}, {"ね", "ネ", "ne", "ne"}, {"の", "ノ", "no", "no"},

    // H consonant + voiced + p
    {"は", "ハ", "ha", "ha"}, {"ひ", "ヒ", "hi", "hi"}, {"ふ", "フ", "fu", "fu"}, {"へ", "ヘ", "he", "he"}, {"ほ", "ホ", "ho", "ho"},
    {"ば", "バ", "ba", "ba"}, {"び", "ビ", "bi", "bi"}, {"ぶ", "ブ", "bu", "bu"}, {"べ", "ベ", "be", "be"}, {"ぼ", "ボ", "bo", "bo"},
    {"ぱ", "パ", "pa", "pa"}, {"ぴ", "ピ", "pi", "pi"}, {"ぷ", "プ", "pu", "pu"}, {"ぺ", "ペ", "pe", "pe"}, {"ぽ", "ポ", "po", "po"},

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

    // Small kana (kept in list but excluded from quizzes)
    {"ゃ", "ャ", "ya (small)", "ya"}, {"ゅ", "ュ", "yu (small)", "yu"}, {"ょ", "ョ", "yo (small)", "yo"},
    {"ぁ", "ァ", "a (small)", "a"}, {"ぃ", "ィ", "i (small)", "i"}, {"ぅ", "ゥ", "u (small)", "u"},
    {"ぇ", "ェ", "e (small)", "e"}, {"ぉ", "ォ", "o (small)", "o"}, {"っ", "ッ", "tsu (small)", "tsu"},
};

unordered_map<string, vector<double>> topTimes;

// ====== Helper Functions ======

// Trim leading and trailing whitespace from a string
string trimWhitespace(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

// Normalize user input (lowercase, remove " (small)")
string normalizeInput(const string &s) {
    string t;
    for (char c : s) t.push_back(tolower(static_cast<unsigned char>(c)));
    string marker = " (small)";
    size_t pos;
    while ((pos = t.find(marker)) != string::npos) t.erase(pos, marker.size());
    return trimWhitespace(t);
}

// ====== Platform-specific input helpers ======

// Check if a key is pressed without blocking
bool isKeyPressed() {
#ifdef _WIN32
    return _kbhit();
#else
    timeval tv{0, 0};
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO, &rfds);
    return select(STDIN_FILENO + 1, &rfds, nullptr, nullptr, &tv) > 0;
#endif
}

// Check if next key pressed is ESC (non-blocking peek)
bool isEscPressed() {
    if (!isKeyPressed()) return false;
#ifdef _WIN32
    int ch = _getch();
    if (ch == 27) return true;
    // For non-ESC chars, no pushback — ignoring them
    return false;
#else
    char ch;
    ssize_t r = read(STDIN_FILENO, &ch, 1);
    if (r <= 0) return false;
    if (ch == 27) return true;
    // no pushback, char is lost but rare issue
    return false;
#endif
}

// Hybrid readLineWithEsc: returns {true,""} if ESC pressed before input, else normal line input
pair<bool, string> readLineWithEsc() {
    if (isEscPressed()) {
        return {true, ""};
    }
    string input;
    getline(cin, input);
    return {false, input};
}

bool countdownWaitWithEsc(int seconds) {
#ifdef _WIN32
    using namespace chrono;
    auto start = high_resolution_clock::now();
    while (true) {
        if (_kbhit()) {
            int c = _getch();
            if (c == 27) return true;
        }
        auto now = high_resolution_clock::now();
        double elapsed = duration_cast<duration<double>>(now - start).count();
        if (elapsed >= seconds) return false;
        Sleep(50);
    }
#else
    using namespace chrono;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    auto start = high_resolution_clock::now();
    bool escPressed = false;
    while (true) {
        if (isKeyPressed()) {
            char ch;
            ssize_t r = read(STDIN_FILENO, &ch, 1);
            if (r > 0 && ch == 27) { escPressed = true; break; }
        }
        auto now = high_resolution_clock::now();
        double elapsed = duration_cast<duration<double>>(now - start).count();
        if (elapsed >= seconds) break;
        usleep(50000);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return escPressed;
#endif
}

// ====== File I/O ======

void loadSettings(Modes &modes) {
    ifstream in("settings.txt");
    if (!in) return;
    bool t,r,rev,exp,h,k;
    int csec;
    if (in >> t >> r >> rev >> exp >> h >> k >> csec) {
        modes.timed = t; modes.review = r; modes.reverse = rev; modes.expert = exp;
        modes.onlyHira = h; modes.onlyKata = k; modes.countdown = (csec>0);
        if (csec > 0) modes.countdownSeconds = csec;
    }
}

void saveSettings(const Modes &modes) {
    ofstream out("settings.txt");
    out << modes.timed << " " << modes.review << " " << modes.reverse << " "
        << modes.expert << " " << modes.onlyHira << " " << modes.onlyKata << " "
        << (modes.countdown ? 1 : 0) << " " << modes.countdownSeconds;
}

void loadTopTimes() {
    ifstream in("toptimes.txt");
    if (!in) return;
    string mode;
    double t;
    while (in >> mode >> t) {
        topTimes[mode].push_back(t);
    }
}

void saveTopTimes() {
    ofstream out("toptimes.txt");
    for (auto &entry : topTimes) {
        for (double t : entry.second) {
            out << entry.first << " " << t << "\n";
        }
    }
}

// ====== Display helpers ======

void showKanaList() {
    cout << "\n==== Kana List ====\n";
    for (const auto &card : flashcards) {
        cout << "H: " << card.hiragana << "\tK: " << card.katakana << "\tR: " << card.romaji << "\n";
    }
}

void showTopTimes() {
    cout << "\n==== Top 3 Times per Mode ====\n";
    if (topTimes.empty()) {
        cout << "(No recorded times yet)\n";
        return;
    }
    for (auto &entry : topTimes) {
        cout << entry.first << " mode:\n";
        for (size_t i = 0; i < entry.second.size(); ++i) {
            cout << "  " << i + 1 << ". " << entry.second[i] << " seconds\n";
        }
    }
}

void showMainMenu() {
    cout << "\n===== Kana Flashcard Menu =====\n";
    cout << "1. Beginner Quiz\n";
    cout << "2. Intermediate Quiz\n";
    cout << "3. Daily Quick Run (10 Cards)\n";
    cout << "4. View Full Kana List\n";
    cout << "5. View Top Times\n";
    cout << "6. Settings\n";
    cout << "0. Exit\n";
}

// ====== Settings Menu ======

void showSettingsMenu(Modes &modes) {
    while (true) {
        cout << "\n===== Settings =====\n";
        cout << "1. Toggle Timed Mode (" << (modes.timed ? "ON" : "OFF") << ")\n";
        cout << "2. Toggle Review Mode (" << (modes.review ? "ON" : "OFF") << ")\n";
        cout << "3. Toggle Reverse Mode (romaji->kana) (" << (modes.reverse ? "ON" : "OFF") << ")\n";
        cout << "4. Toggle Expert Mode (random script only) (" << (modes.expert ? "ON" : "OFF") << ")\n";
        cout << "5. Toggle Hiragana Only (" << (modes.onlyHira ? "ON" : "OFF") << ")\n";
        cout << "6. Toggle Katakana Only (" << (modes.onlyKata ? "ON" : "OFF") << ")\n";
        cout << "7. Toggle Countdown Timer (" << (modes.countdown ? "ON" : "OFF") << "), Seconds: " << modes.countdownSeconds << "\n";
        cout << "0. Save and Return to Main Menu\n";
        cout << "Select option: ";

        auto res = readLineWithEsc();
        if (res.first) {
            cout << "\n(ESC pressed, returning to main menu)\n";
            break;
        }

        string choiceStr = trimWhitespace(res.second);
        if (choiceStr.empty()) continue;
        int choice = -1;
        try { choice = stoi(choiceStr); }
        catch (...) { cout << "Invalid input. Please enter a number.\n"; continue; }

        switch (choice) {
            case 1:
                modes.timed = !modes.timed;
                cout << "Timed mode is now " << (modes.timed ? "ON\n" : "OFF\n");
                break;
            case 2:
                modes.review = !modes.review;
                cout << "Review mode is now " << (modes.review ? "ON\n" : "OFF\n");
                break;
            case 3:
                modes.reverse = !modes.reverse;
                cout << "Reverse mode is now " << (modes.reverse ? "ON\n" : "OFF\n");
                break;
            case 4:
                modes.expert = !modes.expert;
                cout << "Expert mode is now " << (modes.expert ? "ON\n" : "OFF\n");
                break;
            case 5:
                modes.onlyHira = !modes.onlyHira;
                if (modes.onlyHira) modes.onlyKata = false;
                cout << "Hiragana Only mode is now " << (modes.onlyHira ? "ON\n" : "OFF\n");
                break;
            case 6:
                modes.onlyKata = !modes.onlyKata;
                if (modes.onlyKata) modes.onlyHira = false;
                cout << "Katakana Only mode is now " << (modes.onlyKata ? "ON\n" : "OFF\n");
                break;
            case 7:
                modes.countdown = !modes.countdown;
                cout << "Countdown timer is now " << (modes.countdown ? "ON\n" : "OFF\n");
                if (modes.countdown) {
                    cout << "Enter seconds for countdown (5-60): ";
                    auto tsec = readLineWithEsc();
                    if (!tsec.first) {
                        try {
                            int sec = stoi(trimWhitespace(tsec.second));
                            if (sec >= 5 && sec <= 60) {
                                modes.countdownSeconds = sec;
                                cout << "Countdown seconds set to " << sec << "\n";
                            } else {
                                cout << "Invalid number, keeping previous value.\n";
                            }
                        } catch (...) {
                            cout << "Invalid input, keeping previous value.\n";
                        }
                    }
                }
                break;
            case 0:
                saveSettings(modes);
                cout << "Settings saved. Returning to main menu.\n";
                return;
            default:
                cout << "Invalid option.\n";
                break;
        }
    }
}

// ====== Quiz Logic ======

void shuffleCards(vector<Flashcard> &cards) {
    static mt19937 rng(static_cast<unsigned int>(time(nullptr)));
    shuffle(cards.begin(), cards.end(), rng);
}

void runQuiz(Difficulty difficulty, Modes &modes) {
    cout << "\nStarting quiz... Press ESC anytime to quit.\n";

    vector<Flashcard> quizCards;

    // Select cards based on difficulty
    for (auto &card : flashcards) {
        // Exclude small kana for quiz
        if (card.romaji.find("(small)") != string::npos) continue;

        if (difficulty == BEGINNER) {
            // Only basic 46 kana (roughly the first set)
            if (card.romaji.size() <= 3) quizCards.push_back(card);
        } else if (difficulty == INTERMEDIATE) {
            quizCards.push_back(card);
        } else if (difficulty == DAILY) {
            quizCards.push_back(card);
        }
    }

    if (quizCards.empty()) {
        cout << "No cards available for this difficulty.\n";
        return;
    }

    shuffleCards(quizCards);

    size_t limit = (difficulty == DAILY) ? 10 : quizCards.size();

    int correct = 0;
    int total = 0;

    for (size_t i = 0; i < limit; ++i) {
        Flashcard &card = quizCards[i];

        string question, expectedAnswer;

        if (modes.reverse) {
            question = card.quizRomaji;
            expectedAnswer = modes.onlyKata ? card.katakana :
                             modes.onlyHira ? card.hiragana :
                             (rand() % 2 ? card.hiragana : card.katakana);
        } else {
            question = modes.onlyKata ? card.katakana :
                       modes.onlyHira ? card.hiragana :
                       (modes.expert ? (rand() % 2 ? card.hiragana : card.katakana) :
                        (rand() % 2 ? card.hiragana : card.katakana));
            expectedAnswer = card.quizRomaji;
        }

        cout << "\nCard " << (i + 1) << "/" << limit << "\n";
        cout << "Question: " << question << "\n";
        if (modes.timed) {
            cout << "You have " << modes.countdownSeconds << " seconds to answer.\n";
        }
        cout << "Your answer (type and press Enter, or ESC to quit): ";

        if (modes.countdown) {
            bool escPressed = countdownWaitWithEsc(modes.countdownSeconds);
            if (escPressed) {
                cout << "\nESC pressed. Exiting quiz early.\n";
                break;
            }
        }

        auto res = readLineWithEsc();
        if (res.first) {
            cout << "\nESC pressed. Exiting quiz early.\n";
            break;
        }

        string userAnswer = normalizeInput(res.second);

        if (userAnswer == normalizeInput(expectedAnswer)) {
            cout << "Correct!\n";
            ++correct;
        } else {
            cout << "Incorrect. Correct answer: " << expectedAnswer << "\n";
        }

        ++total;
    }

    cout << "\nQuiz finished. Score: " << correct << "/" << total << "\n";
}

// ====== Main ======

int main() {
    Modes modes;
    loadSettings(modes);
    loadTopTimes();

    while (true) {
        showMainMenu();
        cout << "Select an option (ESC to quit): ";
        auto res = readLineWithEsc();

        if (res.first) {
            cout << "\nESC pressed. Exiting program.\n";
            break;
        }

        string choiceStr = trimWhitespace(res.second);
        if (choiceStr.empty()) continue;

        int choice = -1;
        try { choice = stoi(choiceStr); }
        catch (...) {
            cout << "Invalid input.\n";
            continue;
        }

        switch (choice) {
            case 1:
                runQuiz(BEGINNER, modes);
                break;
            case 2:
                runQuiz(INTERMEDIATE, modes);
                break;
            case 3:
                runQuiz(DAILY, modes);
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
                cout << "Exiting program. Goodbye!\n";
                saveSettings(modes);
                saveTopTimes();
                return 0;
            default:
                cout << "Invalid choice.\n";
                break;
        }
    }

    saveSettings(modes);
    saveTopTimes();

    return 0;
}

// UTF-8 with esc from V2