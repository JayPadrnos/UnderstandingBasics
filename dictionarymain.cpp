#include <iostream>
#include "dictionary.hpp"

int main()
{
    Dictionary dictionary;

    // Words to be added here
    dictionary.addWord("perpendicular", "pur-puhn-dik-yuh-ler", {
        {"noun", {"an instrument for indicating the vertical line from any position"}},
        {"adjective", {"vertical or straight up and down line"}}
    });

    dictionary.addWord("susurrus", "soo sur uhs", {
    {"noun", {"a soft murmuring or rustling sound; whisper"}}
});

dictionary.addWord("perpendicular", "per puhn dik yuh ler", {
    {"adjective", {"vertical straight up and down; upright"}},
    {"noun", {"instrument for indicating the vertical line from any point"}}
});

dictionary.addWord("trapezoid", "trap u zoid", {
    {"adjective", {"Also trapezoidal Geometry of relating to or having the form of a trapezoid"}},
    {"noun", {"a quadrilateral place figure having two parallel and two non parallel sides"}}
});

dictionary.addWord("homunculus", "huh muhng kyuh luhs", {
    {"noun", {"A fully formed, miniature human body believed, according to some medical theories of 16th and 17th centuries, to be contained in the spermatozoon"}},
    {"noun2", {"a diminutive human being"}}
});

dictionary.addWord("indubitably", "in doo bi tuh blee", {
    {"adverb", {"in a way that is paternilly evident or certain; unquestionably; without doubt"}}
});

dictionary.addWord("studious", "stoo dee uhs", {
    {"adjective", {"disposed or given diligent study"}},
    {"noun2", {"concerned with, characterized by or pertaining to study"}}
});

dictionary.addWord("confluence", "kon floo uhns", {
    {"noun", {"a flowing together of two or more streams, rivers, or the like"}},
    {"noun2", {"their place of junction"}}
});

dictionary.addWord("equilibrium", "ee kwuh lib ree uhm", {
    {"noun", {"a state of rest or balance due to the equal action of opposing forces"}},
    {"noun2", {"equal balance between any powers, influences, etc; equality of effect"}}
});

dictionary.addWord("copious", "koh pee uh", {
    {"adjective", {"Large in quantity or number; abundant: plentiful"}},
    {"adjective2", {"having or yielding an abundant supply"}}
});

dictionary.addWord("flabbergasted", "flÆb ga stid", {
    {"adjective", {"informal; overcome with astonishment; amazed; astounded"}}
});

dictionary.addWord("gullywasher", "guhl ee wosh er", {
    {"noun", {"a usually short, heavy rainstorm"}}
});

dictionary.addWord("emote", "i moht", {
    {"verb", {"to express emotion in a very dramatic or obvious way"}}
});

dictionary.addWord("bailiwick", "bail li wick", {
    {"noun", {"the sphere in which one has superior knowledge or authority : a special domain"}}
});

dictionary.addWord("cavil", "kav uhl", {
    {"verb", {"to raise irritating and trivial objections; find fault with unnecessarily"}}
});

dictionary.addWord("damask", "dam usk", {
    {"noun", {"shiny or thick fabric (as of linen, cotton, silk, or rayon) made with patterns"}}
});

dictionary.addWord("signet", "sig nut", {
    {"noun", {"a seal or used officially to give personal authority to a document in lieu of a signature or the impression made by or as if by such a seal"}}
});

dictionary.addWord("absolve", "ub zahlv", {
    {"verb", {"to free someone from a responsibility or commitment or from the consequences of guilt"}}
});

oscilate

numoultramicroscopicsilcovolcanoconiosis

torsion

dispoiled

beggered

conquest

masochism

entice

turbid

zither

benall 

poeticising

audacity

chivilary

ludicrous

mythic

exubrant 

melody 

senada 

exuberance 

imbued

sympathy

disfunction

hypoglycemia






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
                std::cout << "Pronunciation: " << word.pronunciation << std::endl;
                for (const auto& typeAndDefinition : word.typesAndDefinitions) {
                    std::cout << "Type: " << typeAndDefinition.first << std::endl;
                    std::cout << "Definition(s): ";
                    for (const auto& definition : typeAndDefinition.second) {
                        std::cout << definition << std::endl;
                    }
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
//// Must fix the code to NOT pick the same word when pulling from the list of words
// Add function to see the full list of words
/// Create an example for it to be shown in sentence use for each type of way the word can be used
//
//