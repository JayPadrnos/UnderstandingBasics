#include <iostream>
using namespace std;

class DetectionMeter {
    private:
    float currentLevel;
    float maxLevel;

    public:
    DetectionMeter(float max) : currentLevel(0), maxLevel(max) {}

    void Update(float detectionValue) {
        currentLevel = detectionValue;
        // Ensure the detection level stays within bounds
        currentLevel = max(0.0f, min(currentLevel, maxLevel));
    }

    void Display(int width) {
        int filledWidth = static_cast<int>((currentLevel / maxLevel) * width);

        cout << "detection Meter: [";
        for (int i = 0; i < width; ++i) {
            if (i < filledWidth) {
                cout << "#";
            } else {
                cout << "-";
            }
        }
        cout << "]" << endl;
    }
};

int main() {
    DetectionMeter meter(100.0f);

    // Update the meter with a sample detection value
    meter.Update(50.0f);

    // Display the meter
    meter.Display(20);

    return 0;
}
