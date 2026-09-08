#include <bits/stdc++.h>
using namespace std;

int process_counter = 0;

class Process {
public:
    int pid;
    double arrivalTime, burstTime, completionTime, turnAroundTime, waitingTime, responseTime;

    Process(int at, int bt) {
        pid = ++process_counter;
        arrivalTime = at;
        burstTime = bt;
    }
};

struct comparator {
    bool operator()(Process* a, Process* b) const {
        if(a->burstTime == b->burstTime) {
            if(a->arrivalTime == b->arrivalTime)
                return a->pid > b->pid;
            return a->arrivalTime > b->arrivalTime;
        }
        return a->burstTime > b->burstTime;
    }
};



int main() {
    int n;
    vector<Process> process_queue;
    priority_queue<Process*, vector<Process*>, comparator> pq;

    cout << "Enter n: ";
    cin >> n;

    for(int i = 1; i <= n; i++) {
        int at, bt;
        cout << endl << "Enter P" << i << " Arrival Time: ";
        cin >> at;
        cout << endl << "Enter P" << i << " Burst Time: ";
        cin >> bt;
        process_queue.push_back(Process(at, bt));
    }
    
    sort(process_queue.begin(), process_queue.end(), [](Process& p1, Process& p2) {
        if(p1.arrivalTime == p2.arrivalTime) return p1.pid < p2.pid;
        return p1.arrivalTime < p2.arrivalTime;
    });

    cout << left
     << setw(5)  << "PID"
     << setw(12) << "Arrival"
     << setw(10) << "Burst"
     << setw(12) << "Completion"
     << setw(12) << "Turnaround"
     << setw(10) << "Waiting"
     << setw(10) << "Response"
     << endl;

     cout << string(65, '-') << '\n';
    
    double process_timer = 0;
    double avgWaitingTime = 0, avgTurnArroundTime = 0;
    int curr_process = 0;
    
    while(curr_process < n || !pq.empty()) {
        if(pq.empty()) {
            process_timer = max(process_timer, process_queue[curr_process].arrivalTime);
        }


        while(curr_process < n &&
            process_queue[curr_process].arrivalTime <= process_timer) {
            pq.push(&process_queue[curr_process++]);
        }

        Process* p = pq.top();
        pq.pop();

        p->responseTime = process_timer - p->arrivalTime;

        process_timer += p->burstTime;

        p->completionTime = process_timer;
        p->turnAroundTime = p->completionTime - p->arrivalTime;
        p->waitingTime = p->turnAroundTime - p->burstTime;

        avgWaitingTime += p->waitingTime;
        avgTurnArroundTime += p->turnAroundTime;
    }


    for (const Process& p : process_queue) {
        cout << left
            << setw(5)  << p.pid
            << setw(12) << p.arrivalTime
            << setw(10) << p.burstTime
            << setw(12) << p.completionTime
            << setw(12) << p.turnAroundTime
            << setw(10) << p.waitingTime
            << setw(10) << p.responseTime
            << endl;
    }


    avgWaitingTime /= n;
    avgTurnArroundTime /= n;

    cout << "Average Waiting Time: " << avgWaitingTime << endl;
    cout << "Average Turn Arround Time: " << avgTurnArroundTime << endl;
}