#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct NameTable
    {
        char* name;
    }nameTable;
    char buffer[100];

    /*while (fgets(buffer, 50, fp_orig) != NULL)
    {
        fputs(buffer, fp_mod);
    }*/
    char* buf = "ertyo";

    //buf[6] = '\0';
    char qq[4],q1[4],q2[4];
    int q3;
    char ch[] = "adi to five 12";
    //int uu = 0;
int code_airport(char* station)
{
    //printf("address = %u", station);
    if (strcmp(station, "New Delhi"))
    {
        return 10;
    }
    else if (strcmp(station, "Mumbai"))
    {
        return 10;
    }
    else if (strcmp(station, "Kolkata"))
    {
        return 10;
    }
    else if (strcmp(station, "Chennai"))
    {
        return 10;
    }
    else if(strcmp(station, "Hyderabad"))
    {
        return 10;
    }
    else
    {
        return 404;
    }
}
int airport_valid(char* airplane_name)
{
    char ports[5][50] = {"New Delhi", "Mumbai", "Kolkata", "Chennai", "Hyderabad"};
    int ctr = 0;
    for (int i = 0; i < 5; i++)
    {
        //printf("Ports = %s\n", ports[i]);
        if (strcmp(airplane_name, ports[i]) == 0)
        {
            //printf("any prob = %d\n", ctr);
            ctr = 1;
        }
        
    }
    return ctr;
}

int main(){
    char buffer[100], timb[] = "ertig";
    /*FILE * fp_orig = fopen("/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/airline_database.txt", "r");
    FILE * fp_mod = fopen("/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/airline_database_mod.txt", "w");
    
    while (fgets(buffer, 100, fp_orig) != NULL)
    {
        if(strcmp(buffer, "Monday\n") == 0)
        {
            printf("Hurrraya\n");
        }
        fputs(buffer, fp_mod);
    }
    //nameTable.name = ch;
    //printf("nametable = %s\n", nameTable.name);
    //sscanf(ch, "%s %s %s %d", qq, q1, q2, &q3);
    //printf("%s\n%s\n%d\n", qq, q2, q3);
    //scanf("%s", ch);
    //ch[6] = '\0';
    /*if (strcmp(ch, "ertyo")==0)
    {
        printf("rodo harami\n");
        printf("size  = %lu\n",sizeof(buf));
        printf("buf = %s\n",buf);
        printf("ch = %s\n", ch);
    }
    else
    {
        printf("Hum bade adaami\n");
        printf("ch = %s\n", ch);
    }*/
    /*char oo[5];
    for (int i = 0; i < 5; i++)
    {
        scanf("%s",oo);
        printf("Print the ul : %s\n", oo);
        //uk = 4;
    }*/
    /*char* p = malloc(strlen(buffer)*sizeof(char));
    p = buffer;
    p[strlen(p)-1] = '\0';*/
    char board[] = "New Delhi", dest[] = "Mumba";
    if (!(airport_valid(board) && airport_valid(dest)))
    {
        printf("Please enter a valid airport name!:|\n");
        //main(app_mode);
    }
    char num[] = "1234\n", nume[100], *cpy;
    int kal;
    printf("enter name = \n");
    //scanf("%s",nume);
    char sed[] = "New Delhi", sed1[] = "Mumbai";
    sprintf(nume, "%s to %s\n", sed, sed1);
    printf("Nume = %s\n",nume);
    //printf("num = %s, nume = %s\n", num, nume);
    sscanf(num, "%d", &kal);
    printf("Kal = %d\n", (kal*100+kal));
    printf("Print the ul : %s\n", num);
    char airp[] = "Mumbai";
    airp[6] = '\0';
    printf("Airport = %s\n", airp);
    char s[1];
    scanf("%s", s);
    if (strcmp(s, "s")==0)
    {
        printf("s = %s\n", s);
    }
    for(int i = 0; i<5; i++)
    {
        for(int j = 0; j < 5; j++)
        {
            if (j == 1 || j== 3 || j==4)
            {
                continue;
            }
            printf("%d, %d\n", i, j);
        }
        if (i  == 2)
        {
            continue;
        }
    }
    if (strcmp(nume, airp)==0)
    {
        printf("Aa gaye hum\n!");
    }
    //main(uk);
    return 0;
}
    