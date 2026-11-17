# Campus Complaint Tracker

## Project Overview

Campus Complaint Tracker is a C++ based complaint management system designed to help students submit and track campus complaints while allowing administrators to manage and prioritize them.

The system calculates complaint priority based on category weights and relevant keywords in the complaint description. Administrators can view complaints by priority, handle urgent complaints, update their status, and view the authority responsible for handling them.

## Features

* Submit complaints under seven different categories.
* Automatically generate unique complaint IDs.
* Calculate priority scores using category weights and keyword matching.
* View waiting complaints in descending priority order.
* Track complaint status using complaint ID.
* Update complaints as In Progress or Resolved.
* View complaints belonging to a particular category.
* Display the campus authority hierarchy.
* Escalate complaints based on priority and predefined time limits.
* Save complaint records in a file and reload them when the program starts.

## Data Structures and Algorithms Used

| Data Structure / Algorithm | Purpose                                                            |
| -------------------------- | ------------------------------------------------------------------ |
| Max Heap (Priority Queue)  | Manage waiting complaints according to priority score.             |
| Linear Search              | Find complaints using their IDs, categories, and statuses.         |
| Merge Sort                 | Sort complaints within a category.                                 |
| Tree                       | Represent the campus authority hierarchy and escalation structure. |
| Array                      | Store complaints, heap elements, and authority information.        |
| Preorder Traversal         | Display the authority hierarchy.                                   |

## Priority Calculation

The priority score is calculated using:

**Priority Score = (Category Weight × 10) + Keyword Bonus**

The system checks relevant keywords in the complaint description and adds a keyword bonus, capped at 6.

## Technologies Used

* C++
* Standard C++ Library
* File Handling

## Project Files

* `main.cpp` – Main program and user/admin menus.
* `complaints.h` – Complaint class, priority queue, category selection, and priority calculation.
* `search.h` – Searching, merge sort, and complaint display functions.
* `storage.h` – File handling, complaint storage, and admin login.
* `tree.h` – Authority hierarchy and complaint escalation.

## How to Run

1. Make sure a C++ compiler such as GCC is installed.

2. Open the project folder in a terminal.

3. Compile the program:

   `g++ main.cpp -o campus`

4. Run the program:

   `./campus`

   On Windows, run:

   `campus.exe`

The program creates and uses `complaints.txt` to store complaint records.

## Team Contributions

This is a group project developed by four members.

* Member 1: [Sachin]– [tree.h]
* Member 2: [Tanishka Bisht]–[complaints.h]
* Member 3: [Soumya]– [search.h]
* Member 4: [Arpit] – [storage.h]

**My Individual Contribution:** [Tanishka Bisht]– Worked on `complaints.h`, including the Complaint class, Max Heap implementation, complaint category selection, and priority score calculation.

---

**Note:** The current implementation uses a demonstration time scale for escalation, where 10 seconds represent one hour. The admin login credentials are hard-coded in the source code and should be changed before any real deployment.
