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
    string kanji;       
    string meaning;     
    string context;     
    string category;    
};

enum Difficulty { BEGINNER, INTERMEDIATE, DAILY };

enum QuizMode { KANA_ONLY, KANJI_ONLY, ROMAJI_ONLY, CONTEXT_ONLY, FULL_RANDOM };

struct Modes {
    bool timed = false;
    bool review = false;
    bool reverse = false;     
    bool expert = false;      
    bool onlyHira = false;    
    bool onlyKata = false;    
    bool countdown = false;   
    int countdownSeconds = 30;

    QuizMode quizMode = KANA_ONLY; // default quiz mode
};

// ====== Globals ======
vector<Flashcard> flashcards = {
    // Vowels
    {"あ","ア","a","a"},{"い","イ","i","i"},{"う","ウ","u","u"},{"え","エ","e","e"},{"お","オ","o","o"},
    // K consonant + voiced
    {"か","カ","ka","ka"},{"き","キ","ki","ki"},{"く","ク","ku","ku"},{"け","ケ","ke","ke"},{"こ","コ","ko","ko"},
    {"が","ガ","ga","ga"},{"ぎ","ギ","gi","gi"},{"ぐ","グ","gu","gu"},{"げ","ゲ","ge","ge"},{"ご","ゴ","go","go"},
    // S consonant + voiced
    {"さ","サ","sa","sa"},{"し","シ","shi","shi"},{"す","ス","su","su"},{"せ","セ","se","se"},{"そ","ソ","so","so"},
    {"ざ","ザ","za","za"},{"じ","ジ","ji","ji"},{"ず","ズ","zu","zu"},{"ぜ","ゼ","ze","ze"},{"ぞ","ゾ","zo","zo"},
    // T consonant + voiced
    {"た","タ","ta","ta"},{"ち","チ","chi","chi"},{"つ","ツ","tsu","tsu"},{"て","テ","te","te"},{"と","ト","to","to"},
    {"だ","ダ","da","da"},{"ぢ","ヂ","ji","ji"},{"づ","ヅ","zu","zu"},{"で","デ","de","de"},{"ど","ド","do","do"},
    // N consonant
    {"な","ナ","na","na"},{"に","ニ","ni","ni"},{"ぬ","ヌ","nu","nu"},{"ね","ネ","ne","ne"},{"の","ノ","no","no"},
    // H consonant + voiced + p
    {"は","ハ","ha","ha"},{"ひ","ヒ","hi","hi"},{"ふ","フ","fu","fu"},{"へ","ヘ","he","he"},{"ほ","ホ","ho","ho"},
    {"ば","バ","ba","ba"},{"び","ビ","bi","bi"},{"ぶ","ブ","bu","bu"},{"べ","ベ","be","be"},{"ぼ","ボ","bo","bo"},
    {"ぱ","パ","pa","pa"},{"ぴ","ピ","pi","pi"},{"ぷ","プ","pu","pu"},{"ぺ","ペ","pe","pe"},{"ぽ","ポ","po","po"},
    // M consonant
    {"ま","マ","ma","ma"},{"み","ミ","mi","mi"},{"む","ム","mu","mu"},{"め","メ","me","me"},{"も","モ","mo","mo"},
    // Y consonant
    {"や","ヤ","ya","ya"},{"ゆ","ユ","yu","yu"},{"よ","ヨ","yo","yo"},
    // R consonant
    {"ら","ラ","ra","ra"},{"り","リ","ri","ri"},{"る","ル","ru","ru"},{"れ","レ","re","re"},{"ろ","ロ","ro","ro"},
    // W consonant
    {"わ","ワ","wa","wa"},{"を","ヲ","wo","wo"},
    // N
    {"ん","ン","n","n"},
    // Small kana
    {"ゃ","ャ","ya (small)","ya"},{"ゅ","ュ","yu (small)","yu"},{"ょ","ョ","yo (small)","yo"},
    {"ぁ","ァ","a (small)","a"},{"ぃ","ィ","i (small)","i"},{"ぅ","ゥ","u (small)","u"},
    {"ぇ","ェ","e (small)","e"},{"ぉ","ォ","o (small)","o"},{"っ","ッ","tsu (small)","tsu"},
};

unordered_map<string, vector<double>> topTimes;

// ====== Helper Functions ======
string trimWhitespace(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n"); // double check what /t /r /n are.
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start,end-start+1);
}

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
    while(true) {
        int ch = _getch();
        if(ch==27) return {true,""};
        else if(ch=='\r'||ch=='\n'){cout<<'\n';return{false,out};}
        else if(ch=='\b'||ch==127){if(!out.empty()){out.pop_back();cout<<"\b \b";}}     // double check logic and /b along with what pop_back is
        else{out.push_back(static_cast<char>(ch));cout<<static_cast<char>(ch);}
    }
}

bool countdownWaitWithEsc(int seconds) {
    using namespace chrono;
    auto start = high_resolution_clock::now();
    while(true){
        if(_kbhit()){int c=_getch();if(c==27) return true;}       // double check getch and kbhit also high_resolution_clock
        auto now=high_resolution_clock::now();
        double elapsed = duration_cast<duration<double>>(now-start).count();
        if(elapsed>=seconds) return false;
        Sleep(50);
    }
}
#else
pair<bool,string> readLineWithEsc() {
    struct termios oldt,newt;
    tcgetattr(STDIN_FILENO,&oldt);      // THIS Entire BLOCK
    newt=oldt;
    newt.c_lflag&=~(ICANON|ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&newt);
    string out;
    bool esc=false;
    while(true){
        char ch;
        ssize_t r=read(STDIN_FILENO,&ch,1);
        if(r<=0) break;
        if(ch==27){esc=true;break;}
        if(ch=='\n'||ch=='\r'){cout<<'\n';break;}
        if(ch==127||ch=='\b'){if(!out.empty()){out.pop_back();cout<<"\b \b";}}
        else{out.push_back(ch);}
    }
    tcsetattr(STDIN_FILENO,TCSANOW,&oldt);
    return {esc,out};
}

bool kbhit_posix() {
    timeval tv{0,0};
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(STDIN_FILENO,&rfds);
    return select(STDIN_FILENO+1,&rfds,NULL,NULL,&tv)>0;
}

bool countdownWaitWithEsc(int seconds){
    using namespace chrono;
    struct termios oldt,newt;
    tcgetattr(STDIN_FILENO,&oldt);
    newt=oldt;
    newt.c_lflag&=~(ICANON|ECHO);
    tcsetattr(STDIN_FILENO,TCSANOW,&newt);
    auto start=high_resolution_clock::now();
    bool escPressed=false;                          // ENTIRE BLOCK
    while(true){
        if(kbhit_posix()){
            char ch;
            ssize_t r=read(STDIN_FILENO,&ch,1);
            if(r>0 && ch==27){escPressed=true;break;}
        }
        auto now=high_resolution_clock::now();
        double elapsed=duration_cast<duration<double>>(now-start).count();
        if(elapsed>=seconds) break;
        usleep(50000);
    }
    tcsetattr(STDIN_FILENO,TCSANOW,&oldt);
    return escPressed;
}
#endif

// ====== File I/O ======
void loadSettings(Modes &modes) {
    ifstream in("settings.txt");
    if(!in) return;
    bool t,r,rev,exp,h,k;
    int csec,qmode;
    if(in>>t>>r>>rev>>exp>>h>>k>>csec>>qmode){
        modes.timed=t; modes.review=r; modes.reverse=rev; modes.expert=exp;
        modes.onlyHira=h; modes.onlyKata=k; modes.countdown=(csec>0);                   // ENTIRE BLOCK
        if(csec>0) modes.countdownSeconds=csec;
        if(qmode>=0 && qmode<=4) modes.quizMode = static_cast<QuizMode>(qmode);
    }
}

void saveSettings(const Modes &modes){
    ofstream out("settings.txt");
    out<<modes.timed<<" "<<modes.review<<" "<<modes.reverse<<" "<<modes.expert<<" "
       <<modes.onlyHira<<" "<<modes.onlyKata<<" "<<(modes.countdown?1:0)<<" "
       <<modes.countdownSeconds<<" "<<static_cast<int>(modes.quizMode);
}

void loadTopTimes() {
    ifstream in("toptimes.txt");
    if(!in) return;
    string mode; double t;
    while(in>>mode>>t) topTimes[mode].push_back(t);
}

void saveTopTimes() {
    ofstream out("toptimes.txt");
    for(auto &entry:topTimes) for(double t:entry.second) out<<entry.first<<" "<<t<<"\n";
}

// ====== Display helpers ======
void showKanaList() {
    cout<<"\n==== Kana List ====\n";
    for(const auto &card:flashcards){
        cout<<"H: "<<card.hiragana<<"\tK: "<<card.katakana<<"\tR: "<<card.romaji<<"\n";
    }
}

void showTopTimes() {
    cout<<"\n==== Top 3 Times per Mode ====\n";
    if(topTimes.empty()){cout<<"(No recorded times yet)\n"; return;}
    for(auto &entry:topTimes){
        cout<<entry.first<<" mode:\n";
        for(size_t i=0;i<entry.second.size();++i) cout<<"  "<<i+1<<". "<<entry.second[i]<<" seconds\n";
    }
}

void showMainMenu() {
    cout<<"\n===== Kana Flashcard Menu =====\n";
    cout<<"1. Beginner Quiz\n2. Intermediate Quiz\n3. Daily Quick Run (10 Cards)\n";
    cout<<"4. View Full Kana List\n5. View Top Times\n6. Settings\n0. Exit\n";
}

// ====== Settings Menu ======
void showSettingsMenu(Modes &modes){
    while(true){
        cout<<"\n===== Settings =====\n";
        cout<<"1. Toggle Timed Mode ("<<(modes.timed?"ON":"OFF")<<")\n";
        cout<<"2. Toggle Review Mode ("<<(modes.review?"ON":"OFF")<<")\n";
        cout<<"3. Toggle Reverse Mode (romaji->kana) ("<<(modes.reverse?"ON":"OFF")<<")\n";
        cout<<"4. Toggle Expert Mode (random script only) ("<<(modes.expert?"ON":"OFF")<<")\n";
        cout<<"5. Toggle Hiragana Only ("<<(modes.onlyHira?"ON":"OFF")<<")\n";
        cout<<"6. Toggle Katakana Only ("<<(modes.onlyKata?"ON":"OFF")<<")\n";
        cout<<"7. Toggle Countdown Timer ("<<(modes.countdown?"ON":"OFF")<<"), Seconds: "<<modes.countdownSeconds<<"\n";
        cout<<"8. Change Quiz Mode (currently: ";
        switch(modes.quizMode){
            case KANA_ONLY: cout<<"Kana Only"; break;
            case KANJI_ONLY: cout<<"Kanji Only"; break;
            case ROMAJI_ONLY: cout<<"Romaji Only"; break;
            case CONTEXT_ONLY: cout<<"Context Only"; break;
            case FULL_RANDOM: cout<<"Full Random"; break;
        } cout<<")\n";
        cout<<"0. Save and Return to Main Menu\nSelect option: ";

        auto res = readLineWithEsc();
        if(res.first){cout<<"\n(ESC pressed, returning to main menu)\n"; break;}
        string choiceStr=trimWhitespace(res.second);
        if(choiceStr.empty()) continue;
        int choice=-1;
        try{choice=stoi(choiceStr);}catch(...){cout<<"Invalid input\n"; continue;}

        switch(choice){
            case 1: modes.timed=!modes.timed; cout<<"Timed mode is now "<<(modes.timed?"ON\n":"OFF\n"); break;
            case 2: modes.review=!modes.review; cout<<"Review mode is now "<<(modes.review?"ON\n":"OFF\n"); break;
            case 3: modes.reverse=!modes.reverse; cout<<"Reverse mode is now "<<(modes.reverse?"ON\n":"OFF\n"); break;
            case 4: modes.expert=!modes.expert; cout<<"Expert mode is now "<<(modes.expert?"ON\n":"OFF\n"); break;
            case 5: modes.onlyHira=!modes.onlyHira; if(modes.onlyHira) modes.onlyKata=false; cout<<"Hiragana only mode is now "<<(modes.onlyHira?"ON\n":"OFF\n"); break;
            case 6: modes.onlyKata=!modes.onlyKata; if(modes.onlyKata) modes.onlyHira=false; cout<<"Katakana only mode is now "<<(modes.onlyKata?"ON\n":"OFF\n"); break;
            case 7:
                modes.countdown=!modes.countdown;
                cout<<"Countdown timer is now "<<(modes.countdown?"ON\n":"OFF\n");
                if(modes.countdown){
                    cout<<"Enter countdown seconds (5-120): ";
                    auto res2=readLineWithEsc();
                    if(res2.first) {cout<<"\nCountdown time input cancelled\n"; break;}
                    string input=trimWhitespace(res2.second);
                    try{
                        int sec=stoi(input);
                        if(sec>=5&&sec<=120){modes.countdownSeconds=sec; cout<<"Countdown seconds set to "<<sec<<".\n";}
                        else cout<<"Invalid range. Keeping previous ("<<modes.countdownSeconds<<")\n";
                    }catch(...){cout<<"Invalid input. Keeping previous ("<<modes.countdownSeconds<<")\n";}
                }
                break;
            case 8:{
                cout<<"Select Quiz Mode:\n1. Kana Only\n2. Kanji Only\n3. Romaji Only\n4. Context Only\n5. Full Random\n";
                auto res2=readLineWithEsc();
                if(res2.first){cout<<"\n(ESC pressed, cancelled)\n"; break;}
                string modeChoiceStr=trimWhitespace(res2.second);
                int mchoice=-1;
                try{mchoice=stoi(modeChoiceStr);}catch(...){}
                switch(mchoice){
                    case 1: modes.quizMode=KANA_ONLY; break;
                    case 2: modes.quizMode=KANJI_ONLY; break;
                    case 3: modes.quizMode=ROMAJI_ONLY; break;
                    case 4: modes.quizMode=CONTEXT_ONLY; break;
                    case 5: modes.quizMode=FULL_RANDOM; break;
                    default: cout<<"Invalid choice.\n"; break;
                }
                break;
            }
            case 0: saveSettings(modes); return;
            default: cout<<"Invalid choice\n"; break;
        }
    }
}

// ====== Quiz Runner ======
void runQuiz(Modes &modes, int numCards){
    vector<Flashcard> cards=flashcards;
    shuffle(cards.begin(),cards.end(),default_random_engine(static_cast<unsigned>(time(nullptr))));

    int correct=0;
    for(int i=0;i<numCards&&i<cards.size();++i){
        const Flashcard &card=cards[i];
        string prompt, answer;

        switch(modes.quizMode){
            case KANA_ONLY:
                if(modes.reverse){
                    prompt=card.romaji;
                    if(modes.onlyHira) answer=card.hiragana;
                    else if(modes.onlyKata) answer=card.katakana;
                    else answer=(rand()%2 ? card.hiragana:card.katakana);
                } else {
                    if(modes.expert) prompt=(rand()%2 ? card.hiragana:card.katakana);
                    else if(modes.onlyHira) prompt=card.hiragana;
                    else if(modes.onlyKata) prompt=card.katakana;
                    else prompt=card.hiragana+" / "+card.katakana;
                    answer=card.quizRomaji;
                }
                break;
            case KANJI_ONLY:
                if(!card.kanji.empty()){prompt=card.kanji; answer=card.quizRomaji;}
                else continue;
                break;
            case ROMAJI_ONLY:
                prompt=card.romaji;
                answer=card.hiragana+" / "+card.katakana;
                break;
            case CONTEXT_ONLY:
                if(!card.context.empty()){prompt=card.context; answer=card.romaji;}
                else continue;
                break;
            case FULL_RANDOM:{
                int choice=rand()%4;
                if(choice==0) {prompt=card.hiragana; answer=card.quizRomaji;}
                else if(choice==1) {prompt=card.katakana; answer=card.quizRomaji;}
                else if(choice==2 && !card.kanji.empty()) {prompt=card.kanji; answer=card.quizRomaji;}
                else if(choice==3 && !card.context.empty()) {prompt=card.context; answer=card.romaji;}
                else {prompt=card.hiragana; answer=card.quizRomaji;}
                break;
            }
        }

        cout<<"\nCard "<<i+1<<"/"<<numCards<<": "<<prompt<<"\nYour answer: ";
        auto res=readLineWithEsc();
        if(res.first){cout<<"\n(ESC pressed, quiz aborted)\n"; break;}
        string user=normalizeInput(res.second);
        if(user==normalizeInput(answer)){cout<<"Correct!\n"; ++correct;}
        else cout<<"Wrong. Answer: "<<answer<<"\n";
    }
    cout<<"\nQuiz Complete! Correct: "<<correct<<"/"<<numCards<<"\n";
}

// ====== Main ======
int main(){
    
     #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);   // <-- Add this
        SetConsoleCP(CP_UTF8);         // optional: ensures input is UTF-8 too
    #endif

    Modes modes;
    loadSettings(modes);
    loadTopTimes();
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
            case 5: showTopTimes(); break;
            case 6: showSettingsMenu(modes); break;
            case 0: cout<<"Exiting...\n"; return 0;
            default: cout<<"Invalid choice\n"; break;
        }
    }
    return 0;
}
