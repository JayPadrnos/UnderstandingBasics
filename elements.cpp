#include "elements.hpp"

ChemicalElement::ChemicalElement(const std::string& name, const std::string& symbol, double atomoicWeight, std::string& acidityBasicity)
    : name(name), symbol(symbol), atomicWeight(atomicWeight), acidityBasicity(acidityBasicity) {

    }

const std::string& ChemicalElement::getName() const {
    return name;
}

const std::string& ChemicalElement::getSymbol() const {
    return symbol;
}

double ChemicalElement::getAtomicWeight() const {
    return atomicWeight;
}

cont std::string& ChemicalElement::getAcidityBasicity() const {
    return AcidityBasicity;
}

void ChemicalElement::displayInfo() const {
    std::cout << "Name: " << name << "\n";
    std::cout << "Symbol: " << symbol << "\n";
    std::cout << "Atomic Weight: " << atomicWeight << "\n";
    std::cout << "Acidity/Basicity: " << acidityBasicity << "\n";
}

std::vector<ChemicalElement> initializeElements() {
    std::vector<ChemicalElement> elements;

    elements.emplace_back("Hydrogen", "H", 1.008, "Neutral");
    elements.emplace_back("Oxygen", "O", 15.999, "Neutral");


    return elements;
}
//