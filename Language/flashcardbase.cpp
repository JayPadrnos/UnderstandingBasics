#include <iostream>
#include <vector>
#include <iomanip>
#include <limits>

#ifdef _WIN32
#include <windows.h>
#endif

struct Kana {
    std::string romaji;
    std::string hiragana;
    std::string katakana;
};

using Row = std::vector<Kana>;
using Grid = std::vector<Row>;

void printKanaGrid(const Grid& kanaGrid) {
    const int cellWidth = 20;
    std::string separator = "+";
    for (int i = 0; i < 5; ++i) {
        separator += std::string(cellWidth, '-') + "+";
    }

    for (const Row& row : kanaGrid) {
        std::cout << separator << "\n";
        for (const Kana& kana : row) {
            if (kana.romaji.empty()) {
                std::cout << "|" << std::setw(cellWidth) << " ";
            } else {
                std::string content = "H: " + kana.hiragana + " K: " + kana.katakana + " | " + kana.romaji;
                std::cout << "| " << std::left << std::setw(cellWidth - 1) << content;
            }
        }
        std::cout << "|\n";
    }
    std::cout << separator << "\n";
}

int main() {
#ifdef _WIN32
    // Enable UTF-8 output in Windows console
    SetConsoleOutputCP(CP_UTF8);
#endif

    Grid kanaGrid = {
        { {"a", "あ", "ア"}, {"i", "い", "イ"}, {"u", "う", "ウ"}, {"e", "え", "エ"}, {"o", "お", "オ"} },
        { {"ka", "か", "カ"}, {"ki", "き", "キ"}, {"ku", "く", "ク"}, {"ke", "け", "ケ"}, {"ko", "こ", "コ"} },
        { {"sa", "さ", "サ"}, {"shi", "し", "シ"}, {"su", "す", "ス"}, {"se", "せ", "セ"}, {"so", "そ", "ソ"} },
        { {"ta", "た", "タ"}, {"chi", "ち", "チ"}, {"tsu", "つ", "ツ"}, {"te", "て", "テ"}, {"to", "と", "ト"} },
        { {"na", "な", "ナ"}, {"ni", "に", "ニ"}, {"nu", "ぬ", "ヌ"}, {"ne", "ね", "ネ"}, {"no", "の", "ノ"} },
        { {"ha", "は", "ハ"}, {"hi", "ひ", "ヒ"}, {"fu", "ふ", "フ"}, {"he", "へ", "ヘ"}, {"ho", "ほ", "ホ"} },
        { {"ma", "ま", "マ"}, {"mi", "み", "ミ"}, {"mu", "む", "ム"}, {"me", "め", "メ"}, {"mo", "も", "モ"} },
        { {"ya", "や", "ヤ"}, {"", "", ""},       {"yu", "ゆ", "ユ"}, {"", "", ""},       {"yo", "よ", "ヨ"} },
        { {"ra", "ら", "ラ"}, {"ri", "り", "リ"}, {"ru", "る", "ル"}, {"re", "れ", "レ"}, {"ro", "ろ", "ロ"} },
        { {"wa", "わ", "ワ"}, {"", "", ""},       {"", "", ""},       {"", "", ""},       {"wo", "を", "ヲ"} },
        { {"n",  "ん", "ン"}, {"", "", ""},       {"", "", ""},       {"", "", ""},       {"", "", ""} }
    };

    printKanaGrid(kanaGrid);

    std::cout << "\nPress Enter to exit...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();

    return 0;
}

// check compile compatible and add click for sound
// line up UTF-8 so that terminal will display the proper language
// ?? Storm
// need something interactive for quizing or flash card esq

// Ask player what each symbol is setup for Hira and kata