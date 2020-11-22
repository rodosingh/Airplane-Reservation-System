#include <stdio.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#define MAX_YR 9999 // max year that we can quest for, beyond that we will get invalid statement
#define MIN_YR 2000 // min year cutoff, below this will give a invalid statement
//system(char * "CLS");
//clear;
//structure to store date
typedef struct //function
{
    int yyyy;
    int mm;
    int dd;
} Date;

typedef struct
{
    char *flt_line;
} flight_lines;
// structure to save the flight details
typedef struct FL_details
{
    char *FLight_id;
    char *Timing;
    char *Timing2;
    int seats_available_e;
    int total_seats_e;
    float fare_economy;
    int seats_available_b;
    int total_seats_b;
    float fare_business;
} flight_details;
// structure to save the traveller details. 
typedef struct TRaveller
{
    char *name;
    int age;
    char *fl_id;
    char *class;
    float conv_seat_price;
    float seat_price;
    char *source;
    char *destination;
    char *departure;
    char *arrival;
    Date getDate;
    long int mobile_no;
} traveller_details;

// check validity of Airport name.
int airport_valid(char *airplane_name)
{
    char ports[5][50] = {"NewDelhi", "Mumbai", "Kolkata", "Chennai", "Hyderabad"};
    int ctr = 0;
    for (int i = 0; i < 5; i++)
    {
        //printf("name = %s\n", airplane_name);
        //printf("ports[i] = %s\n", ports[i]);
        if (strcmp(airplane_name, ports[i]) == 0)
        {
            //printf("any prob = %d\n", ctr);
            ctr = 1;
        }
    }
    return ctr;
}


int fm(int date, int month, int year)
{
    int fmonth, leap;
    if ((year % 100 == 0) && (year % 400 != 0))
        leap = 0;
    else if (year % 4 == 0)
        leap = 1;
    else
        leap = 0;

    fmonth = 3 + (2 - leap) * ((month + 2) / (2 * month)) + (5 * month + month / 9) / 2;

    fmonth = fmonth % 7;

    return fmonth;
}
//function that converts the date to day.
char *day_of_week(int date, int month, int year)
{

    int dayOfWeek;
    int YY = year % 100;
    int century = year / 100;
    char *day = malloc(20);
    printf("\nDate: %d/%d/%d \n", date, month, year);

    dayOfWeek = 1.25 * YY + fm(date, month, year) + date - 2 * (century % 4);

    //remainder on division by 7
    dayOfWeek = dayOfWeek % 7;
    if (dayOfWeek == 0)
        strcpy(day, "Saturday\n");
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
// price conversion for economy class
// 75% discount for infants, 50% for childs, and 0% for adults.
float convert_e(int *age, float *price)
{
    float new_price;
    if (*age < 5)
    {
        new_price = 0.25 * (*price);
    }
    else if (*age < 18 && *age >= 5)
    {
        new_price = 0.5 * (*price);
    }
    else
    {
        new_price = *price;
    }
    return new_price;
}
// price conversion for economy class
// 60% discount for infants, 35% for childs, and 0% for adults.
float convert_b(int *age, float *price)
{
    float new_price;
    if (*age < 5)
    {
        new_price = 0.40 * (*price);
    }
    else if (*age < 18 && *age >= 5)
    {
        new_price = 0.65 * (*price);
    }
    else
    {
        new_price = *price;
    }
    return new_price;
}
// Function to check leap year.
//Function returns 1 if leap year
int IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}
// returns true i.e. 1, if given date is valid.
int isValidDate(Date *validDate)
{
    time_t timing = time(NULL);
    struct tm tm = *localtime(&timing);
    //check range of year,month and day
    if (validDate->yyyy > MAX_YR ||
        validDate->yyyy < (tm.tm_year + 1900)) //if the year that you have enter is less than the minim year or greater than the max year than its a invalid year
        return 0;
    if (validDate->mm < (tm.tm_mon + 1) || validDate->mm > 12) //similarly no of month is basically 12 hence the enter number should not be more than 12 or less than 1
        return 0;
    if (validDate->dd < tm.tm_mday || validDate->dd > 31)
        return 0;
    //Handle feb days in leap year
    if (validDate->mm == 2) // as we know that leap year has 29 days in feb in constrast to normal year which has only 28 days
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
char *Day(Date *getDate)
{

    int status = 0; //variable to check status

    //check date validity
    status = isValidDate(getDate);
    if (status != 1) // conditional operator for validity check, if its not equals 1 then its a invalid , a invalid statement will popup on screen
    {
        printf("\nPlease enter a valid date!\n");
        exit(1);
        //Day(getDate);
    }
    else
    {
        char *day_string = day_of_week(getDate->dd, getDate->mm, getDate->yyyy);
        printf("You journey is on = %s\n", day_string);
        return day_string;
    }
}

//this will be printed at top of the terminal
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

//next the below message will be printed.
void nextMessage()
{
    headMessage();
    printf("\n\n");
    printf("\n\t\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");
    printf("\n\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t\t        =                 WELCOME                   =");
    printf("\n\t\t\t\t        =                   TO                      =");
    printf("\n\t\t\t\t        =             DAARK AIRLINES                =");
    printf("\n\t\t\t\t        =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=");
    printf("\n\t\t\t\t  **-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**-**\n");

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    printf("\n\n\n\t\t\t NOW: %02d-%02d-%d %02d:%02d:%02d\n", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
    printf("\n\n\n\t\t\t Press 'Enter key' to continue.....");
    getchar();
}

//with this function one can change the flight details.
void ADMIN(FILE *fp_orig, FILE *fp_mod)
{
    Date getDate = {0}; //variable to store date
    char *day = malloc(sizeof(char) * 10);
    printf("\nEnter '1' if you want to input 'date' o/w Enter '0' : ");
    int de;
    //char* DAY = malloc(sizeof(char)*10);
    char DAY[10];
    scanf("%d", &de);
    if (de == 1)
    {
        printf("Enter the Date for which you want to modify the flight details : ");
        scanf("%d/%d/%d", &getDate.dd, &getDate.mm, &getDate.yyyy);
        char *day_of_travel = Day(&getDate);
        //printf("date  = %s\n", day_of_travel);
        strcat(DAY, day_of_travel);
    }
    else
    {
        printf("Enter the Day for which you want to modify the flight details : ");
        scanf("%s", day);
        sprintf(DAY, "%s\n", day);
        /*strcat(DAY, day);
        strcat(DAY, "\n");*/
    }
    char buffer[100];
    char *board = malloc(sizeof(char) * 30);
    char *dest = malloc(sizeof(char) * 30);
    printf("Enter the name of Boarding place corresponding to which you want to change flight details : ");
    scanf("%s", board);
    printf("Enter the name of Destination place corresponding to which you want to change flight details : ");
    scanf("%s", dest);
    //printf("Board = %s", DAY);

    // here we check if the airport name is valid or not for both source and
    // destination. If one is wrong then the code will show the below error.
    if (!(airport_valid(board) && airport_valid(dest)))
    {
        printf("Please enter a valid airport name!:|\n");
        //we have used recursion here to start again from first.
        ADMIN(fp_orig, fp_mod);
    }
    while (fgets(buffer, 100, fp_orig) != NULL)
    {
        //printf("Board = %s , %s\n", board, dest);
        if (strcmp(DAY, buffer) == 0)
        {
            // put the whole string line to the fp_mod file.
            fputs(buffer, fp_mod);
            char board_to_dest[100], board_dest[100];
            fgets(board_to_dest, 100, fp_orig);
            sprintf(board_dest, "%s to %s\n", board, dest);
            if (strcmp(board_to_dest, board_dest) == 0)
            {
                // write to the new file fp_mod
                fputs(board_to_dest, fp_mod);
                //allocate a matrix shape memory space to flight_line struct
                flight_lines *fl_line = malloc(sizeof(flight_lines) * 6);
                printf("\n\nAvailable flights on %s\n", DAY);
                printf("\n\t\t\t\t======================================================\n");
                printf("\n\t\t\t\tFlit-ID Dept. Arrv. Eco Ect EcoCost Bus But BusCost\n");
                printf("\t\t\t\t------------------------------------------------------\n");
                for (int i = 0; i < 6; i++)
                {
                    char *flight_line = malloc(sizeof(char) * (100));
                    fgets(flight_line, sizeof(char) * 100, fp_orig);
                    printf("\t\t\t\t* %s", flight_line);
                    fl_line[i].flt_line = flight_line;
                }
                printf("\n\t\t\t\t======================================================\n");
                printf("\n");
                printf("Do you want to change anything here ? y/n\n");
                char Bt[1];
                scanf("%s", Bt);
                if (strcmp(Bt, "y") == 0)
                {
                    for (int i = 0; i < 6; i++)
                    {
                        char *fl_id = malloc(sizeof(char) * 5);
                        //copies first 5 letter from the string.
                        strncpy(fl_id, fl_line[i].flt_line, 5);
                        printf("Do you want to change details for flight '%s'? 0/1\n", fl_id);
                        /*char* Id = malloc(sizeof(char)*5);
                        scanf("%s", Id);*/
                        flight_details *F_details = malloc(sizeof(flight_details) * 1);
                        int chng_details;
                        scanf("%d", &chng_details);
                        if (chng_details)
                        {
                            printf("Do you want to overwrite? 0/1\n");
                            printf("Enter '1' to write something else or change the particulars o/w '0' to keep as it is.\n");
                            int line_p;
                            scanf("%d", &line_p);
                            if (line_p)
                            {
                                //  this removes '\n' from input stream.
                                int c;
                                while ((c = getchar()) != '\n' && c != EOF)
                                    ;
                                char add_line[100];
                                printf("Type below what you want to write...\n");
                                fgets(add_line, 100, stdin);
                                fputs(add_line, fp_mod);
                            }
                            else
                            {
                                fputs(fl_line[i].flt_line, fp_mod);
                            }
                        }
                        else
                        {
                            fputs(fl_line[i].flt_line, fp_mod);
                        }
                    }
                    printf("Modified Data saved successfully!!!\n");
                }
                else
                {
                    for (int i = 0; i < 6; i++)
                    {
                        fputs(fl_line[i].flt_line, fp_mod);
                    }
                    // Below code is an example of recursion, where we intend to change details
                    // of other flights. But due to some time limitation and some glitches we
                    // leave this part.
                    /*printf("Do you want to modify details of other flights? 0/1\n");
                    int mod_flights;
                    scanf("%d", &mod_flights);
                    if (mod_flights)
                    {
                        rewind(fp_orig);
                        ADMIN(fp_orig, fp_mod);
                    }
                    else
                    {
                        printf("You haven't changed anything. Seems all correct! :)\n");
                    }*/
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
// this code helps us in searching for the flights that run from our desired boarding
// place to destination.
void SEARCH(FILE *fp_orig)
{
    printf("\t\t\t\tAvailable airports: NewDelhi, Mumbai, Kolkata, Chennai, Hyderabad\n");
    printf("Enter your Boarding Station : ");
    char *board = malloc(sizeof(char) * 30);
    scanf("%s", board);
    printf("Enter your Destination : ");
    char *dest = malloc(sizeof(char) * 30);
    scanf("%s", dest);
    if (!(airport_valid(board) && airport_valid(dest)))
    {
        printf("Please enter a valid airport name!:|\n");
        printf("Let's start again -->\n");
        SEARCH(fp_orig);
    }
    printf("Do you want to search by DATE? 0/1 \n");
    int BOOL;
    scanf("%d", &BOOL);
    char DAY[100];
    if (BOOL)
    {
        Date getDate = {0};
        printf("\nEnter your journey date in format (dd/mm/yyyy): "); // input from the user in dd/mm/yy
        scanf("%d/%d/%d", &getDate.dd, &getDate.mm, &getDate.yyyy);
        char *day_of_travel = Day(&getDate);
        sprintf(DAY, "%s", day_of_travel);
    }
    char buffer[100];
    // we have put a while loop that reads line from original file and checks further.
    while (fgets(buffer, 100, fp_orig) != NULL)
    {
        char board_to_dest[100], board_dest[100];
        sprintf(board_dest, "%s to %s\n", board, dest);
        if (BOOL)
        {
            // comparing the DAY we entered with the line from file.
            if (strcmp(DAY, buffer) == 0)
            {
                fgets(board_to_dest, 100, fp_orig);
                //allocate a matrix shape memory space to flight_line struct
                if (strcmp(board_to_dest, board_dest) == 0)
                {
                    //printing the flight details on screen.
                    flight_lines *fl_line = malloc(sizeof(flight_lines) * 6);
                    printf("\t\t\t\tAvailable flights on %s from %s", DAY, board_to_dest);
                    printf("\n\t\t\t\t======================================================\n");
                    printf("\n\t\t\t\tFlit-ID Dept. Arrv. Eco Ect EcoCost Bus But BusCost\n");
                    printf("\t\t\t\t------------------------------------------------------\n");
                    for (int i = 0; i < 6; i++)
                    {
                        char *flight_line = malloc(sizeof(char) * (100));
                        fgets(flight_line, sizeof(char) * 100, fp_orig);
                        printf("\t\t\t\t* %s", flight_line);
                        fl_line[i].flt_line = flight_line;
                    }
                    printf("\n\t\t\t\t======================================================\n");
                }
            }
        }
        else
        {
            //removes the last newline char = '\n'
            strtok(buffer, "\n");
            fgets(board_to_dest, 100, fp_orig);
            if (strcmp(board_to_dest, board_dest) == 0)
            {
                flight_lines *fl_line = malloc(sizeof(flight_lines) * 6);
                printf("\n\t\t\t\tAvailable flights on %s from %s", buffer, board_to_dest);
                printf("\n\t\t\t\t======================================================\n");
                printf("\n\t\t\t\tFlit-ID Dept. Arrv. Eco Ect EcoCost Bus But BusCost\n");
                printf("\t\t\t\t------------------------------------------------------\n");
                for (int i = 0; i < 6; i++)
                {
                    char *flight_line = malloc(sizeof(char) * (100));
                    fgets(flight_line, sizeof(char) * 100, fp_orig);
                    printf("\t\t\t\t* %s", flight_line);
                    fl_line[i].flt_line = flight_line;
                }
                printf("\n\t\t\t\t======================================================\n");
            }
        }
    }
}
//this function helps in booking seats in our desired flight and print the corresponding ticket for us.
void USER(FILE *fp_orig, FILE *fp_mod, FILE *ticket)
{
    Date getDate = {0}; //variable to store date
    //get date year,month and day from user
    printf("\nEnter your journey date in format (dd/mm/yyyy): "); // input from the user in dd/mm/yy
    scanf("%d/%d/%d", &getDate.dd, &getDate.mm, &getDate.yyyy);
    char *day_of_travel = Day(&getDate);
    printf("\t\t\t\tAvailable airports: NewDelhi, Mumbai, Kolkata, Chennai, Hyderabad\n");
    char buffer[100];
    char *board = malloc(sizeof(char) * 30);
    char *dest = malloc(sizeof(char) * 30);
    // enter your source airport.
    printf("Enter your source of Journey : ");
    // always note that string is an array of characters and usually writing that string alone means we are
    // giving the address of first element of that array = &string[0]. and hence we don't specify "&string" in "scanf".
    // And more over calling that string "string" serves two purpose at same time i.e. it shows first element address
    // and secondly it also contains the whole string.
    scanf("%s", board);
    //getchar();
    //enter your destination airport.
    printf("Enter your destination of Journey : ");
    scanf("%s", dest);
    // shows the below statement if anyone of the boarding or destination place is wrong.
    if (!(airport_valid(board) && airport_valid(dest)))
    {
        printf("Please enter a valid airport name!:|\n");
        USER(fp_orig, fp_mod, ticket);
    }
    //going through whole file and reading one line each time and comparing it with the day entered
    while (fgets(buffer, 100, fp_orig) != NULL)
    {
        if (strcmp(day_of_travel, buffer) == 0)
        {
            // put the whole string line to the fp_mod file.
            fputs(buffer, fp_mod);
            char board_to_dest[100], board_dest[100];
            fgets(board_to_dest, 100, fp_orig);
            sprintf(board_dest, "%s to %s\n", board, dest);
            //printf("String = %s", board_to_dest);
            // trying to store station id in form of number and then compare
            /*int code;
            sscanf(board_to_dest, "%d", &code);
            int board_int = code_airport(board);
            printf("your board int = %d\n",board_int);
            int dest_int = code_airport(dest);
            printf("What is code = %d\n", code);*/
            //printf("What is bd = %d?\n",5);

            if (strcmp(board_to_dest, board_dest) == 0)
            {
                // write to the new file fp_mod
                fputs(board_to_dest, fp_mod);
                //allocate a matrix shape memory space to flight_line struct
                flight_lines *fl_line = malloc(sizeof(flight_lines) * 6);
                printf("\n\nAvailable flights on %s\n", day_of_travel);
                printf("\n\t\t\t\t======================================================\n");
                printf("\n\t\t\t\tFlit-ID Dept. Arrv. Eco Ect EcoCost Bus But BusCost\n");
                printf("\t\t\t\t------------------------------------------------------\n");
                //print the flights available on user inputted date from source to dest.
                for (int i = 0; i < 6; i++)
                {
                    char *flight_line = malloc(sizeof(char) * (100));
                    fgets(flight_line, sizeof(char) * 100, fp_orig);
                    printf("\t\t\t\t* %s", flight_line);
                    fl_line[i].flt_line = flight_line;
                }
                printf("\n\t\t\t\t======================================================\n");
                printf("\n");
                printf("Do you want to go further? y/n\n");
                char Bt[1];
                scanf("%s", Bt);
                if (strcmp(Bt, "y") == 0)
                {
                    printf("Choose your Plane by its Id\n");
                    char Id[5];
                    scanf("%s", Id);
                    flight_details *F_details = malloc(sizeof(flight_details) * 6);
                    for (int i = 0; i < 6; i++)
                    {
                        //NOTE : if want to put a string variable in loop, it's better
                        //to take pointer type var and allocate some memory instead of
                        // taking char var[50] as it would store only the last string in loop.
                        char *flight_name = malloc(sizeof(char) * (5 + 1));
                        char *timing = malloc(sizeof(char) * (5 + 1));
                        char *timing2 = malloc(sizeof(char) * (5 + 1));
                        flight_name[5] = '\0';
                        timing[5] = '\0';
                        timing2[5] = '\0';
                        int eco_seats_avail, tot_eco, bus_seats_avail, tot_bus;
                        float eco_fare, bus_fare;
                        // now let's read from the file
                        //char* flight_line1 = malloc(sizeof(char)*(100));
                        //fgets(flight_line1, sizeof(char)*100, fp_orig);
                        sscanf(fl_line[i].flt_line, "%s %s %s %d %d %f %d %d %f", flight_name, timing, timing2, &eco_seats_avail,
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
                        //free(flight_name);
                        //free(timing);
                        //free(timing2);
                        if (strcmp(Id, F_details[i].FLight_id) == 0)
                        {
                            //Below once we get into this loop by matching flight id from user and from file.
                            //we enter details of travellers here through struct.
                            printf("Enter no. of Travellers : ");
                            int pass_no;
                            scanf("%d", &pass_no);
                            //F_details[i].seats_available_b -= pass_no;
                            traveller_details *Ticket = malloc(sizeof(traveller_details) * pass_no);
                            float price = 0.0;
                            int bus_ctr = 0, eco_ctr = 0;
                            //not needed...continue
                            for (int j = 0; j < pass_no; j++)
                            {
                                // reading strings that will be printed on screen will inform one what we want to take user input.
                                printf("\nEnter details for traveller no. %d : \n", (j + 1));
                                printf("\nEnter your last name ONLY : \n");
                                char *traveller_name = malloc(sizeof(char) * 50);
                                scanf("%s", traveller_name);
                                Ticket[j].name = traveller_name;
                                printf("\nEnter your age : \n");
                                int age_name;
                                scanf("%d", &age_name);
                                Ticket[j].age = age_name;
                                printf("\nEnter your Mobile Number : \n");
                                long int mobile;
                                scanf("%ld", &mobile);
                                Ticket[j].mobile_no = mobile;
                                char BE[1];
                                printf("\nIn which class '%s' wanna travel? Economy class or Business class.\n", Ticket[j].name);
                                printf("Enter 'B' for Business Class and 'E' for Economy Class -- \n");
                                scanf("%s", BE);
                                if (strcmp(BE, "B") == 0)
                                {
                                    Ticket[j].class = "Business";
                                    Ticket[j].seat_price = F_details[i].fare_business;
                                    Ticket[j].conv_seat_price = convert_b(&Ticket[j].age, &Ticket[j].seat_price);
                                    price += Ticket[j].conv_seat_price;
                                    F_details[i].seats_available_b -= 1;
                                    bus_ctr++;
                                }
                                else
                                {
                                    Ticket[j].class = "Economy";
                                    Ticket[j].seat_price = F_details[i].fare_economy;
                                    Ticket[j].conv_seat_price = convert_e(&Ticket[j].age, &Ticket[j].seat_price);
                                    price += Ticket[j].conv_seat_price;
                                    F_details[i].seats_available_e -= 1;
                                    eco_ctr++;
                                }
                                //sscanf(board_to_dest, "%s %*s %s", Ticket[j].source, Ticket[j].destination);
                                Ticket[j].fl_id = F_details[i].FLight_id;
                                Ticket[j].source = board;
                                Ticket[j].destination = dest;
                                Ticket[j].departure = F_details[i].Timing;
                                Ticket[j].arrival = F_details[i].Timing2;
                                Ticket[j].getDate.dd = getDate.dd;
                                Ticket[j].getDate.mm = getDate.mm;
                                Ticket[j].getDate.yyyy = getDate.yyyy;
                            }
                            printf("Do you want to book more seats? 0/1\n");
                            printf("Enter 1 for 'yes' otherwise enter 0\n");
                            int pass_no1;
                            traveller_details *Ticket1 = malloc(sizeof(traveller_details) * pass_no1);
                            int bus_ctr1 = 0, eco_ctr1 = 0;
                            int Bool1;
                            scanf("%d", &Bool1);
                            //not needed...continue
                            // Here we add details for extra passengers and print that on to sreen.
                            if (Bool1)
                            {
                                printf("Enter no. of Travellers : ");
                                scanf("%d", &pass_no1);
                                for (int j = 0; j < pass_no1; j++)
                                {
                                    printf("\nEnter details for traveller no. %d : \n", (pass_no + j + 1));
                                    printf("\nEnter your last name ONLY : \n");
                                    char *traveller_name1 = malloc(sizeof(char) * 50);
                                    scanf("%s", traveller_name1);
                                    Ticket1[j].name = traveller_name1;
                                    printf("\nEnter your age : \n");
                                    int age_name1;
                                    scanf("%d", &age_name1);
                                    Ticket1[j].age = age_name1;
                                    printf("\nEnter your Mobile Number : \n");
                                    long int mobile1;
                                    scanf("%ld", &mobile1);
                                    Ticket1[j].mobile_no = mobile1;
                                    char BE1[1];
                                    printf("\nIn which class '%s' wanna travel? Economy class or Business class.\n", Ticket1[j].name);
                                    printf("Enter 'B' for Business Class and 'E' for Economy Class -- \n");
                                    scanf("%s", BE1);
                                    if (strcmp(BE1, "B") == 0)
                                    {
                                        Ticket1[j].class = "Business";
                                        Ticket1[j].seat_price = F_details[i].fare_business;
                                        Ticket1[j].conv_seat_price = convert_b(&Ticket1[j].age, &Ticket1[j].seat_price);
                                        price += Ticket1[j].conv_seat_price;
                                        F_details[i].seats_available_b -= 1;
                                        bus_ctr1++;
                                    }
                                    else
                                    {
                                        Ticket1[j].class = "Economy";
                                        Ticket1[j].seat_price = F_details[i].fare_economy;
                                        Ticket1[j].conv_seat_price = convert_e(&Ticket1[j].age, &Ticket1[j].seat_price);
                                        price += Ticket1[j].conv_seat_price;
                                        F_details[i].seats_available_e -= 1;
                                        eco_ctr1++;
                                    }
                                    //sscanf(board_to_dest, "%s %*s %s", Ticket[j].source, Ticket[j].destination);
                                    Ticket1[j].fl_id = F_details[i].FLight_id;
                                    Ticket1[j].source = board;
                                    Ticket1[j].destination = dest;
                                    Ticket1[j].departure = F_details[i].Timing;
                                    Ticket1[j].arrival = F_details[i].Timing2;
                                    Ticket1[j].getDate.dd = getDate.dd;
                                    Ticket1[j].getDate.mm = getDate.mm;
                                    Ticket1[j].getDate.yyyy = getDate.yyyy;
                                    /*printf("Source = %s\n", Ticket1[j].source);
                                    printf("Source_orig = %s\n", board);*/
                                }
                            }
                            printf("Do you want to checkout? 0/1\n");
                            //here we checkout
                            printf("Enter 1 to checkout otherwise enter 0\n");
                            int YN;
                            scanf("%d", &YN);
                            if (YN)
                            {
                                //Here we generate the ticket.txt file
                                ticket = fopen("/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/Ticket.txt", "w");
                                if (ticket == NULL)
                                {
                                    /* Unable to open file hence exit */
                                    printf("\nUnable to open Ticket.txt file.\n");
                                    printf("Please check whether file exists and you have write privilege.\n");
                                    exit(EXIT_FAILURE);
                                }
                                fprintf(ticket, "TICKET\n");
                                fprintf(ticket, "=============================================================\n");
                                for (int j = 0; j < pass_no; j++)
                                {
                                    /*always put %s or %d before \(=continuation of code) unless while
                                    printing there will be an unwanted space. And put \n(=new line) after \ 
                                    unless there will be huge space before the things that needs to be 
                                    printed after \ */
                                    fprintf(ticket, "Name : %s\nAge :%d\nFlight ID : %s\nClass : %s\nFare : %.1f\nSource : %s\
                                    \nDestination : %s\nDeparture time : %s\nArrival time : %s\
                                    \nDate of Boarding : %02d/%02d/%d\nMobile No.: %ld\n\n\n",
                                            Ticket[j].name, Ticket[j].age, Ticket[j].fl_id,
                                            Ticket[j].class, Ticket[j].conv_seat_price, Ticket[j].source, Ticket[j].destination,
                                            Ticket[j].departure, Ticket[j].arrival, Ticket[j].getDate.dd, Ticket[j].getDate.mm,
                                            Ticket[j].getDate.yyyy, Ticket[j].mobile_no);
                                    fprintf(ticket, "\n---------------------------------------------------------\n");
                                }
                                if (Bool1)
                                {
                                    for (int j = 0; j < pass_no1; j++)
                                    {
                                        /*always put %s or %d before \(=continuation of code) unless while
                                        printing there will be an unwanted space. And put \n(=new line) after \ 
                                        unless there will be huge space before the things that needs to be 
                                        printed after \ */
                                        fprintf(ticket, "Name : %s\nAge :%d\nFlight ID : %s\nClass : %s\nFare : %.1f\nSource : %s\
                                        \nDestination : %s\nDeparture time : %s\nArrival time : %s\
                                        \nDate of Boarding : %d/%d/%d\nMobile No.: %ld\n\n\n",
                                                Ticket1[j].name, Ticket1[j].age, Ticket1[j].fl_id,
                                                Ticket1[j].class, Ticket1[j].conv_seat_price, Ticket1[j].source, Ticket1[j].destination,
                                                Ticket1[j].departure, Ticket1[j].arrival, Ticket1[j].getDate.dd, Ticket1[j].getDate.mm,
                                                Ticket1[j].getDate.yyyy, Ticket1[j].mobile_no);
                                        fprintf(ticket, "\n---------------------------------------------------------\n");
                                    }
                                }
                                fprintf(ticket, "\n\n=============================================================\n\n");
                                fprintf(ticket, "Total Fare : %.1f\n\n\n", price);
                                fprintf(ticket, "=============================================================\n");
                                printf("Your Bill:\n");
                                printf("=============================================================\n");
                                for (int j = 0; j < pass_no; j++)
                                {
                                    /*always put %s or %d before \(=continuation of code) unless while
                                    printing there will be an unwanted space. And put \n(=new line) after \ 
                                    unless there will be huge space before the things that needs to be 
                                    printed after \ */
                                    printf("Name : %s\nAge :%d\nFlight ID : %s\nClass : %s\nFare : %.1f\nSource : %s\
                                    \nDestination : %s\nDeparture time : %s\nArrival time : %s\
                                    \nDate of Boarding : %d/%d/%d\nMobile No.: %ld\n",
                                           Ticket[j].name, Ticket[j].age, Ticket[j].fl_id,
                                           Ticket[j].class, Ticket[j].conv_seat_price, Ticket[j].source, Ticket[j].destination,
                                           Ticket[j].departure, Ticket[j].arrival, Ticket[j].getDate.dd, Ticket[j].getDate.mm,
                                           Ticket[j].getDate.yyyy, Ticket[j].mobile_no);
                                    printf("\n---------------------------------------------------------\n");
                                }
                                if (Bool1)
                                {
                                    for (int j = 0; j < pass_no1; j++)
                                    {
                                        /*always put %s or %d before \(=continuation of code) unless while
                                        printing there will be an unwanted space. And put \n(=new line) after \ 
                                        unless there will be huge space before the things that needs to be 
                                        printed after \ */
                                        printf("Name : %s\nAge :%d\nFlight ID : %s\nClass : %s\nFare : %.1f\nSource : %s\
                                        \nDestination : %s\nDeparture time : %s\nArrival time : %s\
                                        \nDate of Boarding : %d/%d/%d\nMobile No.: %ld\n",
                                               Ticket1[j].name, Ticket1[j].age, Ticket1[j].fl_id,
                                               Ticket1[j].class, Ticket1[j].conv_seat_price, Ticket1[j].source, Ticket1[j].destination,
                                               Ticket1[j].departure, Ticket1[j].arrival, Ticket1[j].getDate.dd, Ticket1[j].getDate.mm,
                                               Ticket1[j].getDate.yyyy, Ticket1[j].mobile_no);
                                        printf("\n---------------------------------------------------------\n");
                                    }
                                }

                                printf("\n\n=============================================================\n\n");
                                printf("Total Fare : %.1f\n\n", price);
                                printf("=============================================================\n");
                                //free(Ticket);
                                printf("\n\n\t\t\t\tYOUR TICKET BOOKED SUCCESSFULLY !\n");
                                printf("\t\t\t\tHAPPY JOURNEY ! :)\n\n\n");
                                fprintf(fp_mod, "%s %s %s %d %d %.1f %d %d %.1f\n", F_details[i].FLight_id, F_details[i].Timing,
                                        F_details[i].Timing2, F_details[i].seats_available_e, F_details[i].total_seats_e, F_details[i].fare_economy,
                                        F_details[i].seats_available_b, F_details[i].total_seats_b, F_details[i].fare_business);
                                fclose(ticket);
                            }
                            //if we don't want to checkout then all data will be dumped without any change to the temporary
                            // file fp_mod.
                            else
                            {
                                //free(Ticket);
                                F_details[i].seats_available_e += eco_ctr;
                                F_details[i].seats_available_b += bus_ctr;
                                if (Bool1)
                                {
                                    F_details[i].seats_available_e += eco_ctr1;
                                    F_details[i].seats_available_b += bus_ctr1;
                                }

                                fprintf(fp_mod, "%s %s %s %d %d %.1f %d %d %.1f\n", F_details[i].FLight_id, F_details[i].Timing,
                                        F_details[i].Timing2, F_details[i].seats_available_e, F_details[i].total_seats_e, F_details[i].fare_economy,
                                        F_details[i].seats_available_b, F_details[i].total_seats_b, F_details[i].fare_business);
                                printf("Do you want to book again? y/n\n");
                                char Bool[1];
                                scanf("%s", Bool);
                                if (strcmp(Bool, "y") == 0)
                                {
                                    USER(fp_orig, fp_mod, ticket);
                                }
                                else
                                {
                                    printf("Thank you for booking ticket with us\n");
                                    printf("Hope to see you again! :)\n");
                                }
                                //continue;
                            }
                            //free(flight_line1);
                        }
                        else
                        {
                            fputs(fl_line[i].flt_line, fp_mod);
                            //free(flight_line1);
                        }
                    }
                    //free(fl_line);
                }
                else
                {
                    for (int i = 0; i < 6; i++)
                    {
                        fputs(fl_line[i].flt_line, fp_mod);
                    }
                    printf("Hope you enjoyed our booking service!\n");
                    printf("Hoping to meet you again...\n");
                    //continue;
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

int main()
{
    nextMessage();
    //initialising FILE pointers to open four files.
    FILE *fp_orig;
    FILE *fp_mod;
    FILE *ticket;
    FILE *user_admin;
    // start with searching facility provided by SEARCH() function.
    printf("Do you want to search for flights? 0/1 \n");
    int search_one;
    scanf("%d", &search_one);
    if (search_one)
    {
        fp_orig = fopen("/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/airline_database.txt", "r");
        //search function for searching flights.
        SEARCH(fp_orig);
    }
    // Here we use Ticket Booking facility using USER() function
    char tick_bool[1];
    int admin_bool;
    printf("DO YOU WANT TO BOOK TICKETS? y/n\n");
    scanf("%s", tick_bool);
    if (strcmp(tick_bool, "y") == 0)
    {
        user_admin = fopen("/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/user_admin_data.txt", "r");
        if (user_admin == NULL)
        {
            /* Unable to open file hence exit */
            printf("\nUnable to open user_admin_database.txt file.\n");
            printf("Please check whether file exists and you have write privilege.\n");
            exit(EXIT_FAILURE);
        }
        char buffer[50], user_admin_str[50];
        char q[20], n[20];
        printf("Login as USER\n");
        printf("USER-NAME: ");
        scanf("%s", q);
        printf("PASSWORD: ");
        scanf("%s", n);
        int t1 = 0, count;
        //here we are checking the user credentials are correct or not by comparing with our 
        //user_admin data base file.
        while (fgets(buffer, 50, user_admin) != NULL)
        {
            if (strcmp(buffer, "USER\n") == 0)
            {
                fscanf(user_admin, "%d", &count);
                for (int i = 0; i < count; i++)
                {
                    char *userid = malloc(sizeof(char) * 20);
                    char *passwd = malloc(sizeof(char) * 20);
                    fgets(user_admin_str, 50, user_admin);
                    sscanf(user_admin_str, "%s %s\n", userid, passwd);
                    if (strcmp(userid, q) == 0 && strcmp(passwd, n) == 0)
                    {
                        t1 = 1;
                        break;
                    }
                }
                break;
            }
        }
        if (t1)
        {
            //if matches then do the booking.
            fp_orig = fopen("/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/airline_database.txt", "r");
            fp_mod = fopen("/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/airline_database_mod.txt", "w");
            if (fp_orig == NULL)
            {
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
            printf("\n\t\t\t\t########################################################\n");
            printf("\t\t\t\t#################     Hooray!     #######################\n");
            printf("\t\t\t\t##########  WELCOME TO TICKET BOOKING SYSTEM  ###########\n");
            printf("\t\t\t\t#########################################################\n");
            USER(fp_orig, fp_mod, ticket);
            fclose(fp_mod);
            fclose(fp_orig);
            remove("/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/airline_database.txt");
            rename("/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/airline_database_mod.txt",
                   "/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/airline_database.txt");
        }
        else
        {
            printf("YOU HAVE INPUTTED INVALID USER CREDENTIALS\n");
        }
        fclose(user_admin);
    }
    //here we enjoy the privilege to edit the database using ADMIN()
    //But before we need to login to get into the system.
    printf("DO YOU WANT TO EDIT FLIGHT DETAILS? 0/1 \n");
    scanf("%d", &admin_bool);
    if (admin_bool)
    {
        user_admin = fopen("/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/user_admin_data.txt", "r");
        if (user_admin == NULL)
        {
            /* Unable to open file hence exit */
            printf("\nUnable to open user_admin_database.txt file.\n");
            printf("Please check whether file exists and you have write privilege.\n");
            exit(EXIT_FAILURE);
        }
        char buffer[50], user_admin_str[50];
        char s[20], m[20];
        printf("Login as ADMIN!\n");
        printf("ADMIN-NAME: ");
        scanf("%s", s);
        printf("PASSWORD: ");
        scanf("%s", m);
        int t = 0, count1;
        //here we are checking the admin credentials are correct or not by comparing with our 
        //user_admin data base file.
        while (fgets(buffer, 50, user_admin) != NULL)
        {
            if (strcmp(buffer, "ADMIN\n") == 0)
            {
                fscanf(user_admin, "%d", &count1);
                for (int i = 0; i < count1; i++)
                {
                    char *userid = malloc(sizeof(char) * 20);
                    char *passwd = malloc(sizeof(char) * 20);
                    fgets(user_admin_str, 50, user_admin);
                    sscanf(user_admin_str, "%s %s\n", userid, passwd);
                    if (strcmp(userid, s) == 0 && strcmp(passwd, m) == 0)
                    {
                        t = 1;
                        break;
                    }
                }
                break;
            }
        }
        if (t)
        {
            fp_orig = fopen("/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/airline_database.txt", "r");
            fp_mod = fopen("/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/airline_database_mod.txt", "w");
            printf("\n\t\t\t\t########################################################\n");
            printf("\t\t\t\t##################     Hi! Admin    #####################\n");
            printf("\t\t\t\t############  DAARK AIRLINES EDITING SYSTEM  ############\n");
            printf("\t\t\t\t#########################################################\n");
            ADMIN(fp_orig, fp_mod);
            fclose(fp_mod);
            fclose(fp_orig);
            remove("/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/airline_database.txt");
            rename("/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/airline_database_mod.txt",
                   "/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/airline_database.txt");
        }
        else
        {
            printf("YOU HAVE INPUTTED INVALID ADMIN CREDENTIALS\n");
        }
        fclose(user_admin);
    }
}