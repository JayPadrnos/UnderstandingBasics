#include <iostream>
#include <string>

using namespace std;

struct Item {
    int id;
    string name;
    string description;
    int quantity;
};

class Backpack {
    private:
    static const int MAX_ITEMS = 10;    // Maximum number of items in the backpack
    Item items[MAX_ITEMS];             // Array to store the items 
    int itemCount;                    // Current Number of items in the backpack

    public:
        Backpack();
        void addItem(const Item& item);
        void removeItem(int itemId);
        void displayInventory();
};

Backpack::Backpack() {
    itemCount = 0;
}

void Backpack::addItem(const Item& item) {
    // Check if the backpack is already full
    if (itemCount >= MAX_ITEMS) {
        cout << "The backpack is full." << endl;
        return;
    }

    // Add the item to the backpack
    items[itemCount++] = item;
}
void Backpack::removeItem(int itemId) {
    // Search for the item in the backpack
    for (int i = 0; i < itemCount; ++i) {
        if (items[i].id == itemId) {
            // Remove the item by shifting the remaining items
            for (int j = i; j < itemCount - 1; ++j) {
                items[j] = items[j + 1];
            }
            itemCount--;
            cout << "Item removed with ID: " << itemId << endl;
            return;
        }
    }

    cout << "Item not found with ID: " << itemId << endl;
}

void Backpack::displayInventory() {
    cout << "Inventory" << endl;
    for (int i = 0; i < itemCount; ++i) {
        cout << "ID: " << items[i].id;
        cout << "Name: " << items[i].name;
        cout << "Description: " << items[i].description;
        cout << "Quanity: " << items[i].quantity;
        cout << "-------------------------";
    }
}

int main() {
    Backpack backpack;

    Item item1;
    item1.id = 1;
    item1.name = "Sword";
    item1.description = "A sharp sword.";
    item1.quantity = 1;
    backpack.addItem(item1);

    Item item2;
    item2.id = 2;
    item2.name = "Health Potion";
    item2.description = "Restore health.";
    item2.quantity = 5;
    backpack.addItem(item2);

    backpack.displayInventory();

    backpack.removeItem(1);

    backpack.displayInventory();

    return 0;
}