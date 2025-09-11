
// Unified Kana + Vocabulary Flashcard Program
// Includes:
// - Kana quizzes (with reverse, onlyHira/onlyKata, timed, hints, expert, countdown)
// - Vocabulary quizzes (with pitch accent + notes support)
// - Settings menu for toggles
// - Kana + Vocabulary list viewing
// - Top times tracking
// - ESC universal input handling

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
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;

// ===================== Structures =====================

struct Kana {
    string hira;
    string kata;
    string romaji;
};

struct Word {
    string kana;
    string kata;
    string romaji;
    string english;
    string pitch;   // pitch accent info
    string notes;   // optional notes/context
};

struct Settings {
    bool timed = false;
    bool showHints = false;
    bool showTimer = false;
    string difficulty = "normal"; // "normal" or "expert"
};

struct Modes {
    bool reverse = false;
    bool onlyHira = false;
    bool onlyKata = false;
    bool countdown = false;
};

struct Scores {
    unordered_map<string, double> bestTimes; // quizType -> seconds
};

// ===================== Globals =====================

vector<Kana> kanaList = {
    // Vowels
    {"あ","ア","a"}, {"い","イ","i"}, {"う","ウ","u"}, {"え","エ","e"}, {"お","オ","o"},

    // K consonant
    {"か","カ","ka"}, {"き","キ","ki"}, {"く","ク","ku"}, {"け","ケ","ke"}, {"こ","コ","ko"},
    {"が","ガ","ga"}, {"ぎ","ギ","gi"}, {"ぐ","グ","gu"}, {"げ","ゲ","ge"}, {"ご","ゴ","go"},

    // S consonant
    {"さ","サ","sa"}, {"し","シ","shi"}, {"す","ス","su"}, {"せ","セ","se"}, {"そ","ソ","so"},
    {"ざ","ザ","za"}, {"じ","ジ","ji"}, {"ず","ズ","zu"}, {"ぜ","ゼ","ze"}, {"ぞ","ゾ","zo"},

    // T consonant
    {"た","タ","ta"}, {"ち","チ","chi"}, {"つ","ツ","tsu"}, {"て","テ","te"}, {"と","ト","to"},
    {"だ","ダ","da"}, {"ぢ","ヂ","ji"}, {"づ","ヅ","zu"}, {"で","デ","de"}, {"ど","ド","do"},

    // N consonant
    {"な","ナ","na"}, {"に","ニ","ni"}, {"ぬ","ヌ","nu"}, {"ね","ネ","ne"}, {"の","ノ","no"},

    // H consonant
    {"は","ハ","ha"}, {"ひ","ヒ","hi"}, {"ふ","フ","fu"}, {"へ","ヘ","he"}, {"ほ","ホ","ho"},
    {"ば","バ","ba"}, {"び","ビ","bi"}, {"ぶ","ブ","bu"}, {"べ","ベ","be"}, {"ぼ","ボ","bo"},
    {"ぱ","パ","pa"}, {"ぴ","ピ","pi"}, {"ぷ","プ","pu"}, {"ぺ","ペ","pe"}, {"ぽ","ポ","po"},

    // M consonant
    {"ま","マ","ma"}, {"み","ミ","mi"}, {"む","ム","mu"}, {"め","メ","me"}, {"も","モ","mo"},

    // Y consonant
    {"や","ヤ","ya"}, {"ゆ","ユ","yu"}, {"よ","ヨ","yo"},

    // R consonant
    {"ら","ラ","ra"}, {"り","リ","ri"}, {"る","ル","ru"}, {"れ","レ","re"}, {"ろ","ロ","ro"},

    // W consonant
    {"わ","ワ","wa"}, {"を","ヲ","wo"},

    // N
    {"ん","ン","n"},

    // Small kana
    {"ゃ","ャ","ya (small)"}, {"ゅ","ュ","yu (small)"}, {"ょ","ョ","yo (small)"},
    {"ぁ","ァ","a (small)"}, {"ぃ","ィ","i (small)"}, {"ぅ","ゥ","u (small)"},
    {"ぇ","ェ","e (small)"}, {"ぉ","ォ","o (small)"}, {"っ","ッ","tsu (small)"}
};


vector<Word> wordList = {
    // Vowels
    {"あい","", "ai", "love", "", "H"},
    {"あお","", "ao", "blue", "", "H"},
    {"あし","", "ashi", "foot", "", "A"},
    {"いえ","", "ie", "house", "", "H"},
    {"いす","", "isu", "chair", "", "H"},
    {"いぬ","", "inu", "dog", "", "H"},
    {"うみ","", "umi", "sea", "", "H"},
    {"うた","", "uta", "song", "", "A"},
    {"うし","", "ushi", "cow", "", "H"},
    {"えき","", "eki", "station", "", "A"},
    {"えん","", "en", "yen", "", "A"},
    {"えび","", "ebi", "shrimp", "", "H"},
    {"おか","", "oka", "hill", "", "A"},
    {"おと","", "oto", "sound", "", "A"},
    {"おに","", "oni", "demon", "", "H"},

    // K consonant
    {"かさ","", "kasa", "umbrella", "", "A"},
    {"かみ","", "kami", "paper", "", "H"},
    {"かお","", "kao", "face", "", "A"},
    {"きく","", "kiku", "chrysanthemum", "", "H"},
    {"きの","", "kino", "tree's", "", "H"},
    {"きり","", "kiri", "fog", "", "H"},
    {"くも","", "kumo", "cloud", "", "A"},
    {"くち","", "kuchi", "mouth", "", "A"},
    {"くさ","", "kusa", "grass", "", "A"},
    {"けむ","", "kemu", "smoke", "", "H"},
    {"けし","", "keshi", "poppy", "", "H"},
    {"けん","", "ken", "sword", "", "A"},
    {"こめ","", "kome", "rice", "", "A"},
    {"こと","", "koto", "thing", "", "H"},
    {"こえ","", "koe", "voice", "", "A"},

    // S consonant
    {"さけ","", "sake", "alcohol", "", "A"},
    {"さる","", "saru", "monkey", "", "A"},
    {"さち","", "sachi", "happiness", "", "A"},
    {"しお","", "shio", "salt", "", "A"},
    {"しろ","", "shiro", "white", "", "H"},
    {"しま","", "shima", "island", "", "H"},
    {"すし","", "sushi", "sushi", "", "H"},
    {"すな","", "suna", "sand", "", "A"},
    {"すき","", "suki", "like", "", "H"},
    {"せき","", "seki", "seat", "", "A"},
    {"せみ","", "semi", "cicada", "", "H"},
    {"せん","", "sen", "thousand", "", "A"},
    {"そら","", "sora", "sky", "", "A"},
    {"そう","", "sou", "layer", "", "H"},
    {"そく","", "soku", "speed", "", "A"},

    // T consonant
    {"たま","", "tama", "ball", "", "A"},
    {"たい","", "tai", "sea bream", "", "H"},
    {"たけ","", "take", "bamboo", "", "A"},
    {"ちち","", "chichi", "father", "", "A"},
    {"ちか","", "chika", "basement", "", "A"},
    {"ちず","", "chizu", "map", "", "H"},
    {"つき","", "tsuki", "moon", "", "A"},
    {"つち","", "tsuchi", "earth", "", "A"},
    {"つめ","", "tsume", "nail", "", "A"},
    {"てん","", "ten", "heaven", "", "A"},
    {"てつ","", "tetsu", "iron", "", "A"},
    {"てら","", "tera", "temple", "", "A"},
    {"とり","", "tori", "bird", "", "H"},
    {"とお","", "too", "ten", "", "H"},
    {"とし","", "toshi", "year", "", "A"},

    // N consonant
    {"なつ","", "natsu", "summer", "", "A"},
    {"なみ","", "nami", "wave", "", "H"},
    {"なに","", "nani", "what", "", "H"},
    {"にく","", "niku", "meat", "", "A"},
    {"にわ","", "niwa", "garden", "", "H"},
    {"にん","", "nin", "person", "", "A"},
    {"ぬの","", "nuno", "cloth", "", "H"},
    {"ぬま","", "numa", "swamp", "", "A"},
    {"ぬけ","", "nuke", "escape", "", "A"},
    {"ねこ","", "neko", "cat", "", "A"},
    {"ねず","", "nezu", "mouse", "", "A"},
    {"ねん","", "nen", "year", "", "A"},
    {"のき","", "noki", "eaves", "", "A"},
    {"のり","", "nori", "seaweed", "", "H"},
    {"のう","", "nou", "brain", "", "H"},

    // H consonant
    {"はな","", "hana", "flower/nose", "", "A"},
    {"はや","", "haya", "fast", "", "A"},
    {"はし","", "hashi", "bridge/chopsticks", "", "H"},
    {"ひか","", "hika", "shine", "", "A"},
    {"ひと","", "hito", "person", "", "A"},
    {"ひる","", "hiru", "daytime", "", "H"},
    {"ふね","", "fune", "boat", "", "A"},
    {"ふく","", "fuku", "clothes", "", "A"},
    {"ふゆ","", "fuyu", "winter", "", "H"},
    {"へや","", "heya", "room", "", "O"},
    {"へん","", "hen", "strange", "", "A"},
    {"ほし","", "hoshi", "star", "", "A"},
    {"ほね","", "hone", "bone", "", "A"},
    {"ほう","", "hou", "direction/law", "", "H"},

    // M consonant
    {"まち","", "machi", "town", "", "A"},
    {"まめ","", "mame", "bean", "", "A"},
    {"まる","", "maru", "circle", "", "A"},
    {"みみ","", "mimi", "ear", "", "H"},
    {"みず","", "mizu", "water", "", "A"},
    {"みち","", "michi", "road", "", "A"},
    {"めが","", "mega", "eye", "", "A"},
    {"めし","", "meshi", "meal", "", "A"},
    {"もり","", "mori", "forest", "", "H"},
    {"もも","", "momo", "peach", "", "H"},
    {"もく","", "moku", "tree/wood", "", "A"},

    // Y consonant
    {"やま","", "yama", "mountain", "", "A"},
    {"やみ","", "yami", "darkness", "", "A"},
    {"やね","", "yane", "roof", "", "A"},
    {"ゆき","", "yuki", "snow", "", "A"},
    {"ゆめ","", "yume", "dream", "", "A"},
    {"ゆび","", "yubi", "finger", "", "H"},
    {"よる","", "yoru", "night", "", "A"},
    {"よこ","", "yoko", "side", "", "A"},
    {"よみ","", "yomi", "reading", "", "A"},

    // R consonant
    {"らく","", "raku", "comfort", "", "A"},
    {"らい","", "rai", "next", "", "H"},
    {"りん","", "rin", "bell", "", "A"},
    {"るい","", "rui", "type/kind", "", "H"},
    {"れい","", "rei", "example", "", "H"},
    {"ろう","", "rou", "old/elderly", "", "H"},

    // W consonant
    {"わた","", "wata", "cotton", "", "A"},
    {"わに","", "wani", "crocodile", "", "A"},
    {"をか","", "woka", "phrase placeholder", "", "A"},

    // N
    {"ん","", "n", "syllabic n", "", "H"},

    // Small kana words
    {"きゃく","", "kyaku", "guest", "", "A"},
    {"きゅう","", "kyuu", "nine/urgent", "", "H"},
    {"きょう","", "kyou", "today", "", "O"},
    {"しゃしん","", "shashin", "photo", "", "H"},
    {"しゅくだい","", "shukudai", "homework", "", "O"},
    {"しょう","", "shou", "prize/small", "", "H"}
};


Settings settings;
Modes modes;
Scores scores;

// ===================== Utility =====================

string toLower(const string &s) {
    string out = s;
    transform(out.begin(), out.end(), out.begin(), ::tolower);
    return out;
}

string trim(const string &s) {
    size_t start = s.find_first_not_of(" \t\n\r");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\n\r");
    return s.substr(start, end - start + 1);
}

bool equalsIgnoreCase(const string &a, const string &b) {
    return toLower(trim(a)) == toLower(trim(b));
}

// Cross-platform ESC-enabled input
bool readLineWithEsc(string &input) {
#ifdef _WIN32
    input.clear();
    while (true) {
        int ch = _getch();
        if (ch == 27) return false; // ESC key
        if (ch == '\r') break;
        if (ch == '\b') {
            if (!input.empty()) input.pop_back();
            continue;
        }
        input.push_back((char)ch);
        cout << (char)ch;
    }
    cout << "\n";
#else
    input.clear();
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    char ch;
    while (true) {
        if (read(STDIN_FILENO, &ch, 1) < 1) continue;
        if (ch == 27) { // ESC
            tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
            return false;
        }
        if (ch == '\n') break;
        if (ch == 127) { // backspace
            if (!input.empty()) input.pop_back();
            continue;
        }
        input.push_back(ch);
        cout << ch;
    }
    cout << "\n";
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
#endif
    return true;
}

void saveScores() {
    ofstream out("scores.txt");
    for (auto &p : scores.bestTimes) {
        out << p.first << " " << p.second << "\n";
    }
}

void loadScores() {
    ifstream in("scores.txt");
    if (!in) return;
    string quiz;
    double time;
    while (in >> quiz >> time) {
        scores.bestTimes[quiz] = time;
    }
}

void updateBestTime(const string &quizType, double seconds) {
    if (scores.bestTimes.find(quizType) == scores.bestTimes.end() || seconds < scores.bestTimes[quizType]) {
        scores.bestTimes[quizType] = seconds;
        cout << "🎉 New record for " << quizType << ": " << seconds << "s!\n";
    }
}

// ===================== Quizzes =====================

void runKanaQuiz() {
    cout << "\n--- Kana Quiz ---\n(ESC to quit)\n";

    auto start = chrono::steady_clock::now();
    int correct = 0;

    random_device rd;
    mt19937 g(rd());
    shuffle(kanaList.begin(), kanaList.end(), g);

    for (auto &k : kanaList) {
        string prompt, answer;
        if (modes.reverse) {
            prompt = k.romaji;
            answer = k.hira; // default to hira
            if (modes.onlyKata) answer = k.kata;
        } else {
            if (modes.onlyHira) prompt = k.hira;
            else if (modes.onlyKata) prompt = k.kata;
            else prompt = k.hira + " / " + k.kata;
            answer = k.romaji;
        }

        cout << "Q: " << prompt << "\n> ";
        string user;

        if (settings.timed || modes.countdown) {
            auto qStart = chrono::steady_clock::now();
            if (!readLineWithEsc(user)) return;
            auto qEnd = chrono::steady_clock::now();
            int elapsed = chrono::duration_cast<chrono::seconds>(qEnd - qStart).count();
            if (settings.timed && elapsed > 5) {
                cout << "⏳ Time's up! Correct: " << answer << "\n";
                continue;
            }
        } else {
            if (!readLineWithEsc(user)) return;
        }

        if (equalsIgnoreCase(user, answer)) {
            cout << "✔ Correct!\n";
            correct++;
        } else {
            cout << "✘ Wrong! Answer: " << answer << "\n";
        }
    }

    auto end = chrono::steady_clock::now();
    double elapsed = chrono::duration_cast<chrono::seconds>(end - start).count();
    cout << "Score: " << correct << "/" << kanaList.size() << " in " << elapsed << "s\n";
    updateBestTime("KanaQuiz", elapsed);
}

void runWordQuiz() {
    cout << "\n--- Vocabulary Quiz ---\n(ESC to quit)\n";

    auto start = chrono::steady_clock::now();
    int correct = 0;

    random_device rd;
    mt19937 g(rd());
    shuffle(vocabWords.begin(), vocabWords.end(), g);

    for (auto &w : vocabWords) {
        string prompt = w.kana + " (" + w.kata + ")";
        cout << "Q: " << prompt << " [" << w.pitch << "]\n> ";
        string user;
        if (!readLineWithEsc(user)) return;

        if (equalsIgnoreCase(user, w.romaji) || equalsIgnoreCase(user, w.english)) {
            cout << "✔ Correct! (" << w.english << ")\n";
            correct++;
        } else {
            cout << "✘ Wrong! Romaji: " << w.romaji << " | English: " << w.english << "\n";
        }
    }

    auto end = chrono::steady_clock::now();
    double elapsed = chrono::duration_cast<chrono::seconds>(end - start).count();
    cout << "Score: " << correct << "/" << vocabWords.size() << " in " << elapsed << "s\n";
    updateBestTime("WordQuiz", elapsed);
}

// ===================== Menus =====================

void showKanaList() {
    cout << "\n--- Kana List ---\n";
    for (auto &k : kanaList) {
        cout << k.hira << " | " << k.kata << " | " << k.romaji << "\n";
    }
}

void showWordList() {
    cout << "\n--- Vocabulary List ---\n";
    for (auto &w : vocabWords) {
        cout << w.kana << " | " << w.kata << " | " << w.romaji << " = " << w.english;
        if (!w.pitch.empty()) cout << " [" << w.pitch << "]";
        if (!w.notes.empty()) cout << " {" << w.notes << "}";
        cout << "\n";
    }
}

void settingsMenu() {
    int choice;
    while (true) {
        cout << "\n--- Settings ---\n";
        cout << "1. Toggle Reverse (" << (modes.reverse ? "ON" : "OFF") << ")\n";
        cout << "2. Toggle Only Hira (" << (modes.onlyHira ? "ON" : "OFF") << ")\n";
        cout << "3. Toggle Only Kata (" << (modes.onlyKata ? "ON" : "OFF") << ")\n";
        cout << "4. Toggle Timed (" << (settings.timed ? "ON" : "OFF") << ")\n";
        cout << "5. Toggle Countdown (" << (modes.countdown ? "ON" : "OFF") << ")\n";
        cout << "6. Toggle Hints (" << (settings.showHints ? "ON" : "OFF") << ")\n";
        cout << "7. Difficulty (" << settings.difficulty << ")\n";
        cout << "8. Back\n";
        cout << "> ";
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore();
        if (choice == 1) modes.reverse = !modes.reverse;
        else if (choice == 2) modes.onlyHira = !modes.onlyHira;
        else if (choice == 3) modes.onlyKata = !modes.onlyKata;
        else if (choice == 4) settings.timed = !settings.timed;
        else if (choice == 5) modes.countdown = !modes.countdown;
        else if (choice == 6) settings.showHints = !settings.showHints;
        else if (choice == 7) {
            if (settings.difficulty == "normal") settings.difficulty = "expert";
            else settings.difficulty = "normal";
        }
        else if (choice == 8) break;
    }
}

void mainMenu() {
    int choice;
    while (true) {
        cout << "\n=== Kana & Vocabulary Flashcards ===\n";
        cout << "1. Kana Quiz\n";
        cout << "2. Vocabulary Quiz\n";
        cout << "3. Kana List\n";
        cout << "4. Vocabulary List\n";
        cout << "5. Settings\n";
        cout << "6. Exit\n";
        cout << "> ";
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore();
        if (choice == 1) runKanaQuiz();
        else if (choice == 2) runWordQuiz();
        else if (choice == 3) showKanaList();
        else if (choice == 4) showWordList();
        else if (choice == 5) settingsMenu();
        else if (choice == 6) { saveScores(); break; }
    }
}

// ===================== Main =====================

int main() {
    loadScores();
    mainMenu();
    return 0;
}
