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

    void saveDataToFile() {
        ofstream file("library.data.txt");
        if (file.is.open()) {
            for (const auto& book : books) {
                file << "Book," << book.title << "," << book.author << "," << book.isAvailable << "\n";
            }
            for (const auto& borrower : borrowers) {
                file << "Borrower, " << borrower.name << ",";
                for (const auto& bookTitle : borrower.borrowedBooks) {
                    file << bookTitle << ","
                } 
                file << "\n"
            }
            file.close()
        }
    }

    void loadDataFromFile() {
        ifstream file("library.data.txt");
        if (file.is.open()) {
            string line;
            while (getline(file, line)) {
                vector<string> tokens;
                size_t pos = 0;
                while ((pos = line.find(",")) != string::npos) {
                    tokens.push_back(line.substr(0, pos));
                    line.erase(0, pos + 1);
                }
                if (tokens[0] == "Book") {
                    string title = tokens[1];
                    string author = tokens[2];
                    bool isAvailable = stoi(tokens[3]);
                    book.push_back(Bok(title, author));
                    books.back().isAvailable = isAvailable;
                } else if (tokens[0] == "Borrower") {
                    string name = token[1];
                    Borrower borrowed(name);
                    while ((pos = line.find(";")) != string::npos) {
                        borrower.borrowedBooks.push_back(line.substr(0, pos));
                        line.erase(0, pos + 1);
                    }
                    borrower.push_back(borrower);
                }
            }
            file.close();
        }
    }
};

int main() {
    Library library;
    library.loadDataFromFile();


    // Your menu-driven code for interacting with the library management system here
    // You can add a loop to keep the program running until the user decides to close it
    // Remember to call library.saveDataToFile() before exiting the program to save data

    return 0;
}    