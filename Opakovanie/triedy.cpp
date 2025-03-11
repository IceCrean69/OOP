#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;


class Book {
    public:
    string title;
    string author;
    int bookID;
    bool isAvailable;
    
    public:
    Book(string t, string a, int id) 
    : title(t), author(a), bookID(id), isAvailable(true) {}
    
    virtual void displayInfo() {
        cout << "Title: " << title << "\nAuthor: " << author
        << "\nISBN: " << bookID << "\nStatus: " 
        << (isAvailable ? "Available" : "Borrowed") << endl;
    }
    
    bool checkAvailability() { return isAvailable; }
    void updateStatus(bool status) { isAvailable = status; }
};


class LibraryMember
{
    public:
        string name;
        int memberID;
        vector<Book*> borrowedBooks;
        
    public:
    LibraryMember(string n, int ID, vector<Book*> b): name(n), memberID(ID), borrowedBooks(b){}
    
    void borrowBook(Book* book)
    {
        borrowedBooks.push_back(book);
        book->updateStatus(false);
        return;
    }

    void removeBorrowedBook(int bookID)
    {
        borrowedBooks.erase(borrowedBooks.begin() + bookID);
    }
    
    void introduction()
    {
        cout<< "Hello my name is:" << name << 
        "\nmy ID is: " << memberID << endl;
    }

    void showBorrowedBooks()
    {
        for (auto i: borrowedBooks)
        {
            cout << i->author<< endl;
        }
    }

};
class Library 
{
    public:
        vector<Book*> books;
        vector<LibraryMember*> members;
        int memberCount = 0;
        int bookCount = 0;
    
    public:
        void addBook(Book* newBook) 
        {
            books.push_back(newBook);
            bookCount += 1;
            cout << "New book added" << endl;
        }
        void addMember(LibraryMember* newMember)
        {
            members.push_back(newMember);
            memberCount += 1;
            cout << "New member added: " << newMember->name << endl;
        }

        void listAllMembers()
        {
            for (auto i: members)
            {
                cout << "\nMember kys: " << i->name << 
                        "\nMember id: " << i->memberID << endl;
                
                if (i->borrowedBooks.empty()) 
                {
                    cout << "Member did not borrow any books" << endl;
                } else 
                {
                    for (auto j: i->borrowedBooks)
                    {
                        cout << "\nBook Title: " << j->title
                            << "\nBook Author: " << j->author
                            << "\nBook ISBN: " << j->bookID << endl;
                    }
                }
            }
        }
        void checkAllAvailableBooks()
        {
            for(auto i: books)
            {
                if(i->checkAvailability() == true)
                {
                    cout<<"\nTitle: " << i->title << "\nAuthor: "<< i->author 
                        << "\nISBN: " << i->bookID << "\nStatus: " << (i->isAvailable ? "Available": "Borrow") << endl;
                }
            }
            
        }

        LibraryMember* findMember(int memberID)
        {
            for (auto member: members)
            {
                if(member->memberID == memberID)
                {
                    return member;
                }
                else
                {
                    cout << "user not found"<< endl;
                    return NULL;
                }
            }
            return NULL;
        }

        Book* findBook(int bookID)
        {
            for (auto book: books)
            {
                if(book-> bookID == bookID)
                {
                    return book;
                }
                else
                {
                    cout << "book not found" << endl;
                    return NULL;
                }
            }
            return NULL;
        }
        
        void checkoutBook(Book* book, LibraryMember& member)
        {
            if(book->checkAvailability()) {
                book->updateStatus(false);
                member.borrowBook(book);
                cout << "Book: " << book->title << " borrowed by: " << member.name << endl;
            }
        }

        void checkInBook(Book* book, LibraryMember&  member)
        {
            if(book->checkAvailability() == false)
            {
                book->updateStatus(true);
                member.removeBorrowedBook(book->bookID);
                cout << "Book removed" << endl;
            }
        }
};

int main() 
{
    int x;
    Library library;

    while(true)
    {   
        cout << "\nVyberte moznost" << endl;
        cout << "1. Add member" << endl;
        cout << "2. Add book" << endl;
        cout << "3. Show all members" << endl;
        cout << "4. Show all available books" << endl;
        cout << "5. Borrow book" << endl;
        cout << "6. Return book" << endl;
        cout << "Any other number: exit" << endl;
        cout << "Input: ";
        cin >> x;
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        switch (x)
        {
            case 1:
            {
                string name;
                cout << "\nInput name: ";
                cin >> name;

                LibraryMember* member = new LibraryMember(name, library.memberCount, {});
                library.addMember(member);
                break;
            }
            case 2:
            {
                string title, author;
                
                cout << "\nInput title: ";
                getline(cin, title);
                cout << "Input author of given title: ";
                getline(cin, author);
                Book* book = new Book(title, author, library.bookCount);
                library.addBook(book);

                break;
        
            }
            case 3:
            {
                library.listAllMembers();
                break;
            }
            case 4:
            {
                library.checkAllAvailableBooks();
                break;
            }
            case 5:
                int bookID, memberID;
                cout << "Input userID: "; 
                cin >> memberID;
                cout << "\nIput bookID: ";
                cin >> bookID;

                library.checkoutBook(library.findBook(bookID), *library.findMember(memberID));

                break;
            case 6:
                
                cout << "Input userID: "; 
                cin >> memberID;
                cout << "\nIput bookID: ";
                cin >> bookID;

                library.checkInBook(library.findBook(bookID), *library.findMember(memberID));
                break;
            default:
            {
                return false;
            }
        }

    }


    return 0;
} 