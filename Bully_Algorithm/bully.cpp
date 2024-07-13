// Lab 3 Date: 2081/03/26 //
// WAP to stimulate the Election Algorithm (Bully Algorithm) // 


#include <iostream>
#include <vector>
#include <algorithm>

class Process {
public:
    int id;
    bool active;

    Process(int id) : id(id), active(true) {}

    void sendMessage(const std::string &message) {
        std::cout << "Process " << id << ": " << message << std::endl;
    }
};

class Election {
private:
    std::vector<Process> processes;

public:
    Election(const std::vector<int> &ids) {
        for (int id : ids) {
            processes.push_back(Process(id));
        }
    }

    void startElection(int initiatorId) {
        auto initiator = std::find_if(processes.begin(), processes.end(),
                                      [initiatorId](Process &p) { return p.id == initiatorId; });
        if (initiator == processes.end() || !initiator->active) {
            std::cerr << "Initiator process not found or not active." << std::endl;
            return;
        }

        initiator->sendMessage("starts election");

        int newCoordinatorId = initiator->id;

        for (Process &p : processes) {
            if (p.active && p.id > initiator->id) {
                p.sendMessage("responds to election");
                newCoordinatorId = std::max(newCoordinatorId, p.id);
            }
        }

        declareCoordinator(newCoordinatorId);
    }

    void declareCoordinator(int coordinatorId) {
        for (Process &p : processes) {
            if (p.active) {
                p.sendMessage("new coordinator is " + std::to_string(coordinatorId));
            }
        }
    }

    void deactivateProcess(int id) {
        auto process = std::find_if(processes.begin(), processes.end(),
                                    [id](Process &p) { return p.id == id; });
        if (process != processes.end()) {
            process->active = false;
            std::cout << "Process " << id << " has been deactivated." << std::endl;
        }
    }
};

int main() {
    std::vector<int> processIds = {1, 2, 3, 4, 5};
    Election election(processIds);

    std::cout << "Starting election with process 2:" << std::endl;
    election.startElection(2);

    std::cout << "\nDeactivating process 4 and starting election with process 2:" << std::endl;
    election.deactivateProcess(4);
    election.startElection(2);

    return 0;
}
