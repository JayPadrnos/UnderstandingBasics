#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

struct Task {
    string name;
    string description;
    string dueDate;
};

vector<Task> tasks;

void addTask() {
    // Implement adding a task
}

void listTasks() {
    // Implement a listing tasks
}
void updateTask() {
    // Implement an update tasks
}
void deleteTask() {
    // Implement deleting tasks
}
void saveToFile() {
    // Implement saving tasks to a file
}
void loadFromFile() {
    // Implement loading tasks from a text file
}

int main() {
    loadFromFile(); // Load tasks from the file at program start

    int choice;
    while (true) {
        cout << "Task Manager Menu: " << endl;
        cout << "1. Add Task" << endl;
        cout << "2. List Tasks" << endl;
        cout << "3. Update Tasks" << endl;
        cout << "4. Delete Task" << endl;
        cout << "5. Quit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTask();
                break;
            case 2:
                listTasks();
                break;
            case 3:
                updateTask();
                break;
            case 4:
                deleteTask();
                break;
            case 5:
                savetoFile(); // Save tasks to file before quitting the program
                return 0;
            default:
                cout << "Invalid choice. Try again. " << endl;
        }
    }

    return 0;
}