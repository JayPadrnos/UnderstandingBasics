#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Vehicle {
    public:
        string make;
        string model;
        string specifications;

};

class VehicleInventory {
    private:
        // data storage here
    public:
        VehicleInventory();
        ~VehicleInventory();

        void initializeDatabase();

        void addVehicle();
        void editVehicle();
        void deleteVehicle();
        void viewInventory();
        void viewVehicleDetails();
        void searchVehicles();
        // Your choices for the switch loop and the user input

        // Optional user authentication to use program
        bool authenticatedUser(string username, string password);
        void grantAccess(string username, string role);
        void revokeAccess(string username);

        bool validateInput();
        void handleErrors();

        // Advanced features(e.g., data analyitics, real time updates, internalization) can be added here.
};

int main() {
    VehicleInventory inventory;
    inventory.initializeDatabase();

    int choice;
    while (true) {
        cout << "1. ";
        cout << "2. ";
        cout << "3. ";
        cout << "4. ";
        cout << "5. ";
        cout << "6. ";
        cout << "7. ";
        cout << "8. ";
        cin >> choice;

        switch (choice) {
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
            case 4:

                break;
            case 5:

                break;
            case 6:

                break;
            case 7:

                break;
            case 8:
                
                break;
            default:
                cout << "invalid choice, Try again." << "\n";
        }
    }
}