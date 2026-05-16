// PROJECT: Bank Management System; Programmer:ROHIT CHANDA
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

struct account
{
    int acc_no;
    char name[50];
    char password[20];
    float balance;
};

FILE *fp;
struct account acc;

/* Function Declarations */
void show_time();

void admin_login();
void admin_menu();
void create_account();
void view_accounts();
void search_account();
void delete_account();

void user_login();
void user_menu(struct account);
void deposit(int);
void withdraw(int);
void check_balance(int);

/* MAIN FUNCTION */
void main()
{
    int choice;
    

    do
    {
        
        show_time();

        printf("\n=================================");
        printf("\n   BANK MANAGEMENT SYSTEM");
        printf("\n=================================");
        printf("\n1. Admin Login");
        printf("\n2. User Login");
        printf("\n3. Exit");
        printf("\n---------------------------------");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: admin_login(); break;
            case 2: user_login(); break;
            case 3: exit(0);
            default: printf("\nInvalid Choice!");
        }
        
    } while(choice != 3);
}

/* SHOW DATE & TIME */
void show_time()
{
    time_t t;
    t = time(NULL);
    printf("\nCurrent Date & Time: %s", ctime(&t));
}

/* ADMIN LOGIN */
void admin_login()
{
    char pass[20];
    
    show_time();

    printf("\nEnter Admin Password: ");
    scanf("%s", &pass);

    if(strcmp(pass, "admin123") == 0)
        admin_menu();
    else
        printf("\nWrong Password!");
    
}

/* ADMIN MENU */
void admin_menu()
{
    int choice;
    do
    {
        
        show_time();

        printf("\n------ ADMIN MENU ------");
        printf("\n1. Create Account");
        printf("\n2. View All Accounts");
        printf("\n3. Search Account");
        printf("\n4. Delete Account");
        printf("\n5. Logout");
        printf("\n------------------------");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: create_account(); break;
            case 2: view_accounts(); break;
            case 3: search_account(); break;
            case 4: delete_account(); break;
            case 5: return;
            default: printf("\nInvalid Choice!");
        }
        
    } 
   while(choice != 5);
   

}

/* CREATE ACCOUNT */
void create_account()
{
    fp = fopen("bank.dat", "ab");
    
    show_time();

    printf("\nEnter Account Number: ");
    scanf("%d", &acc.acc_no);
    printf("Enter Name: ");
    scanf("%s", &acc.name);
    printf("Set Password: ");
    scanf("%s", &acc.password);
    printf("Enter Initial Balance: ");
    scanf("%f", &acc.balance);

    fwrite(&acc, sizeof(acc), 1, fp);
    fclose(fp);

    printf("\nAccount Created Successfully!");
    
}

/* VIEW ALL ACCOUNTS */
void view_accounts()
{
    fp = fopen("bank.dat", "rb");
    
    show_time();

    printf("\nACC NO\tNAME\tBALANCE\n");
    printf("--------------------------------");

    while(fread(&acc, sizeof(acc), 1, fp))
    {
        printf("\n%d\t%s\t%.2f", acc.acc_no, acc.name, acc.balance);
    }
    fclose(fp);


}

/* SEARCH ACCOUNT */
void search_account()
{
    int accno, found = 0;
    fp = fopen("bank.dat", "rb");
    
    show_time();

    printf("\nEnter Account Number: ");
    scanf("%d", &accno);

    while(fread(&acc, sizeof(acc), 1, fp))
    {
        if(acc.acc_no == accno)
        {
            printf("\nName: %s", acc.name);
            printf("\nBalance: %.2f", acc.balance);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if(found != 1)
        printf("\nAccount Not Found!");
    
}

/* DELETE ACCOUNT */
void delete_account()
{
    FILE *temp;
    int accno, found = 0;

    fp = fopen("bank.dat", "rb");
    temp = fopen("temp.dat", "wb");

    
    show_time();

    printf("\nEnter Account Number to Delete: ");
    scanf("%d", &accno);

    while(fread(&acc, sizeof(acc), 1, fp))
    {
        if(acc.acc_no != accno)
            fwrite(&acc, sizeof(acc), 1, temp);
        else
            found = 1;
    }

    fclose(fp);
    fclose(temp);
    remove("bank.dat");
    rename("temp.dat", "bank.dat");

    if(found = 1)
        printf("\nAccount Deleted Successfully!");
    else
        printf("\nAccount Not Found!");
    
}

/* USER LOGIN */
void user_login()
{
    int accno, found = 0;
    char pass[20];

    fp = fopen("bank.dat", "rb");
    
    show_time();

    printf("\nEnter Account Number: ");
    scanf("%d", &accno);
    printf("Enter Password: ");
    scanf("%s", &pass);

    while(fread(&acc, sizeof(acc), 1, fp))
    {
        if(acc.acc_no == accno && strcmp(acc.password, pass) == 0)
        {
            found = 1;
            fclose(fp);
            user_menu(acc);
            return;
        }
    }
    fclose(fp);

    if(found != 1)
        printf("\nInvalid Login!");
    
}

/* USER MENU */
void user_menu(struct account user)
{
    int choice;
    do
    {
        
        show_time();

        printf("\n----- USER MENU -----");
        printf("\n1. Deposit");
        printf("\n2. Withdraw");
        printf("\n3. Check Balance");
        printf("\n4. Logout");
        printf("\n---------------------");
        printf("\nEnter choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1: deposit(user.acc_no); break;
            case 2: withdraw(user.acc_no); break;
            case 3: check_balance(user.acc_no); break;
            case 4: return;
            default: printf("\nInvalid Choice!");
        }
        
    } 
   while(choice != 4);
   
}

/* DEPOSIT */
void deposit(int accno)
{
    float amt;
    fp = fopen("bank.dat", "rb+");
    
    show_time();

    printf("\nEnter Amount to Deposit: ");
    scanf("%f", &amt);

    while(fread(&acc, sizeof(acc), 1, fp))
    {
        if(acc.acc_no == accno)
        {
            acc.balance += amt;
            fseek(fp, -sizeof(acc), SEEK_CUR);
            fwrite(&acc, sizeof(acc), 1, fp);
            printf("\nDeposit Successful!");
            break;
        }
    }
    fclose(fp);
    

}

/* WITHDRAW */
void withdraw(int accno)
{
    float amt;
    fp = fopen("bank.dat", "rb+");
    
    show_time();

    printf("\nEnter Amount to Withdraw: ");
    scanf("%f", &amt);

    while(fread(&acc, sizeof(acc), 1, fp))
    {
        if(acc.acc_no == accno)
        {
            if(acc.balance >= amt)
            {
                acc.balance -= amt;
                fseek(fp, -sizeof(acc), SEEK_CUR);
                fwrite(&acc, sizeof(acc), 1, fp);
                printf("\nWithdrawal Successful!");
            }
            else
                printf("\nInsufficient Balance!");
            break;
        }
    }
    fclose(fp);
    
}

/* CHECK BALANCE */
void check_balance(int accno)
{
    fp = fopen("bank.dat", "rb");
    
    show_time();

    while(fread(&acc, sizeof(acc), 1, fp))
    {
        if(acc.acc_no == accno)
        {
            printf("\nCurrent Balance: %.2f", acc.balance);
            break;
        }
    }
    fclose(fp);
    
}
