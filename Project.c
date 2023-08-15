#include <stdio.h>
#include <windows.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

int loadingbar();
int loadingcolor();
int br(int line);
int pre(int tab);

float interest(float t,float amount,int rate)
{
    float SI;
    SI=(rate*t*amount)/100.0;
    return (SI);

}

struct date
{
    int month, day, year;
};

struct
{
    char name[100];
    char email[100];
    int accNum;
    int pin;
    int age;
    float amt;
    double phoneNum;
    struct date dob;
    struct date deposit;
    struct date withdraw;

} add, read,upd, del, trans;

int tryAgainCustomer(int userAccNum)
{
    char dec;

    system("cls");
    printf("\n Would you like to try another transaction? \n [Y] Yes \n [N] No \n\n Enter your choice: ");
    scanf(" %c", &dec);

    switch(dec)
    {
        case 'Y':
        case 'y':
            printf("\n Returning to Main Menu...");
            mainMenuCustomer(userAccNum);
            break;
        case 'N':
        case 'n':
            printf("\n Redirecting...");
            getch();
            closer();
            break;
        default:
            printf(" Invalid Input! Try again!");
            tryAgainCustomer(userAccNum);
            break;
    }
    return 0;
}

int withdrawCustomer(int userAccNum)
{
    FILE *oldInfo, *newInfo;
    int test = 0;

    oldInfo = fopen("info.dat", "r");
    newInfo = fopen("new.dat", "w");

    system("cls");
    printf("\n Enter your account PIN number: ");
    scanf("%d", &trans.pin);

    while(fscanf(oldInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",&add.accNum,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.email,&add.phoneNum,&add.amt,&add.pin,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
    {
        if (add.accNum == userAccNum && add.pin == trans.pin)
        {
            withdraw_verify:
            test = 1;
            printf(" Enter the amount to be withdraw: $");
            scanf("%f", &trans.amt);

            if (add.amt < trans.amt)
            {
                printf("\n\n Insufficient Funds!");
                getch(); system("cls");
                goto withdraw_verify;
            }

            else
            {
                add.amt -= trans.amt;
                fprintf(newInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",add.accNum,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.email,add.phoneNum,add.amt,add.pin,add.deposit.month,add.deposit.day,add.deposit.year);
                printf("\n\n Withdraw Transaction is Successful!");
            }
        }

        else
        {
            fprintf(newInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",add.accNum,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.email,add.phoneNum,add.amt,add.pin,add.deposit.month,add.deposit.day,add.deposit.year);
        }
    }

    fclose(oldInfo);
    fclose(newInfo);
    remove("info.dat");
    rename("new.dat","info.dat");

    getch();

    if (test != 1)
    {
        system("cls");
        printf(" \n ERROR 404: Account Credentials are either incorrect or not found! ");
        getch(); withdrawCustomer(userAccNum);
    }
    else
        tryAgainCustomer(userAccNum);

    return 0;
}

int depositCustomer(int userAccNum)
{
    FILE *oldInfo, *newInfo;
    int test = 0;

    oldInfo = fopen("info.dat", "r");
    newInfo = fopen("new.dat", "w");

    system("cls");
    printf("\n Enter your account PIN number: ");
    scanf("%d", &trans.pin);

    while(fscanf(oldInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",&add.accNum,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.email,&add.phoneNum,&add.amt,&add.pin,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
    {
        if (add.accNum == userAccNum && add.pin == trans.pin)
        {
            test = 1;
            printf(" Enter the amount to be deposit: $");
            scanf("%f", &trans.amt);
            add.amt += trans.amt;

            fprintf(newInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",add.accNum,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.email,add.phoneNum,add.amt,add.pin,add.deposit.month,add.deposit.day,add.deposit.year);
            printf("\n\n Deposit Transaction is Successful!");
        }

        else
        {
            fprintf(newInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",add.accNum,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.email,add.phoneNum,add.amt,add.pin,add.deposit.month,add.deposit.day,add.deposit.year);
        }
    }

    fclose(oldInfo);
    fclose(newInfo);
    remove("info.dat");
    rename("new.dat","info.dat");

    getch();

    if (test != 1)
    {
        system("cls");
        printf(" \n ERROR 404: Account Credentials are either incorrect or not found! ");
        getch(); depositCustomer(userAccNum);
    }
    else
        tryAgainCustomer(userAccNum);

    return 0;
}

int editCustomer(int userAccNum)
{
    int dec, test = 0;

    FILE *oldInfo, *newInfo;

    oldInfo = fopen("info.dat", "r");
    newInfo = fopen("new.dat", "w");

    system("cls");
    printf("\n Enter PIN Number: ");
    scanf("%d", &upd.pin);

    while(fscanf(oldInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",&add.accNum,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.email,&add.phoneNum,&add.amt,&add.pin,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
    {
        if(add.accNum == userAccNum && add.pin == upd.pin)
        {
            test = 1;
            printf("\n Choose Information Credentials to change: \n [1] EMAIL \n [2] PHONE NUMBER \n [3] PIN \n\n Enter you choice: ");
            scanf("%d", &dec);

            if (dec == 1)
            {
                printf("\n Enter new email address: ");
                scanf("%s", &upd.email);
                fprintf(newInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",add.accNum,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,upd.email,add.phoneNum,add.amt,add.pin,add.deposit.month,add.deposit.day,add.deposit.year);
                printf(" New Email Information successfully updated! ");
            }
            else if (dec == 2)
            {
                printf("\n Enter new phone number: ");
                scanf("%lf", &upd.phoneNum);
                fprintf(newInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",add.accNum,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.email,upd.phoneNum,add.amt,add.pin,add.deposit.month,add.deposit.day,add.deposit.year);
                printf(" New Phone Number successfully updated! ");
            }
            else if (dec == 3)
            {
                printf("\n Enter new PIN code: ");
                scanf("%d", &upd.pin);
                fprintf(newInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",add.accNum,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.email,add.phoneNum,add.amt,upd.pin,add.deposit.month,add.deposit.day,add.deposit.year);
                printf(" New PIN Code successfully updated! ");
            }
            else
            {
                printf("\n Invalid Input! ");
                fprintf(newInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",add.accNum,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.email,add.phoneNum,add.amt,add.pin,add.deposit.month,add.deposit.day,add.deposit.year);
                getch();
                editCustomer(userAccNum);
            }
        }
        else
        {
                fprintf(newInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",add.accNum,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.email,add.phoneNum,add.amt,add.pin,add.deposit.month,add.deposit.day,add.deposit.year);
        }
    }

    fclose(oldInfo);
    fclose(newInfo);
    remove("info.dat");
    rename("new.dat", "info.dat");

    getch();
    if (test != 1)
    {
        system("cls");
        printf(" \n ERROR 404: Account Credentials are not found! ");
        getch(); editCustomer(userAccNum);
    }
    else
        tryAgainCustomer(userAccNum);

    return 0;
}

int viewCustomer(int userAccNum)
{
    FILE *ptr;

    int test = 0, rate, dec;
    float time, interester;

    ptr = fopen("info.dat", "r");
    system("cls");

    while(fscanf(ptr,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",&add.accNum,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.email,&add.phoneNum,&add.amt,&add.pin,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
        {
            if(add.accNum == userAccNum)
            {
                system("cls");
                test = 1;
                printf("\n\n ACCOUNT CREDENTIALS\n");
                printf("\n ACCOUNT NUMBER: %d \n FULL NAME: %s \n DATE OF BIRTH: %d/%d/%d \n AGE: %d \n EMAIL: %s \n PHONE NUMBER: %.0lf \n BALANCE INQUIRY: $%.2f \n PIN: %d \n DATE JOINED: %d/%d/%d \n", add.accNum, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.email, add.phoneNum, add.amt, add.pin, add.deposit.month, add.deposit.day, add.deposit.year);

                time = (1.0/12.0);
                rate = 8;
                interester = interest(time, add.amt, rate);
                printf("\n INTEREST GAINED EVERY MONTH = $.%.2f", interester, add.deposit.day);
            }
        }

    fclose(ptr);

    getch();
    if (test != 1)
    {
        system("cls");
        printf(" \n ERROR 404: Account Credentials are not found! ");
        getch(); viewCustomer(userAccNum);
    }
    else
        tryAgainCustomer(userAccNum);

    return 0;
}

int mainMenuCustomer(int userAccNum)
{
    FILE *ptr;

    int dec;

    ptr = fopen("info.dat", "r");

    while(fscanf(ptr,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",&add.accNum,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.email,&add.phoneNum,&add.amt,&add.pin,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
    {
        if(add.accNum == userAccNum)
            break;
    }

    fclose(ptr);

    system("cls");
    system("color E9");

    for(int i=0; i<100; i++)
    {
        printf("\xb2");
    }
    br(1);
    time_t t;
    time(&t);
    pre(12); printf("%s", ctime(&t));
    br(3); pre(4);printf("           *Welcome %s*          ", add.name); Sleep(300);
    br(2); pre(3);printf("           ==|BALANCE INQUIRY => $%.2f|==          ", add.amt);
    br(3);pre(4);printf("Please Enter Designated Key To Continue");br(2); Sleep(300);

    printf("\n\n \t \t \t \t MONEY PURSE| SPEND LESS| SAVE MORE \n"); Sleep(400);
    printf("\n\n \t \t \t \t ==========MAIN MENU=========="); Sleep(400);
    printf("\n \n \t \t \t \t [1] Withdraw Funds"); Sleep(400);
    printf("\n \t \t \t \t [2] Deposit Money"); Sleep(400);
    printf("\n \t \t \t \t [3] View Account and Balance"); Sleep(400);
    printf("\n \t \t \t \t [4] Edit Account Credentials"); Sleep(400);
    printf("\n \t \t \t \t [5] Exit"); Sleep(400);

    br(3);
    pre(3);printf("\xa9 Copyright © 2021 HEIST Inc. All Rights Reserved \n\n");
    for(int i=0; i<100; i++)
    {
        printf("\xb2");
    }
    printf("\n\n \t \t \t \t Enter your choice: ");
    scanf("%d", &dec);

    switch(dec)
    {
        case 1:
            withdrawCustomer(userAccNum);
            break;
        case 2:
            depositCustomer(userAccNum);
            break;
        case 3:
            viewCustomer(userAccNum);
            break;
        case 4:
            editCustomer(userAccNum);
            break;
        case 5:
            closer();
            break;
        default:
            printf(" \n Invalid Input! Returning to Main Menu!");
            mainMenuCustomer(userAccNum);
            break;
    }

    return 0;
}

int closer()
{
    int i, j, n = 10;

    system("cls");
    br(2); pre(4); printf(" Submitted by: \n \t\t\t\t Jimbo Carlo G. Delfin \n \t\t\t\t Angelou O. Lucero \n \t\t\t\t James Vincent P. Grabador \n \t\t\t\t Louise S. Maminta \n \t\t\t\t Archie V. Abuan \n \t\t\t\t Ryan Chris O. Tupil \n \t\t\t\t Ma. Nica Mae M. Mendoza \n \t\t\t\t Dana Trisha B. Valencia \n \t\t\t\t BSIT - 2AB - NS\n\n");
    getch();

    system ("color 4F");
    for(i=n/2; i<=n; i+=2)
    {
        for(j=1; j<n-i; j+=2)
        {
            printf(" ");
        }
        for(j=1; j<=i; j++)
        {
            printf("*");
        }
        for(j=1; j<=n-i; j++)
        {
            printf(" ");
        }
        for(j=1; j<=i; j++)
        {
            printf("*");
        }
        printf("\n");
    }

    for(i=n; i>=1; i--)
    {
        for(j=i; j<n; j++)
        {
            printf(" ");
        }
        for(j=1; j<=(i*2)-1; j++)
        {
            printf("*");
        }
        printf("\n");
    }

    printf("\n\n \t\t\t\t Brought To You by HEIST (Home - Base E - Wallet, Insurance, Savings Technology) Incorporated");

    getch();
    return 0;
}

int tryAgain()
{
    char dec;

    system("cls");
    br(2); pre(4); printf(" Would you like to try another transaction? \n \t\t\t\t [Y] Yes \n \t\t\t\t [N] No \n\n \t\t\t\t Enter your choice: ");
    scanf(" %c", &dec);

    switch(dec)
    {
        case 'Y':
        case 'y':
            br(2); pre(4); printf(" Returning to Main Menu...");
            mainMenu();
            break;
        case 'N':
        case 'n':
            br(2); pre(4); printf(" Redirecting...");
            getch();
            closer();
            break;
        default:
            br(2); pre(4); printf(" Invalid Input! Try again!");
            tryAgain();
            break;
    }
    return 0;
}

void withdraw(void)
{
    FILE *oldInfo, *newInfo;
    int test = 0;

    oldInfo = fopen("info.dat", "r");
    newInfo = fopen("new.dat", "w");

    system("cls");
    br(2); pre(4); printf(" Enter account number: ");
    scanf("%d", &trans.accNum);

    while(fscanf(oldInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",&add.accNum,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.email,&add.phoneNum,&add.amt,&add.pin,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
    {
        if (add.accNum == trans.accNum)
        {
            withdraw_verify1:
            test = 1;
            br(2); pre(4); printf(" Enter the amount to be withdraw: $");
            scanf("%f", &trans.amt);

            if(add.amt < trans.amt)
            {
                br(2); pre(4); printf("\n\n Insufficient Funds!");
                getch(); system("cls");
                goto withdraw_verify1;
            }

            else
            {
                add.amt -= trans.amt;
                fprintf(newInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",add.accNum,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.email,add.phoneNum,add.amt,add.pin,add.deposit.month,add.deposit.day,add.deposit.year);
                br(2); pre(4); printf(" Withdraw Transaction is Successful!");
            }
        }
        else
        {
            fprintf(newInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",add.accNum,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.email,add.phoneNum,add.amt,add.pin,add.deposit.month,add.deposit.day,add.deposit.year);
        }
    }

    fclose(oldInfo);
    fclose(newInfo);
    remove("info.dat");
    rename("new.dat","info.dat");

    getch();

    if (test != 1)
    {
        system("cls");
        printf(" \n ERROR 404: Account Credentials are not found! ");
        getch(); withdraw();
    }
    else
        tryAgain();
}

void deposit(void)
{
    FILE *oldInfo, *newInfo;
    int test = 0;

    oldInfo = fopen("info.dat", "r");
    newInfo = fopen("new.dat", "w");

    system("cls");
    br(2); pre(4); printf(" Enter account number: ");
    scanf("%d", &trans.accNum);

    while(fscanf(oldInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",&add.accNum,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.email,&add.phoneNum,&add.amt,&add.pin,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
    {
        if (add.accNum == trans.accNum)
        {
            test = 1;
            br(2); pre(4); printf(" Enter the amount to be deposit: $");
            scanf("%f", &trans.amt);
            add.amt += trans.amt;

            fprintf(newInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",add.accNum,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.email,add.phoneNum,add.amt,add.pin,add.deposit.month,add.deposit.day,add.deposit.year);
            br(2); pre(4); printf(" Deposit Transaction is Successful!");

        }

        else
        {
            fprintf(newInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",add.accNum,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.email,add.phoneNum,add.amt,add.pin,add.deposit.month,add.deposit.day,add.deposit.year);
        }

    }

    fclose(oldInfo);
    fclose(newInfo);
    remove("info.dat");
    rename("new.dat","info.dat");
    getch();

    if (test != 1)
    {
        system("cls");
        printf(" \n ERROR 404: Account Credentials are not found! ");
        getch(); deposit();
    }
    else
        tryAgain();
}

void view(void)
{
    FILE *ptr;

    int test = 0, rate, dec;
    float time, interester;

    ptr = fopen("info.dat", "r");

    system("cls");
    br(2); pre(4);printf(" View Account through: \n \t\t\t\t [1] Account Number \n \t\t\t\t [2] Name");
    br(2); pre(4);printf("Enter your choice: ");
    scanf("%d", &dec);

    if(dec == 1)
    {
        br(2); pre(4); printf("  Enter Account Number: ");
        scanf("%d", &read.accNum);

        while(fscanf(ptr,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",&add.accNum,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.email,&add.phoneNum,&add.amt,&add.pin,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
        {
            if(add.accNum == read.accNum)
            {
                system("cls");
                test = 1;
                br(2); pre(4); printf(" ACCOUNT CREDENTIALS\n");
                br(2); pre(4); printf(" ACCOUNT NUMBER: %d \n \t\t\t\t FULL NAME: %s \n \t\t\t\t DATE OF BIRTH: %d/%d/%d \n \t\t\t\t AGE: %d \n \t\t\t\t EMAIL: %s \n \t\t\t\t PHONE NUMBER: %.0lf \n \t\t\t\t BALANCE INQUIRY: $%.2f \n \t\t\t\t PIN: %d \n \t\t\t\t DATE JOINED: %d/%d/%d \n", add.accNum, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.email, add.phoneNum, add.amt, add.pin, add.deposit.month, add.deposit.day, add.deposit.year);

                time = (1.0/12.0);
                rate = 8;
                interester = interest(time, add.amt, rate);
                br(2); pre(4); printf(" INTEREST GAINED EVERY MONTH = $.%.2f", interester, add.deposit.day);
            }
        }
    }
    else if (dec == 2)
    {
        br(2); pre(4); printf(" Enter Account Full Name: ");
        scanf("%s", &read.name);

        while(fscanf(ptr,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",&add.accNum,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.email,&add.phoneNum,&add.amt,&add.pin,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
        {
            if(strcmpi(add.name, read.name) == 0)
            {
                system("cls");
                test = 1;
                br(2); pre(4); printf(" ACCOUNT CREDENTIALS\n");
                br(2); pre(4); printf(" ACCOUNT NUMBER: %d \n \t\t\t\t FULL NAME: %s \n \t\t\t\t DATE OF BIRTH: %d/%d/%d \n \t\t\t\t AGE: %d \n \t\t\t\t EMAIL: %s \n \t\t\t\t PHONE NUMBER: %.0lf \n \t\t\t\t BALANCE INQUIRY: $%.2f \n \t\t\t\t PIN: %d \n \t\t\t\t DATE JOINED: %d/%d/%d \n", add.accNum, add.name, add.dob.month, add.dob.day, add.dob.year, add.age, add.email, add.phoneNum, add.amt, add.pin, add.deposit.month, add.deposit.day, add.deposit.year);

                time = (1.0/12.0);
                rate = 8;
                interester = interest(time, add.amt, rate);
                br(2); pre(4); printf(" INTEREST GAINED EVERY MONTH = $.%.2f", interester, add.deposit.day);
            }
        }
    }
    else
    {
        br(2); pre(4); printf(" Invalid Input!");
        getch();
        view();
    }

    fclose(ptr);

    getch();
    if (test != 1)
    {
        system("cls");
        printf(" \n ERROR 404: Account Credentials are not found! ");
        getch(); view();
    }
    else
        tryAgain();
}

void edit(void)
{
    int dec, test = 0;

    FILE *oldInfo, *newInfo;

    oldInfo = fopen("info.dat", "r");
    newInfo = fopen("new.dat", "w");

    system("cls");
    br(2); pre(4); printf(" Enter Account Number: ");
    scanf("%d", &upd.accNum);

    while(fscanf(oldInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",&add.accNum,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.email,&add.phoneNum,&add.amt,&add.pin,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
    {
        if(add.accNum == upd.accNum)
        {
            test = 1;
            br(2); pre(4); printf(" Choose Information Credentials to change: \n \t\t\t\t [1] EMAIL \n \t\t\t\t [2] PHONE NUMBER \n \t\t\t\t [3] PIN \n\n \t\t\t\t Enter you choice: ");
            scanf("%d", &dec);

            if (dec == 1)
            {
                br(2); pre(4); printf(" Enter new email address: ");
                scanf("%s", &upd.email);
                fprintf(newInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",add.accNum,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,upd.email,add.phoneNum,add.amt,add.pin,add.deposit.month,add.deposit.day,add.deposit.year);
                br(2); pre(4); printf(" New Email Information successfully updated! ");
            }
            else if (dec == 2)
            {
                br(2); pre(4); printf(" Enter new phone number: ");
                scanf("%lf", &upd.phoneNum);
                fprintf(newInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",add.accNum,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.email,upd.phoneNum,add.amt,add.pin,add.deposit.month,add.deposit.day,add.deposit.year);
                br(2); pre(4); printf(" New Phone Number successfully updated! ");
            }
            else if (dec == 3)
            {
                br(2); pre(4); printf(" Enter new PIN code: ");
                scanf("%d", &upd.pin);
                fprintf(newInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",add.accNum,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.email,add.phoneNum,add.amt,upd.pin,add.deposit.month,add.deposit.day,add.deposit.year);
                br(2); pre(4); printf(" New PIN Code successfully updated! ");
            }
            else
            {
                br(2); pre(4); printf(" Invalid Input! ");
                fprintf(newInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",add.accNum,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.email,add.phoneNum,add.amt,add.pin,add.deposit.month,add.deposit.day,add.deposit.year);
                getch();
                edit();
            }
        }
        else
        {
                fprintf(newInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",add.accNum,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.email,add.phoneNum,add.amt,add.pin,add.deposit.month,add.deposit.day,add.deposit.year);
        }
    }

    fclose(oldInfo);
    fclose(newInfo);
    remove("info.dat");
    rename("new.dat", "info.dat");

    getch();
    if (test != 1)
    {
        system("cls");
        printf(" \n ERROR 404: Account Credentials are not found! ");
        getch(); edit();
    }
    else
        tryAgain();
}

void remover(void)
{
    FILE *oldInfo, *newInfo;
    int test = 0;

    oldInfo = fopen("info.dat", "r");
    newInfo = fopen("new.dat", "w");

    system("cls");
    br(2); pre(4); printf(" Enter Account Number: ");
    scanf("%d", &del.accNum);

    while(fscanf(oldInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",&add.accNum,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.email,&add.phoneNum,&add.amt,&add.pin,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
    {
        if (add.accNum != del.accNum)
        {
            fprintf(newInfo,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",add.accNum,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.email,add.phoneNum,add.amt,add.pin,add.deposit.month,add.deposit.day,add.deposit.year);
        }
        else
        {
            test++;
            br(2); pre(4); printf(" Savings Account %d successfully deleted! ", del.accNum);
        }
    }

    fclose(oldInfo);
    fclose(newInfo);
    remove("info.dat");
    rename("new.dat", "info.dat");

    getch();
   if (test != 1)
    {
        system("cls");
        printf(" \n ERROR 404: Account Credentials are not found! ");
        getch(); remover();
    }
    else
        tryAgain();
}

void listAccs(void)
{
    FILE *ptr;
    int test = 0;

    ptr = fopen("info.dat", "r");
    system("cls");
    printf("\nACC. NO.\tNAME\t\t\tEMAIL ADD\t\t\tPHONE\n");
    while(fscanf(ptr,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",&add.accNum,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.email,&add.phoneNum,&add.amt,&add.pin,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
    {
        printf("\n%6d\t %10s\t\t\t%10s\t\t%.0lf\n",add.accNum,add.name,add.email,add.phoneNum);
        test = 1;
    }

    fclose(ptr);

    getch();
    if (test != 1)
    {
        system("cls");
        printf(" \n ERROR 404: Account Credentials are not found! ");
        getch(); listAccs();
    }
    else
        tryAgain();
}

void mainMenu(void)
{
    int dec;

    system("cls");
    system("color E9");

    for(int i=0; i<100; i++)
    {
        printf("\xb2");
    }
    time_t t;
    time(&t);
    pre(13); printf("%s", ctime(&t));
    br(2); pre(4);printf("           *Welcome Admin*          "); Sleep(300);
    br(3);
    pre(4);printf("Please Enter Designated Key To Continue");br(2); Sleep(300);

    printf("\n \t \t \t \t MONEY PURSE| SPEND LESS| SAVE MORE \n"); Sleep(400);
    printf("\n\n \t \t \t \t ==========|MAIN MENU|=========="); Sleep(400);
    printf("\n \n \t \t \t \t [1] Withdraw Funds"); Sleep(400);
    printf("\n \t \t \t \t [2] Deposit Money"); Sleep(400);
    printf("\n \t \t \t \t [3] View Account and Balance"); Sleep(400);
    printf("\n \t \t \t \t [4] Edit Account Credentials"); Sleep(400);
    printf("\n \t \t \t \t [5] Remove Existing Account"); Sleep(400);
    printf("\n \t \t \t \t [6] List all Accounts"); Sleep(400);
    printf("\n \t \t \t \t [7] Exit"); Sleep(400);

    br(3);
    pre(3);printf("\xa9 Copyright © 2021 HEIST Inc. All Rights Reserved \n\n");
    for(int i=0; i<100; i++)
    {
        printf("\xb2");
    }
    printf("\n\n \t \t \t \t Enter your choice: ");
    scanf("%d", &dec);

    switch(dec)
    {
        case 1:
            withdraw();
            break;
        case 2:
            deposit();
            break;
        case 3:
            view();
            break;
        case 4:
            edit();
            break;
        case 5:
            remover();
            break;
        case 6:
            listAccs();
            break;
        case 7:
            closer();
            break;
        default:
            printf(" \n Invalid Input! Returning to Main Menu!");
            mainMenu();
            break;
    }

    return 0;
}

void loginAcc(void)
{
    FILE *ptr;
    ptr = fopen("info.dat", "r");

    int tempAccNum, tempPin, test = 0, i, adminAccount = 12664;

        system("cls");
        for(i=0; i<100; i++){ printf("\xb2"); }
        br(3); pre(2);        printf("\t____________________________________________________________\n");
        br(2); pre(4);printf("==========|LOGIN YOUR ACCOUNT|==========");

        br(2); pre(4); printf(" Enter your account number: ");
        scanf("%d", &tempAccNum);

        br(2); pre(4); printf(" Enter your pin: ");
        scanf("%d", &tempPin);

        while(fscanf(ptr,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",&add.accNum,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.email,&add.phoneNum,&add.amt,&add.pin,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
        {       //add.accNum
            if(tempAccNum == adminAccount && add.pin == tempPin)
            {
                test = 1;
                br(1); pre(4); printf(" Login Successfully! WELCOME ADMIN! ");
                br(2); pre(2);        printf("\t____________________________________________________________\n");
                br(2); for(i=0; i<100; i++){ printf("\xb2");    }
                getch();
                fclose(ptr);
                mainMenu();
                break;
            }
            else if (add.accNum == tempAccNum && add.pin == tempPin)
            {
                test = 1;
                br(1); pre(4); printf(" Login Successfully! WELCOME %s! ", add.name);
                br(2); pre(2);        printf("\t____________________________________________________________\n");
                br(2); for(i=0; i<100; i++){ printf("\xb2");    }
                getch();
                fclose(ptr);
                mainMenuCustomer(tempAccNum);
                break;
            }
        }

    fclose(ptr);

    getch();
    if (test != 1)
    {
        system("cls");
        printf(" \n ERROR 404: Account Credentials are either incorrect or NULL! ");
        getch(); loginAcc();
    }

    return 0;
}

int regAcc()
{
    FILE *ptr;
    int num, i;

    ptr = fopen("info.dat", "a+");

    account_no:
    system("cls");

    for(i=0; i<100; i++){ printf("\xb2"); }

    br(3); pre(2);        printf("\t____________________________________________________________\n\n");
    printf(" \t \t \t \t ==========|CREATE AN ACCOUNT|==========");
    printf("\n\n\n \t\t\t Enter date today(mm/dd/yyyy): ");
    scanf("%d/%d/%d",&add.deposit.month,&add.deposit.day,&add.deposit.year);

    srand(time(0));
    num = (rand() % (100000 - 100 + 1)) + 100;
    printf("\n \t\t\t Your Account number is: %d", num);
    read.accNum = num;

                        //accnum, name, dob, age ,email, phone, amt, pin, date today
    while(fscanf(ptr,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",&add.accNum,add.name,&add.dob.month,&add.dob.day,&add.dob.year,&add.age,add.email,&add.phoneNum,&add.amt,&add.pin,&add.deposit.month,&add.deposit.day,&add.deposit.year)!=EOF)
    {
        if (read.accNum == add.accNum)
        {
            printf("\n Account Number is existing! Generating a new one!");
            goto account_no;
            getch();
        }
    }

    add.accNum = read.accNum;

    printf("\n \n \t\t\t Enter your name: ");
    scanf("%s", add.name);

    printf("\n \t\t\t Enter date of birth (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &add.dob.month,&add.dob.day,&add.dob.year);

    printf("\n \t\t\t Enter age: ");
    scanf("%d", &add.age);

    printf("\n \t\t\t Enter email: ");
    scanf("%s", add.email);

    printf("\n \t\t\t Enter phone number: ");
    scanf("%lf", &add.phoneNum);

    dep_try:
    printf("\n \t\t\t Enter starting deposit amount (not less than $25): $");
    scanf("%f", &add.amt);
    if (add.amt < 25) goto dep_try;

    printf("\n \t\t\t Enter pin: ");
    scanf("%d", &add.pin);

    fprintf(ptr,"%d %s %d/%d/%d %d %s %lf %f %d %d/%d/%d\n",add.accNum,add.name,add.dob.month,add.dob.day,add.dob.year,add.age,add.email,add.phoneNum,add.amt,add.pin,add.deposit.month,add.deposit.day,add.deposit.year);
    fclose(ptr);
    printf(" \n\n \t\t\t Successfully created Account!!! ");
    br(1); pre(2);        printf("\t____________________________________________________________\n\n");

    br(2); for(i=0; i<100; i++){ printf("\xb2");    }

    getch();
    loginAcc();

    return 0;
}

int main()
{
    int i;
    char dec;
    FILE *ptr;

    for(i=0; i<100; i++) //box shaped at the top
    {
        printf("\xb2");
    }
    printf("\n");
    for(i=0; i<100; i++)
    {
        printf("\xb2");
    }
    system("color E9"); // color of the text, background

    time_t t;
    time(&t);
    pre(13);printf("%s", ctime(&t));
    br(3);
   pre(1); printf("\t________________________________________________________\n");
   pre(1); printf("\t|                                                      |\n");
   pre(1); printf("\t|           **|Welcome to Savings  System|**           |\n");
   pre(1); printf("\t|                                                      |\n");
   pre(1); printf("\t|______________________________________________________|\n");
   pre(1); printf("\t|                                                      |\n");
   pre(1); printf("\t|               **|HEIST Incorporated|**               |\n");
   pre(1); printf("\t|                                                      |\n");
   pre(1); printf("\t|______________________________________________________|\n");


    br(7);pre(2); printf("Please Enter Any Key to Continue");
    for(i=0; i<5; i++)
    {
        printf(".");
        Sleep(500);//after printing one . another comes after 0.5 seconds
    }
printf("\n\n\n\n");

    for(i=0; i<100; i++) //box shaped at the bottom
    {
        printf("\xb2");
    }
    printf("\n");
    for(i=0; i<100; i++)
    {
        printf("\xb2");
    }

    getch();
    system("cls");//clears the screen

    verify:
        ptr = fopen("E:\\verify.txt", "r");

        if(ptr == NULL)
        {
            printf("\n File undetected! \nPlease insert the removable flash drive...");
            getch();
            goto verify;
        }
    fclose(ptr);


    printf("\n");
    loadingbar();
    system("cls");
    system("color E9");

    for(i=0; i<100; i++)
    {
        printf("\xb2");
    }
    printf("\n");
    for(i=0; i<100; i++)
    {
        printf("\xb2");
    }
    br(3);
    pre(2);        printf("\t_______________________________________________________\n\n");
    pre(3);               printf(" ==========|Select a function to begin with|========== ");
    br(2); pre(4);        printf("[L] LOGIN AN EXISTING ACCOUNT");
    br(2); pre(4);        printf("[R] REGISTER A NEW ACCOUNT");
    br(2); pre(2); printf("\t_______________________________________________________\n");
    br(4);

    for(i=0; i<100; i++)
    {
        printf("\xb2");
    }
    printf("\n");
    for(i=0; i<100; i++)
    {
        printf("\xb2");
    }

    br(2); pre(4);        printf("Enter your choice: ");
    scanf(" %c", &dec);

    switch(dec)
    {
        case 'L':
        case 'l':
            loginAcc();
            break;

        case 'R':
        case 'r':
            regAcc();
            break;

        default:
            printf("\n Invalid Input!");
            break;
    }
    return 0;
}

int loadingbar(){

	for (int i=10;i<=100;i+=8){
        system("color F1");
		system("cls");

		br(7);pre(4);
		printf("%d %% Loading...\n\n\t\t",i);
		printf(" ");

		for (int j=0; j<i;j+=2){
			loadingcolor(300+j);
			printf(" ");
		}
		Sleep(100);
    }
}

int loadingcolor(void){

	HANDLE  hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, BACKGROUND_RED|BACKGROUND_INTENSITY);
}

int br(int line){
	for(int i=0; i<line;i++){
		printf("\n");
	}
}

int pre(int tab){

	for(int i=0; i<tab;i++){
		printf("\t");
	}

}
