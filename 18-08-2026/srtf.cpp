#include <bits/stdc++.h>
using namespace std;

int process_counter = 0;

class Process {
public:
    int pid;
    double arrivalTime, burstTime;
    double remainingTime;
    double completionTime = 0;
    double turnAroundTime = 0;
    double waitingTime = 0;
    double responseTime = -1;

    Process(int at, int bt) {
        pid = ++process_counter;
        arrivalTime = at;
        burstTime = bt;
        remainingTime = bt;
    }
};

struct comparator {
    bool operator()(Process* a, Process* b) const {
        if(a->remainingTime == b->remainingTime) {

            if(a->arrivalTime == b->arrivalTime)
                return a->pid > b->pid;

            return a->arrivalTime > b->arrivalTime;
        }

        return a->remainingTime > b->remainingTime;
    }
};

int main() {

    int n;
    vector<Process> process_queue;

    priority_queue<Process*,
                   vector<Process*>,
                   comparator> pq;

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

    // Sort according to arrival time
    sort(process_queue.begin(), process_queue.end(),
        [](Process& p1, Process& p2) {

            if(p1.arrivalTime == p2.arrivalTime)
                return p1.pid < p2.pid;

            return p1.arrivalTime < p2.arrivalTime;
        });

    double process_timer = 0;

    double avgWaitingTime = 0;
    double avgTurnArroundTime = 0;

    int curr_process = 0;
    int completed = 0;

    while(completed < n) {

        if(pq.empty() &&
           curr_process < n &&
           process_timer < process_queue[curr_process].arrivalTime) {

            process_timer = process_queue[curr_process].arrivalTime;
        }

        while(curr_process < n &&
              process_queue[curr_process].arrivalTime <= process_timer) {

            pq.push(&process_queue[curr_process]);
            curr_process++;
        }

        Process* p = pq.top();
        pq.pop();

        if(p->responseTime == -1) {
            p->responseTime =
                process_timer - p->arrivalTime;
        }

        p->remainingTime--;
        process_timer++;

        if(p->remainingTime == 0) {

            p->completionTime = process_timer;

            p->turnAroundTime =
                p->completionTime - p->arrivalTime;

            p->waitingTime =
                p->turnAroundTime - p->burstTime;

            avgWaitingTime += p->waitingTime;
            avgTurnArroundTime += p->turnAroundTime;

            completed++;
        }
        else {
            pq.push(p);
        }
    }

    cout << endl;

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

    for(const Process& p : process_queue) {

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

    cout << "\nAverage Waiting Time: "
         << avgWaitingTime << endl;

    cout << "Average Turn Arround Time: "
         << avgTurnArroundTime << endl;

    return 0;
}
