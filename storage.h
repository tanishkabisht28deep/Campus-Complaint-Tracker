#pragma once
#include <fstream>
#include <ctime>
#include "complaints.h"

// Storage and login: remembers every complaint (saved to a file) and checks the admin login.

const int MAX_STORE = 1000;
Complaint store[MAX_STORE];
long long submittedAt[MAX_STORE];       // when each complaint was submitted (seconds), same position as store[]
string assignedTo[MAX_STORE];           // which authority holds it now ("" = nobody yet), same position as store[]
int storeCount = 0;

// a new complaint is stamped with the current time; loadAll passes the saved time instead
void addToStore(Complaint c, long long when = 0, string who = "") {
    if (storeCount < MAX_STORE) {
        if (when == 0) {
            when = time(0);
        }
        store[storeCount] = c;
        submittedAt[storeCount] = when;
        assignedTo[storeCount] = who;
        storeCount = storeCount + 1;
    }
}

// write every complaint to complaints.txt, one per line: id|category|status|time|assigned|description
void saveAll() {
    ofstream out("complaints.txt");
    for (int i = 0; i < storeCount; i++) {
        out << store[i].getId() << "|" << store[i].getCategory() << "|"
            << store[i].getStatus() << "|" << submittedAt[i] << "|"
            << assignedTo[i] << "|" << store[i].getDescription() << "\n";
    }
}

// read the file at startup and rebuild the store and the heap
void loadAll() {
    ifstream in("complaints.txt");
    if (!in) {
        return;                               // first run: no file yet
    }

    string line;
    while (getline(in, line)) {
        int p1 = line.find('|');
        int p2 = line.find('|', p1 + 1);
        int p3 = line.find('|', p2 + 1);
        int p4 = line.find('|', p3 + 1);
        int p5 = line.find('|', p4 + 1);
        if (p1 < 0 || p2 < 0 || p3 < 0 || p4 < 0 || p5 < 0) {
            continue;                         // skip a damaged line
        }

        Complaint c;
        c.setId(stoi(line.substr(0, p1)));
        c.setCategory(stoi(line.substr(p1 + 1, p2 - p1 - 1)));
        c.setStatus(stoi(line.substr(p2 + 1, p3 - p2 - 1)));
        long long when = stoll(line.substr(p3 + 1, p4 - p3 - 1));
        string who = line.substr(p4 + 1, p5 - p4 - 1);
        c.setDescription(line.substr(p5 + 1));
        c.setPriorityScore(calculatePriorityScore(c));

        addToStore(c, when, who);
        if (c.getStatus() == 0) {
            pq.insert(c);                     // only waiting complaints join the heap
        }
        if (c.getId() >= nextId) {
            nextId = c.getId() + 1;           // never reuse an ID
        }
    }
}

// ---------------- Admin login ----------------
// Admin accounts are kept in arrays; the username is found with a linear search.

const int ADMIN_COUNT = 2;
string adminNames[ADMIN_COUNT] = {"admin", "warden"};
string adminPasswords[ADMIN_COUNT] = {"admin123", "warden123"};

// returns true if username and password match one of the admins
bool adminLogin() {
    string name, pass;
    cout << "Admin username: ";
    cin >> name;
    cout << "Admin password: ";
    cin >> pass;

    for (int i = 0; i < ADMIN_COUNT; i++) {          // linear search
        if (adminNames[i] == name) {
            if (adminPasswords[i] == pass) {
                return true;
            }
            break;                                    // right name, wrong password
        }
    }
    cout << "Wrong username or password.\n";
    return false;
}