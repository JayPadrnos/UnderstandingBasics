#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Task {
    public:
    string name;
    string description;
    bool completed;

    Task(string n, string desc) : name(n), description(desc), completed(false) {}
};

class TodoList {
    private:
    vector<Task> tasks;

    public:
    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    void viewTasks() {
        for (const Task& task : tasks) {
            cout << task.name << " - " << task.description << " - " << (task.completed ? "Completed" : "Pending") << endl;
        }
    }

    void markTaskCompleted(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks[index].completed = true;
        } else {
            cout << "Invalid task index." << endl;
        }
    }

    void removeTask(int index) {
        if (index >= 0 && index < tasks.size()) {
            tasks.erase(tasks.begin() + index);
        } else {
            cout << "Invalid task index." << endl;
        }
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (file.is_open()) {
            for (const Task& task : tasks) {
                file << task.name << "," << task.description << "," << task.completed << endl;
            }
            file.close();
            cout << "Unable to open file." <<endl;
        }
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            tasks.clear();
            string line;
            while (getline(file, line)) {
                string name, desc, completed;
                stringstream ss(line);
                getline(ss, name, ',');
                getline(ss, desc, ',');
                getline(ss, completed, ',');
                tasks.push_back(Task(name,desc));
                tasks.back().completed = (completed == "1");
            }
            file.close();
            cout << "Tasks loaded from file." << endl;
        } else {
            cout << "Unable to open file." << endl;
        }
    }
};

int main() {
    TodoList todoList;
    int choice;

    do {
        cout << "Todo list menu: \n";
        cout << "1. Add task\n";
        cout << "2. View tasks\n";
        cout << "3. Mark task completed\n"; 
        cout << "4. Remove task\n";
        cout << "5. Save tasks to file\n";
        cout << "6. Load tasks from file\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

            switch (choice) {
                case 1: {
                    string name, desc;
                    cout << "Enter task name: ";
                    cin >> name;
                    cout << "Enter task description: ";
                    cin >> desc;
                    todoList.addTask(Task(name, desc));
                    break;
                }
                case 2:
                    todoList.viewTasks();
                    break;
                case 3: {
                    int index;
                    cout << "Enter index of task to mark as completed: ";
                    cin >> index;
                    todoList.markTaskCompleted(index);
                    break;
            }
                case 4:{
                    int index;
                    cout << "Enter index of task to remove: ";
                    cin >> index;
                    todoList.removeTask(index);
                    break;
            }
                case 5: {
                    string filename;
                    cout << "Enter filename to save tasks to: ";
                    cin >> filename;
                    todoList.saveToFile(filename);
                    break;
                }
                case 6:{
                    string filename;
                    cout << "Enter filename to load tasks from: ";
                    cin >> filename;
                    todoList.loadFromFile(filename);
                    break;
                }
                case 0:
                    cout << "Exiting program. \n";
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    break;

        }
    } while (choice != 0);

    return 0;
}