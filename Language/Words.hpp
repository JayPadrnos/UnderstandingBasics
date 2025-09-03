// words.hpp
#ifndef WORDS_HPP
#define WORDS_HPP

#include <string>
#include <vector>

// Structure for words with pitch accent
struct Word {
    std::string kana;    // Word in Hiragana/Katakana
    std::string romaji;  // Romanization
    std::string english; // Meaning
    std::string pitch;   // Pitch accent type
};

// Word list with pitch accent annotations
// Pitch Accent Types:
// - Heiban (flat) → rises then stays flat
// - Atamadaka (頭高, head-high) → falls after the first mora
// - Nakadaka (中高, middle-high) → falls in the middle
// - Odaka (尾高, tail-high) → rises and falls at the last mora
// - Special cases (e.g., compound variations) can be noted

const std::vector<Word> words = {
    // Heiban (flat)
    {"あした", "ashita", "tomorrow", "Heiban"},
    {"くるま", "kuruma", "car", "Heiban"},
    {"いぬ", "inu", "dog", "Heiban"},
    {"ねこ", "neko", "cat", "Heiban"},
    {"たべる", "taberu", "to eat", "Heiban"},
    {"のむ", "nomu", "to drink", "Heiban"},

    // Atamadaka (head-high)
    {"はし", "hashi", "chopsticks", "Atamadaka"},
    {"あめ", "ame", "candy", "Atamadaka"},
    {"かみ", "kami", "god", "Atamadaka"},
    {"いし", "ishi", "stone", "Atamadaka"},

    // Nakadaka (middle-high)
    {"はし", "hashi", "bridge", "Nakadaka"},
    {"あめ", "ame", "rain", "Nakadaka"},
    {"かみ", "kami", "paper", "Nakadaka"},
    {"おとこ", "otoko", "man", "Nakadaka"},
    {"おんな", "onna", "woman", "Nakadaka"},
    {"さくら", "sakura", "cherry blossom", "Nakadaka"},

    // Odaka (tail-high)
    {"ともだち", "tomodachi", "friend", "Odaka"},
    {"たんじょうび", "tanjoubi", "birthday", "Odaka"},
    {"ぎんこう", "ginkou", "bank", "Odaka"},
    {"にほんご", "nihongo", "Japanese (language)", "Odaka"},

    // Common expressions
    {"おはよう", "ohayou", "good morning", "Heiban"},
    {"こんにちは", "konnichiwa", "good afternoon/hello", "Heiban"},
    {"こんばんは", "konbanwa", "good evening", "Heiban"},
    {"ありがとう", "arigatou", "thank you", "Heiban"},
    {"すみません", "sumimasen", "excuse me / sorry", "Heiban"},
    {"ごめんなさい", "gomennasai", "I’m sorry", "Heiban"},
    {"さようなら", "sayounara", "goodbye", "Heiban"}
};

#endif
