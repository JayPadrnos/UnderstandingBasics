#include <iostream>
#include <string>
#include <vector>
#include <cmath> // For the pow() function
#include <algorithm> // for the find() function

using namespace std;

class Champion {
    public:
    string name;
    int level;
    int maxLevel;
    int xpToNextLevel;
    int baseAttackDamage;
    int baseAbilityPower;
    int baseArmor;
    int baseMagicResistance;
    int baseCooldownReduction;
    double baseArmorPenetration;
    double baseMagicPenetration;
    string qAbility;
    double qCooldown;
    string wAbility;
    double wCooldown;
    string eAbility;
    double eCooldown;
    string rAbility;
    double rCooldown;

    Champion(string name, int maxLevel, int xpToNextLevel, int baseAttackDamage, int baseAbilityPower, int baseArmor, int baseMagicResistance, int baseCooldownReduction, double baseArmorPenetration, double baseMagicPenetration)
    : name(name), maxLevel(maxLevel), xpToNextLevel(xpToNextLevel), baseAttackDamage(baseAttackDamage), baseAbilityPower(baseAbilityPower), baseArmor(baseArmor), baseMagicResistance(baseMagicResistance),
     baseCooldownReduction(baseCooldownReduction), baseArmorPenetration(baseArmorPenetration), baseMagicPenetration(baseMagicPenetration) {
        level = 1;
     }

    void gainExperience(int xp) {
        xpToNextLevel -= xp;
        if (xpToNextLevel <= 0) {
            level++;
            xpToNextLevel = calculateXPRequired(level);
        }
    }

    void displayInfo() {
        cout << "Name: " << name << endl;
        cout << "Level: " << level << endl;
        cout << "Attack Damage: " << calculateStat(baseAttackDamage) << endl;
        cout << "Ability Power: " << calculateStat(baseAbilityPower) << endl;
        cout << "Armor: " << calculateStat(baseArmor) << endl;
        cout << "Magic Resistance: " << calculateStat(baseMagicResistance) << endl;
        cout << "Cooldown Reduction: " << calculateStat(baseCooldownReduction) << endl;
        cout << "Armor Penetration: " << calculateStat(baseArmorPenetration) << endl;
        cout << "Magic Penetration: " << calculateStat(baseMagicPenetration) << endl;
        cout << "Q Ability: " << qAbility << " (Cooldwon: " << qCooldown << " seconds)" << endl;
        cout << "W Ability: " << wAbility << " (Cooldwon: " << wCooldown << " seconds)" << endl;
        cout << "E Ability: " << eAbility << " (Cooldwon: " << eCooldown << " seconds)" << endl;
        cout << "R Ability: " << rAbility << " (Cooldwon: " << rCooldown << " seconds)" << endl;
        cout << endl;
    }

    private:
        int calculateXPRequired(int level) {
            return 100 * level; // example of linear XP production
        }

        double calculateStat(double baseValue) {
            double scalingFactor = 1.2; // Example of scaling factor of 1.2
            return baseValue * pow(scalingFactor, level - 1);
        }
};

int main() {
    vector<Champion> champions;

    // Create champion objects
    Champion ahri("Ahri", 18, 100, 70, 100, 30, 20, 10, 0, 0);
    ahri.qAbility = "Orb of Deception";
    ahri.qCooldown = 7.0;
    ahri.wAbility = "Fox-Fire";
    ahri.wCooldown = 9.0;
    ahri.eAbility = "Charm";
    ahri.eCooldown = 12.0;
    ahri.rAbility = "Spirit Rush";
    ahri.rCooldown = 110.0;
    champions.push_back(ahri);

    // More champions can be added in here

    // Display information for all champions
    for (auto& champion : champions) {
        champion.displayInfo();
    }

    // Summoner Spells
    vector<string> summonerSpells = {
        "Flash", "Ignite", "Teleport", "Barrier", "Exhaust", "Cleanse", "Heal", "Ghost"
    };
    vector<string> chosenSummonerSpells;

    cout << "Choose two summoner spells" << endl;

    // Display available summoner spells
    for (int i = 0; i < summonerSpells.size(); i++) {
        cout << i + 1 << ". " << summonerSpells[i] << endl;
    } 

    // Get user input for summoner spell choices
    int spellChoice;
    while (chosenSummonerSpells.size() < 2) {
        cout << "Enter the number of a summoner spell: ";
        cin >> spellChoice;

            if (spellChoice >= 1 && spellChoice <= summonerSpells.size()) {
                string chosenSpell = summonerSpells[spellChoice - 1];

                // Check if the chosen spell has already been selected
                if (find(chosenSummonerSpells.begin(), chosenSummonerSpells.end(), chosenSpell) == 
                chosenSummonerSpells.end()) {
                    chosenSummonerSpells.push_back(chosenSpell);
                    cout << "Summoner spell '" << chosenSpell << "' selected." << endl;
                } else {
                    cout << "You have already chosen that summoner spell. Please chose another." << endl;
                }
            } else {
                cout << "Invalid choice. Please eneter a valid number." << endl;
            }
        }

        // Display chosen summoner spells
        cout << "Your chosen summoner spells: " << endl;
            for (const auto& spell : chosenSummonerSpells) {
                cout << ". " << spell << endl;
            }

            return 0;
}