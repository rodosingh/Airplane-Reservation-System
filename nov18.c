#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    //FILE * fp_orig = fopen("/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/airline_database.txt", "r");
    //FILE * fp_mod = fopen("/mnt/03aac6ab-de5b-4f92-8b47-5e62ac811a34/9th SEM/CS3101_C_&_DS/C_and_DS/Airplane-Reservation-System/airline_database_mod.txt", "w");
    
    struct NameTable
    {
        char* name;
    }nameTable;
    char buffer[50];

    /*while (fgets(buffer, 50, fp_orig) != NULL)
    {
        fputs(buffer, fp_mod);
    }*/
    char* buf = "ertyo";

    //buf[6] = '\0';
    char qq[4],q1[4],q2[4];
    int q3;
    char ch[] = "adi:to:five 12";
    //nameTable.name = ch;
    //printf("nametable = %s\n", nameTable.name);
    sscanf(ch, "%s:%s:%s %d", qq, q1, q2, &q3);
    printf("%s\n%s\n%d\n", qq, q2, q3);
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
    
    return 0;
}
    