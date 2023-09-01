#include "Note.hpp"
#include <iostream>

Note::Note(const std::string& _title, const std::string& _content)
    : title(_title), content(_content) {}

void Note::display() const {
    std::cout << "Title: " << title << "\n";
    std::cout << "Content: " << content << "\n";
}

std::string Note::getTitle() const {
    return title;
}

std::string Note::getContent() const {
    return content;
}