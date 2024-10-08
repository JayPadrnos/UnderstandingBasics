#include <vector>
#include <map>
using namespace std;

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        if (hand.size() % groupSize != 0) return false;

        map<int, int> cardCount;
        for (int card : hand) {
            cardCount[card]++;
        }

        for (auto& [card, count] : cardCount) {
            if (count > 0) {
                for (int i = 1; i < groupSize; i++) {
                    if (cardCount[card + i] < count) {
                        return false;
                    }
                    cardCount[card + i] -= count;
                }
            }
        }
        return true;
    }
};
