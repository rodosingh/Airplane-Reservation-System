#include <stdio.h>
#include <time.h>
#include<math.h>
#include <string.h>
#include <stdlib.h>
#define MAX_YR  9999  // max year that we can quest for, beyond that we will get invalid statement
#define MIN_YR  2000  // min year cutoff, below this will give a invalid statement
//structure to store date
typedef struct   //function
{
    int yyyy;
    int mm;
    int dd;
} Date;


int fm(int date, int month, int year) {
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
char* day_of_week(int date, int month, int year) {

   int dayOfWeek;
   int YY = year % 100;
   int century = year / 100;
   char *day = malloc(20);
   printf("\nDate: %d/%d/%d \n", date, month, year);

   dayOfWeek = 1.25 * YY + fm(date, month, year) + date - 2 * (century % 4);

   //remainder on division by 7
   dayOfWeek = dayOfWeek % 7;
   if (dayOfWeek == 0)
   strcpy(day,"Saturday") ;
   else if (dayOfWeek == 1)
   strcpy(day, "Sunday");
   else if (dayOfWeek == 2)
   strcpy(day, "Monday");
   else if (dayOfWeek == 3)
   strcpy(day, "Tuesday");
   else if (dayOfWeek == 4)
   strcpy(day, "Wednesday");
   else if (dayOfWeek == 5)
   strcpy(day, "Thursday");
   else if (dayOfWeek == 6)
   strcpy(day, "Friday");
   else
   strcpy(day, "Invalid Date");
   /*switch (dayOfWeek) 
   {
      case 0:
        char day[] = "Saturday";
        break;
      case 1:
        char day[] = "Sunday";
        break;
      case 2:
        char day[] = "Monday";
        break;
      case 3:
        char day[] = "Tuesday";
        break;
      case 4:
        char day[] = "Wednesday";
        break;
      case 5:
        char day[] = "Thursday";
        break;
      case 6:
        char day[] = "Friday";
        break;
      default:
        char day[] = "Incorrect data";
        break;
   }*/
   return day;
}

// Function to check leap year.
//Function returns 1 if leap year
int  IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}
// returns 1 if given date is valid.
int isValidDate(Date *validDate)
{
    //check range of year,month and day
    if (validDate->yyyy > MAX_YR ||         
            validDate->yyyy < MIN_YR) //if the year that you have enter is less than the minim year or greater than the max year than its a invalid year
        return 0;
    if (validDate->mm < 1 || validDate->mm > 12) //similarly no of month is basically 12 hence the enter number should not be more than 12 or less than 1  
        return 0;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 0;
    //Handle feb days in leap year
    if (validDate->mm == 2)  // as we know that leap year has 29 days in feb in constrast to normal year which has only 28 days
    {
        if (IsLeapYear(validDate->yyyy))
            return (validDate->dd <= 29); //leap year has 29 days in feb  
        else
            return (validDate->dd <= 28); 
    }
    //handle months which has only 30 days
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11) // respective month april, June, september and november has 30 days 
        return (validDate->dd <= 30);
    return 1;
}
char* Day(void)
{
    Date getDate = {0}; //variable to store date
    int status = 0; //variable to check status
    //get date year,month and day from user
    printf("\n\n Enter date in format (dd/mm/yyyy): "); // input from the user in dd/mm/yy
    scanf("%d/%d/%d",&getDate.dd,&getDate.mm,&getDate.yyyy);
    //check date validity
    status = isValidDate(&getDate);
    if(status !=1) // conditional operator for validity check, if its not equals 1 then its a invalid , a invalid statement will popup on screen
    {
        printf("\n Please enter a valid date!\n");
        exit(1);
    }
    else 
    {
        char* day_string = day_of_week(getDate.dd, getDate.mm, getDate.yyyy);
        printf("Your journey is on = %s\n", day_string);
        return day_string ;
    }
}
void main()
{
  char * day_of_travel = Day();
  //printf("We will travel on = %s", day_of_travel);
}



