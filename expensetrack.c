#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define FILE_NAME "transactions.txt"
#define MAX 200

/* Structure to store a transaction */
struct Transaction {
    char date[15];
    char category[20];
    char description[100];
    int amount;
};

/* Function to get today's date */
void get_today_date(char *date) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    sprintf(date,"%02d-%02d-%04d",tm.tm_mday,tm.tm_mon+1,tm.tm_year+1900);
}

/* Add a new transaction */
void add_transaction() {

    FILE *fp = fopen(FILE_NAME,"a");
    if(fp == NULL){
        printf("Error opening file\n");
        return;
    }

    struct Transaction t;
    int type_choice;
    int date_choice;

    printf("\nTransaction type\n");
    printf("1. Income\n");
    printf("2. Expense\n");
    printf("Enter choice: ");
    scanf("%d",&type_choice);

    if(type_choice!=1 && type_choice!=2){
        printf("Invalid type\n");
        fclose(fp);
        return;
    }

    printf("\nDate selection\n");
    printf("1. Use today's date\n");
    printf("2. Enter custom date\n");
    printf("Enter choice: ");
    scanf("%d",&date_choice);

    if(date_choice==1){
        get_today_date(t.date);
    }
    else{
        printf("Enter date (DD-MM-YYYY): ");
        scanf("%s",t.date);
    }

    if(type_choice==1){
        strcpy(t.category,"income");
    }
    else{

        int cat;

        printf("\nExpense category\n");
        printf("1. Food\n");
        printf("2. Travel\n");
        printf("3. Utilities\n");
        printf("4. Other\n");
        printf("Enter option: ");
        scanf("%d",&cat);

        switch(cat){
            case 1: strcpy(t.category,"food"); break;
            case 2: strcpy(t.category,"travel"); break;
            case 3: strcpy(t.category,"utilities"); break;
            case 4: strcpy(t.category,"other"); break;
            default:
                printf("Invalid category\n");
                fclose(fp);
                return;
        }
    }

    getchar(); // clear buffer

    printf("Enter description: ");
    fgets(t.description,100,stdin);
    t.description[strcspn(t.description,"\n")] = 0;

    printf("Enter amount: ");
    scanf("%d",&t.amount);

    if(type_choice==2)
        t.amount = -t.amount;

    fprintf(fp,"%s,%s,%s,%d\n",t.date,t.category,t.description,t.amount);

    fclose(fp);

    printf("Transaction added successfully\n");
}

/* View all transactions */

void view_transactions(){

    FILE *fp = fopen(FILE_NAME,"r");

    if(fp==NULL){
        printf("No transactions available\n");
        return;
    }

    struct Transaction t;

    printf("\nDate\t\tCategory\tDescription\tAmount\n");
    printf("---------------------------------------------------------------\n");

    while(fscanf(fp,"%[^,],%[^,],%[^,],%d\n",t.date,t.category,t.description,&t.amount)!=EOF){

        printf("%s\t%-10s\t%-20s\t%d\n",
               t.date,
               t.category,
               t.description,
               t.amount);
    }

    fclose(fp);
}

/* Filter transactions */

void filter_transactions(){

    char filter[50];

    printf("Enter date or category to filter: ");
    scanf("%s",filter);

    FILE *fp = fopen(FILE_NAME,"r");

    if(fp==NULL){
        printf("No data available\n");
        return;
    }

    struct Transaction t;

    printf("\nFiltered results\n");

    while(fscanf(fp,"%[^,],%[^,],%[^,],%d\n",t.date,t.category,t.description,&t.amount)!=EOF){

        if(strstr(t.date,filter) || strstr(t.category,filter)){

            printf("%s\t%s\t%s\t%d\n",
                   t.date,
                   t.category,
                   t.description,
                   t.amount);
        }
    }

    fclose(fp);
}

/* Sum expenses by category */

void sum_by_category(){

    FILE *fp = fopen(FILE_NAME,"r");

    if(fp==NULL){
        printf("No data available\n");
        return;
    }

    struct Transaction t;

    int food=0, travel=0, utilities=0, other=0;

    while(fscanf(fp,"%[^,],%[^,],%[^,],%d\n",t.date,t.category,t.description,&t.amount)!=EOF){

        if(t.amount < 0){

            if(strcmp(t.category,"food")==0)
                food += -t.amount;

            else if(strcmp(t.category,"travel")==0)
                travel += -t.amount;

            else if(strcmp(t.category,"utilities")==0)
                utilities += -t.amount;

            else if(strcmp(t.category,"other")==0)
                other += -t.amount;
        }
    }

    printf("\nTotal Spending By Category\n");
    printf("Food: %d\n",food);
    printf("Travel: %d\n",travel);
    printf("Utilities: %d\n",utilities);
    printf("Other: %d\n",other);

    fclose(fp);
}

/* Monthly balance */

void monthly_balance(){

    FILE *fp = fopen(FILE_NAME,"r");

    if(fp==NULL){
        printf("No data available\n");
        return;
    }

    struct Transaction t;

    int income=0;
    int expense=0;

    while(fscanf(fp,"%[^,],%[^,],%[^,],%d\n",t.date,t.category,t.description,&t.amount)!=EOF){

        if(t.amount > 0)
            income += t.amount;
        else
            expense += -t.amount;
    }

    printf("\nTotal Income : %d\n",income);
    printf("Total Expense: %d\n",expense);
    printf("Balance      : %d\n",income-expense);

    fclose(fp);
}

/* Main program */

int main(){

    int choice;

    while(1){

        printf("\n===== PERSONAL FINANCE TRACKER =====\n");
        printf("1. Add Transaction\n");
        printf("2. View All Transactions\n");
        printf("3. Filter Transactions\n");
        printf("4. Sum By Category\n");
        printf("5. Monthly Balance\n");
        printf("6. Exit\n");
        printf("====================================\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice){

            case 1:
                add_transaction();
                break;

            case 2:
                view_transactions();
                break;

            case 3:
                filter_transactions();
                break;

            case 4:
                sum_by_category();
                break;

            case 5:
                monthly_balance();
                break;

            case 6:
                printf("Program terminated\n");
                exit(0);

            default:
                printf("Invalid option\n");
        }
    }

    return 0;
}
