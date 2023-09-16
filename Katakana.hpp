#ifndef KATAKANA_HPP
#define KATAKANA_HPP

#include <string>
#include <vector>

class Katakana {
    public:
        Katakana();
        void displayAlphabet() const;

        private:
            struct KatakanaCharacter {
                std::string character;
                std::string pronunciation;
            };

            std::vector<KatakanaCharacter> katakanaAlphabet;
};

#endif