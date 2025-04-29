#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Book structure
struct Book {
    int id;
    string title;
    string author;
    int year;

    void display() {
        cout << "ID: " << id << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Year: " << year << endl;
        cout << "----------------------" << endl;
    }
};

int main() {
    vector<Book> library;
    int choice;

    do {
        cout << "\n1. Add Book\n2. Display All Books\n3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            Book b;
            cout << "Enter Book ID: ";
            cin >> b.id;
            cin.ignore();  // Clear input buffer
            cout << "Enter Title: ";
            getline(cin, b.title);
            cout << "Enter Author: ";
            getline(cin, b.author);
            cout << "Enter Year: ";
            cin >> b.year;
            library.push_back(b);
            cout << "Book added successfully!\n";
        }
        else if (choice == 2) {
            cout << "\nList of Books:\n";
            for (const Book& b : library) {
                b.display();
            }
        }

    } while (choice != 3);

    return 0;
}
