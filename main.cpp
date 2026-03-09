#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <queue>
using namespace std;
void sortbooks();

struct book
{
    int id;
    string title;
    string author;
    bool issued;
    queue<string> waitinglist;
};
vector<book> books;
void addbook()
{
    book b;
    cout << "Enter book ID : ";
    cin >> b.id;
    cin.ignore();
    cout << "Enter book title : ";
    getline(cin, b.title);
    cout << "Enter Author name : ";
    getline(cin, b.author);
    b.issued = false;
    for (auto &bk : books)
    {
        if (bk.id == b.id)
        {
            cout << "Book ID already exists\n";
            return;
        }
    }
    books.push_back(b);
    sortbooks();
    cout << "Book added sucuessfully\n";
}
void displaybook()
{
    if (books.empty())
    {
        cout << "No books available.\n";
        return;
    }

    cout << " ====== Book list ====== \n";
    for (int i = 0; i < books.size(); i++)
    {
        cout << "Book ID : " << books[i].id << endl;
        cout << "Title : " << books[i].title << endl;
        cout << "Author : " << books[i].author << endl;
        if (books[i].issued)
            cout << "Status : Issued.\n";

        else
            cout << "Status : Available.\n";

        cout << "\n-----------------\n";
    }
}
void searchbook()
{
    int id;
    cout << "Enter Book ID to search : ";
    cin >> id;

    int left = 0;
    int right = books.size() - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;

        if (books[mid].id == id)
        {
            cout << "\nBook Found\n";
            cout << "Book ID : " << books[mid].id << endl;
            cout << "Title : " << books[mid].title << endl;
            cout << "Author : " << books[mid].author << endl;

            if (books[mid].issued)
                cout << "Status : Issued\n";
            else
                cout << "Status : Available\n";

            return;
        }

        if (books[mid].id < id)
            left = mid + 1;
        else
            right = mid - 1;
    }

    cout << "Book not found\n";
}
void issuebook()
{
    int id;
    cout << "Enter Book ID to issue: ";
    cin >> id;

    for (auto &b : books)
    {
        if (b.id == id)
        {
            if (!b.issued)
            {
                b.issued = true;
                cout << "Book issued successfully.\n";
            }
            else
            {
                string name;
                cout << "Book already issued.\n";
                cout << "Enter your name to join waiting list: ";
                cin >> name;

                b.waitinglist.push(name);

                cout << "Added to waiting list.\n";
            }
            return;
        }
    }

    cout << "Book not found.\n";
}
void returnbook()
{
    int id;
    cout << "Enter Book ID to return: ";
    cin >> id;

    for (auto &b : books)
    {
        if (b.id == id)
        {
            if (!b.issued)
            {
                cout << "Book was not issued.\n";
            }
            else
            {
                if (!b.waitinglist.empty())
                {
                    string nextUser = b.waitinglist.front();
                    b.waitinglist.pop();

                    cout << "Book returned and issued to: " << nextUser << endl;
                }
                else
                {
                    b.issued = false;
                    cout << "Book returned successfully.\n";
                }
            }
            return;
        }
    }

    cout << "Book not found.\n";
}
void savebooks()
{
    ofstream file("books.txt");

    for (int i = 0; i < books.size(); i++)
    {
        file << books[i].id << " "
             << books[i].title << " "
             << books[i].author << " "
             << books[i].issued << endl;
    }

    file.close();
}
void loadbooks()
{
    ifstream file("books.txt");

    book b;

    while (file >> b.id >> b.title >> b.author >> b.issued)
    {
        books.push_back(b);
    }

    file.close();
}
void deletebook()
{
    int id;
    cout << "Enter Book ID to delete: ";
    cin >> id;

    for (int i = 0; i < books.size(); i++)
    {
        if (books[i].id == id)
        {
            books.erase(books.begin() + i);
            cout << "Book deleted successfully\n";
            return;
        }
    }

    cout << "Book not found\n";
}
void sortbooks()
{
    sort(books.begin(), books.end(), [](book a, book b)
         { return a.id < b.id; });
}
int main()
{
    loadbooks();
    int choice;
    do
    {
        cout << "\n======== Library Management System ==========\n"
             << endl;
        cout << "1.Add Book\n";
        cout << "2.Display Book\n";
        cout << "3.Search Book\n";
        cout << "4.Issue Book\n";
        cout << "5.Return Book\n";
        cout << "6.Delete Book\n";
        cout << "7.Exit\n";

        cout << "Enter choice : ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid choice\n";
            continue;
        }
        switch (choice)
        {
        case 1:
            addbook();
            break;
        case 2:
            displaybook();
            break;
        case 3:
            searchbook();
            break;
        case 4:
            issuebook();
            break;
        case 5:
            returnbook();
            break;
        case 6:
            deletebook();
            break;
        case 7:
            savebooks();
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice";
        }
    } while (choice != 6);

    return 0;
}