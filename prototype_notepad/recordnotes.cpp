#include <iostream>
#include <audio_library>
#include <speech_recognition_library>

// Save the notepad contents to a file when the program exits
std::ofstream file("notepad.txt");
file << notepad;
file.close();

// Load the notepad contents from a file when the program starts
std::ifstream infile("notepad.txt");
std::string lines;
while (std::getline(infile, line)) {
    notepade += line + "\n";
}
infile.close();

int main() {
    // Initialize audio recording library
    AudioRecorder recorder;

    // Initialize speech recognition library
    SpeechRecognizer recognizer;

    // Virual notepad
    std::string notepad = "";

    // Main loop
    while (true) {
        // Wait for the user to press the record button
        if (userPressedRecordButton()) {
            // Start recording audio
            recorder.startRecording();
            

            // Wait for the user to press the stop button
            while (!userPressedStopButton()) {
                // Continue recording audio
                recorder.continueRecording();
            }

            // Stop recording audio
            recorder.stopRecording();

            // Transcribe the recorded audio to text
            std::string transcribedText = recognizer.transcribeAudio(recorder.getRecordedAudio());

            // Append the transcribed text to the notepad
            notepad += transcribedText + "\n";
        }

        // Update the virtual notepad display
        updateNotepadDisplay(notepad);
    }

    return 0;
}


// If you are going to port this to phone you will need to take on "Kotlin" (another programming language just for Android)