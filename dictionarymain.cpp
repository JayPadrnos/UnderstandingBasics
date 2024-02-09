#include <iostream>
#include "dictionary.hpp"

int main()
{
    Dictionary dictionary;

    // Words to be added here
    dictionary.addWord("apple", "noun", {"apel"}, {"A fruit"});
    dictionary.addWord("susurrus", "noun", {"soo", "sur", "uhs"}, {"a soft murmuring or rustling sound; whisper."});
    dictionary.addWord("perpendicular", "adjective", {"per", "puhn", "dik", "yuh", "ler"}, {"vertical straight up and down; upright"}, "noun", {"instrument for indicating the vertical line from any point."});
    dictionary.addWord("trapezoid", "adjective", {"trap", "u", "zoid"}, {"Also trap e zoidal Geometry of relating to or having the form of a trapezoid"}, "noun", {"a quadrilateral place figure having two parallel and two non parallel sides."});
    dictionary.addWord("homunculus", "noun", {"huh", "muhng", "kyuh", "luhs"}, {"A fully formed, miniature human body believed, according to some medical theories of 16th and 17th centuries, to be contained in the spermatozoon."}, "noun2", {"a diminutive human being."});
    dictionary.addWord("indubitably", "adverb", {"in", "doo", "bi", "tuh", "blee"}, {"in a way that is paternilly evident or certain unquestionably. without doubt"});
    dictionary.addWord("studious", "adjective", {"stoo", "dee", "uhs"}, {"disposed or gien diligent study"}, "noun2", {"concerned with, characterized by or pertaining to study."});
    dictionary.addWord("confluence", "noun", {"kon", "floo", "uhns"}, {"a flowing together of two or more streams, rivers, or the like."}, "noun2", {"their place of junction."});
    dictionary.addWord("equilibrium", "noun", {"ee", "kwuh", "lib", "ree", "uhm"}, {"a state of rest or balance due to the equal action of opposing forces"}, "noun2", {"equal balance between any powers, influences, etc; equality of effect"});
    dictionary.addWord("copious", "adjective", {"koh", "pee", "uh"}, {"Large in quantity or number; abundant:plentiful"}, "adjective2", {"having or yielding an abundant supply"});
    dictionary.addWord("flabbergasted", "adjective", {"flÆb", "ga", "stid"}, {"informal overcome with astonishment, amazed: astounded."});
    dictionary.addWord("gullywasher", "noun", {"guhl", "ee", "wosh", "er"}, {"a usually short, heavy rainstorm."});
    dictionary.addWord("emote", "verb", {"i", "moht"}, {"to express emotion in a very dramatic or obvious way."});
    dictionary.addWord("bailiwick", "noun", {"bail", "li", "wick"}, {"the sphere in which on has superior knowledge or authority : a special domain."});
    dictionary.addWord("cavil", "verb", {"kav", "uhl"}, {"to raise irritating and trivial objections; find fault with unecessarily"});
    dictionary.addWord("damask", "noun", {"dam", "usk"}, {"shiny or thick fabric (as of linen, cotton, silk, or rayon) made with patterns"});
    dictionary.addWord("signet", "noun", {"sig", "nut"}, {"a seal or used officially to give personal authority to a document in lieu of a signature or the impression made by or as if by such a seal."});
    dictionary.addWord("absolve", "verb", {"ub", "zahlv"}, {"to free someone from a responsibility or commitment or from the consequences of guilt"});

    // Main loop
    while (true) {
        std::string input;
        std::cout << "Enter '1', '5', or '10' to get 1, 5, or 10 random words, or quit to exit: ";
        std::cin >> input;

        if (input == "quit") {
            break;
        }

        int count = std::stoi(input);
        if (count == 1 || count == 5 || count == 10) {
            std::vector<Word> randomWords = dictionary.getRandomWords(count);
            for (const auto& word : randomWords) {
                std::cout << "Word: " << word.word << std::endl;
                std::cout << "Type: " << word.type << std::endl;
                std::cout << "Pronunciation: ";
                for (const auto& pronunciation : word.pronunciation) {
                    std::cout << pronunciation << ", ";
                }
                std::cout << std::endl;
                std::cout << "Definition(s): ";
                for (const auto& definition : word.definitions) {
                    std::cout << definition << std::endl;
                }
                std::cout << std::endl;
            }
        } else {
            std::cout << "Invalid input. Please enter '1', '5', or '10'. " << std::endl;
        }
    }

    return 0;
}

// lazy friday need to code later 