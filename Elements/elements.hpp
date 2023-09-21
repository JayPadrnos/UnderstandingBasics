#pragma once

#include <string>
#include <vector>

class ChemicalElement {
    public:
        ChemicalElement(const std::string& name, const std::string& symbol, double atomicWeight, const std::string& acidityBasicity)
        : name(name), symbol(symbol), atomicWeight(atomicWeight), acidityBasicity(acidityBasicity) {

        }

        void displayInfo() const;

        const std::string& getSymbol() const;

    private:
        std::string name;
        std::string symbol;
        double atomicWeight;
        std::string acidityBasicity;
};

std::vector<ChemicalElement> initializeElements();