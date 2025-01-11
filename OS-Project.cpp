#include <iostream>
#include <algorithm>
#include <windows.h>  

using namespace std;

const int MAX_PROCESSES = 10;

struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitTime;
};

void PreemptiveScheduling() {
	system("Color E4"); 
    int numProcesses;
    cout<<"\t\t\t-------------------------------------------------------------\n";
    cout << "\t\t\tEnter the number of processes: ";
    cin >> numProcesses;
    cout<<"\t\t\t-------------------------------------------------------------\n";
    Process processes[MAX_PROCESSES];

    for (int i = 0; i < numProcesses; ++i) {
        cout << "\t\t\tEnter details for Process " << i + 1 << ":\n";
        processes[i].id = i + 1;
        cout << "\t\t\tArrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "\t\t\tBurst Time: ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].waitTime = 0;
    }
    cout<<"\t\t\t-------------------------------------------------------------\n";
    int currentTime = 0;
    int totalRemainingTime = 0;
    for (int i = 0; i < numProcesses; ++i) {
        totalRemainingTime += processes[i].burstTime;
    }

    while (totalRemainingTime > 0) {
        int shortestJobIndex = -1;
        int shortestJobTime = INT_MAX;
        for (int i = 0; i < numProcesses; ++i) {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                if (processes[i].burstTime < shortestJobTime) {
                    shortestJobIndex = i;
                    shortestJobTime = processes[i].burstTime;
                }
            }
        }
        if (shortestJobIndex == -1) {
            currentTime++;
        } else {
            int executeTime = 1;
            processes[shortestJobIndex].remainingTime -= executeTime;
            totalRemainingTime -= executeTime;
            currentTime++;

            // Update wait time for processes that are waiting
            for (int i = 0; i < numProcesses; ++i) {
                if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime > 0) {
                    processes[i].waitTime += executeTime; // Increment wait time by the execution time
                }
            }

            if (processes[shortestJobIndex].remainingTime == 0) {
                cout << "\t\t\tTime " << currentTime << ": Process " << processes[shortestJobIndex].id << " completed\n";
                cout<<"\t\t\t-------------------------------------------------------------\n";
            }
        }
    }

    cout << "\n\t\t\tTurnaround Time:\n";
    for (int i = 0; i < numProcesses; ++i) {
        int turnaroundTime = processes[i].burstTime + processes[i].waitTime; // Turnaround time = Burst time + Wait time
        cout << "\t\t\tProcess " << processes[i].id << ": " << turnaroundTime << " units\n";
    }

    cout<<"\t\t\t--------------------------------------------------------------------------\n";
    cout << "\n\t\t\tProcesses before scheduling:\n";
    cout << "\t\t\tProcess ID\tArrival Time\tBurst Time\tRemaining Time\tWait Time\n";
    for (int i = 0; i < numProcesses; ++i) {
        cout << "\t\t\t"<< processes[i].id << "\t\t"
             << processes[i].arrivalTime << "\t\t"
             << processes[i].burstTime << "\t\t"
             << processes[i].remainingTime << "\t\t"
             << processes[i].waitTime << "\n";
    }
    cout<<"\t\t\t--------------------------------------------------------------------------\n";
    cout << "\n\t\t\tTurnaround Time for each process:\n";
    cout << "\t\t\tProcess ID\tTurnaround Time\n";
    for (int i = 0; i < numProcesses; ++i) {
        cout <<"\t\t\t" << processes[i].id << "\t\t" << processes[i].waitTime << "\n";
    }
    cout<<"\t\t\t-------------------------------------------------------------\n";
    int totalWaitTimeSJF = 0;
    for (int i = 0; i < numProcesses; ++i) {
        totalWaitTimeSJF += processes[i].waitTime;
    }
    float averageWaitTimeSJF = static_cast<float>(totalWaitTimeSJF) / numProcesses;
    cout << "\n\t\t\tAverage Wait Time (SJF): " << averageWaitTimeSJF << "\n";
    cout<<"\t\t\t-------------------------------------------------------------\n";

    int currentTimeFCFS = 0;
    for (int i = 0; i < numProcesses; ++i) {
        processes[i].waitTime = max(0, currentTimeFCFS - processes[i].arrivalTime);
        currentTimeFCFS += processes[i].burstTime;
    }

    int totalWaitTimeFCFS = 0;
    for (int i = 0; i < numProcesses; ++i) {
        totalWaitTimeFCFS += processes[i].waitTime;
    }
    float averageWaitTimeFCFS = static_cast<float>(totalWaitTimeFCFS) / numProcesses;
    cout<<"\t\t\t-------------------------------------------------------------\n";
    cout << "\t\t\tAverage Wait Time (FCFS): " << averageWaitTimeFCFS << "\n";
    cout<<"\t\t\t-------------------------------------------------------------\n";
    if (averageWaitTimeSJF < averageWaitTimeFCFS) {
        cout << "\t\t\tSJF has less average wait time.\n";
        cout<<"\t\t\t-------------------------------------------------------------\n";
    } else if (averageWaitTimeSJF > averageWaitTimeFCFS) {
        cout << "\t\t\tFCFS has less average wait time.\n";
        cout<<"\t\t\t-------------------------------------------------------------\n";
    } else {
        cout << "\t\t\tBoth SJF and FCFS have the same average wait time.\n";
        cout<<"\t\t\t-------------------------------------------------------------\n";
    }
}

void roundRobinScheduling() {
	system("Color 0A");
    int numProcesses;
    cout<<"\t\t\t-------------------------------------------------------------\n";
    cout << "\t\t\tEnter the number of processes: ";
    cin >> numProcesses;
     cout<<"\t\t\t-------------------------------------------------------------\n";
    Process processes[MAX_PROCESSES];

    for (int i = 0; i < numProcesses; ++i) {
        cout << "\t\t\tEnter details for Process " << i + 1 << ":\n";
        processes[i].id = i + 1;
        cout << "\t\t\tArrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "\t\t\tBurst Time: ";
        cin >> processes[i].burstTime;
        processes[i].remainingTime = processes[i].burstTime;
        processes[i].waitTime = 0;
    }
    cout<<"\t\t\t-------------------------------------------------------------\n";
    int timeQuantum;
    cout << "\t\t\tEnter the time quantum: ";
    cin >> timeQuantum;
    cout<<"\t\t\t-------------------------------------------------------------\n";
    cout << "\n\t\t\tRound-Robin Scheduling:\n";
    int turnaroundTime[MAX_PROCESSES] = {0};
    int totalRemainingTime = 0;
    for (int i = 0; i < numProcesses; ++i) {
        totalRemainingTime += processes[i].burstTime;
    }
    int currentTime = 0;
    while (totalRemainingTime > 0) {
        for (int i = 0; i < numProcesses; ++i) {
            if (processes[i].remainingTime > 0) {
                int executeTime = min(timeQuantum, processes[i].remainingTime);
                processes[i].remainingTime -= executeTime;
                totalRemainingTime -= executeTime;
                currentTime += executeTime;
                if (processes[i].remainingTime == 0) {
                    turnaroundTime[i] = currentTime - processes[i].arrivalTime;
                }
            }
        }
    }

    for (int i = 0; i < numProcesses; ++i) {
        processes[i].waitTime = turnaroundTime[i] - processes[i].burstTime;
    }
    cout<<"\t\t\t-------------------------------------------------------------\n";
    cout << "\n\t\t\tProcesses before scheduling:\n";
    cout << "\t\t\tProcess ID\tArrival Time\tBurst Time\tRemaining Time\tWait Time\n";
    for (int i = 0; i < numProcesses; ++i) {
        cout << "\t\t\t" << processes[i].id << "\t\t"
             << processes[i].arrivalTime << "\t\t"
             << processes[i].burstTime << "\t\t"
             << processes[i].remainingTime << "\t\t"
             << processes[i].waitTime << "\n";
    }
    cout<<"\t\t\t-------------------------------------------------------------\n";
    cout << "\n\t\t\tTurnaround Time for each process:\n";
    cout << "\t\t\tProcess ID\tTurnaround Time\n";
    for (int i = 0; i < numProcesses; ++i) {
        cout << "\t\t\t" << processes[i].id << "\t\t" << turnaroundTime[i] << "\n";
    }
    cout<<"\t\t\t-------------------------------------------------------------\n";
    int totalWaitTime = 0;
    for (int i = 0; i < numProcesses; ++i) {
        totalWaitTime += processes[i].waitTime;
    }
    float averageWaitTime = static_cast<float>(totalWaitTime) / numProcesses;
    cout << "\n\t\t\tAverage Wait Time: " << averageWaitTime << "\n";
    cout<<"\t\t\t-------------------------------------------------------------\n";
}

void nonPreemptive() {
	system("Color DE"); 
    int choice;

    cout << "\t\t\t----------------Which non-preemptive scheduling?-----------------\n"
         << "\t\t\t1) Round Robin\n"
         << "\t\t\t2) Main Menu\n"
         << "\t\t\t-----------------------------------------------------------------\n";
         cout<<"\t\t\t-------------------------------------------------------------\n";
    cin >> choice;

    switch (choice) {
        case 1:
            roundRobinScheduling();
            break;
        case 2:
            break;
        default:
            cout << "\t\t\tInvalid choice. Please try again.\n";
            nonPreemptive();
    }
}

void preemptive() {
	system("Color 5E"); 
    int choice; 
    cout << "\t\t\t-------------------Preemptive scheduling---------------------\n"
         << "\t\t\t1) Enter the required input\n"
         << "\t\t\t2) Main Menu\n"
         << "\t\t\t-------------------------------------------------------------\n";
    cout<<"\t\t\t-------------------------------------------------------------\n";
    cin >> choice;

    switch (choice) {
        case 1:
            PreemptiveScheduling();
            break;
        case 2:
        	system("color 4B");
            break;
        default:
        	system("color 2D");
            cout << "\t\t\tInvalid choice. Please try again.\n";
            cout<<"\t\t\t-------------------------------------------------------------\n";
    }
}

void scheduling() {
	system("Color F1"); 
    int choice;
    cout<<"\t\t\t-------------------------------------------------------------\n";
    cout << "\t\t\tWhich scheduling?\n"
         << "\t\t\t1) Non-Preemptive\n"
         << "\t\t\t2) Preemptive\n"
         << "\t\t\t3) Main Menu\n";
    cin >> choice;
    cout<<"\t\t\t-------------------------------------------------------------\n";
    switch (choice) {
        case 1:
            nonPreemptive();
            break;
        case 2:
            preemptive();
            break;
        case 3:
        	system("color B6");
            break;
        default:
            cout << "\t\t\tInvalid choice. Please try again.\n";
            cout<<"\t\t\t-------------------------------------------------------------\n";
            scheduling();
    }
}

void inputArray(int arr[], int size) {
	system("Color 02"); 
	cout<<"\t\t\t--------------------------------------------------------------\n";
    cout << "\t\t\tEnter the elements of the array: ";
    for (int i = 0; i < size; ++i) {
        cin >> arr[i];
    }
    cout<<"\t\t\t-------------------------------------------------------------\n";
    
}

void fixedSizePartition(const int arr[], int size, int partitionSize) {
    int partitions = size / partitionSize;
    if (size % partitionSize != 0)
        partitions++;

    int index = 0;
    system("Color 65"); 
    cout<<"\t\t\t-------------------------------------------------------------\n";
    for (int i = 0; i < partitions; ++i) {
        cout << "\t\t\tPartition " << i + 1 << ": ";
        for (int j = 0; j < partitionSize && index < size; ++j) {
            cout << arr[index] << " ";
            index++;
        }
        cout << endl;
    }
    cout<<"\t\t\t-------------------------------------------------------------\n";
}

void variableSizePartition(const int arr[], int size, int partitionSizes[], int numPartitions) {
    int index = 0;
    system("Color 8F"); 
    for (int i = 0; i < numPartitions; ++i) {
        cout << "\t\t\tPartition " << i + 1 << ": ";
        int partitionSize = partitionSizes[i];
        for (int j = 0; j < partitionSize && index < size; ++j) {
            cout << arr[index] << " ";
            index++;
        }
        cout << endl;
    }
}

void partitioning() {
	system("Color E4"); 
    int size;
    cout<<"\t\t\t-------------------------------------------------------------\n";
    cout << "\t\t\tEnter the size of the array: ";
    cin >> size;

    int* arr = new int[size];
    inputArray(arr, size);

    int choice;
    
    cout << "\t\t\t Enter 1 for Fixed Size Partitioning \n\t\t\t Enter 2 for Variable Size Partitioning\n ";
    cin >> choice;
    cout<<"\t\t\t-------------------------------------------------------------\n";
    if (choice == 1) {
    	system("COLOR F5");
        int partitionSize;
        cout << "\t\t\tEnter the partition size: ";
        cin >> partitionSize;
        cout<<"\t\t\t-------------------------------------------------------------\n";
        system("COLOR 94");
        cout << "\t\t\tFixed Size Partitioning:\n";
        fixedSizePartition(arr, size, partitionSize);
        cout<<"\t\t\t-------------------------------------------------------------\n";
    } else if (choice == 2) {
        int numPartitions;
        cout << "\t\t\tEnter the number of partitions: ";
        cin >> numPartitions;
        cout<<"\t\t\t-------------------------------------------------------------\n";

        int* partitionSizes = new int[numPartitions];
        cout << "\t\t\tEnter the sizes of partitions: ";
        for (int i = 0; i < numPartitions; ++i) {
            cin >> partitionSizes[i];
        }
        cout<<"\t\t\t-------------------------------------------------------------\n";

        cout << "\t\t\tVariable Size Partitioning:\n";
        variableSizePartition(arr, size, partitionSizes, numPartitions);
        cout<<"\t\t\t-------------------------------------------------------------\n";
        delete[] partitionSizes;
    } else {
        cout << "\t\t\tInvalid choice. Exiting...\n";
        cout<<"\t\t\t-------------------------------------------------------------\n";
    }

    delete[] arr;
}

int main() {
	system("color 0A"); 
    int choice;
    cout<<"\t\t\t-------------------------------------------------------------\n";
    while (true) {
        cout << "\t\t\tWhat activity are you interested in pursuing?\n"
             <<"\t\t\t-------------------------------------------------------------\n"
             << "\t\t\tPress desired number: \n"
             << "\t\t\t1) Scheduling\n"
             << "\t\t\t2) Partitioning\n"
             << "\t\t\t3) Quit\n";
             cout<<"\t\t\t-------------------------------------------------------------\n";
        cin >> choice;

        switch (choice) {
            case 1:
                scheduling();
                break;
            case 2:
            	cout<<"\t\t\t-------------------------------------------------------------\n";
            	system("color E4");
                partitioning();
                break;
            case 3:
            	system("color 0F");
                exit(0);
            default:
            	system("color B0");
            	cout<<"\t\t\t-------------------------------------------------------------\n";
                cout << "\t\t\tInvalid choice. Please try again.\n";
        }
    }
    system("color 1E");
    cout<<"\t\t\t-------------------------------------------------------------\n";
    return 0;
}

