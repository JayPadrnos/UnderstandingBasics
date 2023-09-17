#ifndef HIRAGANA_HPP
#define HIRAGANA_HPP

#include <string>
#include <vector>

class Hiragana {
    public:
        Hiragana();
        void displayAlphabet() const;

    private:
        struct HiraganaCharacter {
            std:: string character;
            std:: string pronunciation;
        };

        std::vector<HiraganaCharacter> hiraganaAlphabet;
};

#endif