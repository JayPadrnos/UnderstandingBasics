#ifndef NUMBERGEN_H
#define NUMBERGEN_H

#include <vector>

enum class RandomMethod {
    RANDOM,         // fully random
    WORD_OF_THE_DAY // sequential cycle
};

int getRandomNumber(int max, RandomMethod method = RandomMethod::RANDOM);
std::vector<int> getUniqueRandomNumbers(int max, int count);

#endif
