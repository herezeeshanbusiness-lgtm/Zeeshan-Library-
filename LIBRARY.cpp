#include <iostream>
#include <string>
#include <limits>
using namespace std;

struct BookRequestNode {
    int studentID;
    string studentName;
    int bookID;
    string bookTitle;
    int priority;
    BookRequestNode* next;
};

class PriorityQueue {
private:
    BookRequestNode* front;
    BookRequestNode* rear;
    int count;

public:
    PriorityQueue() {
        front = NULL;
        rear = NULL;
        count = 0;
    }

    void Add(int sid, string sname, int bid,
             string btitle, int p) {

        BookRequestNode* request = new BookRequestNode;

        request->studentID = sid;
        request->studentName = sname;
        request->bookID = bid;
        request->bookTitle = btitle;
        request->priority = p;
        request->next = NULL;

        if (front == NULL) {
            front = request;
            rear = request;
        }
        else if (p < front->priority) {
            request->next = front;
            front = request;
        }
        else {
            BookRequestNode* current = front;

            while (current->next != NULL &&
                   current->next->priority <= p) {
                current = current->next;
            }

            request->next = current->next;
            current->next = request;

            if (request->next == NULL) {
                rear = request;
            }
        }

        count++;
        cout << "Book request added successfully!\n";
    }

    void Remove() {
        if (front == NULL) {
            cout << "Queue is empty. No request to process.\n";
            return;
        }

        BookRequestNode* temp = front;

        cout << "\nRequest Processed Successfully!\n";
        cout << "Student ID: " << temp->studentID << "\n";
        cout << "Student Name: " << temp->studentName << "\n";
        cout << "Book ID: " << temp->bookID << "\n";
        cout << "Book Title: " << temp->bookTitle << "\n";
        cout << "Priority: " << temp->priority << "\n";

        front = front->next;

        if (front == NULL) {
            rear = NULL;
        }

        delete temp;
        count--;
    }

    bool IsEmpty() {
        return front == NULL;
    }

    void PrintQueue() {
        if (front == NULL) {
            cout << "No pending book requests.\n";
            return;
        }

        BookRequestNode* current = front;

        while (current != NULL) {
            cout << "\nStudent ID: " << current->studentID << "\n";
            cout << "Student Name: " << current->studentName << "\n";
            cout << "Book ID: " << current->bookID << "\n";
            cout << "Book Title: " << current->bookTitle << "\n";
            cout << "Priority: " << current->priority << "\n";
            cout << "-----------------------------\n";

            current = current->next;
        }
    }

    int GetCount() {
        return count;
    }

    ~PriorityQueue() {
        while (front != NULL) {
            BookRequestNode* temp = front;
            front = front->next;
            delete temp;
        }

        rear = NULL;
        count = 0;
    }
};

int main() {
    PriorityQueue requests;
    int choice = 0;

    do {
        cout << "\n===== Library Book Request System =====\n";
        cout << "1. Add Book Request\n";
        cout << "2. Process Highest Priority Request\n";
        cout << "3. Display All Requests\n";
        cout << "4. Check Queue Status\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: {
                int sid, bid, priority;
                string sname, btitle;

                cout << "Enter Student ID: ";
                if (!(cin >> sid)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid Student ID.\n";
                    break;
                }

                cout << "Enter Student Name: ";
                getline(cin >> ws, sname);

                cout << "Enter Book ID: ";
                if (!(cin >> bid)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid Book ID.\n";
                    break;
                }

                cout << "Enter Book Title: ";
                getline(cin >> ws, btitle);

                cout << "Enter Priority (1=Urgent, 2=Assignment, 3=Normal): ";
                if (!(cin >> priority)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid priority input.\n";
                    break;
                }

                if (priority < 1 || priority > 3) {
                    cout << "Priority must be 1, 2, or 3.\n";
                    break;
                }

                requests.Add(sid, sname, bid, btitle, priority);
                break;
            }

            case 2:
                requests.Remove();
                break;

            case 3:
                requests.PrintQueue();
                break;

            case 4:
                if (requests.IsEmpty()) {
                    cout << "Queue Status: Empty\n";
                }
                else {
                    cout << "Queue Status: Not Empty\n";
                    cout << "Pending Requests: "
                         << requests.GetCount() << "\n";
                }
                break;

            case 5:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
