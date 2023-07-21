#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student 
{
    int rollNumber;
    char name[50];
    float marks;
    struct Student* next;
};

struct Student* createStudent(int rollNumber, const char* name, float marks) {
    struct Student* newStudent = (struct Student*)malloc(sizeof(struct Student));
    newStudent->rollNumber = rollNumber;
    strcpy(newStudent->name, name);
    newStudent->marks = marks;
    newStudent->next = NULL;
    return newStudent;
}
void insertStudent(struct Student** head, int rollNumber, const char* name, float marks) {
    struct Student* newStudent = createStudent(rollNumber, name, marks);

    if (*head == NULL) {
        *head = newStudent;
    } else {
        struct Student* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newStudent;
    }
}
void deleteStudent(struct Student** head, int rollNumber) {
    if (*head == NULL) {
        printf("List is empty.\n");
        return;
    }

    struct Student* current = *head;
    struct Student* prev = NULL;

    while (current != NULL && current->rollNumber != rollNumber) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Student with roll number %d not found.\n", rollNumber);
        return;
    }

    if (prev == NULL) {
        *head = current->next;
    } else {
        prev->next = current->next;
    }

    free(current);
}
void traverseStudents(struct Student* head) {
    struct Student* current = head;
    while (current != NULL) {
        printf("Roll Number: %d, Name: %s, Marks: %.2f\n", current->rollNumber, current->name, current->marks);
        current = current->next;
    }
}
void freeStudents(struct Student* head) {
    struct Student* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    struct Student* studentList = NULL;
    insertStudent(&studentList, 101, "Suhaas", 89.1);
    insertStudent(&studentList, 102, "Sreeshanth", 77.5);
    insertStudent(&studentList, 103, "Navadeep", 96.0);
    printf("Student List:\n");
    traverseStudents(studentList);
    deleteStudent(&studentList, 102);
    printf("\nStudent List after deleting record:\n");
    traverseStudents(studentList);

    freeStudents(studentList);

    return 0;
}