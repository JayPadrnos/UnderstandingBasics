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

#ifdef _WIN32

pair<bool,string> readLineWithEsc() {
    string out;
    while (true) {
        int ch = _getch();
        if (ch == 27) { // ESC
            return {true, ""};
        } else if (ch == '\r' || ch == '\n') {
            cout << '\n';
            return {false, out};
        } else if (ch == '\b' || ch == 127) {
            if (!out.empty()) {
                out.pop_back();
                cout << "\b \b";
            }
        } else {
            out.push_back(static_cast<char>(ch));
            cout << static_cast<char>(ch);
        }
    }
}

bool countdownWaitWithEsc(int seconds) {
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
}

#else

pair<bool,string> readLineWithEsc() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    string out;
    bool esc = false;
    while (true) {
        char ch;
        ssize_t r = read(STDIN_FILENO, &ch, 1);
        if (r <= 0) break;
        if (ch == 27) { esc = true; break; }
        if (ch == '\n' || ch == '\r') { cout << '\n'; break; }
        if (ch == 127 || ch == '\b') {
            if (!out.empty()) {
                out.pop_back();
                cout << "\b \b";
            }
        } else {
            out.push_back(ch);
            cout << ch;
        }
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    if (esc) return {true, ""};
    return {false, out};
}

bool kbhit_posix() {
    timeval tv{0,0};
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO, &rfds);
    return select(STDIN_FILENO+1, &rfds, NULL, NULL, &tv) > 0;
}

bool countdownWaitWithEsc(int seconds) {
    using namespace chrono;
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    auto start = high_resolution_clock::now();
    bool escPressed = false;
    while (true) {
        if (kbhit_posix()) {
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
}

#endif

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
                if (modes.onlyHira) modes.onlyKata = false; // mutually exclusive
                cout << "Hiragana only mode is now " << (modes.onlyHira ? "ON\n" : "OFF\n");
                break;
            case 6:
                modes.onlyKata = !modes.onlyKata;
                if (modes.onlyKata) modes.onlyHira = false; // mutually exclusive
                cout << "Katakana only mode is now " << (modes.onlyKata ? "ON\n" : "OFF\n");
                break;
            case 7:
                modes.countdown = !modes.countdown;
                cout << "Countdown timer is now " << (modes.countdown ? "ON\n" : "OFF\n");
                if (modes.countdown) {
                    cout << "Enter countdown seconds (5-120): ";
                    auto res2 = readLineWithEsc();
                    if (res2.first) {
                        cout << "\nCountdown time input cancelled.\n";
                    } else {
                        string input = trimWhitespace(res2.second);
                        try {
                            int sec = stoi(input);
                            if (sec >= 5 && sec <= 120) {
                                modes.countdownSeconds = sec;
                                cout << "Countdown seconds set to " << sec << ".\n";
                            } else {
                                cout << "Invalid range. Keeping previous value (" << modes.countdownSeconds << ").\n";
                            }
                        } catch (...) {
                            cout << "Invalid input. Keeping previous value (" << modes.countdownSeconds << ").\n";
                        }
                    }
                }
                break;
            case 0:
                saveSettings(modes);
                cout << "Settings saved.\n";
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }
}

// ====== Utility functions ======

template<typename T>
void shuffleVector(vector<T>& vec) {
    static random_device rd;
    static mt19937 g(rd());
    shuffle(vec.begin(), vec.end(), g);
}

vector<Flashcard> getFilteredCards(const Modes& modes) {
    vector<Flashcard> filtered;
    for (const auto& card : flashcards) {
        // Skip small kana cards from quiz
        if (card.romaji.find("(small)") != string::npos) continue;

        if (modes.onlyHira && !card.hiragana.empty()) {
            filtered.push_back(card);
        } else if (modes.onlyKata && !card.katakana.empty()) {
            filtered.push_back(card);
        } else if (!modes.onlyHira && !modes.onlyKata) {
            filtered.push_back(card);
        }
    }
    return filtered;
}

// Wait for input with optional countdown and ESC detection, returns true if ESC pressed
bool waitForUserAnswer(const Modes& modes, string& userInput) {
    if (modes.countdown) {
        cout << "(You have " << modes.countdownSeconds << " seconds to answer)\n";
        bool escPressed = countdownWaitWithEsc(modes.countdownSeconds);
        if (escPressed) {
            return true; // ESC pressed
        }
        // Timeout reached, no input
        userInput.clear();
        return false;
    } else {
        auto res = readLineWithEsc();
        if (res.first) return true;
        userInput = trimWhitespace(res.second);
        return false;
    }
}

// Run quiz with given difficulty and modes
void runQuiz(Difficulty diff, Modes& modes) {
    vector<Flashcard> quizCards = getFilteredCards(modes);

    size_t numQuestions = 0;
    switch (diff) {
        case BEGINNER: numQuestions = 20; break;
        case INTERMEDIATE: numQuestions = 40; break;
        case DAILY: numQuestions = 10; break;
    }
    if (quizCards.size() < numQuestions) numQuestions = quizCards.size();

    shuffleVector(quizCards);
    quizCards.resize(numQuestions);

    int correct = 0;
    using clock = chrono::high_resolution_clock;
    auto start = clock::now();

    for (size_t i = 0; i < quizCards.size(); ++i) {
        const auto& card = quizCards[i];
        string prompt, answer;

        if (modes.reverse) {
            prompt = card.romaji;
            if (modes.onlyHira) answer = card.hiragana;
            else if (modes.onlyKata) answer = card.katakana;
            else answer = (rand() % 2 == 0 ? card.hiragana : card.katakana);
        } else {
            if (modes.expert) {
                prompt = (rand() % 2 == 0 ? card.hiragana : card.katakana);
            } else if (modes.onlyHira) {
                prompt = card.hiragana;
            } else if (modes.onlyKata) {
                prompt = card.katakana;
            } else {
                prompt = card.hiragana + " / " + card.katakana;
            }
            answer = card.quizRomaji;
        }

        cout << "\nQuestion " << (i + 1) << "/" << numQuestions << ": " << prompt << "\nYour answer (ESC to exit): ";

        string userInput;
        bool escPressed = waitForUserAnswer(modes, userInput);
        if (escPressed) {
            cout << "\n(ESC pressed, exiting quiz)\n";
            break;
        }

        if (userInput.empty()) {
            cout << "Time's up or no input! Correct answer: " << answer << "\n";
            continue;
        }

        string normInput = normalizeInput(userInput);
        string normAnswer = normalizeInput(answer);

        if (normInput == normAnswer) {
            cout << "Correct!\n";
            correct++;
        } else {
            cout << "Incorrect! Correct answer: " << answer << "\n";
        }
    }

    auto end = clock::now();
    double duration = chrono::duration_cast<chrono::seconds>(end - start).count();

    cout << "\nQuiz finished! Score: " << correct << " / " << numQuestions
         << " (" << (correct * 100 / numQuestions) << "%)\n";
    cout << "Total time: " << duration << " seconds\n";

    if (modes.timed) {
        string modeName = (diff == BEGINNER ? "Beginner" : diff == INTERMEDIATE ? "Intermediate" : "Daily");
        topTimes[modeName].push_back(duration);
        auto &times = topTimes[modeName];
        sort(times.begin(), times.end());
        if (times.size() > 3) times.resize(3);
        saveTopTimes();
    }
}

// ====== Main ======

int main() {
#ifdef _WIN32
    // Make Windows console print UTF-8 kana correctly
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
    SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE),
                   ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);
#endif

    srand(static_cast<unsigned int>(time(nullptr)));
    Modes modes;
    loadSettings(modes);
    loadTopTimes();


    while (true) {
        showMainMenu();
        cout << "> ";

        auto res = readLineWithEsc();
        if (res.first) {
            cout << "\n(ESC pressed, exiting program)\n";
            break;
        }

        string choiceStr = trimWhitespace(res.second);
        if (choiceStr.empty()) continue;

        int choice = -1;
        try { choice = stoi(choiceStr); }
        catch (...) { cout << "Invalid input. Enter a number.\n"; continue; }

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
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice, try again.\n";
        }
    }

    return 0;
}


//- we need the UTF-8 to properly display hira and kata the esc still works on this version

//- intermediate difficulty does not say if your answers are correct or incorrect 
//- same issue in daily
//- take the logic for beginner to other functions or have it set as a setting so that any test will have it if turned on

// set up a checklist for daily completion, or rather checks for different study types on launch, 
// different goals have a seed for random goal for the day 

//- make sure ro is displayed proper in katakana

// top times are only saved with time mode on******


// Add score with top times, this way not only time is displayed but score is as well, which means we have to prefer higher scores than faster time,
// a time of 22 seconds with a score of 70% should not be ahead of a time of 27 seconds with a score of 100% as we value the correct answer over time,
// even though it is a timed trial.

// when REVERSE mode is ON you can only answer with katakana not hira we should try to allow for both answers to be correct, unless we hira or kata mode on, then 
// we can have the input be specified in REVERSE along with the intentional function of only displaying that character when asked the question

// specify in parenthesis if the time was in reverse mode for TOP TIMES // EXPERT as well
// Unable to type with countdown TIMER MODE ON
// the COUNTDOWN TIMER ON makes it so each question is timed, wanted a timer for full quiz unanswered questions marked wrong
// How ever when questions and quizes get more intricate then We will user current settings, make a new mode for FULL QUIZ TIMER higher time setting capacity in minutes vs seconds
//
// learn the next step in vectors for project