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

        // Optional user authentication to use program
        bool authenticatedUser(string username, string password);
        void grantAccess(string username, string role);
        void revokeAccess(string username);

        bool validateInput();
        void handleErrors();

        // Advanced features(e.g., data analyitics, real time updates, internalization) can be added here.
};