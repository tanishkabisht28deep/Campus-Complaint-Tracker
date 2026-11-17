#pragma once
#include<iostream>
#include<string>
#include <cctype>
using namespace std;
class Complaint{
    int id;
    int category;
    int status;
    string description;
    double priorityScore;
    public:
        Complaint(){
            id = 0;
            category = 0;
            status = 0;
            description = "";
            priorityScore = 0.0;

        }
        void setId(int i) {id = i;}
        void setCategory(int c) {category = c;}
        void setStatus(int s) {status = s;}
        void setDescription(string d) {description = d;}
        void setPriorityScore(double p) {priorityScore = p;}

        int getId() {return id;}
        int getCategory() {return category;}
        int getStatus() {return status;}
        string getDescription() {return description;}
        double getPriorityScore() {return priorityScore;}
        string getCategoryName() {
            switch (category) {
                case 1: return "Security & Safety";
                case 2: return "Academic";
                case 3: return "Mess & Food";
                case 4: return "Sanitation & Cleanliness";
                case 5: return "Infrastructure & Maintenance";
                case 6: return "IT & Network";
                case 7: return "Administrative";
                default: return "Unknown";
            }
        }  
        string getStatusName() {
            switch (status) {
                case 0: return "Submitted";
                case 1: return "In Progress";
                case 2: return "Resolved";
                default: return "Unknown";
            }
        }  
};

int nextId = 101;
const int MAX_COMPLAINTS = 1000;

class PriorityQueue {
    Complaint heapArr[MAX_COMPLAINTS];
    int count;

public:
    PriorityQueue() {
        count = 0;
    }

    bool isEmpty() {
        return count == 0;
    }
    
    int getCount(){
        return count;
    }
    Complaint getAt(int i){
        return heapArr[i];
    }

    void insert(Complaint c) {
        if (count == MAX_COMPLAINTS) {
            cout << "Heap is full\n";
            return;
        }

        // step 1: put the new complaint in the first empty spot
        heapArr[count] = c;
        int child = count;
        count = count + 1;

        // step 2: keep moving it up while it beats its parent
        while (child > 0) {
            int parent = (child - 1) / 2;

            if (heapArr[child].getPriorityScore() > heapArr[parent].getPriorityScore()) {
                Complaint temp = heapArr[child];
                heapArr[child] = heapArr[parent];
                heapArr[parent] = temp;

                child = parent;
            } else {
                break;
            }
        }
    }

    Complaint extractMax() {
        Complaint top = heapArr[0];          // step 1: save the top

        count = count - 1;                   // step 2: one fewer complaint
        heapArr[0] = heapArr[count];         //         last one moves to the top

        int parent = 0;                      // step 3: push it down
        while (true) {
            int left = 2 * parent + 1;
            int right = 2 * parent + 2;
            int biggest = parent;

            if (left < count && heapArr[left].getPriorityScore() > heapArr[biggest].getPriorityScore()) {
                biggest = left;
            }
            if (right < count && heapArr[right].getPriorityScore() > heapArr[biggest].getPriorityScore()) {
                biggest = right;
            }

            if (biggest == parent) {
                break;
            }

            Complaint temp = heapArr[parent];
            heapArr[parent] = heapArr[biggest];
            heapArr[biggest] = temp;

            parent = biggest;
        }

        return top;
    }
};

PriorityQueue pq;

bool chooseCategory(Complaint &c) {
    int choice;

    cout << "\n====== SELECT COMPLAINT CATEGORY ======\n";

    cout << "1. Security & Safety\n";
    cout<< "   Safety threats, security risks, or danger to people/property\n"<< "   e.g. theft, unauthorized entry, broken locks, hazards\n\n";

    cout << "2. Academic\n";
    cout<< "   Teaching, examinations, learning, or academic records\n"<< "   e.g. marks, grading, syllabus, lectures, attendance\n\n";

    cout << "3. Mess & Food\n";
    cout<< "   Food quality, hygiene, menu, or mess services\n"<< "   e.g. food quality, hygiene, billing, menu issues\n\n";

    cout << "4. Sanitation & Cleanliness\n";
    cout<< "   Waste disposal, hygiene, drainage, or campus cleanliness\n"<< "   e.g. garbage, dirty washrooms, drainage, pest sightings\n\n";

    cout << "5. Infrastructure & Maintenance\n";
    cout<< "   Physical facilities, equipment, or repair problems\n"<< "   e.g. broken furniture, leaking taps, faulty fans, cracks\n\n";

    cout << "6. IT & Network\n";
    cout<< "   Digital systems, internet, software, or network problems\n"<< "   e.g. Wi-Fi failure, portal error, login failure\n\n";

    cout << "7. Administrative\n";
    cout<< "   Official procedures, documents, fees, or student services\n"<< "   e.g. pending certificate, fee receipt, scholarship, approval\n\n";
    
    cout << "8. Exit\n";

    while (true) {
        cout << "\nChoose category (1-8): ";
        cin >> choice;

        if (cin.fail()) {                  // user typed something that isn't a number
            cin.clear();                   // reset cin so it works again
            cin.ignore(1000, '\n');        // throw away the bad text
            cout << "Invalid input. Please enter a number.\n";
            continue;                      // ask again
        }
        if (choice < 1 || choice > 8) {
            cout << "Invalid choice. Try again.\n";
            continue;
        }

        break;                             // valid, leave the loop
    }
    if (choice == 8) {
        return false;
    }
    c.setCategory(choice);
    return true;
}
// priority score calculation
int getCategoryWeight(int category) {
    switch (category) {
        case 1: return 8;
        case 2: return 7;
        case 3: return 6;
        case 4: return 5;
        case 5: return 4;
        case 6: return 3;
        case 7: return 2;
        default: return 0;
    }
}
int countMatches(string desc, string words[], int n) {
    int count = 0;

    for (int i = 0; i < n; i++) {
        if (desc.find(words[i]) != string::npos) {
            count++;
        }
    }

    return count;
}
int calculateKeywordBonus(string desc, int category) {
    string security[] = {"fire", "smoke", "spark", "theft", "weapon", "broken", "unauthorized", "intruder"};
    string academic[] = {"misconduct", "late", "incomplete", "unfair", "discrimination", "absent"};
    string mess[] = {"spoiled", "rotten", "contaminated", "poisoning", "expired", "insect"};
    string sanitation[] = {"sewage", "blocked", "garbage", "mosquito", "breeding", "pest"};
    string infrastructure[] = {"collapse", "leakage", "broken", "crack", "damaged"};
    string it[] = {"down", "breach", "hacked", "unavailable", "outage", "exposed"};
    string administrative[] = {"fee", "payment", "deadline", "overdue", "rejected", "pending"};

    int bonus = 0;
    switch (category) {
        case 1:
            bonus = countMatches(desc, security, 8);
            break;
        case 2:
            bonus = countMatches(desc, academic, 6);
            break;
        case 3:
            bonus = countMatches(desc, mess, 6);
            break;
        case 4:
            bonus = countMatches(desc, sanitation, 6);
            break;
        case 5:
            bonus = countMatches(desc, infrastructure, 5);
            break;
        case 6:
            bonus = countMatches(desc, it, 6);
            break;
        case 7:
            bonus = countMatches(desc, administrative, 6);
            break;
    }

    if (bonus > 6)
        bonus = 6;

    return bonus;
}
double calculatePriorityScore(Complaint c) {
    int weight = getCategoryWeight(c.getCategory());
    int keywordBonus = calculateKeywordBonus(c.getDescription(), c.getCategory());

    double score = (weight * 10) + keywordBonus;
    return score;
}

void viewByPriority() {
    PriorityQueue temp = pq;                 

    cout << "\n===== ALL COMPLAINTS BY PRIORITY =====\n";
    while (!temp.isEmpty()) {
        Complaint c = temp.extractMax();
        int weight = getCategoryWeight(c.getCategory());
        int bonus = calculateKeywordBonus(c.getDescription(), c.getCategory());

        cout << "ID " << c.getId() << " | " << c.getCategoryName()
             << " | " << c.getStatusName() << endl;
        cout << "    Weight " << weight << " x 10 + Keyword bonus " << bonus
             << " = Score " << c.getPriorityScore() << endl;
        cout << "    " << c.getDescription() << endl;
    }
}

bool submitComplaint(Complaint &c) {
    if (!chooseCategory(c)) {
        return false;
    }

    c.setId(nextId);     
    nextId = nextId + 1; 
    
    string description;
    cout << "\nEnter complaint description: ";
    cin.ignore(1000, '\n');
    getline(cin, description);

    for (int i = 0; i < description.length(); i++) {
        description[i] = tolower((unsigned char)description[i]);
    }
    c.setDescription(description);

    double score = calculatePriorityScore(c);
    c.setPriorityScore(score);
    pq.insert(c);

    cout << "\nComplaint submitted successfully!\n";
    cout << "Your Complaint ID is: " << c.getId() << " (save this to track status)\n";

    return true;
}
