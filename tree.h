#pragma once
#include "search.h"

// Escalation hierarchy: a tree of authorities stored in arrays.
// Every node stores the position of its parent. The root (Principal) has parent -1.
// Every node also has an SLA: the maximum hours it is allowed to keep a complaint.
// A complaint that is not solved in time is pushed UP the tree towards the Principal.

const int NODES = 12;

// Hours are measured by the program from the time the complaint was submitted.
// For the demo, 10 seconds count as 1 hour. Change this to 3600 for real hours.
const int SECONDS_PER_HOUR = 10;

string roleName[NODES] = {
    "Principal",             // 0
    "Dean of Students",      // 1
    "Dean of Academics",     // 2
    "Administrative Head",   // 3
    "Hostel Warden",         // 4
    "Mess Committee Head",   // 5
    "Security Officer",      // 6
    "Head of Department",    // 7
    "IT Cell Head",          // 8
    "Maintenance Engineer",  // 9
    "Sanitation Supervisor", // 10
    "Accounts Officer"       // 11
};

int parentOf[NODES] = {-1, 0, 0, 0, 1, 1, 1, 2, 2, 3, 3, 3};

// SLA in hours for each node
int slaHours[NODES] = {72, 24, 48, 24, 12, 8, 6, 12, 6, 8, 8, 12};

// the first authority who handles each category (category 1..7)
int firstHandler[8] = {-1, 6, 7, 5, 10, 9, 8, 11};

// print the tree: a node, then all its children, one level deeper (preorder traversal)
void printNode(int node, int depth) {
    for (int i = 0; i < depth; i++) {
        cout << "    ";
    }
    cout << "- " << roleName[node] << " (SLA " << slaHours[node] << "h)" << endl;

    for (int child = 0; child < NODES; child++) {
        if (parentOf[child] == node) {
            printNode(child, depth + 1);
        }
    }
}

void showHierarchy() {
    cout << "\n===== AUTHORITY HIERARCHY =====\n";
    printNode(0, 0);
}

// Decide who should hold complaint number i (position in store[]) right now.
// Rule 1: a very urgent complaint (score 80 or more) starts one level higher.
// Rule 2: if the hours already spent are more than the SLA of the current
//         authority, move up to the parent, and check again.
// talk = true prints each step. Returns the position of the final authority.
int findAuthority(int i, bool talk) {
    int hours = (time(0) - submittedAt[i]) / SECONDS_PER_HOUR;   // measured by the program
    double score = store[i].getPriorityScore();

    if (talk) {
        cout << "\nComplaint " << store[i].getId() << " (" << store[i].getCategoryName()
             << ", priority score " << score << ")\n";
        cout << "Time since submission: " << hours << " hour(s)\n";
    }

    int node = firstHandler[store[i].getCategory()];
    if (talk) {
        cout << "Starts with: " << roleName[node] << endl;
    }

    if (score >= 80 && parentOf[node] != -1) {
        node = parentOf[node];
        if (talk) {
            cout << "High priority -> moved to " << roleName[node] << endl;
        }
    }

    while (parentOf[node] != -1 && hours > slaHours[node]) {
        if (talk) {
            cout << hours << "h is more than the " << slaHours[node] << "h SLA of "
                 << roleName[node] << " -> escalated to " << roleName[parentOf[node]] << endl;
        }
        node = parentOf[node];
    }
    return node;
}

// admin option: show the escalation steps, then save who holds the complaint now
void showEscalationPath() {
    int id;
    cout << "Enter complaint ID: ";
    cin >> id;

    int i = linearSearchById(id);
    if (i == -1) {
        cout << "No complaint found with that ID.\n";
        return;
    }
    if (store[i].getStatus() == 2) {
        cout << "Complaint " << id << " is already resolved. No escalation needed.\n";
        return;
    }

    int node = findAuthority(i, true);
    assignedTo[i] = roleName[node];
    saveAll();
    cout << "Final authority: " << roleName[node] << " (saved)\n";
}