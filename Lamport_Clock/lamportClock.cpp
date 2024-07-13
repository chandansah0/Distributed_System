// Lab: 2  Date: 2081/03/19 //
//WAP to stimulate the functioning of the lamport's logical clock in C++ //

#include <iostream>
using namespace std;

// Function to find the maximum timestamp between 2 events
int max1(int a, int b) {
    return (a > b) ? a : b;
}

// Function to display the logical timestamp
void display(int e1, int e2, int p1[], int p2[]) {
    cout << "\nThe time stamps of events in P1:\n";
    for (int i = 0; i < e1; i++) {
        cout << p1[i] << " ";
    }
    cout << "\nThe time stamps of events in P2:\n";
    for (int i = 0; i < e2; i++) {
        cout << p2[i] << " ";
    }
}

// Function to find the timestamp of events
void lamportLogicalClock(int e1, int e2, int m[5][3]) {
    int p1[e1], p2[e2];

    // Initialize p1[] and p2[]
    for (int i = 0; i < e1; i++) {
        p1[i] = i + 1;
    }

    for (int i = 0; i < e2; i++) {
        p2[i] = i + 1;
    }

    cout << "\t";
    for (int i = 0; i < e2; i++) {
        cout << "\te2" << i + 1;
    }

    for (int i = 0; i < e1; i++) {
        cout << "\n e1" << i + 1 << "\t";
        for (int j = 0; j < e2; j++) {
            cout << m[i][j] << "\t";
        }
    }

    for (int i = 0; i < e1; i++) {
        for (int j = 0; j < e2; j++) {
            if (m[i][j] == 1) {
                p2[j] = max1(p2[j], p1[i] + 1);
                for (int k = j + 1; k < e2; k++) {
                    p2[k] = p2[k - 1] + 1;
                }
            }

            if (m[i][j] == -1) {
                p1[i] = max1(p1[i], p2[j] + 1);
                for (int k = i + 1; k < e1; k++) {
                    p1[k] = p1[k - 1] + 1;
                }
            }
        }
    }

    // Function Call
    display(e1, e2, p1, p2);
}

int main() {
    int e1, e2;

    // Read number of events in P1
    cout << "Enter the number of events in P1: ";
    cin >> e1;

    // Read number of events in P2
    cout << "Enter the number of events in P2: ";
    cin >> e2;

    // Ensure matrix size matches the input
    if (e1 > 5 || e2 > 3) {
        cout << "Error: Maximum supported events are 5 for P1 and 3 for P2." << endl;
        return 1;
    }

    int m[5][3] = {0};  // Initialize matrix to 0

    // Read the message matrix
    cout << "Enter the message matrix (0 for no message, 1 for sent, -1 for received):" << endl;
    for (int i = 0; i < e1; i++) {
        for (int j = 0; j < e2; j++) {
            cin >> m[i][j];
        }
    }

    // Function Call
    lamportLogicalClock(e1, e2, m);

    return 0;
}

