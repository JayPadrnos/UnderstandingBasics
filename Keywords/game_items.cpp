#include "game_items.hpp"
#include <iostream>

using namespace std;

// Implement the setStatsBasedOnMaterial function for each armor type
void HeadArmor::setStatsBasedOnMaterial() {
    if (material == "metal") {
        defense = 15;
    } else if (material == "leather") {
        defense = 10;
    } else if (material == "cloth")  {
        defense = 5;
    }
}

void ChestArmor::setStatsBasedOnMaterial() {
     if (material == "metal") {
        defense = 25;
    } else if (material == "leather") {
        defense = 15;
    } else if (material == "cloth")  {
        defense = 10;
    }
}

void LegArmor::setStatsBasedOnMaterial() {
     if (material == "metal") {
        defense = 20;
    } else if (material == "leather") {
        defense = 10;
    } else if (material == "cloth")  {
        defense = 5;
    }
}

// Implement the use() function for each armor type (you can customize this based on game logic)
void HeadArmor::use() {
    cout << "Equipped Head Armor: " << getName() << " (Defense: " << defense << ", Material: " << ")";
}

void ChestArmor::use() {
    cout << "Equipped Chest Armor: " << getName() << " (Defense: " << defense << ", Material: " << ")";
}

void HeadArmor::use() {
    cout << "Equipped Leg Armor: " << getName() << " (Defense: " << defense << ", Material: " << ")";
}