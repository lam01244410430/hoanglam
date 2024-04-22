#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUM_USERS 99999
#define MAX_USERNAME_LENGTH 25
#define MAX_PASSWORD_LENGTH 25

struct user{
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

typedef struct emp{
    char name[10001];
    char number[10001];
    int salary;
    int hour;
    struct emp *next;
} emp;

emp *head;

void hidePass(char *password, int maxLength){
    int i = 0;
    char ch;
    while(1) {
        ch = getchar();
        if (ch == 13) 
            break;
        if (i < maxLength - 1){
            password[i] = ch;
            putchar("*");
            i++;
        }
    }
    password[i] = '\0';
    printf("\n");
}

void login(struct user *users, int numUsers, const char *username, const char *password){
    for (int i = 0; i < numUsers; i++){
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("")
        }
    }
}

int readAccountsFromFile(FILE *file, struct user *users) {
    int numUsers = 0;
    while (fscanf(file, "%s %s", users[numUsers].username, users[numUsers].password) == 2) {
        numUsers++;
    }
    return numUsers;
}

void writetoFile(FILE *file, emp *head){
    if(head->next != NULL) {
        fprintf(file, "\n%s %s %d %d", head->name, head->number, head->salary, head->hour);
        writetoFile(file, head->next);
    }
    else
        fprintf(file, "\n%s %s %d %d\n", head->name, head->number, head->salary, head->hour);
}

void option1(emp *head){
    int choice;
    do{
        printf("========================= COLLEGE FACULTY AND STAFF MANAGEMENT SYSTEM  =========================\n\n");
        printf("[1] Teacher\n");
        printf("[2] Laboratory staff\n");
        printf("[3] Office staff\n");
        printf("[0] Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch(choice){
        case '1':
            teacher(head);
            break;
        case '2':
            labostaff(head);
            break;
        case '3':
            offstaff(head);
            break;
        case '0':
            printf("Exiting...\n");
            break;
        default:
            printf("INVALID SELECTION, PLEASE CHOOSE AGAIN!\n");
            printf("Enter to continue...");
            getch();
            return option1(head);
    } while(choice!=0);
    }
}

void option2(FILE *file, emp *head){
    printf("[1] View\n");
    printf("[2] Create\n");
    printf("[3] Delete\n");
    printf("[4] Search\n");
    printf("[0] Exit\n");
    printf("Enter your choice: ");
    int choice;
    scanf("%d", &choice);

    switch(choice){
        case '1':
            viewEmp(file, head);
            break;
        case '2':
            createEmp(file, head);
            break;
        case '3':
            deleteEmp(file, head);
            break;
        case '4':
            searchEmp(file, head);
            break;
        case '0':
            printf("Exiting...\n");
            getch();
            option1(head);
            break;
        default:
            printf("INVALID SELECTION, PLEASE CHOOSE AGAIN!\n");
            printf("Enter to continue...");
            getch();
            return option2(file, head);
    }
}

void viewEmp(FILE *file, emp *head){
    emp *staff;
    staff = head;
    printf("=====================================================================================\n");
    printf("%-20s %-20s %-10s %-10s %-20s\n", "Name", "Number", "Salary", "Hour", "Month of Salary");
    while(staff != NULL){
        while (fscanf(file, "%s %s %d %d", staff->name, staff->number, &head->salary, &head->hour) != EOF) {
            int monthsalary = staff->salary * staff->hour;
            printf("%-20s %-20s %-10d %-10d %-20d\n", head->name, head->number, head->salary, head->hour, monthsalary);
            if (staff = staff->next) break;
        }
    }
    printf("=====================================================================================\n");
}

void createEmp(FILE *file, emp **head) {
    emp *newEmployee = (emp *)malloc(sizeof(emp));

    if (newEmployee == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }

    emp *staff = *head;
    while (staff != NULL && staff->next != NULL) {
        staff = staff->next;
    }

    printf("Enter name: ");
    fflush(stdin);
    fgets(newEmployee->name, 10001, stdin);

    printf("Enter number: ");
    fflush(stdin);
    fgets(newEmployee->number, 10001, stdin);

    printf("Enter salary: ");
    fflush(stdin);
    scanf("%d", &newEmployee->salary);

    printf("Enter worked hour: ");
    fflush(stdin);
    scanf("%d", &newEmployee->hour);

    staff = *head;
    while (staff != NULL) {
        if (atoi(newEmployee->number) == atoi(staff->number)) { 
            printf("Employee with this number already exists. Please enter a different number!\n");
            free(newEmployee); 
            printf("Press Enter to continue...");
            getch();
            return;
        }
        staff = staff->next;
    }

    if (*head == NULL) *head = newEmployee;
    else {
        staff = *head;
        while (staff->next != NULL) {
            staff = staff->next;
        }
        staff->next = newEmployee;
    }

    writetoFile(file, *head);

    printf("Create successful!\n");
    printf("Press Enter to continue...");
    getch();
    return option2(file, *head);
}
void deleteEmp(FILE *file, emp *head, int NUM_USERS){
    int numdel;
    printf("Number delete: ");
    scanf("%d", &numdel);

    emp *current = head;
    emp *pre = NULL;

    while (current != NULL) {
        if (atoi(current->number) == numdel){
           if(pre != NULL) pre->next = current->next;
           else head = current->next;
           free(current);
            printf("Delete completed! Press Enter to continue...");
            getch();
            return option2(file, head);
        }
        pre = current;
        current = current->next;
    }
} 

void searchEmp(FILE *file, emp *head, int NUM_USERS){
    char searchNum[80];
    printf("Enter staff number need to search: ");
    scanf("%s", searchNum);

    emp *staff = head;

    while (staff != NULL) {
        int monthsalary = staff->salary * staff->hour;
        if (strcmp(staff->number, searchNum) == 0){
            printf("%s %s %d %d %d", staff->name, staff->number, staff->salary, staff->hour, monthsalary);
            if(staff->next = NULL) break;
            staff = staff->next;
            printf("Press Enter to continue...");
            getch();
            return option2(choice);
        }
        else {
            printf("This person does not exit!");
            printf("Press Enter to continue...");
            getch();
            return option2(choice);
        }
    }
}

void teacher(emp *head){

    FILE *pt = fopen("teacher.txt", "w");
    
    if (pt == NULL) {
        printf("Error opening file!\n");
        return;
    }

    option2(pt, head);
    fclose(pt);
}

void labostaff(emp *head){

    FILE *pt = fopen("laboratory_staff.txt", "w");

    if (pt == NULL) {
        printf("Error opening file!\n");
        return;
    }

    option2(pt, head);
    fclose(pt);
}

void offstaff(emp *head){

    FILE *pt = fopen("office_staff.txt", "s");
    if (pt == NULL) {
        printf("Error opening file!\n");
        return;
    }

    option2(pt, head);
    fclose(pt);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_USERS 100
#define MAX_USERNAME_LENGTH 50
#define MAX_PASSWORD_LENGTH 50

struct user {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
};

int readAccountsFromFile(FILE *file, struct user *users) {
    int numUsers = 0;
    char line[MAX_USERNAME_LENGTH + MAX_PASSWORD_LENGTH + 2];

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;
        char *username = strtok(line, ",");
        char *password = strtok(NULL, ",");
        strcpy(users[numUsers].username, username);
        strcpy(users[numUsers].password, password);
        numUsers++;
    }

    return numUsers;
}

int login(struct user *users, int numUsers, const char *inputUser, const char *inputPass) {
    for (int i = 0; i < numUsers; i++) {
        if (strcmp(users[i].username, inputUser) == 0 && strcmp(users[i].password, inputPass) == 0) {
            return 1;
        }
    }
    return 0;
}

void hidePass(char *password, int maxLength) {
    for (int i = 0; i < maxLength; i++) {
        password[i] = '*';
    }
}

void option1(emp *head) {
    // Implementation of option1 function
}

int main() {
    struct user users[NUM_USERS];
    char inputUser[MAX_USERNAME_LENGTH];
    char inputPass[MAX_PASSWORD_LENGTH];
    int numUsers;

    FILE *file = fopen("accounts.txt", "r");
    if (!file) {
        perror("File Error!");
        return 1;
    }

    numUsers = readAccountsFromFile(file, users);

    fclose(file);

    int logSuccess = 0;

    do {
        printf("Username: ");
        fgets(inputUser, sizeof(inputUser), stdin);
        inputUser[strcspn(inputUser, "\n")] = 0;

        printf("Password: ");
        fgets(inputPass, sizeof(inputPass), stdin);
        inputPass[strcspn(inputPass, "\n")] = 0;
        hidePass(inputPass, MAX_PASSWORD_LENGTH);

        if (login(users, numUsers, inputUser, inputPass)) {
            printf("               ===============================               \n");
            printf("               |           WELCOME TO         |              \n");
            printf("               |  COLLEGE FACULTY AND STAFF   |              \n");
            printf("               |       MANAGEMENT SYSTEM      |              \n");
            printf("               ===============================               \n\n");
            printf("Press Any Key to Continue...\n");
            getch();
            logSuccess = 1;
        } else {
            printf("Login failed! Please check your username or password.\n");
        }
    } while (!logSuccess);

    emp *head = NULL;

    option1(head);

    return 0;
}