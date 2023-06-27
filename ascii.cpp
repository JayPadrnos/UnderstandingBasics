#include <iostream> // doesnt run in terminal may need POSIX Compatible terminal, other extensions maybe?
#include <chrono>
#include <thread>

// Function to clear the terminal screen
void clearScreen()
{
    // Assuming standard terminal, uses a different approach to clear screen
    std::cout << "\033[2J\033[1;1H"; // ANSI escape sequence to clear screen
}

int main()
{
    int screenWidth = 80; // Width of the terminal screen

    // Array of spaceship frames
    const std::string spaceshipFrames[] = {
        "   ▄▄   ",
        "  █░█   ",
        "███████ ",
        "█░░█░░█",
        "█░░░░░█",
        " ▀░░░░▀ "
    };

    int numFrames = sizeof(spaceshipFrames) / sizeof(spaceshipFrames[0]);

    while (true) {
        for (int i = 0; i < screenWidth; i++) {
            clearScreen();

            // Print spaceship frame with current position
            std::cout << std::string(i, ' ') << spaceshipFrames[i % numFrames] << std::endl;

            std::this_thread::sleep_for(std::chrono::milliseconds(100)); // Pause between frames
        }
    }

    return 0;
}
