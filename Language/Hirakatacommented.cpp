// flashcardbase.cpp
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

#ifdef _WIN32
#include <windows.h>
#endif

using namespace std;

// ====== Structures ======
struct Flashcard {
    string hiragana;
    string katakana;
    string romaji;      // Display name
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
    bool reverse = false;
    bool expert = false;
    bool onlyHira = false;
    bool onlyKata = false;
    bool countdown = false;
    int countdownSeconds = 30;
};

// ====== Globals ======
vector<Flashcard> flashcards = {
    // Vowels
    {"あ", "ア", "a", "a"}, {"い", "イ", "i", "i"}, {"う", "ウ", "u", "u"}, {"え", "エ", "e", "e"}, {"お", "オ", "o", "o"},

    // K consonant
    {"か", "カ", "ka", "ka"}, {"き", "キ", "ki", "ki"}, {"く", "ク", "ku", "ku"}, {"け", "ケ", "ke", "ke"}, {"こ", "コ", "ko", "ko"},
    {"が", "ガ", "ga", "ga"}, {"ぎ", "ギ", "gi", "gi"}, {"ぐ", "グ", "gu", "gu"}, {"げ", "ゲ", "ge", "ge"}, {"ご", "ゴ", "go", "go"},

    // S consonant
    {"さ", "サ", "sa", "sa"}, {"し", "シ", "shi", "shi"}, {"す", "ス", "su", "su"}, {"せ", "セ", "se", "se"}, {"そ", "ソ", "so", "so"},
    {"ざ", "ザ", "za", "za"}, {"じ", "ジ", "ji", "ji"}, {"ず", "ズ", "zu", "zu"}, {"ぜ", "ゼ", "ze", "ze"}, {"ぞ", "ゾ", "zo", "zo"},

    // T consonant
    {"た", "タ", "ta", "ta"}, {"ち", "チ", "chi", "chi"}, {"つ", "ツ", "tsu", "tsu"}, {"て", "テ", "te", "te"}, {"と", "ト", "to", "to"},
    {"だ", "ダ", "da", "da"}, {"ぢ", "ヂ", "ji", "ji"}, {"づ", "ヅ", "zu", "zu"}, {"で", "デ", "de", "de"}, {"ど", "ド", "do", "do"},

    // N consonant
    {"な", "ナ", "na", "na"}, {"に", "ニ", "ni", "ni"}, {"ぬ", "ヌ", "nu", "nu"}, {"ね", "ネ", "ne", "ne"}, {"の", "ノ", "no", "no"},

    // H consonant
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

    // Small kana
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
string normalizeInput(string s);

// ====== Main ======
int main() {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif

    Modes modes;
    loadSettings(modes);
    loadTopTimes();

    showKanaList();

    while (true) {
        showMainMenu();
        cout << "\nSelect an option: ";
        int choice;
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
            default: cout << "Invalid choice.\n";
        }
    }
}

// ====== Settings & File I/O ======
void loadSettings(Modes &modes) {
    ifstream in("settings.txt");
    if (!in) return;
    in >> modes.timed >> modes.review >> modes.reverse >> modes.expert
       >> modes.onlyHira >> modes.onlyKata >> modes.countdown >> modes.countdownSeconds;
}

void saveSettings(const Modes &modes) {
    ofstream out("settings.txt");
    out << modes.timed << " " << modes.review << " " << modes.reverse << " " << modes.expert << " "
        << modes.onlyHira << " " << modes.onlyKata << " " << modes.countdown << " " << modes.countdownSeconds;
}

void loadTopTimes() {
    ifstream in("toptimes.txt");
    if (!in) return;
    string mode; double time;
    while (in >> mode >> time) {
        topTimes[mode].push_back(time);
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

// ====== Helpers ======
string normalizeInput(string s) {
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    size_t pos;
    while ((pos = s.find(" (small)")) != string::npos) {
        s.erase(pos, 8);
    }
    return s;
}

void showKanaList() {
    cout << "\n==== Kana List ====\n";
    for (const auto &card : flashcards) {
        cout << "H: " << card.hiragana << "\tK: " << card.katakana << "\tR: " << card.romaji << "\n";
    }
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
        cout << "1. Toggle Timed Mode (" << (modes.timed ? "ON" : "OFF") << ")\n";
        cout << "2. Toggle Review Mode (" << (modes.review ? "ON" : "OFF") << ")\n";
        cout << "3. Toggle Reverse Mode (" << (modes.reverse ? "ON" : "OFF") << ")\n";
        cout << "4. Toggle Expert Mode (" << (modes.expert ? "ON" : "OFF") << ")\n";
        cout << "5. Toggle Hiragana Only (" << (modes.onlyHira ? "ON" : "OFF") << ")\n";
        cout << "6. Toggle Katakana Only (" << (modes.onlyKata ? "ON" : "OFF") << ")\n";
        cout << "7. Toggle Countdown Timer (" << (modes.countdown ? "ON" : "OFF") << ") - Seconds: " << modes.countdownSeconds << "\n";
        cout << "0. Return\n> ";
        cin >> input;

        switch (input) {
            case 1: modes.timed = !modes.timed; break;
            case 2: modes.review = !modes.review; break;
            case 3: modes.reverse = !modes.reverse; break;
            case 4: modes.expert = !modes.expert; break;
            case 5: modes.onlyHira = !modes.onlyHira; break;
            case 6: modes.onlyKata = !modes.onlyKata; break;
            case 7: modes.countdown = !modes.countdown;
                    if (modes.countdown) {
                        cout << "Enter countdown seconds: ";
                        cin >> modes.countdownSeconds;
                    }
                    break;
            case 0: return;
            default: cout << "Invalid input.\n";
        }
    }
}

void startQuiz(Difficulty difficulty, const Modes &modes) {
    vector<Flashcard> cards;
    for (auto &c : flashcards) {
        bool isSmall = c.romaji.find("(small)") != string::npos;
        if (isSmall) continue; // skip small kana in quiz

        if (modes.onlyHira && modes.onlyKata) {
            // fail-safe: allow all
        } else if (modes.onlyHira && c.katakana != "") {
            cards.push_back(c);
        } else if (modes.onlyKata && c.hiragana != "") {
            cards.push_back(c);
        } else if (!modes.onlyHira && !modes.onlyKata) {
            cards.push_back(c);
        }
    }

    if (difficulty == DAILY && cards.size() > 10) {
        random_shuffle(cards.begin(), cards.end());
        cards.resize(10);
    }

    random_shuffle(cards.begin(), cards.end());

    int correct = 0;
    vector<Flashcard> wrongAnswers;

    auto start = chrono::high_resolution_clock::now();

    for (auto &card : cards) {
        string question, answer;
        if (modes.reverse) {
            question = card.quizRomaji;
            answer = modes.expert ? (rand() % 2 ? card.hiragana : card.katakana) : card.hiragana + " / " + card.katakana;
        } else {
            if (modes.expert) {
                if (rand() % 2) {
                    question = card.hiragana;
                    answer = card.quizRomaji;
                } else {
                    question = card.katakana;
                    answer = card.quizRomaji;
                }
            } else {
                question = card.hiragana + " / " + card.katakana;
                answer = card.quizRomaji;
            }
        }

        cout << "Question: " << question << "\n> ";
        string input;
        getline(cin, input);

        if (normalizeInput(input) == normalizeInput(answer)) {
            if (modes.review) cout << "Correct!\n";
            correct++;
        } else {
            if (modes.review) cout << "Wrong! Correct answer: " << answer << "\n";
            wrongAnswers.push_back(card);
        }
    }

    auto end = chrono::high_resolution_clock::now();
    double timeTaken = chrono::duration<double>(end - start).count();

    cout << "\nScore: " << correct << " / " << cards.size() << "\n";

    if (modes.timed) {
        cout << "Time taken: " << timeTaken << " seconds\n";
        recordTime(timeTaken, difficulty);
    }
}

void recordTime(double timeTaken, Difficulty difficulty) {
    string key = (difficulty == BEGINNER ? "Beginner" :
                 (difficulty == INTERMEDIATE ? "Intermediate" : "Daily"));
    topTimes[key].push_back(timeTaken);
    sort(topTimes[key].begin(), topTimes[key].end());
    if (topTimes[key].size() > 3) topTimes[key].resize(3);
}

void showTopTimes() {
    cout << "\n==== Top 3 Times per Mode ====\n";
    for (auto &entry : topTimes) {
        cout << entry.first << " mode:\n";
        for (size_t i = 0; i < entry.second.size(); ++i) {
            cout << "  " << i + 1 << ". " << entry.second[i] << " seconds\n";
        }
    }
}
