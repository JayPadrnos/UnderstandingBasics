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
  #include <conio.h>
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
    string kanji;       
    string meaning;     
    string context;     
    string category;    
    string pitch; 
};

struct Word {
    string kana;       // hiragana or katakana
    string kanji;      // optional kanji
    string romaji;     // phonetic
    string english;    // meaning
    string hint;       // optional context/hint
    string pitch;      // pitch accent pattern ("HL" "LH" "LHL")
};

// ====== Enums ======
enum Difficulty { BEGINNER, INTERMEDIATE, DAILY };
enum QuizMode { KANA_ONLY, KANJI_ONLY, ROMAJI_ONLY, CONTEXT_ONLY, FULL_RANDOM, WORDS_ONLY };

struct Modes {
    bool timed = false;
    bool review = false;
    bool reverse = false;
    bool expert = false;
    bool onlyHira = false;
    bool onlyKata = false;
    bool countdown = false;
    int countdownSeconds = 30;
    QuizMode quizMode = KANA_ONLY; // default
    bool wordQuizRomaji = true;    // true: answer in romaji, false: answer in English
};

// ====== Globals ======
vector<Flashcard> flashcards = {
    // KANA DATABASE HERE
    // Vowels a i u e o
    {"あ","ア","a","a","","","", ""},
    {"い","イ","i","i","","","", ""},
    {"う","ウ","u","u","","","", ""},
    {"え","エ","e","e","","","", ""},
    {"お","オ","o","o","","","", ""},

    // K consonant + voiced
    {"か","カ","ka","ka","","","", ""},{"き","キ","ki","ki","","","", ""},{"く","ク","ku","ku","","","", ""},{"け","ケ","ke","ke","","","", ""},{"こ","コ","ko","ko","","","", ""},
    {"が","ガ","ga","ga","","","", ""},{"ぎ","ギ","gi","gi","","","", ""},{"ぐ","グ","gu","gu","","","", ""},{"げ","ゲ","ge","ge","","","", ""},{"ご","ゴ","go","go","","","", ""},

    // S consonant + voiced
    {"さ","サ","sa","sa","","","", ""},{"し","シ","shi","shi","","","", ""},{"す","ス","su","su","","","", ""},{"せ","セ","se","se","","","", ""},{"そ","ソ","so","so","","","", ""},
    {"ざ","ザ","za","za","","","", ""},{"じ","ジ","ji","ji","","","", ""},{"ず","ズ","zu","zu","","","", ""},{"ぜ","ゼ","ze","ze","","","", ""},{"ぞ","ゾ","zo","zo","","","", ""},

    // T consonant + voiced
    {"た","タ","ta","ta","","","", ""},{"ち","チ","chi","chi","","","", ""},{"つ","ツ","tsu","tsu","","","", ""},{"て","テ","te","te","","","", ""},{"と","ト","to","to","","","", ""},
    {"だ","ダ","da","da","","","", ""},{"ぢ","ヂ","ji","ji","","","", ""},{"づ","ヅ","zu","zu","","","", ""},{"で","デ","de","de","","","", ""},{"ど","ド","do","do","","","", ""},

    // N consonant
    {"な","ナ","na","na","","","", ""},{"に","ニ","ni","ni","","","", ""},{"ぬ","ヌ","nu","nu","","","", ""},{"ね","ネ","ne","ne","","","", ""},{"の","ノ","no","no","","","", ""},

    // H consonant + voiced + p
    {"は","ハ","ha","ha","","","", ""},{"ひ","ヒ","hi","hi","","","", ""},{"ふ","フ","fu","fu","","","", ""},{"へ","ヘ","he","he","","","", ""},{"ほ","ホ","ho","ho","","","", ""},
    {"ば","バ","ba","ba","","","", ""},{"び","ビ","bi","bi","","","", ""},{"ぶ","ブ","bu","bu","","","", ""},{"べ","ベ","be","be","","","", ""},{"ぼ","ボ","bo","bo","","","", ""},
    {"ぱ","パ","pa","pa","","","", ""},{"ぴ","ピ","pi","pi","","","", ""},{"ぷ","プ","pu","pu","","","", ""},{"ぺ","ペ","pe","pe","","","", ""},{"ぽ","ポ","po","po","","","", ""},

    // M consonant
    {"ま","マ","ma","ma","","","", ""},{"み","ミ","mi","mi","","","", ""},{"む","ム","mu","mu","","","", ""},{"め","メ","me","me","","","", ""},{"も","モ","mo","mo","","","", ""},

    // Y consonant
    {"や","ヤ","ya","ya","","","", ""},{"ゆ","ユ","yu","yu","","","", ""},{"よ","ヨ","yo","yo","","","", ""},

    // R consonant
    {"ら","ラ","ra","ra","","","", ""},{"り","リ","ri","ri","","","", ""},{"る","ル","ru","ru","","","", ""},{"れ","レ","re","re","","","", ""},{"ろ","ロ","ro","ro","","","", ""},

    // W consonant
    {"わ","ワ","wa","wa","","","", ""},{"を","ヲ","wo","wo","","","", ""},

    // N
    {"ん","ン","n","n","","","", ""},

    // Small kana
    {"ゃ","ャ","ya (small)","ya","","","", ""},{"ゅ","ュ","yu (small)","yu","","","", ""},{"ょ","ョ","yo (small)","yo","","","", ""},
    {"ぁ","ァ","a (small)","a","","","", ""},{"ぃ","ィ","i (small)","i","","","", ""},{"ぅ","ゥ","u (small)","u","","","", ""},
    {"ぇ","ェ","e (small)","e","","","", ""},{"ぉ","ォ","o (small)","o","","","", ""},{"っ","ッ","tsu (small)","tsu","","","", ""}
};

vector<Word> vocabWords = {
    // WORDS DATABASE HERE
    // Vowels a i u e o
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

// Small kana (replaced with real words that use them)
{"きゃく","", "kyaku", "guest", "", "A"},
{"きゅう","", "kyuu", "nine/urgent", "", "H"},
{"きょう","", "kyou", "today", "", "O"},
{"しゃしん","", "shashin", "photo", "", "H"},
{"しゅくだい","", "shukudai", "homework", "", "O"},
{"しょう","", "shou", "prize/small", "", "H"}

};

// ====== Helpers ======
string trimWhitespace(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start,end-start+1);
}

string normalizeInput(const string &s) {
    string t;
    for (char c : s) t.push_back(tolower(static_cast<unsigned char>(c)));
    return trimWhitespace(t);
}

#ifdef _WIN32
pair<bool,string> readLineWithEsc() {
    string out;
    while(true){
        int ch=_getch();
        if(ch==27) return {true,""};
        else if(ch=='\r'||ch=='\n'){cout<<'\n';return{false,out};}
        else if(ch=='\b'||ch==127){if(!out.empty()){out.pop_back();cout<<"\b \b";}}
        else{out.push_back(static_cast<char>(ch));cout<<static_cast<char>(ch);}
    }
}
#else
pair<bool,string> readLineWithEsc() { string input; getline(cin,input); return {false,input}; }
#endif

// ====== Display Functions ======
void showKanaList() {
    cout<<"\n==== Kana List ====\n";
    for(const auto &card:flashcards){
        cout<<"H: "<<card.hiragana<<"\tK: "<<card.katakana<<"\tR: "<<card.romaji<<"\n";
    }
}

void showWordList() {
    cout<<"\n==== Vocabulary List ====\n";
    for(const auto &w: vocabWords){
        cout<<"Kana: "<<w.kana<<"\tKanji: "<<w.kanji<<"\tRomaji: "<<w.romaji<<"\tMeaning: "<<w.english<<"\tPitch: "<<w.pitch<<"\n";
    }
}

// ====== Quiz Runner ======
void runQuiz(Modes &modes, int numCards){
    if(modes.quizMode == WORDS_ONLY){
        vector<Word> cards = vocabWords;
        shuffle(cards.begin(), cards.end(), default_random_engine(static_cast<unsigned>(time(nullptr))));
        int correct=0;
        for(int i=0;i<numCards && i<cards.size(); ++i){
            const Word &w = cards[i];
            string prompt = w.kana.empty() ? w.kanji : w.kana;
            string answer = modes.wordQuizRomaji ? w.romaji : w.english;
            cout<<"\nCard "<<i+1<<"/"<<numCards<<": "<<prompt<<"\nYour answer: ";
            auto res = readLineWithEsc();
            if(res.first){cout<<"\n(ESC pressed, quiz aborted)\n"; break;}
            string user = normalizeInput(res.second);
            if(user == normalizeInput(answer)){cout<<"Correct!\n"; ++correct;}
            else cout<<"Wrong. Answer: "<<answer<<"\n";
        }
        cout<<"\nQuiz Complete! Correct: "<<correct<<"/"<<numCards<<"\n";
        return;
    }
    // Implement kana quiz logic similarly…
}

// ====== Main Menu ======
void showMainMenu() {
    cout<<"\n===== Kana Flashcard Menu =====\n";
    cout<<"1. Beginner Quiz\n2. Intermediate Quiz\n3. Daily Quick Run (10 Cards)\n";
    cout<<"4. View Full Kana List\n5. View Top Times\n6. Settings\n";
    cout<<"7. Word Quiz (Vocabulary)\n8. View Vocabulary List\n0. Exit\n";
}

// ====== Main ======
int main(){
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    Modes modes;

    while(true){
        showMainMenu();
        auto res=readLineWithEsc();
        if(res.first){cout<<"\nExiting...\n"; break;}
        string choiceStr=trimWhitespace(res.second);
        int choice=-1;
        try{choice=stoi(choiceStr);}catch(...){cout<<"Invalid input\n"; continue;}

        switch(choice){
            case 1: runQuiz(modes,30); break;
            case 2: runQuiz(modes,50); break;
            case 3: runQuiz(modes,10); break;
            case 4: showKanaList(); break;
            case 5: cout<<"Top times feature not implemented yet.\n"; break;
            case 6: cout<<"Settings menu not implemented yet.\n"; break;
            case 7: { modes.quizMode = WORDS_ONLY; runQuiz(modes,20); break; }
            case 8: showWordList(); break;
            case 0: cout<<"Exiting...\n"; return 0;
            default: cout<<"Invalid choice\n"; break;
        }
    }
    return 0;
}

// Need to add the translated word next to the kana phrase in options mode
// Create a new list for katakana words 

// make an ALL VOCAB mode
// make an ALL HIRA OR KATA mode (default will be HIRA)
// Make a more difficult quiz like for letters where we can go 10 20 50 questions


// make way for user to see the pitch tones help in the vocab list
// clean up vocab list and letter list to be more appealing for users to see


// Settings menu not implimented yet
// Beginner quiz uses words not kana
// intermediate uses words not kana
// Daily users words not kana
// set up a SETTING to change the beginer and intermediate to words or kana

// VIEW TOP TIMES not implimented yet
// words like hashi only have one pitch check if that is correct for the word list
// word of day pick random word from list and give all info in organized display with menu

// have 10 words at random displayed for menu
// double check that the pitch is used properly for each version of the word
// prefecture list of japan?
// some form of note taking or rather cliff notes on the country and language?

// prefectures, main cities, mountain/volcanos, flower/ tree, soba or udon ramen, 
// each city needs these and look into lakes 
// add in later as a full addition to the program as another category, also add sakura season for each prefecture,

// formal phrases category
// sorting system for words.
// Kanji words/ added to already formed words

// 