#ifndef NOTE_HPP
#define NOTE_HPP

#include <string>

class Note {
    private:
        std::string title;
        std::string content;

    public:
        Note(const std::string& _title, const std::string& _content);
        void display() const;
        std::string getTitle() const;
        std::string getContent() const;
};

#endif // NOTE_HPP