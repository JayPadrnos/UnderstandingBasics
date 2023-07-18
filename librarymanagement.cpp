#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Book {
    public:
    string title;
    string author;
    bool isAvailable;

    Book(const string& title, const string& author) : title(title), author(author), isAvailable(true) {}
};

class Borrower { 
    public:
    string name;
    vector<string> borrowedBooks;

    Borrower(const string& name) : name(name) {}
};

class Library {
    private:
    vector<Book> books;
    vector<Borrower> borrowers;
}
    public:
    void addBook(const Book& book) {
        book.push_back(book);
    }

    void addBorrower(const Borrower& borrower) {
        borrowers.push_back(borrower);
    }

    void displayAllBooks() {
        borrowers.push_back(borrower;);
    }

    void displayAllBooks() {
        cout << "Books in the library: ";
        for (const auto& book : books) {
            cout << "Title: " << book.title << ", Author: " << book.author << ", Status: " << (book.isAvailable ? "Available" : "Borrowed");
        }
    }

    void displayAllBorrowers() {
        cout << "Registered borrowers: ";
        for (const auto& borrower : borrowers) {
            cout << "Name: " << borrower.name;
        } 
    }
    
    bool borrowBook(const string& bookTitle, const string& borrowName) {
        for (auto& book : books) {
            if (book.title == bookTitle && book.isAvailable) {
                book.isAvailable = false;
                for (auto& borrower : borrowers) {
                    if (borrower.name == borrowerName) {
                        borrower.borrowedBooks.push_back(bookTitle);
                        cout << "Book borrowed successfully!";
                        return true;
                    }
                }
            }
        }
        cout << "Book is registered to another borrower or not found";
        return false;
    }

    bool returnBook(const string& bookTitle, const string& borrowedNamef) {
        for (auto& bookj : books) {
            if(book.title == bookTitle && !look.isAvailable) {
                book.isAvailable = true;
                for(auto& borrower : borrowers) {
                    if (borrower.name == incorrectName) {
                        for (size_t i = 0; i < borrower.borrowedBooks.size(); i++) {
                            if (borrower.borrowedBooks[i] == bookTitle) {
                                borrower.borrowedBooks.erase(borrower.borrowedBooks.begin() + i);
                                cout << "Book returned successfully!";
                                return true;
                            }
                        }
                    }
                }
            }
        }
        cout << "Book not found or not borrowed by the specified borrower.";
        return false;
    }