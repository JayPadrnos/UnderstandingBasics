// flashcardbase.cpp
// Loop-safe version with ESC-to-exit, safe file I/O, countdown timer abort, and robust input handling.

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

    // Small kana (kept in list but will be excluded from quizzes)
    {"ゃ", "ャ", "ya (small)", "ya"}, {"ゅ", "ュ", "yu (small)", "yu"}, {"ょ", "ョ", "yo (small)", "yo"},
    {"ぁ", "ァ", "a (small)", "a"}, {"ぃ", "ィ", "i (small)", "i"}, {"ぅ", "ゥ", "u (small)", "u"},
    {"ぇ", "ェ", "e (small)", "e"}, {"ぉ", "ォ", "o (small)", "o"}, {"っ", "ッ", "tsu (small)", "tsu"},
};

unordered_map<string, vector<double>> topTimes;

// ====== Function Declarations ======
void loadSettings(Modes &modes);
void saveSettings(const Modes &modes);
void loadTopTimes();
void saveTopTimes();
void showKanaList();
void showMainMenu();
void showSettingsMenu(Modes &modes);
void startQuiz(Difficulty difficulty, const Modes &modes);
void recordTime(double timeTaken, Difficulty difficulty);
void showTopTimes();
string normalizeInput(const string &s);
pair<bool,string> readLineWithEsc(); // returns (true, "") if ESC pressed
bool countdownWaitWithEsc(int seconds); // returns true if ESC pressed
void clearCinLine();

// ====== Platform-specific helpers for raw input detection ======
#ifdef _WIN32

// Windows: use _getch to build a line char-by-char and detect ESC (27)
pair<bool,string> readLineWithEsc() {
    string out;
    while (true) {
        int ch = _getch(); // does not echo
        if (ch == 27) { // ESC
            return {true, ""};
        } else if (ch == '\r' || ch == '\n') {
            cout << '\n';
            return {false, out};
        } else if (ch == '\b' || ch == 127) {
            if (!out.empty()) {
                out.pop_back();
                // erase last char from console
                cout << "\b \b";
            }
        } else {
            out.push_back(static_cast<char>(ch));
            cout << static_cast<char>(ch); // echo
        }
    }
}

bool countdownWaitWithEsc(int seconds) {
    using namespace chrono;
    auto start = high_resolution_clock::now();
    while (true) {
        if (_kbhit()) {
            int c = _getch();
            if (c == 27) return true; // ESC
            // ignore other keys
        }
        auto now = high_resolution_clock::now();
        double elapsed = duration_cast<duration<double>>(now - start).count();
        if (elapsed >= seconds) return false;
        // small sleep to avoid busy-loop
        Sleep(50);
    }
}

#else // POSIX (Linux / macOS)
pair<bool,string> readLineWithEsc() {
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO); // raw mode, no echo
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
    newt.c_lflag &= ~(ICANON | ECHO); // raw
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
        // small sleep
        usleep(50000);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return escPressed;
}

#endif

// ====== Utility helpers ======
void clearCinLine() {
    // If there is leftover input in std::cin, clear it.
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

string normalizeInput(const string &s) {
    // Lowercase and strip " (small)" and surrounding whitespace.
    string t;
    for (char c : s) t.push_back(tolower(static_cast<unsigned char>(c)));
    // remove " (small)" occurrences
    string marker = " (small)";
    size_t pos;
    while ((pos = t.find(marker)) != string::npos) t.erase(pos, marker.size());
    // trim spaces at ends
    size_t start = t.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = t.find_last_not_of(" \t\r\n");
    return t.substr(start, end - start + 1);
}

// ====== File I/O (safe reading) ======
void loadSettings(Modes &modes) {
    ifstream in("settings.txt");
    if (!in) return;
    // read with guard: if file content bad, keep defaults
    bool t,r,rev,exp, h, k;
    int csec;
    if (in >> t >> r >> rev >> exp >> h >> k >> csec) {
        modes.timed = t; modes.review = r; modes.reverse = rev; modes.expert = exp;
        modes.onlyHira = h; modes.onlyKata = k; modes.countdown = (csec>0);
        if (csec > 0) modes.countdownSeconds = csec;
    }
}

void saveSettings(const Modes &modes) {
    ofstream out("settings.txt");
    // save countdownSeconds even if countdown is off so user can keep setting
    out << modes.timed << " " << modes.review << " " << modes.reverse << " " << modes.expert << " "
        << modes.onlyHira << " " << modes.onlyKata << " " << (modes.countdown ? 1 : 0) << " " << modes.countdownSeconds;
}

void loadTopTimes() {
    ifstream in("toptimes.txt");
    if (!in) return;
    string mode;
    double t;
    // Safe form: while(getline) OR >> mode >> t (both okay). We'll use >> which stops on EOF.
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
        cout << "4. Toggle Expert Mode (show only one script) (" << (modes.expert ? "ON" : "OFF") << ")\n";
        cout << "5. Toggle Hiragana Only (" << (modes.onlyHira ? "ON" : "OFF") << ")\n";
        cout << "6. Toggle Katakana Only (" << (modes.onlyKata ? "ON" : "OFF") << ")\n";
        cout << "7. Toggle Countdown Timer (" << (modes.countdown ? "ON" : "OFF") << ") - Seconds: " << modes.countdownSeconds << "\n";
        cout << "0. Return\n";
        cout << "(Press ESC anytime while entering a number to cancel)\n";
        cout << "> ";

        auto res = readLineWithEsc();
        if (res.first) { // ESC pressed -> return to previous menu
            cout << "\n(Exited settings with ESC)\n";
            return;
        }
        string choiceStr = res.second;
        if (choiceStr.empty()) { cout << "No input. Try again.\n"; continue; }
        int choice = -1;
        try { choice = stoi(choiceStr); } catch (...) { cout << "Invalid input; enter a number.\n"; continue; }

        switch (choice) {
            case 1: modes.timed = !modes.timed; cout << "Timed: " << (modes.timed ? "ON\n" : "OFF\n"); break;
            case 2: modes.review = !modes.review; cout << "Review: " << (modes.review ? "ON\n" : "OFF\n"); break;
            case 3: modes.reverse = !modes.reverse; cout << "Reverse: " << (modes.reverse ? "ON\n" : "OFF\n"); break;
            case 4: modes.expert = !modes.expert; cout << "Expert: " << (modes.expert ? "ON\n" : "OFF\n"); break;
            case 5: modes.onlyHira = !modes.onlyHira; if (modes.onlyHira && modes.onlyKata) { cout << "Both filters set; will default to mixed mode at quiz time.\n"; } cout << "Hiragana only: " << (modes.onlyHira ? "ON\n" : "OFF\n"); break;
            case 6: modes.onlyKata = !modes.onlyKata; if (modes.onlyHira && modes.onlyKata) { cout << "Both filters set; will default to mixed mode at quiz time.\n"; } cout << "Katakana only: " << (modes.onlyKata ? "ON\n" : "OFF\n"); break;
            case 7:
                modes.countdown = !modes.countdown;
                cout << "Countdown timer: " << (modes.countdown ? "ON\n" : "OFF\n");
                if (modes.countdown) {
                    cout << "Enter countdown seconds (integer): ";
                    auto t = readLineWithEsc();
                    if (t.first) { cout << "\nCancelled setting seconds.\n"; break; }
                    try { int s = stoi(t.second); if (s > 0) modes.countdownSeconds = s; else cout << "Invalid seconds; kept previous.\n"; }
                    catch (...) { cout << "Invalid entry; kept previous.\n"; }
                }
                break;
            case 0: return;
            default: cout << "Invalid choice.\n"; break;
        }
    }
}

// ====== Quiz logic ======
void startQuiz(Difficulty difficulty, const Modes &modes) {
    // Build card pool (exclude small kana from quiz)
    vector<Flashcard> pool;
    pool.reserve(flashcards.size());
    for (const auto &c : flashcards) {
        if (c.romaji.find("(small)") != string::npos) continue; // keep in list but not in quiz
        pool.push_back(c);
    }

    if (pool.empty()) {
        cout << "No quizable cards available.\n";
        return;
    }

    // Determine number of questions
    size_t numQuestions = pool.size();
    if (difficulty == DAILY) numQuestions = min<size_t>(10, pool.size());
    else if (difficulty == BEGINNER) numQuestions = min<size_t>(20, pool.size()); // cap for safety

    // shuffle pool
    random_device rd;
    mt19937 g(rd());
    shuffle(pool.begin(), pool.end(), g);
    if (pool.size() > numQuestions) pool.resize(numQuestions);

    int correct = 0;
    vector<Flashcard> wrongs;

    cout << "\n(Press ESC anytime to abort the quiz and return to menu)\n";

    // If countdown mode is on, start countdown (user can abort)
    bool abortedByEsc = false;
    if (modes.countdown) {
        cout << "Countdown starts now for " << modes.countdownSeconds << " seconds. Press ESC to cancel countdown and return.\n";
        bool esc = countdownWaitWithEsc(modes.countdownSeconds);
        if (esc) {
            cout << "\nCountdown aborted by ESC. Returning to menu.\n";
            return;
        } else {
            cout << "Countdown finished. Starting quiz now.\n";
        }
    }

    // Start timing manually (elapsed time)
    auto startTime = chrono::high_resolution_clock::now();

    for (size_t idx = 0; idx < pool.size(); ++idx) {
        const Flashcard &card = pool[idx];
        string displayQuestion;
        string expectedAnswer; // normalized romaji OR kana depending on mode
        bool acceptKanaAsAnswer = false;

        // Determine what to display and what to expect
        if (modes.reverse) {
            // show romaji, expect kana (either hiragana or katakana depending on expert/filters)
            displayQuestion = card.quizRomaji;
            if (modes.expert) {
                // expert: randomly pick one script to expect
                if (rand() % 2 == 0) expectedAnswer = card.hiragana;
                else expectedAnswer = card.katakana;
                acceptKanaAsAnswer = true;
            } else {
                // non-expert: accept either kana form
                expectedAnswer = card.hiragana + "|" + card.katakana; // special delimiter
                acceptKanaAsAnswer = true;
            }
        } else {
            // normal direction: show kana, expect romaji
            if (modes.expert) {
                // show one script randomly (or obey onlyHira/onlyKata)
                bool pickHira;
                if (modes.onlyHira && !modes.onlyKata) pickHira = true;
                else if (modes.onlyKata && !modes.onlyHira) pickHira = false;
                else pickHira = (rand() % 2 == 0);
                if (pickHira) displayQuestion = card.hiragana, expectedAnswer = card.quizRomaji;
                else displayQuestion = card.katakana, expectedAnswer = card.quizRomaji;
            } else {
                // Show both unless user selected onlyHira/onlyKata
                if (modes.onlyHira && !modes.onlyKata) displayQuestion = card.hiragana;
                else if (modes.onlyKata && !modes.onlyHira) displayQuestion = card.katakana;
                else displayQuestion = card.hiragana + " / " + card.katakana;
                expectedAnswer = card.quizRomaji;
            }
        }

        cout << "\nQuestion " << (idx+1) << " of " << pool.size() << ": " << displayQuestion << "\n> ";

        auto inputRes = readLineWithEsc();
        if (inputRes.first) { // ESC pressed
            cout << "\nQuiz aborted by ESC. Returning to menu.\n";
            abortedByEsc = true;
            break;
        }
        string userInput = inputRes.second;
        string normInput = normalizeInput(userInput);

        bool correctThis = false;
        if (acceptKanaAsAnswer) {
            // user may have entered kana or romaji; accept either if matches
            // if expectedAnswer contains '|' we treat as "either" (both kana forms allowed)
            if (expectedAnswer.find('|') != string::npos) {
                // compare raw input (not normalized) to either kana directly
                string k1 = card.hiragana, k2 = card.katakana;
                if (userInput == k1 || userInput == k2) correctThis = true;
                // also accept romaji typed as romaji
                if (!correctThis && normalizeInput(userInput) == normalizeInput(card.quizRomaji)) correctThis = true;
            } else {
                // expectedAnswer is a single kana string
                if (userInput == expectedAnswer) correctThis = true;
                if (!correctThis && normalizeInput(userInput) == normalizeInput(card.quizRomaji)) correctThis = true;
            }
        } else {
            // expecting romaji: compare normalized strings
            if (normalizeInput(expectedAnswer) == normInput) correctThis = true;
        }

        if (correctThis) {
            correct++;
            if (modes.review) cout << "Correct!\n";
        } else {
            if (modes.review) {
                if (acceptKanaAsAnswer) {
                    cout << "Wrong! Expected: ";
                    if (expectedAnswer.find('|') != string::npos) cout << card.hiragana << " or " << card.katakana << " (" << card.quizRomaji << ")\n";
                    else cout << expectedAnswer << " (" << card.quizRomaji << ")\n";
                } else {
                    cout << "Wrong! Correct answer: " << expectedAnswer << "\n";
                }
            }
            wrongs.push_back(card);
        }

        // small safe guard: if user toggles both filters on and it ends up zero cards, we would have returned earlier;
        // also provide an optional small pause? skip for console speed.
    }

    auto endTime = chrono::high_resolution_clock::now();
    double elapsed = chrono::duration<double>(endTime - startTime).count();

    if (!abortedByEsc) {
        cout << "\nScore: " << correct << " / " << pool.size() << "\n";
        if (modes.timed) {
            cout << "Elapsed time: " << elapsed << " seconds\n";
            recordTime(elapsed, difficulty);
        }
        if (!wrongs.empty()) {
            cout << "You missed " << wrongs.size() << " cards. Use 'Review Mode' ON to see more feedback during quizzes.\n";
        }
    }
}

// ====== Record times ======
void recordTime(double timeTaken, Difficulty difficulty) {
    string key = (difficulty == BEGINNER ? "Beginner" :
                 (difficulty == INTERMEDIATE ? "Intermediate" : "Daily"));
    topTimes[key].push_back(timeTaken);
    sort(topTimes[key].begin(), topTimes[key].end());
    if (topTimes[key].size() > 3) topTimes[key].resize(3);
}

// ====== main ======
int main() {
    srand(static_cast<unsigned>(time(nullptr)));

#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    Modes modes;
    loadSettings(modes);
    loadTopTimes();

    // Show kana list automatically on start (as requested)
    showKanaList();

    while (true) {
        showMainMenu();
        cout << "\nSelect an option (or press ESC to exit): ";
        auto res = readLineWithEsc();
        if (res.first) {
            // ESC pressed -> exit and save
            saveSettings(modes);
            saveTopTimes();
            cout << "\nESC pressed — saving and exiting. Goodbye!\n";
            return 0;
        }
        string choiceStr = res.second;
        if (choiceStr.empty()) { cout << "No input given. Try again.\n"; continue; }
        int choice = -1;
        try { choice = stoi(choiceStr); } catch (...) { cout << "Invalid input; enter a number.\n"; continue; }

        switch (choice) {
            case 1: startQuiz(BEGINNER, modes); break;
            case 2: startQuiz(INTERMEDIATE, modes); break;
            case 3: startQuiz(DAILY, modes); break;
            case 4: showKanaList(); break;
            case 5: showTopTimes(); break;
            case 6: showSettingsMenu(modes); break;
            case 0:
                saveSettings(modes);
                saveTopTimes();
                cout << "Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
                break;
        }
    }

    return 0;
}


// Add a review wrong answers routine that re-asks incorrect cards until the user gets them right or ESCs.
// Move the kana data to a .txt file so you can edit/expand without recompiling