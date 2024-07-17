// Lab 5 Date:2081/04/09 //
// Tittle: Bankers Algorithm for deadlock detection in distributed sytsem
// Objectives;
// 1. To understand the concept of deadlock in distributed system.
// 2. To implement Bankers Algorithm for deadlock detection.


#include <iostream>
#include <vector>
using namespace std;

class BankersAlgorithm {
public:
    BankersAlgorithm(int numProcesses, int numResources,
                     const vector<vector<int>>& maxMatrix,
                     const vector<vector<int>>& allocationMatrix,
                     const vector<int>& availableResources) {
        n = numProcesses;
        m = numResources;
        Max = maxMatrix;
        Allocation = allocationMatrix;
        Available = availableResources;
        Need = vector<vector<int>>(n, vector<int>(m));
       
        calculateNeed();
    }

    bool isSafeState() {
        vector<int> Work = Available;
        vector<bool> Finish(n, false);
        vector<int> safeSequence;
       
        while (safeSequence.size() < n) {
            bool found = false;
            for (int i = 0; i < n; ++i) {
                if (!Finish[i]) {
                    bool canProceed = true;
                    for (int j = 0; j < m; ++j) {
                        if (Need[i][j] > Work[j]) {
                            canProceed = false;
                            break;
                        }
                    }
                    if (canProceed) {
                        for (int j = 0; j < m; ++j) {
                            Work[j] += Allocation[i][j];
                        }
                        Finish[i] = true;
                        safeSequence.push_back(i);
                        found = true;
                    }
                }
            }
            if (!found) {
                break;
            }
        }
       
        if (safeSequence.size() == n) {
            cout << "System is in a safe state.\nSafe sequence is: ";
            for (int i : safeSequence) {
                cout << "P" << i << " ";
            }
            cout << endl;
            return true;
        } else {
            cout << "System is not in a safe state." << endl;
            return false;
        }
    }

    bool requestResources(int process, const vector<int>& request) {
        for (int j = 0; j < m; ++j) {
            if (request[j] > Need[process][j]) {
                cout << "Error: Process has exceeded its maximum claim." << endl;
                return false;
            }
            if (request[j] > Available[j]) {
                cout << "Error: Not enough resources available." << endl;
                return false;
            }
        }
       
        for (int j = 0; j < m; ++j) {
            Available[j] -= request[j];
            Allocation[process][j] += request[j];
            Need[process][j] -= request[j];
        }
       
        if (isSafeState()) {
            cout << "Request can be granted." << endl;
            return true;
        } else {
            cout << "Request cannot be granted as it leads to an unsafe state." << endl;
            for (int j = 0; j < m; ++j) {
                Available[j] += request[j];
                Allocation[process][j] -= request[j];
                Need[process][j] += request[j];
            }
            return false;
        }
    }

private:
    int n, m;
    vector<vector<int>> Max, Allocation, Need;
    vector<int> Available;

    void calculateNeed() {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                Need[i][j] = Max[i][j] - Allocation[i][j];
            }
        }
    }
};

int main() {
    int numProcesses, numResources;

    cout << "Enter the number of processes: ";
    cin >> numProcesses;
    cout << "Enter the number of resources: ";
    cin >> numResources;

    vector<vector<int>> Max(numProcesses, vector<int>(numResources));
    vector<vector<int>> Allocation(numProcesses, vector<int>(numResources));
    vector<int> Available(numResources);

    cout << "Enter the Max matrix:\n";
    for (int i = 0; i < numProcesses; ++i) {
        for (int j = 0; j < numResources; ++j) {
            cin >> Max[i][j];
        }
    }

    cout << "Enter the Allocation matrix:\n";
    for (int i = 0; i < numProcesses; ++i) {
        for (int j = 0; j < numResources; ++j) {
            cin >> Allocation[i][j];
        }
    }

    cout << "Enter the Available resources:\n";
    for (int i = 0; i < numResources; ++i) {
        cin >> Available[i];
    }

    BankersAlgorithm ba(numProcesses, numResources, Max, Allocation, Available);
   
    ba.isSafeState();

    int process;
    cout << "Enter the process number making the request: ";
    cin >> process;

    vector<int> request(numResources);
    cout << "Enter the request vector:\n";
    for (int i = 0; i < numResources; ++i) {
        cin >> request[i];
    }

    ba.requestResources(process, request);

    return 0;
}


// Output: 
// Enter the number of processes: 5
// Enter the number of resources: 3
// Enter the Max matrix:
// 7
// 5
// 3
// 3
// 2
// 2
// 9
// 0
// 2
// 2
// 2
// 2
// 4
// 3
// 3
// Enter the Allocation matrix:
// 0
// 1
// 0
// 2
// 0
// 0
// 3
// 0
// 2
// 2
// 1
// 1
// 0
// 0
// 2
// Enter the Available resources:
// 3
// 3
// 2
// System is in a safe state.
// Safe sequence is: P1 P3 P4 P0 P2
// Enter the process number making the request: 1
// Enter the request vector:
// 1
// 0
// 2
// System is in a safe state.
// Safe sequence is: P1 P3 P4 P0 P2
// Request can be granted.
