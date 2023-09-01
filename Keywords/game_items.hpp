#ifndef GAME_ITEMS_HPP
#define GAME_ITEMS_HPP

#include <string>
#include <vector>

using namespace std;

// Forward declaration of Effect class (needed for using Effect in Item)
class Effect;

// base class for all items
class Item {
    public:
    Item(const string& name, int value) : name(name), value(value) {}

    string getName() const { return name; }
    int getValue() const { return value; }

    virtual void use() = 0; // Make this function pure virtual, meaning it must be overridden in derived classes

    // ... Any common item functionality can be defined here ...

    protected:
        string name;
        int value;
        vector<Effect> effects;
};

// Class to represent an effect
class Effect {
    public:
        Effect(const string& name, int damage) : name(name), damage(damage) {}

        string getName() const { return name; }
        int getDamage() const { return damage; }

        private:
            string name;
            int damage;
};

// Derived classes for weapon types
// ... (previously defined weapon classes) ...

// Base class for armor types
class Armor : public Item {
    public:
    Armor(const string& name, int value) : Item(name, value) {} 

    virtual void use() override; // Armor-specific use function (to be defined in derived classes)

    protected:
    int defense;
};

// Derived classes for armor types
class HeadArmor : public Armor {
    public:
        HeadArmor(const string& name, int value, const string& material)
        : Armor(name, value), material(material) {
            setStatsBasedOnMaterial(); // see the stats based off of the material when constructing
        }

        void use() override;

    private:
        string material;

        void setStatsBasedOnMaterial();
};

class ChestArmor : public Armor {
    public: 
        ChestArmor(const string& name, int value, const string& material)
        : Armor(name, value), material(material) {
            setStatsBasedOnMaterial(); // Set stats based on the material when constructing
        }

        void use() override;

    private:
        string material;

        void setStatsBasedOnMaterial();
};

class LegArmor : public Armor {
    public:
        LegArmor(const string& name, int value, const string& material)
        : Armor(name, value), material(material) {
            setStatsBasedOnMaterial(); // Set stats based on the material when constructing
        }

        void use() override;

    private:
        string material;

        void setStatsBasedOnMaterial();
};

#endif // GAME_ITEMS_HPP