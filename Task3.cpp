#include <iostream>
using namespace std;

struct PrintRequest {
    int requestID;
    int arrivalTime;
    int pages;
};

class CircularQueue {
private:
    PrintRequest* queue;
    int front;
    int rear;
    int count;
    int capacity;

    void resize() {
        int newCapacity = capacity * 2;
        PrintRequest* newQueue = new PrintRequest[newCapacity];

        for (int i = 0; i < count; i++) {
            newQueue[i] = queue[(front + i) % capacity];
        }

        delete[] queue;

        queue = newQueue;
        capacity = newCapacity;
        front = 0;
        rear = count;
    }

public:
    CircularQueue() {
        capacity = 2;
        queue = new PrintRequest[capacity];
        front = 0;
        rear = 0;
        count = 0;
    }

    ~CircularQueue() {
        delete[] queue;
    }

    bool isEmpty() {
        return count == 0;
    }

    int size() {
        return count;
    }

    void enqueue(PrintRequest request) {
        if (count == capacity) {
            resize();
        }

        queue[rear] = request;
        rear = (rear + 1) % capacity;
        count++;
    }

    PrintRequest dequeue() {
        if (isEmpty()) {
            return {-1, 0, 0};
        }

        PrintRequest request = queue[front];
        front = (front + 1) % capacity;
        count--;

        return request;
    }
};

int main() {
    CircularQueue printQueue;

    int numberOfRequests;

    cout << "PRINT SERVER SIMULATION" << endl;
    cout << "Enter number of print requests: ";
    cin >> numberOfRequests;

    if (numberOfRequests <= 0) {
        cout << "Number of requests must be positive." << endl;
        return 0;
    }

    for (int i = 0; i < numberOfRequests; i++) {
        PrintRequest request;

        request.requestID = i + 1;

        cout << "\nRequest " << request.requestID << endl;

        cout << "Enter arrival time: ";
        cin >> request.arrivalTime;

        cout << "Enter number of pages: ";
        cin >> request.pages;

        if (request.arrivalTime < 0 || request.pages <= 0) {
            cout << "Invalid input. Arrival time must be non-negative "
                 << "and pages must be positive." << endl;
            return 0;
        }

        printQueue.enqueue(request);
    }

    int currentTime = 0;
    int totalWaitingTime = 0;

    cout << "\n--- PRINT SERVER RESULTS ---" << endl;

    while (!printQueue.isEmpty()) {
        PrintRequest request = printQueue.dequeue();

        int startTime;

        if (currentTime < request.arrivalTime) {
            startTime = request.arrivalTime;
        } else {
            startTime = currentTime;
        }

        int waitingTime = startTime - request.arrivalTime;
        int finishTime = startTime + request.pages;

        cout << "\nRequest ID: " << request.requestID << endl;
        cout << "Arrival Time: " << request.arrivalTime << endl;
        cout << "Pages: " << request.pages << endl;
        cout << "Start Time: " << startTime << endl;
        cout << "Waiting Time: " << waitingTime << endl;
        cout << "Finish Time: " << finishTime << endl;

        totalWaitingTime += waitingTime;
        currentTime = finishTime;
    }

    double averageWaitingTime =
        static_cast<double>(totalWaitingTime) / numberOfRequests;

    cout << "\nTotal Waiting Time: " << totalWaitingTime << endl;
    cout << "Average Waiting Time: "
         << averageWaitingTime << endl;

    return 0;
}
