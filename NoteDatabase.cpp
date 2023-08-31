#include "NoteDatabase.hpp"
#include <iostream>
#include <fstream>

void NotesDatabase::addNote(const Note& note) {
    notes.push_back(note);
    saveToFile(note);
}

void NotesDatabase::displayAllNotes() const {
    for (const Note& note : notes) {
        note.display();
    }
}

void NotesDatabase::saveToFile(const Note& note) const {
    std::ofstream outputFile("notes.txt" , std::ios::app);
    if (!outputFile) {
        std::cerr << "Error opening file for writing!" << std::endl;
        return;
    }

    outputFile << "Title: " << note.getTitle() << "\n";
    outputFile << "Content: " << note.getContent() << "\n";

    std::cout << "Note saved successfully!" << std::endl;
}