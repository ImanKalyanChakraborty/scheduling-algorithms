#include <iostream>
#include <vector>
#include <tuple>
#include <string>
#include <queue>

using namespace std;

vector<vector<char> > timeline;
vector<int> finishTime;
vector<tuple<string, int, int>> processes;

double fcfs() {
    int time = 0;
    finishTime.resize(processes.size());
    timeline.resize(20, vector<char>(processes.size(), ' '));

    for (int i = 0; i < processes.size(); i++) {
        int processIndex = i;
        int arrivalTime = get<1>(processes[i]);
        int burstTime = get<2>(processes[i]);

        time = max(time, arrivalTime);

        finishTime[processIndex] = time + burstTime;

        for (int j = time; j < time + burstTime; j++) {
            timeline[j][processIndex] = 'X';
        }

        time += burstTime;
    }

    double avgTurnaroundTime = 0;
    for (int i = 0; i < processes.size(); i++) {
        avgTurnaroundTime += finishTime[i] - get<1>(processes[i]);
    }
    avgTurnaroundTime /= processes.size();

    return avgTurnaroundTime;
}

double roundRobin(int timeQuantum) {
    int time = 0;
    int processIndex = 0;
    finishTime.resize(processes.size());
    timeline.resize(20, vector<char>(processes.size(), ' '));
    queue<int> readyQueue;
    vector<int> burstTimeLeft(processes.size());

    for (int i = 0; i < processes.size(); i++) {
        burstTimeLeft[i] = get<2>(processes[i]);
    }

    while (true) {
        while (processIndex < processes.size() && get<1>(processes[processIndex]) <= time) {
            readyQueue.push(processIndex);
            processIndex++;
        }

        if (readyQueue.empty()) {
            if (processIndex < processes.size()) {
                time = get<1>(processes[processIndex]);
            } else {
                break;
            }
            continue;
        }

        int currentProcessIndex = readyQueue.front();
        readyQueue.pop();
        int remainingTime = burstTimeLeft[currentProcessIndex];

        int execTime = min(timeQuantum, remainingTime);
        for (int i = time; i < time + execTime; i++) {
            timeline[i][currentProcessIndex] = 'X';
        }

        time += execTime;
        burstTimeLeft[currentProcessIndex] -= execTime;

        if (burstTimeLeft[currentProcessIndex] > 0) {
            while (processIndex < processes.size() && get<1>(processes[processIndex]) <= time) {
                readyQueue.push(processIndex);
                processIndex++;
            }
            readyQueue.push(currentProcessIndex);
        } else {
            finishTime[currentProcessIndex] = time;
            int arrivalTime = get<1>(processes[currentProcessIndex]);
            int serviceTime = get<2>(processes[currentProcessIndex]);
        }
    }

    double avgTurnaroundTime = 0;
    for (int i = 0; i < processes.size(); i++) {
        avgTurnaroundTime += finishTime[i] - get<1>(processes[i]);
    }
    avgTurnaroundTime /= processes.size();

    return avgTurnaroundTime;
}

double srtf() {
    int time = 0;
    finishTime.resize(processes.size());
    timeline.resize(20, vector<char>(processes.size(), ' ')); 
    vector<int> burstTimeLeft(processes.size());
    bool done = false;

    for (int i = 0; i < processes.size(); i++) {
        burstTimeLeft[i] = get<2>(processes[i]);
    }

    while (!done) {
        vector<int> indexOfProcessesToBeConsidered;

        for (int i = 0; i < processes.size(); i++) {
            if (get<1>(processes[i]) <= time && burstTimeLeft[i] > 0) {
                indexOfProcessesToBeConsidered.push_back(i);
            }
        }

        int minIndex = -1;

        for (int i = 0; i < indexOfProcessesToBeConsidered.size(); i++) {
            if (minIndex == -1 || burstTimeLeft[indexOfProcessesToBeConsidered[i]] < burstTimeLeft[minIndex]) {
                minIndex = indexOfProcessesToBeConsidered[i];
            }
        }

        burstTimeLeft[minIndex]--;
        for (int i = time; i < time + 1; i++) {
            timeline[i][minIndex] = 'X';
        }

        time++;

        if (burstTimeLeft[minIndex] == 0) {
            finishTime[minIndex] = time;
        }

        done = true;
        for (int i = 0; i < processes.size(); i++) {
            if (burstTimeLeft[i] > 0) {
                done = false;
                break;
            }
        }
    }

    double avgTurnaroundTime = 0;
    for (int i = 0; i < processes.size(); i++) {
        avgTurnaroundTime += finishTime[i] - get<1>(processes[i]);
    }
    avgTurnaroundTime /= processes.size();

    return avgTurnaroundTime;
}

void printTimeline()
{
    cout << "------------------------------------------------\n";
    for (int i = 0; i < processes.size(); i++)
    {
        cout << get<0>(processes[i]) << "     |";
        for (int j = 0; j < timeline.size(); j++)
        {
            cout << timeline[j][i] << "|";
        }
        cout << " \n";
    }
    cout << "------------------------------------------------\n";
}

void emptyTimeline() {
    timeline.clear();
    finishTime.clear();
}

int main() {
    processes.push_back(make_tuple("P1", 0, 3));
    processes.push_back(make_tuple("P2", 2, 6));
    processes.push_back(make_tuple("P3", 4, 4));
    processes.push_back(make_tuple("P4", 6, 5));
    processes.push_back(make_tuple("P5", 8, 2));

    cout << "Average Turnaround Time for First Come First Serve: " << fcfs() << "\n";
    printTimeline();
    emptyTimeline();
    cout << "\n";

    cout << "Average Turnaround Time for Round Robin with Time Quantum 1: " << roundRobin(1) << "\n";
    printTimeline();
    emptyTimeline();
    cout << "\n";

    cout << "Average Turnaround Time for Shortest Remaining Time First: " << srtf() << "\n";
    printTimeline();
    emptyTimeline();
    cout << "\n";

    return 0;
}