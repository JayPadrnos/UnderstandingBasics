#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main() {
    std::ofstream myfile;

    myfile.open("Example.txt"); // open a file
    myfile << "Writing this to a file. ";
        // Write to the file
    myfile.close(); // ALWAYS remember to close the file

    std::string line;
    std::ifstream myfile2("Example.txt");
        // OPEN the file for reading
    if (myfile2.is_open()) {
        while (getline(myfile2, line)) {
            std::cout << line << endl;
            // READ and PRINT each line from the file
        }
        myfile2.close();
    }

    return 0;
}