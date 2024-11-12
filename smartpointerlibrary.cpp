#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

// Book class definition
class Book {
    std::string title;
    std::string author;
    std::string isbn;
    bool available;

public:
    Book(const std::string& title, const std::string& author, const std::string& isbn)
        : title(title), author(author), isbn(isbn), available(true)  {}

        std::string getTitle() const { return title; }
        std::string getAuthor() const { return author; }
        std::string getISBN() const {return isbn; }
        bool isAvailable() const { return available; }


        // Setter function to mark book as available or not
        void setAvailability(bool status) {available = status; }
};

// Patron class definition
class Patron {
    std::string name;
    std::string id;

public:
    Patron(const std::string& name, const std::string& id)
        : name(name), id(id) {}

    std::string getName() const { return name; }
    std::string getID() const { return id; }
};

// Library class definition
class Library {
    std::vector<std::shared_ptr<Book>> books;
    std::vector<std::shared_ptr<Patron>> patrons;

public:
    void addBook (const Book& book) {
        books.push_back(std::make_shared<Book>(book));
    }

    void addPatron(const Patron& patron) {
        patrons.push_back(std::make_shared<Patron>(patron));
    }

    std::string checkOutBook(const std::string& patronID, const std::string& bookTitle) {
        // Find the book and the patron
        auto bookIter = std::find_if(books.begin(), books.end(), [&](const auto& book) {
            return book->getTitle() == bookTitle;
        });

        auto patronIter = std::find_if(patrons.begin(), patrons.end(), [&](const auto& patron) {
            return patron->getID() == patronID;
        });

        // Check if the both book and patron exist
        if (bookIter != books.end() && patronIter != patrons.end()) {
            // Book and patron found, perform checkout
            // Here we use a ternary operator to determine if the book is available
            std::string result = (*bookIter)->getTitle() + ((*bookIter)->isAvailable() ? " is available and checked out by " : "is not available");
            return result;
        } else {
            // Book or patron not found
            return "Book or patron not found.";
        }
    }
};

int main() {
    Library library;

    // Adding books and patrons
    library.addBook(Book("The Great Gatsby", "F. Scott Fitzgerald", "9780743273565"));
    library.addBook(Book("To Kill a Mockingbird", "Harper Lee", "97800611200084"));
    library.addBook(Book("1984", "George Orwell", "9780451524935"));

    library.addPatron(Patron("Alice", "1001"));
    library.addPatron(Patron("Bob", "1002"));

    // Check out book
    std::cout << library.checkOutBook("1001", "The Great Gatsby") << std::endl;

    return 0;
}