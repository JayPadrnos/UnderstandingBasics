#ifndef USERINPUTHANDLER_HPP
#define USERINPUTHANDLER_HPP

#include "NoteDatabase.hpp"

class UserInputHandler {
    private:
        NotesDatabase& database;

    public:
        UserInputHandler(NotesDatabase& _database);
        void startInputLoop();
};

#endif // USERINPUTHANDLER_HPP