#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Book {
public:
    Book(int isbn, string title, string author, int publicationYear)
        : isbn(isbn), title(title), author(author), publicationYear(publicationYear), available(true) {}

    int getISBN() const { return isbn; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }
    int getPublicationYear() const { return publicationYear; }
    bool isAvailable() const { return available; }
    void setAvailability(bool status) { available = status; }

private:
    int isbn;
    string title;
    string author;
    int publicationYear;
    bool available;
};

class User {
private:
    int id;
    string contact;
    string name;
    string membershipType;
    string password;
    int borrowedBooks;
    int borrowingLimit;
    double borrowingFee;

public:
    User(int userId, string userContact, string userName, string userMembershipType, string userPassword)
        : id(userId), contact(userContact), name(userName), membershipType(userMembershipType), password(userPassword), borrowedBooks(0) {
        setMembershipDetails();
    }

    void setMembershipDetails() {
        if (membershipType == "student") {
            borrowingLimit = 3;
            borrowingFee = 5.0; // Student fee per book borrowed
        } else if (membershipType == "faculty") {
            borrowingLimit = 5;
            borrowingFee = 0.0; // Faculty members borrow for free
        } else if (membershipType == "staff") {
            borrowingLimit = 4;
            borrowingFee = 3.0; // Staff fee per book borrowed
        }
    }

    int getId() const { return id; }
    string getContact() const { return contact; }
    string getName() const { return name; }
    string getMembershipType() const { return membershipType; }
    int getBorrowedBooks() const { return borrowedBooks; }
    double getBorrowingFee() const { return borrowingFee; }
    int getBorrowingLimit() const { return borrowingLimit; }

    void setContact(string userContact) { contact = userContact; }
    void setName(string userName) { name = userName; }
    void setMembershipType(string userMembershipType) { membershipType = userMembershipType; }
    void setPassword(string userPassword) { password = userPassword; }

    bool loginUser(string userContact, string userPassword) {
        if (contact == userContact && password == userPassword) {
            cout << "Login successful!" << endl;
            return true;
        } else {
            cout << "Login failed. Please check your contact and password." << endl;
            return false;
        }
    }

    bool canBorrow() {
        return borrowedBooks < borrowingLimit;
    }

    void incrementBorrowedBooks() {
        borrowedBooks++;
    }

    void decrementBorrowedBooks() {
        borrowedBooks--;
    }

    void displayUserInfo() const {
        cout << "ID: " << id << "\n"
             << "Contact: " << contact << "\n"
             << "Name: " << name << "\n"
             << "Membership Type: " << membershipType << "\n"
             << "Borrowed Books: " << borrowedBooks << "/" << borrowingLimit << endl;
    }
};

class Library {
public:
    void addBook(Book book) {
        books.push_back(book);
    }

    void borrowBook(User* user, Book& book) {
        if (book.isAvailable() && user->canBorrow()) {
            book.setAvailability(false);
            user->incrementBorrowedBooks();
            double fee = user->getBorrowingFee();
            if (fee > 0) {
                cout << user->getName() << " has borrowed '" << book.getTitle() << "' with a fee of R" << fee << ".\n";
            } else {
                cout << user->getName() << " has borrowed '" << book.getTitle() << "' for free.\n";
            }
        } else if (!book.isAvailable()) {
            cout << "'" << book.getTitle() << "' is currently not available.\n";
        } else {
            cout << user->getName() << " has reached their borrowing limit of " << user->getBorrowingLimit() << " books.\n";
        }
    }

    void returnBook(User* user, Book& book) {
        if (!book.isAvailable()) {
            book.setAvailability(true);
            user->decrementBorrowedBooks();
            cout << user->getName() << " has returned '" << book.getTitle() << "'.\n";
        } else {
            cout << "'" << book.getTitle() << "' was not borrowed by " << user->getName() << ".\n";
        }
    }

    void displayBooks() {
        for (const auto& book : books) {
            cout << "Title: " << book.getTitle() << " | Author: " << book.getAuthor() << " | Year: " << book.getPublicationYear()
                 << " | Available: " << (book.isAvailable() ? "Yes" : "No") << endl;
        }
    }

    vector<Book>& getBooks() {
        return books;
    }

private:
    vector<Book> books;
};

int main() {
    Library library;

    // Predefined books with 4-digit ISBNs
    library.addBook(Book(1234, "The C Programming Language", "Brian W. Kernighan, Dennis M. Ritchie", 1988));
    library.addBook(Book(5678, "C++ Primer", "Stanley B. Lippman", 2012));
    library.addBook(Book(9101, "Clean Code", "Robert C. Martin", 2008));
    library.addBook(Book(1122, "The Pragmatic Programmer", "Andrew Hunt, David Thomas", 1999));
    library.addBook(Book(3344, "Structure and Interpretation of Computer Programs", "Harold Abelson, Gerald Jay Sussman", 1996));

    // User input to create a new user
    int userId;
    string contact, name, membershipType, password;

    cout << "Welcome to the Library System\n";
    cout << "Please enter your details to register:\n";
    cout << "ID: ";
    cin >> userId;
    cout << "Contact: ";
    cin >> contact;
    cout << "Name: ";
    cin.ignore(); // to clear the newline left by the previous input
    getline(cin, name);
    cout << "Membership Type: ";
    getline(cin, membershipType);
    cout << "Password: ";
    getline(cin, password);

    User user(userId, contact, name, membershipType, password);

    // Login prompt
    string loginContact, loginPassword;
    cout << "\nPlease enter your contact and password to login:\n";
    cout << "Contact: ";
    cin >> loginContact;
    cout << "Password: ";
    cin >> loginPassword;

    if (user.loginUser(loginContact, loginPassword)) {
        while (true) {
            int choice;
            cout << "\nMenu:\n1. Add book\n2. Return book\n3. Borrow book\n4. Display books\n5. Exit\nEnter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: {
                    int isbn, publicationYear;
                    string title, author;
                    cout << "Enter ISBN: ";
                    cin >> isbn;
                    cout << "Enter Title: ";
                    cin.ignore();
                    getline(cin, title);
                    cout << "Enter Author: ";
                    getline(cin, author);
                    cout << "Enter Publication Year: ";
                    cin >> publicationYear;

                    library.addBook(Book(isbn, title, author, publicationYear));
                    cout << "Book added successfully.\n";
                    break;
                }
                case 2: {
                    int isbn;
                    cout << "Enter ISBN of the book to return: ";
                    cin >> isbn;
                    for (auto& book : library.getBooks()) {
                        if (book.getISBN() == isbn) {
                            library.returnBook(&user, book);
                            break;
                        }
                    }
                    break;
                }
                case 3: {
                    int isbn;
                    cout << "Enter ISBN of the book to borrow: ";
                    cin >> isbn;
                    for (auto& book : library.getBooks()) {
                        if (book.getISBN() == isbn) {
                            library.borrowBook(&user, book);
                            break;
                        }
                    }
                    break;
                }
                case 4:
                    library.displayBooks();
                    break;
                case 5:
                    return 0;
                default:
                    cout << "Invalid choice. Please try again.\n";
            }
        }
    } else {
        cout << "Login failed. Exiting program.\n";
    }

    return 0;
}
