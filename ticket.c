#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
typedef struct Admin
{
    char *name;
    char *pass;
} ADMIN;
typedef struct User
{
    char *cust_name;
    char *cust_pass;
} USER;
int main(void)
{
    char ch;
    char s[10], m[10], q[10], n[10];
    ADMIN admin[2];
    USER customer[2];
    admin[0].name = "RAKESH";
    admin[0].pass = "rakesh";
    admin[1].name = "RODO";
    admin[1].pass = "rodo";
    customer[0].cust_name = "KAUSHIK";
    customer[0].cust_pass = "kaushik";
    customer[1].cust_name = "ASISH";
    customer[1].cust_pass = "asish";

    printf("ADMIN login(A) or CUSTOMER LOGIN(C): ");
    ch = getc(stdin);

    if (ch == 'A')
    {
        printf("ADMIN-NAME: ");
        scanf("%s", s);
        printf("PASSWORD: ");
        scanf("%s", m);
        int t = 0;
        for (int i = 0; i < 2; i++)
        {
            if (strcmp(admin[i].name, s) == 0 && strcmp(admin[i].pass, m) == 0)
            {
                t = 1;
            }
        }
        if (t)
        {
            printf("Welcome To the airline service\n");
        }
        else
        {
            printf("INVALID LOGIN\n");
        }
    }
    else if (ch == 'C')
    {
        printf("CUSTOMER-NAME: ");
        scanf("%s", q);
        printf("PASSWORD: ");
        scanf("%s", n);
        int t = 0;
        for (int j = 0; j < 2; j++)
        {
            if (strcmp(customer[j].cust_name, q) == 0 && strcmp(customer[j].cust_pass, n) == 0)
            {
                t = 1;
            }
        }
        if (t)
        {
            printf("Welcome To the airline booking service\n");
        }
        else
        {
            printf("INVALID CREDENTIALS\n");

            printf("%s\t%s\n", q, n);
            printf("%s\t%s\n", customer[1].cust_name, customer[1].cust_pass);
        }
    }
    else
    {
        printf("Please type the correct option\n");
    }
}
/*int main(void)
{
    FILE *fptr;
    char s[10],m[10];
    ADMIN admin[2];
    USER customer[2];    
    fptr=fopen("ADMIN_USER.txt","r");
    for (int i = 0; i < 2; i++)
    {
        
        fread(&admin[i],sizeof(ADMIN),1,fptr);
        //fread(fptr,"%s\t%s",customer[i].cust_name,customer[i].cust_pass);
    } 
    /*printf("USERNAME: ");
    scanf("%s", s);
    printf("PASSWORD: ");
    scanf("%s", m);
    for (int i = 0; i < 2; i++)
    {
        if (strcmp(customer[i].cust_name, s) == 0 && strcmp(customer[i].cust_pass, m) == 0)
        {
            printf("Welcome\n");
            return 0;
        }
    }
    printf("INVALID LOGIN\n");
    return 1; 
    for (int i = 0; i < 2; i++)
    {
        printf("%s %s\n",admin[i].name,admin[i].pass);
    }
    
}*/