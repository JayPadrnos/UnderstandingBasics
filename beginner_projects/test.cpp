#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Task {
    string title;
    string description;
    string deadline;
    int priority;
    string status;
};

vector<Task> tasks;

void addTask() {
    Task task;
    cout << "Enter task title: ";
    cin.ignore();
    getline(cin, task.title);
    cout << "Enter task description: ";
    getline(cin, task.description);
    cout << "Enter task deadline: ";
    getline(cin, task.deadline);
    cout << "Enter task priority (1-5): ";
    cin >> task.priority;
    task.status = "To Do";
    tasks.push_back(task);
    cout << "Task added successfully!\n";
}

void listTasks() {
    cout << "Tasks:\n";
    for (size_t i = 0; i < tasks.size(); ++i) {
        cout << i + 1 << ". "<< tasks[i].title << " (Priority: " << tasks[i].priority << ", Status: " << tasks[i].status << ")\n";
    }
}

void saveTasksToFile() {
    ofstream file("tasks.txt");
    if (file.is_open()) {
        for (const Task& task : tasks) {
            file << task.title << "\n" << task.description << "\n" << task.deadline << "\n" << task.priority << "\n" << task.status << "\n";
        }
        file.close();
        cout << "Tasks saved to file.\n";
    } else {
        cout << "Unable to open the file for saving tasks. \n";
    }
}

void loadTasksFromFile() {
    ifstream file("tasks.txt");
    tasks.clear();
    if (file.is_open()) {
        while (!file.eof()) {
            Task task;
            getline(file, task.title);
            getline(file, task.description);
            getline(file, task.deadline);
            file >> task.priority;
            file.ignore();
            getline(file, task.status);
            tasks.push_back(task);
        }
        file.close();
        cout << "Take loaded from file. \n";
    } else {
        cout << "No saved tasks found. \n";
    }
}

int main() {
    loadTasksFromFile();

    int choice;
    do {
        cout << "\nTask Manager Menu:\n";
        cout << "1. Add Task\n";
        cout << "2. List Tasks\n";
        cout << "3. Save Tasks to File\n";
        cout << "4. Quit\n";
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
                saveTasksToFile();
                break;
            case 4:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Please try again. \n";
        }
    } while (choice != 4);

    return 0;
}