#pragma once
#include "storage.h"

// ===== helpers =====
int linearSearchById(int searchId);   // defined below, printOne needs it
string lower(string t) {
    for (int i = 0; i < t.length(); i++) {
        t[i] = tolower((unsigned char)t[i]);
    }
    return t;
}

void printOne(Complaint c) {
    cout << "ID " << c.getId() << " | " << c.getCategoryName()
         << " | " << c.getStatusName();
    int pos = linearSearchById(c.getId());
    if (pos != -1 && assignedTo[pos] != "") {
        cout << " | Assigned to: " << assignedTo[pos];
    }
    cout << endl;
    cout << "    " << c.getDescription() << endl;
}

// ===== LINEAR SEARCH: checks every complaint in turn, O(n) =====
int linearSearchById(int searchId) {
    for (int i = 0; i < storeCount; i++) {
        if (store[i].getId() == searchId) {
            return i;
        }
    }
    return -1;
}

// fills results[] with positions of matches, returns how many
int linearSearchByCategory(int category, int results[]) {
    int found = 0;
    for (int i = 0; i < storeCount; i++) {
        if (store[i].getCategory() == category) {
            results[found] = i;
            found++;
        }
    }
    return found;
}

int linearSearchByStatus(int status, int results[]) {
    int found = 0;
    for (int i = 0; i < storeCount; i++) {
        if (store[i].getStatus() == status) {
            results[found] = i;
            found++;
        }
    }
    return found;
}

void trackComplaint() {
    int id;
    cout << "Enter your complaint ID: ";
    cin >> id;

    int i = linearSearchById(id);
    if (i == -1) {
        cout << "No complaint found with that ID.\n";
        return;
    }
    cout << "ID " << store[i].getId() << " | " << store[i].getCategoryName()
         << " | Status: " << store[i].getStatusName();
    if (assignedTo[i] != "") {
        cout << " | Assigned to: " << assignedTo[i];
    }
    cout << endl;
}

// ===== MERGE SORT: sorts a list of positions, O(n log n), stable =====
const int BY_ID = 1;
const int BY_STATUS = 2;
const int BY_TEXT = 3;           // description A-Z

// true if complaint at position a must come strictly before the one at b
bool before(int a, int b, int key) {
    if (key == BY_ID) {
        return store[a].getId() < store[b].getId();
    }
    if (key == BY_STATUS) {
        return store[a].getStatus() < store[b].getStatus();
    }
    return lower(store[a].getDescription()) < lower(store[b].getDescription());
}

void mergeSort(int order[], int temp[], int lo, int hi, int key) {
    if (lo >= hi) {
        return;
    }
    int mid = lo + (hi - lo) / 2;
    mergeSort(order, temp, lo, mid, key);
    mergeSort(order, temp, mid + 1, hi, key);

    int i = lo;
    int j = mid + 1;
    int k = lo;
    while (i <= mid && j <= hi) {
        if (before(order[j], order[i], key)) {
            temp[k] = order[j];
            j++;
        } else {
            temp[k] = order[i];
            i++;
        }
        k++;
    }
    while (i <= mid) { temp[k] = order[i]; i++; k++; }
    while (j <= hi)  { temp[k] = order[j]; j++; k++; }

    for (int x = lo; x <= hi; x++) {
        order[x] = temp[x];
    }
}

// show every complaint of one category, sorted by the chosen key
void showCategorySorted(int category, int key) {
    int order[MAX_STORE];
    int temp[MAX_STORE];
    int n = linearSearchByCategory(category, order);

    if (n == 0) {
        cout << "No complaints in this category.\n";
        return;
    }
    mergeSort(order, temp, 0, n - 1, key);
    for (int i = 0; i < n; i++) {
        printOne(store[order[i]]);
    }
}

void showByStatus(int status) {
    int results[MAX_STORE];
    int n = linearSearchByStatus(status, results);
    if (n == 0) {
        cout << "No complaints with that status.\n";
        return;
    }
    for (int i = 0; i < n; i++) {
        printOne(store[results[i]]);
    }
}