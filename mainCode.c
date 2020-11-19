#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <conio.h>
void headMessage()
{
    system("cls");
    printf("\t\t\t###########################################################################");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t############      Airplane Reservation System Project in C     ############");
    printf("\n\t\t\t############                                                   ############");
    printf("\n\t\t\t###########################################################################");
    printf("\n\t\t\t---------------------------------------------------------------------------\n");
    //printMessageCenter(message);
    printf("\n\t\t\t----------------------------------------------------------------------------");
}



int checkUser(char *name)
{
    if (strcmp(name, nameInStruct))
    {
        return 1;
    }
    else
    {
        return 0;
    }
    
}
int checkPassword(char *name, char *password)
{
    if (checkUser(name))
    {
        //point to the location where name is stored and match password with the string in successive post;
    }
    else
    {
        return 0;
    }
    
}
int checkAdmin(char *name)
{
    if (strcmp(name, admin_nameInStruct))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int checkDateValidity(char *date)
{
    //code to check date validity
}

char DateToDay()
{
    int fm(int date, int month, int year) 
    {
        int fmonth, leap;
        if ((year % 100 == 0) && (year % 400 != 0))
            leap = 0;
        else if (year % 4 == 0)
            leap = 1;
        else
            leap = 0;

        fmonth = 3 + (2 - leap) * ((month + 2) / (2 * month))+ (5 * month + month / 9) / 2;

        fmonth = fmonth % 7;

        return fmonth;
    }
    int day_of_week(int date, int month, int year) 
    {

        int dayOfWeek;
        int YY = year % 100;
        int century = year / 100;

        printf("\nDate: %d/%d/%d \n", date, month, year);

        dayOfWeek = 1.25 * YY + fm(date, month, year) + date - 2 * (century % 4);

        //remainder on division by 7
        dayOfWeek = dayOfWeek % 7;

        switch (dayOfWeek) 
        {
            case 0:
                printf("weekday = Saturday\n");
                break;
            case 1:
                printf("weekday = Sunday\n");
                break;
            case 2:
                printf("weekday = Monday\n");
                break;
            case 3:
                printf("weekday = Tuesday\n");
                break;
            case 4:
                printf("weekday = Wednesday\n");
                break;
            case 5:
                printf("weekday = Thursday\n");
                break;
            case 6:
                printf("weekday = Friday\n");
                break;
            default:
                printf("Incorrect data\n");
        }
        return 0;
    }
    int date, month, year;

    printf("\nEnter the year ");
    scanf("%d", &year);

    printf("\nEnter the month ");
    scanf("%d", &month);

    printf("\nEnter the date ");
    scanf("%d", &date);

    day_of_week(date, month, year);
    
}

void main()
{
    char name[5], AU, password[100], boarding_place[100], destination_place[100], date1[8], date2[8];

    headMessage();
    printf("\n\n\n\n");
    printf("\n\t\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t\t        =                 WELCOME                   =");
    printf("\n\t\t\t\t        =                   TO                      =");
    printf("\n\t\t\t\t        =        AIRPLANE RESERVATION SYSTEM        =");
    printf("\n\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\n\n\t\t\t Press 'Enter key' to continue.....");
    getchar();
    printf("\n\n\n\t\t\t Are you an admin or an user? Press 'A' for admin and 'U' for user : ");
    scanf("%s", &AU);
    if (strcmp(AU, "U"))
    {
        printf("\n Enter your User ID : ");
        scanf("%s", &name);
        do
        {
            printf("\n User ID is Inavlid! Please Enter again : ");
            scanf("%s",&name);
        }while (checkUser(name) == 0);
        fputs("\n Enter your password : ", stdout);
        scanf("%s", &password);
        do
        {
            printf("Invalid Password!");
            scanf("%s", &password);
        }while (checkPassword(name, password) == 0);
        printf("Login Successful !!!");
        printf("Available airports: ROdoo, DEHueue, Kauaua, Hutashs, jsdhcbj, asbjcsc\n");
        fputs("Enter your Boarding Place : ", stdout);
        scanf("%s", &boarding_place);
        fputs("\n Enter your Destination Place : ", stdout);
        scanf("%s", &destination_place);
        printf("\n Enter your date of journey : ");
        scanf("%s", &date1);
        do
        {
            printf("\n Please enter a valid Date : ");
            scanf("%s", &date1);
        } while (checkDateValidity(date1) == 0);
        char day[] = DateToDay(date1);
        
    }
    else
    {
        /* code */
    }
}
    
