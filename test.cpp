#include <iostream>
#include <vector>
#include <string>

struct Task {
    std::string title;
    std::string description;
};

int main() {
    std::vector<Task> tasks;
    std::string title, description;

    std::cout << "Enter task title: ";
    std::getline(std::cin, title);
    std::cout << "Enter task description: ";
    std::getline(std::cin, description);

    Task newTask = {title, description};
    tasks.push_back(newTask);
    
    std::cout << "Task added successfully!\n";

    // Additional code for saving tasks to a file can be added here

    return 0;
}

// references are pointers with safter measures & vs *
