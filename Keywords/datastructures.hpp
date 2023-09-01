#ifndef DATA_STRUCTURES_HPP
#define DATA_STRUCTURES_HPP

#include <string>

class Example {
    public:
        std::string text;
};

class Category {
    public:
        std::string name;
};

class Subject {
    public:
        std::string name;
        Category category;
};

class Keyword {
    public:
        std::string word;
        std::string definition;
        Subject subject;
        Example example;
};

#endif // DATA_STRUCTURES_HPP