#include "Note.hpp"
#include "NoteDatabase.hpp"
#include "UserInputHandler.hpp"

int main() {
    NotesDatabase notesDatabase;
    UserInputHandler inputHandler(notesDatabase);
    inputHandler.startInputLoop();

    return 0;
}