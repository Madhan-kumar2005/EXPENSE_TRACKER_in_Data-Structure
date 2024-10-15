#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M 30
double currentincome = 0;
double currentexpense = 0;
struct node
{
    char date[M];
    double amount;
    struct node *next;
} *income = NULL, *expense = NULL;
void create(char x[], double y, struct node **temp);
void display(int a3);
void deleterecord(struct node **ptr, char date[], double amount, double *currentTotal);
int main()
{
    int option;
    double b;
    char a[M];
    char s1[15], s2[15], s3[15];
    do
    {
        // Display menu and current financial status
        printf("*****************\n");
        printf("YOUR INCOME: %.2lf INR\n", currentincome);
        printf("YOUR EXPENSE: %.2lf INR\n", currentexpense);
        printf("YOUR BALANCE: %.2lf INR\n", currentincome - currentexpense);
        printf("*****************\n");
        printf("1.INSERT INCOME\n");
                printf("2.INSERT EXPENSE\n");
        printf("3.VIEW INCOME RECORD\n");
        printf("4.VIEW EXPENSE RECORD\n");
        printf("5.DELETE INCOME RECORD\n");
        printf("6.DELETE EXPENSE RECORD\n");
        printf("7.EXIT\n");
        printf("Enter your choice: ");
        scanf("%d", &option);
        switch (option)
        {
            case 1:
                // Input income details
                printf("Enter the Date (e.g., day month year):");
                scanf("%s %s %s", s1, s2, s3);
                snprintf(a, sizeof(a), "%s %s %s", s1, s2, s3);
                printf("Enter the amount: ");
                scanf("%lf", &b);
                create(a, b, &income);
                currentincome += b;
                break;
                        case 2:
                // Input expense details
                printf("Enter the Date (e.g., day month year):");
                scanf("%s %s %s", s1, s2, s3);
                snprintf(a, sizeof(a), "%s %s %s", s1, s2, s3);
                printf("Enter the amount: ");
                scanf("%lf", &b);

                create(a, b, &expense);
                currentexpense += b;
                break;
            case 3:
                // View income records
                display(3);
                break;
            case 4:
                // View expense records
                display(4);
                break;
            case 5:
                                // Delete income record
                printf("Enter the Date of the income to delete (e.g., day month year):");
                scanf("%s %s %s", s1, s2, s3);
                snprintf(a, sizeof(a), "%s %s %s", s1, s2, s3);
                printf("Enter the amount of the income to delete: ");
                scanf("%lf", &b);
                deleterecord(&income, a, b, &currentincome);
                break;
            case 6:
                // Delete expense record
                printf("Enter the Date of the expense to delete (e.g., day month year):");
                scanf("%s %s %s", s1, s2, s3);
                snprintf(a, sizeof(a), "%s %s %s", s1, s2, s3);
                printf("Enter the amount of the expense to delete: ");
                scanf("%lf", &b);
                deleterecord(&expense, a, b, &currentexpense);
                break;
            case 7:
                // Exit
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    } while (option != 7);
    return 0;
}
void create(char x[], double y, struct node **temp)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        return;
	}
    strcpy(newNode->date, x);
    newNode->amount = y;
    newNode->next = *temp;
    *temp = newNode;
}
void display(int a3)
{
    struct node *ptr;
    if (a3 == 3)
        ptr = income;
    else if (a3 == 4)
        ptr = expense;
    // Print table header
    printf("\n------------------------------------------\n");
        printf("|     Date      |     Amount (INR)       |\n");
    printf("------------------------------------------\n");
    // Print table rows
    while (ptr != NULL)
    {
        printf("| %13s | %18.2lf |\n", ptr->date, ptr->amount);
        ptr = ptr->next;
    }
    printf("------------------------------------------\n");
}
void deleterecord(struct node **head, char date[], double amount, double *currentTotal)
{
    struct node *temp = *head, *prev = NULL;
    // If head node itself holds the key to be deleted
    if (temp != NULL && strcmp(temp->date, date) == 0 && temp->amount == amount)
    {
        *head = temp->next; // Changed head
        *currentTotal -= temp->amount;
        free(temp); // free old head
        printf("Record deleted successfully.\n");
                return;
	}
    // Search for the key to be deleted, keep track of the previous node
    while (temp != NULL && (strcmp(temp->date, date) != 0 || temp->amount != amount))
    {
        prev = temp;
        temp = temp->next;
	}
    // If key was not present in linked list
    if (temp == NULL)
    {
        printf("Record not found.\n");
        return;
	}
    // Unlink the node from linked list
    prev->next = temp->next;
    *currentTotal -= temp->amount;
    free(temp);
    printf("Record deleted successfully.\n");
}