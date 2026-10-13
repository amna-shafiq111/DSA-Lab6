#include <iostream>
using namespace std;

struct Patient {
int id;
char name[50];
};

class PatientQueue {
private:
Patient patients[100];
int front;
int rear;
int count;

public:
PatientQueue() {
front = 0;
rear = -1;
count = 0;
}

bool isEmpty() {
    return count == 0;
}

bool isFull() {
    return count == 100;
}

void RegisterPatient() {
    if (isFull()) {
        cout << "Waiting queue is full. Cannot register more patients.\n";
        return;
    }

    Patient p;

    cout << "Enter patient ID: ";
    cin >> p.id;

    cout << "Enter patient name (no spaces): ";
    cin >> p.name;

    rear = (rear + 1) % 100;
    patients[rear] = p;
    count++;

    cout << "Patient registered successfully.\n";
}

void ServePatient() {
    if (isEmpty()) {
        cout << "No patients are waiting.\n";
        return;
    }

    cout << "Now serving: " << patients[front].name
         << " (ID: " << patients[front].id << ")\n";

    front = (front + 1) % 100;
    count--;
}

void CancelAll() {
    if (isEmpty()) {
        cout << "There are no patients to cancel.\n";
        return;
    }

    front = 0;
    rear = -1;
    count = 0;

    cout << "All waiting patients have been cancelled.\n";
}

void CanDoctorGoHome() {
    if (isEmpty()) {
        cout << "Yes, the doctor can go home. No patients are waiting.\n";
    } else {
        cout << "No, the doctor cannot go home. Patients are still waiting.\n";
    }
}

void ShowAllPatient() {
    if (isEmpty()) {
        cout << "No patients are waiting.\n";
        return;
    }

    cout << "\n--- Waiting Patients ---\n";

    for (int i = 0; i < count; i++) {
        int index = (front + i) % 100;

        cout << "Patient ID: " << patients[index].id
             << " | Name: " << patients[index].name << '\n';
    }
}


};

int main() {
PatientQueue queue;
int choice;


do {
    cout << "\n===== PATIENT WAITING QUEUE =====\n";
    cout << "1. Register Patient\n";
    cout << "2. Serve Patient\n";
    cout << "3. Cancel All Patients\n";
    cout << "4. Can Doctor Go Home?\n";
    cout << "5. Show All Patients\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";

    cin >> choice;

    switch (choice) {
        case 1:
            queue.RegisterPatient();
            break;

        case 2:
            queue.ServePatient();
            break;

        case 3:
            queue.CancelAll();
            break;

        case 4:
            queue.CanDoctorGoHome();
            break;

        case 5:
            queue.ShowAllPatient();
            break;

        case 0:
            cout << "Exiting program.\n";
            break;

        default:
            cout << "Invalid choice. Please try again.\n";
    }

} while (choice != 0);

return 0;


}
