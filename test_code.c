#include <stdio.h>
#include <time.h>
#include <math.h>
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

typedef struct FL_details
{
    char* FLight_id;
    char* Timing;
    char* Timing2;
    int seats_available_e;
    int total_seats_e;
    float fare_economy;
    int seats_available_b;
    int total_seats_b;
    float fare_business; 
}flight_details;

typedef struct fl_line
{
    char* flight_line;
}FLight_line;

typedef struct TRaveller
{
    char* name;
    int age;
    char* class;
    float seat_price;
    char* source;
    char* destination;
    char* departure;
    char* arrival;
    Date getDate;
    int mobile_no;
}traveller_details;



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
   strcpy(day,"Saturday\n") ;
   else if (dayOfWeek == 1)
   strcpy(day, "Sunday\n");
   else if (dayOfWeek == 2)
   strcpy(day, "Monday\n");
   else if (dayOfWeek == 3)
   strcpy(day, "Tuesday\n");
   else if (dayOfWeek == 4)
   strcpy(day, "Wednesday\n");
   else if (dayOfWeek == 5)
   strcpy(day, "Thursday\n");
   else if (dayOfWeek == 6)
   strcpy(day, "Friday\n");
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
    time_t timing = time(NULL);
    struct tm tm = *localtime(&timing);
    //check range of year,month and day
    if (validDate->yyyy > MAX_YR ||         
            validDate->yyyy < (tm.tm_year+1900)) //if the year that you have enter is less than the minim year or greater than the max year than its a invalid year
        return 0;
    if (validDate->mm < (tm.tm_mon+1) || validDate->mm > 12) //similarly no of month is basically 12 hence the enter number should not be more than 12 or less than 1  
        return 0;
    if (validDate->dd < tm.tm_mday || validDate->dd > 31)
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
char* Day(Date *getDate)
{
    
    int status = 0; //variable to check status
    
    //check date validity
    status = isValidDate(getDate);
    if(status !=1) // conditional operator for validity check, if its not equals 1 then its a invalid , a invalid statement will popup on screen
    {
        printf("\nPlease enter a valid date!\n");
        //exit(1);
        Day(getDate);
    }
    else 
    {
        char* day_string = day_of_week(getDate->dd, getDate->mm, getDate->yyyy);
        printf("You journey is on = %s\n", day_string);
        return day_string ;
    }
}

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

void nextMessage()
{
    headMessage();
    printf("\n\n\n\n");
    printf("\n\t\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t\t        =                 WELCOME                   =");
    printf("\n\t\t\t\t        =                   TO                      =");
    printf("\n\t\t\t\t        =        AIRPLANE RESERVATION SYSTEM        =");
    printf("\n\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("\n\n\n\t\t\t NOW: %02d-%02d-%d %02d:%02d:%02d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("\n\n\n\t\t\t Press 'Enter key' to continue.....");
    getchar();
}

int main(int app_mode)
{
    nextMessage();
    FILE * fp_orig = fopen("/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/airline_database.txt", "r");
    FILE * fp_mod = fopen("/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/airline_database_mod.txt", "w");
    int app_mode = 0;
    FILE * ticket;
    if (app_mode)
    {
        ticket = fopen("/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/Ticket.txt", "w");
    }
    else
    {
        ticket = fopen("/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/Ticket.txt", "a");
    }
    
    
    if (fp_orig == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open airline_database.txt file.\n");
        printf("Please check whether file exists and you have write privilege.\n");
        exit(EXIT_FAILURE);
    }
    if (fp_mod == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open airline_database_mod.txt file.\n");
        printf("Please check whether file exists and you have write privilege.\n");
        exit(EXIT_FAILURE);
    }
    if (ticket == NULL)
    {
        /* Unable to open file hence exit */
        printf("\nUnable to open Ticket.txt file.\n");
        printf("Please check whether file exists and you have write privilege.\n");
        exit(EXIT_FAILURE);
    }

    Date getDate = {0}; //variable to store date
    //get date year,month and day from user
    printf("\n Enter your journey date in format (dd/mm/yyyy): "); // input from the user in dd/mm/yy
    scanf("%d/%d/%d",&getDate.dd,&getDate.mm,&getDate.yyyy);
    char * day_of_travel = Day(&getDate);
    printf("Available airports: New Delhi, Mumbai, Kolkata, Chennai, Hyderabad\n");
    char buffer[100], board[30], dest[20];
    printf("Enter your source of Journey : ");
    // always note that string is an array of characters and usually writing that string alone means we are 
    // giving the address of first element of that array = &string[0]. and hence we don't specify "&string" in "scanf".
    // And more over calling that string "string" serves two purpose at same time i.e. it shows first element address 
    // and secondly it also contains the whole string.
    scanf("%s\n", board);
    printf("Enter your destination of Journey : ");
    scanf("%s\n", dest);
    if (fp_orig == NULL)
    {
        printf("Error in opening file! :(\n");
        exit(1);
    }
    while (fgets(buffer, 100, fp_orig) != NULL)
    {
        if (strcmp(day_of_travel, buffer) == 0)
        {
            // put the whole string line to the fp_mod file.
            fputs(buffer, fp_mod);
            char board_to_dest[100];
            fgets(board_to_dest, 100, fp_orig);
            strcat(strcat(board, " to "), strcat(dest, "\n"));

            if (strcmp(board_to_dest, board) == 0)
            {
                // write to the new file fp_mod.
                fputs(board_to_dest, fp_mod);
                //allocate a matrix shape memory space to Flight_line struct
                FLight_line* Flight_line = malloc(sizeof(FLight_line) * 6);
                printf("Available flights on %s from %s :--", day_of_travel, board_to_dest);
                for (int i = 0; i < 6; i++)
                {
                    fgets(Flight_line[i].flight_line, sizeof(FLight_line), fp_orig);
                    printf("%s", Flight_line[i].flight_line);
                }
                printf("\n");
                free(Flight_line);//free up the used up space

                printf("Choose your Plane by its Id\n");
                char Id[5];
                scanf("%s", Id);
                flight_details* F_details = malloc(sizeof(flight_details) * 6);
                for (int i = 0; i < 6; i++)
                {
                    char * flight_name = malloc(sizeof(char)*(5+1));
                    char * timing = malloc(sizeof(char)*(5+1));
                    char * timing2 = malloc(sizeof(char)*(5+1));
                    flight_name[6] = '\0';
                    timing[6] = '\0';
                    int eco_seats_avail, tot_eco, bus_seats_avail, tot_bus;
                    float eco_fare, bus_fare;
                    // now let's read from the file
                    fscanf(fp_orig, "%s %s %d %d %.1f %d %d %.1f", flight_name, timing, timing2, &eco_seats_avail,\
                     &tot_eco, &eco_fare, &bus_seats_avail, &tot_bus, &bus_fare);
                    F_details[i].FLight_id = flight_name;
                    F_details[i].Timing = timing;
                    F_details[i].Timing2 = timing2;
                    F_details[i].seats_available_e = eco_seats_avail;
                    F_details[i].total_seats_e = tot_eco;
                    F_details[i].fare_economy = eco_fare;
                    F_details[i].seats_available_b = bus_seats_avail;
                    F_details[i].total_seats_b = tot_bus;
                    F_details[i].fare_business = bus_fare;
                    free(flight_name);
                    free(timing);
                    free(timing2);
                    if (strcmp(Id, F_details[i].FLight_id)==0)
                    {
                        char BE[1];
                        printf("In which class you wanna travel? Economy class or Business class.\n");
                        printf("Enter 'B' for Business Class and 'E' for Economy Class -- ");
                        scanf("%s", BE);
                        if (strcmp(BE, "B")==0)
                        {
                            printf("Enter no. of Travellers : ");
                            int pass_no;
                            scanf("%d", &pass_no);
                            F_details[i].seats_available_b -= pass_no;
                            traveller_details* Ticket = malloc(sizeof(traveller_details)*pass_no);
                            float price =  0.0;
                            for (int j = 0; j < pass_no; j++)
                            {
                                printf("\nEnter details for traveller no. %d : \n", (j+1));
                                printf("Enter name : ");
                                char traveller_name[50];
                                scanf("%s", traveller_name);
                                Ticket[j].name = traveller_name;
                                printf("\nEnter your age : ");
                                int age_name;
                                scanf("%d", &age_name);
                                Ticket[j].age = age_name;
                                printf("\nEnter your Mobile Number ; ");
                                int mobile;
                                scanf("%d", &mobile);
                                Ticket[j].mobile_no = mobile;
                                Ticket[j].class = BE;
                                Ticket[j].seat_price = F_details[i].fare_business;
                                price += Ticket[j].seat_price;
                                sscanf(board_to_dest, "%s %*s %s", Ticket[j].source, Ticket[j].destination);
                                Ticket[j].departure = F_details[i].Timing;
                                Ticket[j].arrival = F_details[i].Timing2;
                                Ticket[j].getDate.dd = getDate.dd;
                                Ticket[j].getDate.mm = getDate.mm;
                                Ticket[j].getDate.yyyy = getDate.yyyy;
                            }
                            printf("Do you want to checkout? y/n");
                            char YN[1];
                            scanf("%s", YN);
                            if (strcmp(YN, "y") == 0)
                            {
                                for (int j = 0; j < pass_no; j++)
                                {
                                    fprintf(ticket, "Name : %s\nAge :%d\nClass : %s\nFare : %.1f\nSource : \
                                    %s\nDestination : %s\nDeparture time : %s\nArrival time : %s\n\
                                    Date of Boarding : %02d/%02d/%d\nMobile No.: %d\n", Ticket[j].name, Ticket[j].age, \
                                    Ticket[j].class, Ticket[j].seat_price, Ticket[j].source, Ticket[j].destination, \
                                    Ticket[j].departure, Ticket[j].arrival, Ticket[j].getDate.dd, Ticket[j].getDate.mm,\
                                    Ticket[j].getDate.yyyy, Ticket[j].mobile_no);
                                }
                                fprintf(ticket, "Total Fare : %.1f\n\n\n",price);
                                printf("Your Ticket Booked Successfully !\n");
                                printf("HAPPY JOURNEY ! :)\n");
                                printf("Your Bill:\n");
                                printf("=============================================================\n");
                                for (int j = 0; j < pass_no; j++)
                                {
                                    printf("Name : %s\nAge :%d\nClass : %s\nFare : %.1f\nSource : \
                                    %s\nDestination : %s\nDeparture time : %s\nArrival time : %s\n\
                                    Date of Boarding : %02d/%02d/%d\nMobile No.: %d\n", Ticket[j].name, Ticket[j].age, \
                                    Ticket[j].class, Ticket[j].seat_price, Ticket[j].source, Ticket[j].destination, \
                                    Ticket[j].departure, Ticket[j].arrival, Ticket[j].getDate.dd, Ticket[j].getDate.mm,\
                                    Ticket[j].getDate.yyyy, Ticket[j].mobile_no);
                                    printf("\n---------------------------------------------------------\n");
                                }
                                printf("\n\n=============================================================\n");
                                printf("Total Fare : %.1f\n\n\n",price);
                                printf("=============================================================\n");
                                free(Ticket);
                                printf("Do you want to book more seats? y/n\n");
                                char Bool1[1];
                                scanf("%s", Bool1);
                                if (strcmp(Bool1, "y") == 0)
                                {
                                    app_mode = 0;
                                    main(app_mode);
                                }
                                else
                                {
                                    printf("Thank you for booking ticket with us\n");
                                    printf("Hope to see you again! :)\n");
                                    exit(1);
                                }

                            }
                            else
                            {
                                free(Ticket);
                                printf("Do you want to book again? y/n\n");
                                char Bool[1];
                                scanf("%s", Bool);
                                if (strcmp(Bool, "y") == 0)
                                {
                                    main(app_mode);
                                }
                                else
                                {
                                    exit(1);
                                }
                                
                            }
                        }
                        else
                        {
                            printf("Enter no. of Travellers : ");
                            int pass_no;
                            scanf("%d", &pass_no);
                            F_details[i].seats_available_e -= pass_no;
                            traveller_details* Ticket = malloc(sizeof(traveller_details)*pass_no);
                            float price =  0.0;
                            for (int j = 0; j < pass_no; j++)
                            {
                                printf("\nEnter details for traveller no. %d : \n", (j+1));
                                printf("Enter name : ");
                                char traveller_name[50];
                                scanf("%s", traveller_name);
                                Ticket[j].name = traveller_name;
                                printf("\nEnter your age : ");
                                int age_name;
                                scanf("%d", &age_name);
                                Ticket[j].age = age_name;
                                printf("\nEnter your Mobile Number ; ");
                                int mobile;
                                scanf("%d", &mobile);
                                Ticket[j].mobile_no = mobile;
                                Ticket[j].class = BE;
                                Ticket[j].seat_price = F_details[i].fare_business;
                                price += Ticket[j].seat_price;
                                sscanf(board_to_dest, "%s %*s %s", Ticket[j].source, Ticket[j].destination);
                                Ticket[j].departure = F_details[i].Timing;
                                Ticket[j].arrival = F_details[i].Timing2;
                                Ticket[j].getDate.dd = getDate.dd;
                                Ticket[j].getDate.mm = getDate.mm;
                                Ticket[j].getDate.yyyy = getDate.yyyy;
                            }
                            printf("Do you want to checkout? y/n");
                            char YN[1];
                            scanf("%s", YN);
                            if (strcmp(YN, "y") == 0)
                            {
                                for (int j = 0; j < pass_no; j++)
                                {
                                    fprintf(ticket, "Name : %s\nAge :%d\nClass : %s\nFare : %.1f\nSource : \
                                    %s\nDestination : %s\nDeparture time : %s\nArrival time : %s\n\
                                    Date of Boarding : %02d/%02d/%d\nMobile No.: %d\n", Ticket[j].name, Ticket[j].age, \
                                    Ticket[j].class, Ticket[j].seat_price, Ticket[j].source, Ticket[j].destination, \
                                    Ticket[j].departure, Ticket[j].arrival, Ticket[j].getDate.dd, Ticket[j].getDate.mm,\
                                    Ticket[j].getDate.yyyy, Ticket[j].mobile_no);
                                }
                                fprintf(ticket, "Total Fare : %.1f\n\n\n",price);
                                printf("Your Ticket Booked Successfully !\n");
                                printf("HAPPY JOURNEY ! :)\n");
                                printf("Your Bill:\n");
                                printf("=============================================================\n");
                                for (int j = 0; j < pass_no; j++)
                                {
                                    printf("Name : %s\nAge :%d\nClass : %s\nFare : %.1f\nSource : \
                                    %s\nDestination : %s\nDeparture time : %s\nArrival time : %s\n\
                                    Date of Boarding : %02d/%02d/%d\nMobile No.: %d\n", Ticket[j].name, Ticket[j].age, \
                                    Ticket[j].class, Ticket[j].seat_price, Ticket[j].source, Ticket[j].destination, \
                                    Ticket[j].departure, Ticket[j].arrival, Ticket[j].getDate.dd, Ticket[j].getDate.mm,\
                                    Ticket[j].getDate.yyyy, Ticket[j].mobile_no);
                                    printf("\n---------------------------------------------------------\n");
                                }
                                printf("\n\n=============================================================\n");
                                printf("Total Fare : %.1f\n\n\n",price);
                                printf("=============================================================\n");
                                free(Ticket);
                                printf("Do you want to book more seats? y/n\n");
                                char Bool1[1];
                                scanf("%s", Bool1);
                                if (strcmp(Bool1, "y") == 0)
                                {
                                    app_mode = 0;
                                    main(app_mode);
                                }
                                else
                                {
                                    printf("Thank you for booking ticket with us\n");
                                    printf("Hope to see you again! :)\n");
                                    exit(1);
                                }

                            }
                            else
                            {
                                free(Ticket);
                                printf("Do you want to book again? y/n\n");
                                char Bool[1];
                                scanf("%s", Bool);
                                if (strcmp(Bool, "y") == 0)
                                {
                                    main(app_mode);
                                }
                                else
                                {
                                    exit(1);
                                }
                                
                            }
                            
                        }
                    }
                    else
                    {
                        fprintf(fp_mod, "%s %s %s %d %d %.1f %d %d %.1f\n", F_details[i].FLight_id, F_details[i].Timing, \
                        F_details[i].Timing2, F_details[i].seats_available_e, F_details[i].total_seats_e, F_details[i].fare_economy, \
                        F_details[i].seats_available_b, F_details[i].total_seats_b, F_details[i].fare_business);
                    }
                }
            }
            else
            {
                fputs(board_to_dest, fp_mod);
            }
        }
        else
        {
            fputs(buffer, fp_mod);
        }
    }
}