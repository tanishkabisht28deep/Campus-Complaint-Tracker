#include "complaints.h"
#include "storage.h"
#include "tree.h"

void userMenu() {
    int choice;
    do {
        cout << "\n===== USER MENU =====\n";
        cout << "1. Submit a complaint\n";
        cout << "2. Track my complaint\n";
        cout << "3. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            Complaint c;
            if (submitComplaint(c)) {
                addToStore(c);
                saveAll();
            }
        } else if (choice == 2) {
            trackComplaint();
        }
    } while (choice != 3);
}

void adminMenu() {
    int choice;
    do {
        cout << "\n===== ADMIN PANEL =====\n";
        cout << "1. View all waiting complaints (by priority)\n";
        cout << "2. Handle next most urgent complaint\n";
        cout << "3. Mark a complaint as resolved\n";
        cout << "4. View complaints of one category\n";
        cout << "5. Escalation path of a complaint\n";
        cout << "6. View authority hierarchy\n";
        cout << "7. Back\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            if (pq.isEmpty()) {
                cout << "No complaints in the queue.\n";
            } else {
                viewByPriority();
            }
        } else if (choice == 2) {
            if (pq.isEmpty()) {
                cout << "No complaints to handle.\n";
            } else {
                Complaint c = pq.extractMax();
                int i = linearSearchById(c.getId());
                if (i != -1) {
                    store[i].setStatus(1);
                    assignedTo[i] = roleName[findAuthority(i, false)];
                    saveAll();
                }
                cout << "\nNow handling the most urgent complaint:\n";
                cout << "ID " << c.getId() << " | " << c.getCategoryName()
                     << " | Score " << c.getPriorityScore() << endl;
                cout << "Description: " << c.getDescription() << endl;
                if (i != -1) {
                    cout << "Assigned to: " << assignedTo[i] << endl;
                }
            }
        } else if (choice == 3) {
            int id;
            cout << "Enter complaint ID: ";
            cin >> id;
            int i = linearSearchById(id);
            if (i == -1) {
                cout << "No complaint found with that ID.\n";
            } else if (store[i].getStatus() != 1) {
                cout << "Only a complaint that is In Progress can be resolved.\n";
            } else {
                store[i].setStatus(2);
                saveAll();
                cout << "Complaint " << id << " marked Resolved.\n";
            }
        } else if (choice == 4) {
            int cat;
            cout << "Category number (1-7): ";
            cin >> cat;
            showCategorySorted(cat, BY_ID);
        } else if (choice == 5) {
            showEscalationPath();
        } else if (choice == 6) {
            showHierarchy();
        }
    } while (choice != 7);
}

int main() {
    int choice;
    loadAll();
    do {
        cout << "\n===== CAMPUS COMPLAINT TRACKER =====\n";
        cout << "1. User\n";
        cout << "2. Admin\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            userMenu();
        } else if (choice == 2) {
            if (adminLogin()) {
                adminMenu();
            }
        }
    } while (choice != 3);
    return 0;
}