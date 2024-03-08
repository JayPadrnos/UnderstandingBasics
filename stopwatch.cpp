#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

class Stopwatch {
    private:
        steady_clock::time_point start_time;
        steady_clock::time_point end_time;
        bool is_running;

    public:
        Stopwatch() : is_running(false) {}

        void start() {
            if (!is_running) {
                start_time = steady_clock::now();
                is_running = true;
                cout << "Stopwatch started." <<endl;
            } else {
                cout << "Stopwatch is already running." <<endl;
            }
        }

        void stop() {
            if (is_running) {
                end_time = steady_clock::now();
                is_running = false;
                cout << "Stopwatch stopped." << endl;
            } else {
                cout << "Stopwatch is not running." << endl;
            }
        }

        void reset() {
            start_time = end_time = steady_clock::now();
            cout << "Stopwatch reset." << endl;
        }

        void displayElapsedTime() {
            if (!is_running) {
                duration<double> elapsed_seconds = end_time - start_time;
                cout << "Elapsed time: " << elapsed_seconds.count() << " seconds." << endl;
            } else {
                steady_clock::time_point current_time = steady_clock::now();
                duration<double> elapsed_seconds = current_time - start_time;
                cout << "Elapsed time: " << elapsed_seconds.count() << " seconds." << endl;
            }
        }
    };

int main() {
    Stopwatch stopwatch;
    int choice;

    do {
        cout << "\nStopwatch Menu:\n";
        cout << "1. Start\n";
        cout << "2. Stop\n";
        cout << "3. Reset\n";
        cout << "4. Display Elapsed Time\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                stopwatch.start();
                break;
            case 2:
                stopwatch.stop();
                break;
            case 3:
                stopwatch.reset();
                break;
            case 4:
                stopwatch.displayElapsedTime();
                break;
            case 0:
                cout << "Exiting program.\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 0);

    return 0;
}