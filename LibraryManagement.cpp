#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
//This is changed file.

using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    int year;
    float price;

    Book() {}

    Book(int i, string t, string a, int y, float p) {
        id = i;
        title = t;
        author = a;
        year = y;
        price = p;
    }

    void display() const {
        cout << "ID: " << id << "\nTitle: " << title << "\nAuthor: " << author
             << "\nYear: " << year << "\nPrice: $" << price << "\n";
        cout << "--------------------------------------\n";
    }

    string toString() const {
        return to_string(id) + "|" + title + "|" + author + "|" + to_string(year) + "|" + to_string(price);
    }

    static Book fromString(const string& line) {
        size_t pos = 0;
        size_t next;
        vector<string> tokens;

        while ((next = line.find('|', pos)) != string::npos) {
            tokens.push_back(line.substr(pos, next - pos));
            pos = next + 1;
        }
        tokens.push_back(line.substr(pos)); // Last element

        return Book(stoi(tokens[0]), tokens[1], tokens[2], stoi(tokens[3]), stof(tokens[4]));
    }
};

class Library {
private:
    vector<Book> books;
    string filename = "library.txt";

    void loadFromFile() {
        ifstream file(filename);
        string line;

        books.clear();
        while (getline(file, line)) {
            books.push_back(Book::fromString(line));
        }
        file.close();
    }

    void saveToFile() {
        ofstream file(filename);
        for (const Book& b : books) {
            file << b.toString() << endl;
        }
        file.close();
    }

public:
    Library() {
        loadFromFile();
    }

    void addBook() {
        int id, year;
        float price;
        string title, author;

        cout << "Enter ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        cout << "Enter Year: ";
        cin >> year;
        cout << "Enter Price: ";
        cin >> price;

        books.emplace_back(id, title, author, year, price);
        saveToFile();
        cout << "Book added successfully!\n";
    }

    void viewAllBooks() const {
        if (books.empty()) {
            cout << "No books available.\n";
            return;
        }

        for (const Book& b : books) {
            b.display();
        }
    }

    void searchByTitle() const {
        string keyword;
        cin.ignore();
        cout << "Enter title to search: ";
        getline(cin, keyword);

        bool found = false;
        for (const Book& b : books) {
            if (b.title.find(keyword) != string::npos) {
                b.display();
                found = true;
            }
        }

        if (!found)
            cout << "No book found with that title.\n";
    }

    void deleteBook() {
        int id;
        cout << "Enter book ID to delete: ";
        cin >> id;

        auto it = remove_if(books.begin(), books.end(), [id](Book& b) {
            return b.id == id;
        });

        if (it != books.end()) {
            books.erase(it, books.end());
            saveToFile();
            cout << "Book deleted successfully.\n";
        } else {
            cout << "Book not found.\n";
        }
    }

    void updateBook() {
        int id;
        cout << "Enter book ID to update: ";
        cin >> id;

        for (Book& b : books) {
            if (b.id == id) {
                cout << "Updating Book with ID: " << id << "\n";

                cin.ignore();
                cout << "Enter new Title: ";
                getline(cin, b.title);
                cout << "Enter new Author: ";
                getline(cin, b.author);
                cout << "Enter new Year: ";
                cin >> b.year;
                cout << "Enter new Price: ";
                cin >> b.price;

                saveToFile();
                cout << "Book updated successfully!\n";
                return;
            }
        }

        cout << "Book not found.\n";
    }
};

void showMenu() {
    cout << "\n====== LIBRARY MENU ======\n";
    cout << "1. Add Book\n";
    cout << "2. View All Books\n";
    cout << "3. Search Book by Title\n";
    cout << "4. Delete Book\n";
    cout << "5. Update Book\n";
    cout << "6. Exit\n";
    cout << "Choose an option: ";
}

int main() {
    Library lib;
    int choice;

    do {
        showMenu();
        cin >> choice;

        switch (choice) {
            case 1: lib.addBook(); break;
            case 2: lib.viewAllBooks(); break;
            case 3: lib.searchByTitle(); break;
            case 4: lib.deleteBook(); break;
            case 5: lib.updateBook(); break;
            case 6: cout << "Exiting program...\n"; break;
            default: cout << "Invalid option.\n";
        }
    } while (choice != 6);

    return 0;
}
