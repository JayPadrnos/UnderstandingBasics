#ifndef NOTEDATABASE_HPP
#define NOTEDATABASE_HPP

#include "Note.hpp"
#include <vector>

class NotesDatabase {
    private:
        std::vector<Note> notes;

    public:
        void addNote(const Note& note);
        void displayAllNotes() const;

    private:
        void saveToFile(const Note& note) const;
};

#endif // NOTESDATABASE_HPP

