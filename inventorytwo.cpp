#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Item {
    int id;
    string name;
    string description;
    int quantity;
};

struct Stats {
    int hp;
    int defense;
    int attack;
};

class Backpack {
    private:
    vector<Item> items;

    public:
    void addItem(const Item& item);
    void removeItem(int itemId);
    void displayInventory();
    Item* getItem(int itemId);
};

void Backpack::addItem(const Item& item) {
    items.push_back(item);
}

void Backpack::removeItem(int itemId) {
    for (auto it = items.begin(); it != items.end(); ++it) {
        if (it->id == itemId) {
            items.erase(it);
            cout << "Item removed with ID: " << itemId;
            return;
        }
    }
    cout << "Item not found with ID: " << itemId;
}

void Backpack::displayInventory() {
    cout << "Inventory: ";
    for (const auto& item : items) {
    cout << "ID: ";
    cout << "Description: ";
    cout << "Quantity: ";
    cout << "------------------";
    }
}

Item* Backpack::getItem(int itemId) {
    for (auto& item : items) {
        if (item.id == itemId) {
            return &item;
        }
    }
    return nullptr;
}

class Character {
    private:
    Backpack backpack;
    Item* equippedWeapon;
    Item* equippedArmor;
    Item* equippedUtility;
    Stats stats;
    
    public:
    void addItemToBackpack(const Item& item);
    void removeItemFromBackpack(int itemId);
    void displayInventory();
    void equipItem(int itemId);
    void unequipItem(int itemId);
    void setStats(int hp, int defense, int attack);
    void fight(Character& enemey);
};

void Character:: addItemToBackpack(const Item& item) {
    backpack.addItem(item);
}

void Character::removeItemFromBackpack(int itemId) {
    backpack.removeItem(itemId);
}

void Character::displayInventory() {
    backpack.displayInventory();
}

void Character::equipItem(int itemId) {
    Item* item = backpack.getItem(itemId);
    if (item == nullptr) {
        cout << "Item not found with ID: " << itemId;
        return;
    }

    if (item->name == "Sword") {
        equippedWeapon = item;
        cout << "Weapon equipped: " << equippedWeapon->name;
    } else if (item->name == "Metal Armor") {
        equippedArmor = item;
        cout << "Armor equipped: " << equippedArmor->name;
    } else if (item->name == "Health Potion") {
        equippedUtility = item;
        cout << "Potion equipped: " << equippedUtility->name;
    } else {
        cout << "Item cannot be equipped.";
    }
}

void Character::unequipItem(int itemId) {
    if (equippedWeapon && equippedWeapon->id == itemId) {
        equippedWeapon = nullptr;
        cout << "Weapon unequipped.";
    } else if (equippedArmor && equippedArmor->id == itemId) {
        equippedArmor = nullptr;
        cout << "Armor unequipped.";
    } else if (equippedUtility && equippedUtility->id == itemId) {
        equippedUtility = nullptr;
        cout << "Potion unequipped.";
    } else {
        cout << "Item not equipped.";
    }
}

void Character::setStats(int hp, int defense, int attack) {
    stats.hp = hp;
    stats.defense = defense;
    stats.attack = attack;
}

void Character::fight(Character& enemy) {
    cout << "Player attacks the enemy!";

    if (equippedWeapon != nullptr) {
        int attackDamage = stats.attack;
        if (equippedWeapon->name == "Sword") {
            attackDamage += 5;
        }
        enemy.stats.hp -= attackDamage;
        cout << "Player deals " << attackDamage << " damage to the enemy";
    } else {
        cout << "Player has no weapon equipped. Cannot attack.";
    }
}

int main() {
    Character player;
    Character enemey;

    Item sword;
    sword.id = 1;
    sword.name = "Sword";
    sword.description = "A sharp sword";
    sword.quantity = 1;

    Item metalArmor;
    metalArmor.id = 2;
    metalArmor.name = "Metal Armor";
    metalArmor.description = "Strong Metal Armor";
    metalArmor.quantity = 1;

    Item healthPotion;
    healthPotion.id = 3;
    healthPotion.name = "Health Potion";
    healthPotion.description = "Restores Health";
    healthPotion.quantity = 5;

    player.addItemToBackpack(sword);
    player.addItemToBackpack(metalArmor);
    player.addItemToBackpack(healthPotion);

    Item woodenArmor;
    woodenArmor.id = 4;
    woodenArmor.name = "WoodenArmor";
    woodenArmor.description = "Basic Wooden Armor";
    woodenArmor.quantity = 1;

    enemey.setStats(30, 2, 5);
    enemey.addItemToBackpack(woodenArmor);

    player.displayInventory();
    enemey.displayInventory();

    player.equipItem(1);
    player.equipItem(2);
    player.equipItem(3);

    player.fight(enemey);

    return 0;
}