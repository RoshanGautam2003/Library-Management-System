#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;
class Book
{
protected:
    string bookName;
    string authorName;
    int bookID;
    bool isAvailable;
    static int nextID; // there is only one copy of this variable shared by all objects of the class.

public:
    Book()
    {
        this->bookName = " ";
        this->authorName = " ";
        this->bookID = 0;
        this->isAvailable = true;
    }
    Book(string bookName, string authorName, int bookID, bool isAvailable)
    {
        this->bookName = bookName;
        this->authorName = authorName;
        this->bookID = ++nextID; // This is optional.
        this->isAvailable = isAvailable;
    }
    virtual void addBook()
    {
        cout << "Enter the Book Name:" << endl;
        getline(cin, this->bookName);
        cout << "Enter the Author Name:" << endl;
        getline(cin, this->authorName);
        this->bookID = ++nextID;
        cout << "The Book ID is: " << this->bookID << endl;
        this->isAvailable = true;
        cout << "The Book Added Succesfully:" << endl;
    }
    virtual void savetoFile(ofstream &outfile)
    {
        outfile << this->bookName << endl;
        outfile << this->authorName << endl;
        outfile << this->bookID << endl;
        outfile << this->isAvailable << endl;
    }
    virtual void readfromFile(ifstream &infile)
    {
        getline(infile, bookName);
        getline(infile, authorName);
        infile >> bookID;
        infile >> this->isAvailable;
        infile.ignore();
    }
    virtual void displayBook()
    {
        cout << "The Book Name is: " << this->bookName << endl;
        cout << "The Author Name is: " << this->authorName << endl;
        cout << "The Book ID is: " << this->bookID << endl;
        if (isAvailable)
        {
            cout << "The Book is Available:" << endl;
        }
        else
        {
            cout << "The Book is not Available:" << endl;
        }
    }
    void issueBook()
    {
        if (this->isAvailable)
        {
            this->isAvailable = false;
            cout << "The Book is Issued Succesfully:" << endl;
        }
        else
        {
            cout << "The Book is Already Issued:" << endl;
        }
    }
    void returnBook()
    {
        if (this->isAvailable)
        {
            cout << "The Book is not Issued Yet:" << endl;
        }
        else
        {
            this->isAvailable = true;
            cout << "The Book is Returned Succesfully:" << endl;
        }
    }
    int getbookID() // This is a getter function, to acess the bookID.
    {
        return this->bookID;
    }
};
class Ebook : public Book
{
protected:
    string downloadLink;
    float fileSize;

public:
    Ebook() : Book()
    {
        this->downloadLink = " ";
        this->fileSize = 0.0;
    }
    Ebook(string bookName, string authorName, int bookID, bool isAvailable, string downloadLink, float fileSize) : Book(bookName, authorName, bookID, isAvailable)
    {
        this->downloadLink = downloadLink;
        this->fileSize = fileSize;
    }
    void addBook()
    {
        Book::addBook();
        cout << "Enter the Download Link :" << endl;
        getline(cin, this->downloadLink);
        cout << "Enter The Size of The Book in MB(Enter Number only)" << endl;
        cin >> this->fileSize;
        cin.ignore();
    }
    void savetoFile(ofstream &outfile)
    {
        Book::savetoFile(outfile);
        outfile << this->downloadLink << endl;
        outfile << this->fileSize << endl;
    }
    void readfromFile(ifstream &infile)
    {
        Book::readfromFile(infile);
        getline(infile, this->downloadLink);
        infile >> this->fileSize;
        infile.ignore();
    }
    void displayBook()
    {
        Book::displayBook();
        cout << "Download Link: " << this->downloadLink << endl;
        cout << "File Size: " << this->fileSize << endl;
    }
    void downloadBook()
    {
        if (this->isAvailable)
        {
            cout << "Click the Link: " << this->downloadLink << "to download the Book:" << endl;
            cout << "Size is: " << this->fileSize << endl;
        }
        else
        {
            cout << "The Book is Not Available:" << endl;
        }
    }
};
int Book::nextID = 999;
int main()
{
    cout << "------------------------------" << endl;
    cout << "LIBRARY MANAGEMENT SYSTEM" << endl;
    cout << "------------------------------" << endl;
    vector<Book *> Library; // Lirary is a vector that stores the pointer object of Book Class.
    int choice;
    do
    {
        cout << "\n 1. Add Book" << endl;
        cout << "2. Issue Book" << endl;
        cout << "3. Return Book" << endl;
        cout << "4. Download Book" << endl;
        cout << "5. Display Book" << endl;
        cout << "6. Save To File" << endl;
        cout << "7. Load From File" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter Your Choice:" << endl;
        cin >> choice;
        cin.ignore();
        switch (choice)
        {
        case 1:
        {
            int type;
            cout << "1. Book" << endl;
            cout << "2. Ebook" << endl;
            cout << "Enter Your Choice:" << endl;
            cin >> type;
            cin.ignore();
            if (type == 1)
            {
                Book *b = new Book(); // nameless book object is created and its adress is stored in b which is a object pointer of book type.
                b->addBook();
                Library.push_back(b);
            }
            else if (type == 2)
            {
                Ebook *e = new Ebook();
                e->addBook();
                Library.push_back(e);
            }
            break;
        }
        case 2:
        {
            int id;
            cout << "Enter Book ID to Issue:" << endl;
            cin >> id;
            cin.ignore();
            for (int i = 0; i < Library.size(); i++)
            {
                if (Library[i]->getbookID() == id)
                {
                    Library[i]->issueBook();
                    break;
                }
            }
            break;
        }
        case 3:
        {
            int id;
            cout << "Enter Book ID to Return:" << endl;
            cin >> id;
            cin.ignore();
            for (int i = 0; i < Library.size(); i++)
            {
                if (Library[i]->getbookID() == id)
                {
                    Library[i]->returnBook();
                    break;
                }
            }
            break;
        }
        case 4:
        {
            int id;
            cout << "Enter Book ID to Download:" << endl;
            cin >> id;
            cin.ignore();
            for (int i = 0; i < Library.size(); i++)
            {
                if (Library[i]->getbookID() == id)
                {
                    Ebook *e = dynamic_cast<Ebook *>(Library[i]);
                    if (e != nullptr)
                    {
                        e->downloadBook();
                    }
                    else
                    {
                        cout << "This is not an Ebook:" << endl;
                    }
                }
            }
            break;
        }
        case 5:
        {
            for (int i = 0; i < Library.size(); i++)
            {
                Library[i]->displayBook();
            }
            break;
        }
        case 6:
        {
            ofstream outfile("Library.txt");
            if (!outfile)
            {
                cout << "Error:" << endl;
                return 1;
            }
            else
            {
                outfile << Library.size() << endl;
                for (int i = 0; i < Library.size(); i++)
                {
                    Ebook *e = dynamic_cast<Ebook *>(Library[i]);
                    if (e != nullptr)
                    {
                        outfile << "Ebook" << endl;
                    }
                    else
                    {
                        outfile << "Book" << endl;
                    }
                    Library[i]->savetoFile(outfile);
                }
                outfile.close();
            }
            break;
        }
        case 7:
        {
            ifstream infile("Library.txt");
            if (!infile)
            {
                cout << "Error" << endl;
                return 1;
            }
            else
            {
                int size;
                infile >> size;
                infile.ignore();
                for (int i = 0; i < size; i++)
                {
                    string type;
                    getline(infile, type);
                    if (type == "Ebook")
                    {
                        Ebook *e = new Ebook();
                        e->readfromFile(infile);
                        Library.push_back(e);
                    }
                    else
                    {
                        Book *b = new Book();
                        b->readfromFile(infile);
                        Library.push_back(b);
                    }
                }
                infile.close();
            }
            break;
        }
        case 8:
        {
            cout << "Good Bye!!" << endl;
            break;
        }
        default:
        {
            cout << "Invalid Choice!!" << endl;
            break;
        }
        }
    } while (choice != 8);
    return 0;
}