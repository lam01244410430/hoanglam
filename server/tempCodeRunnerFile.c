void createEmp(FILE *file, emp **head) {
    emp *newEmployee = (emp *)malloc(sizeof(emp));

    if (newEmployee == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    
    newEmployee->next = NULL;

    printf("Enter name: ");
    scanf("%s", newEmployee->name);
    printf("Enter number: ");
    scanf("%s", newEmployee->number);

    printf("Enter wage: ");
    scanf("%d", &newEmployee->wage);
    while (getchar() != '\n');

    printf("Enter worked hour: ");
    scanf("%d", &newEmployee->hour);
    while (getchar() != '\n');
    
    for (emp *staff = *head; staff != NULL; staff = staff->next) {
        if (strcmp(newEmployee->number, staff->number) == 0) {
            printf("Employee with this number already exists. Please enter a different number!\n");
            free(newEmployee);
            printf("Press Enter to continue...");
            while (getchar() != '\n');
            return createEmp(file, *head);
        }
    }

    if (*head == NULL) *head = newEmployee;
    else {
        emp *staff = *head;
        while (staff->next != NULL) {
            staff = staff->next;
        }
        staff->next = newEmployee;
    }

    printf("Create successful!\n");
    printf("Press Enter to continue...");
    getch();
    system("cls");
    option2(file, *head);
}

void deleteEmp(FILE *file, emp *head) {
    char yn[4];
    char numdel[10];
    printf("Number delete: ");
    scanf("%s" ,numdel);

    emp *current = head;
    emp *pre = NULL;
    int found = 0;

    while (current != NULL) {
        while (fscanf(file, "%s %s %d %d", current->name, current->number, &current->wage, &current->hour) != EOF) {
            if (strcmp(current->number, numdel) == 0) {
                found = 1;
                printf("Are you sure to delete this person? [Yes/No]\n");
                fgets(yn, 4, stdin);
                if (strcmp(yn, "Yes\n") == 0) {
                    if (pre != NULL) pre->next = current->next;
                    else head = current->next;

                    free(current);
                    printf("Delete completed! Press Enter to continue...\n");
                    getch();
                    fflush(stdin);
                    system("cls");
                    return option2(file, head);
                } else {
                    printf("Deletion cancelled.\n");
                    return option2(file, head);
                }
            }
            pre = current;
            current = current->next;
        }
    }

    if (!found) {
        printf("This person does not exist!\n");
    }

    freopen(NULL, "w", file);
    emp *tmp = head;
    while (tmp != NULL) {
        fprintf(file, "%s %s %d %d\n", tmp->name, tmp->number, tmp->wage, tmp->hour);
        tmp = tmp->next;
    }
}
