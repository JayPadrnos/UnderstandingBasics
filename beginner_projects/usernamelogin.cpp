#include <iostream>
#include <string>

using namespace std;

struct User {
    string username;
    string password;
    // You can include more fields as per your requirments, such as email, age, etc...
};

int main() {
    const int  MAX_USERS = 100; // Maximum number of users in the database
    User users[MAX_USERS]; // Array to store user data
    int numUsers = 0; // Current number of users in the database

    // Add user data to the database
    users[numUsers].username = "John";
    users[numUsers].password = "password123";
    numUsers++;

    users[numUsers].username = "Big";
    users[numUsers].password = "Doc";
    numUsers++;

    // Perform login verification
    string inputUsername;
    string inputPassword;
    cout << "Enter the name you which to be called.";
    cin >> inputUsername;
    cout << "What is the combination to your lock";
    cin >> inputPassword;

    bool isLoggedIn = false;

    for (int i = 0; i < numUsers; i++) {
        if (users[i].username == inputUsername && users[i].password == inputPassword) {
            isLoggedIn = true;
            break;
        }
    }

    // Output login status
    if (isLoggedIn) {
        cout << "Login successful" << endl;
    } else {
        cout << "Invalid username or password. Login failed" << endl;
    }

    return 0;
}