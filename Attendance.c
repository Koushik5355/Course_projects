#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STUDENTS 100

int allStudents[MAX_STUDENTS];
int totalStudents = 0;

struct Node {
    int id;
    struct Node* next;
};

/* Check if a student is registered */
bool isRegistered(int id) {
    for (int i = 0; i < totalStudents; i++) {
        if (allStudents[i] == id)
            return true;
    }
    return false;
}

/* Check if a student is already marked present */
bool isAlreadyPresent(struct Node* head, int id) {
    while (head != NULL) {
        if (head->id == id)
            return true;
        head = head->next;
    }
    return false;
}

/* Add student ID to attendance list */
struct Node* addAtEnd(struct Node* head, int id) {
    struct Node* newNode = malloc(sizeof(struct Node));
    newNode->id = id;
    newNode->next = NULL;

    if (head == NULL)
        return newNode;

    struct Node* temp = head;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;

    return head;
}

/* Register students */
void registerStudents() {
    printf("Enter number of students to register: ");
    scanf("%d", &totalStudents);

    if (totalStudents <= 0 || totalStudents > MAX_STUDENTS) {
        printf("Invalid number of students.\n");
        totalStudents = 0;
        return;
    }

    for (int i = 0; i < totalStudents; i++) {
        printf("Enter ID for student %d: ", i + 1);
        scanf("%d", &allStudents[i]);
    }
}

/* Show all registered students */
void showAllStudents() {
    if (totalStudents == 0) {
        printf("No students registered.\n");
        return;
    }

    printf("\n--- Registered Students ---\n");

    for (int i = 0; i < totalStudents; i++)
        printf("Student ID: %d\n", allStudents[i]);
}

/* Show present students */
void showPresentStudents(struct Node* head) {
    if (head == NULL) {
        printf("No attendance marked yet.\n");
        return;
    }

    printf("\n--- Present Students ---\n");

    while (head != NULL) {
        printf("Student ID: %d\n", head->id);
        head = head->next;
    }
}

/* Show absent students */
void showAbsentStudents(struct Node* head) {
    if (totalStudents == 0)
        return;

    printf("\n--- Absent Students ---\n");

    for (int i = 0; i < totalStudents; i++) {
        if (!isAlreadyPresent(head, allStudents[i]))
            printf("Student ID: %d\n", allStudents[i]);
    }
}

/* Mark attendance */
struct Node* markAttendance(struct Node* head) {
    int n, id;

    printf("Enter number of students to mark present: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter ID of student %d: ", i + 1);
        scanf("%d", &id);

        if (!isRegistered(id)) {
            printf("ID %d is not registered.\n", id);
            continue;
        }

        if (isAlreadyPresent(head, id)) {
            printf("ID %d is already marked present.\n", id);
            continue;
        }

        head = addAtEnd(head, id);
        printf("ID %d marked present.\n", id);
    }

    return head;
}

/* Display menu */
void showMenu() {
    printf("\n=== Attendance Menu ===\n");
    printf("1. Mark Attendance\n");
    printf("2. Show Present Students\n");
    printf("3. Show Absent Students\n");
    printf("4. Show All Registered Students\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

/* Main function */
int main() {
    struct Node* attendanceList = NULL;
    int choice;

    printf("\n--- Digital Attendance System ---\n\n");

    registerStudents();

    while (1) {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                attendanceList = markAttendance(attendanceList);
                break;

            case 2:
                showPresentStudents(attendanceList);
                break;

            case 3:
                showAbsentStudents(attendanceList);
                break;

            case 4:
                showAllStudents();
                break;

            case 5:
                printf("Exiting... Goodbye!\n");
                return 0;

            default:
                printf("Invalid option. Please try again.\n");
        }
    }

    return 0;
}
