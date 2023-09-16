#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>

struct TodoItem {
    std::string description;
    bool completed;
};

std::vector<TodoItem> todoList;

void addTask(const std::string& description) {
    TodoItem newItem;
    newItem.description = description;
    newItem.completed = false;
    todoList.push_back(newItem);   
}

void displayTasks() {
    std::cout << "To-Do List: \n";
    for (size_t i = 0; i < todoList.size(); ++i) {
        std::cout << "[" << i + 1 << "] ";
        if (todoList[i].completed) {
            std::cout << "[X] ";
        } else {
            std::cout << "[ ] ";
        }
        std::cout << todoList[i].description << std::endl;
    }
}

int main() {
    char choice;
    std::string task;

    do {
        std::cout << "\nMenu:\n";
        std::cout << "1. Add Task\n";
        std::cout << "2. Display Tasks\n";
        std::cout << "3. Quit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case '1':
                std::cout << "Enter task description: ";
                std::cin.ignore(); // Clear newline from previous input
                std::getline(std::cin, task);
                addTask(task);
                break;
            case '2':
                displayTasks();
                break;
            case '3':
                std::cout << "Exiting Program";
                break;
        }
    } while (choice != '3');

    return 0;
}