#include "numbergen.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>

static bool seeded = false;
static int sequentialIndex = 0; // for Word of the Day

int getRandomNumber(int max, RandomMethod method) {
    if (!seeded) { srand((unsigned)time(0)); seeded = true; }

    switch (method) {
        case RandomMethod::WORD_OF_THE_DAY:
            if (sequentialIndex >= max) sequentialIndex = 0;
            return sequentialIndex++;

        case RandomMethod::RANDOM:
        default:
            return rand() % max;
    }
}

std::vector<int> getUniqueRandomNumbers(int max, int count) {
    if (!seeded) { srand((unsigned)time(0)); seeded = true; }

    std::vector<int> numbers(max);
    for (int i = 0; i < max; i++) numbers[i] = i;
    std::random_shuffle(numbers.begin(), numbers.end());

    if (count > max) count = max;
    return std::vector<int>(numbers.begin(), numbers.begin() + count);
}
