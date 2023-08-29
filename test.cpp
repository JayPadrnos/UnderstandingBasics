#include <string>
#include <iostream>
#include <vector>


using namespace std;

int main() {
    std::vector<string> names = {"Jay", "Giz", "Ked",};
    std::vector<int> age = {29, 102, 32};
    
    std::vector<std::string> names = {"ked", "Jay", "giz"};

    // Loop using a size_t variable (i) to iterate through the vector
    for (size_t i = 0; i < names.size(); ++i) {
        // Output each name in the vector
        std::cout << names[i] << std::endl;
    }

}