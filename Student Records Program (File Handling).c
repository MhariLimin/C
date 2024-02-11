#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <windows.h>


int main()
{

 do
{
    int select;
    int limit = 4;
    int counter = 1;
    int index = 1;
    int length = 0;
    int idnum = 0;
    char stud_name[100];
    char studname[100];
    char line_read[150];
    char space[] = "\t";
    char option[6];
    char* pos;
    float Mgrade = 0;
    float Sgrade = 0;
    float Egrade = 0;
    float mgrade = 0;
    float sgrade = 0;
    float egrade = 0;
    float new_math = 0;
    float new_science = 0;
    float new_english = 0;
    // declared the variables inside the loop for them to reset every cycle

    FILE* records;
        //main menu layout
        printf("\n                    ------------------------------------------------------------------");
    printf("\n                                Welcome to the Student Grade Management System \n");
        printf("                    ------------------------------------------------------------------\n");
        printf("                                              -Main Menu- \n");
        printf("\n                                       [1]     Add Student \n");
        printf("                                       [2]     Open Records \n");
        printf("                                       [3]     Edit Records \n");
        printf("                                       [4]     Delete Record \n");
        printf("                                       [0]     Exit Program  \n");
        printf("                    ------------------------------------------------------------------\n");

        printf("Enter the number corresponding to the type of service you want: ");
        scanf("%d", &select);


        if (select == 0)
        {
            printf("Thank you for using the system!");
            exit(0);
        }
        else if (select > limit || select < 1)
        {
            printf("\nInvalid input! Please enter the correct input from the Main menu\n");
        }
        else if (select == 1)
        {
            records = fopen("Student-Record.txt", "a");
            if (records == NULL)
            {
                printf("ERROR: File not found");
                exit(1);
            }

            //if file is empty, create header
            fseek(records, 0, SEEK_END);

            if (ftell(records) == 0)
            {
                char header[] = "Id #                  Name            Math Grade            Science Grade            English Grade";

                fprintf(records, "%s", header);
            }
            if (ftell(records) > 1)
              {
                printf("Please enter student name: ");
                gets(stud_name);
                fgets(stud_name, sizeof(stud_name) - 1, stdin);

            // remove trailing newline from input
            if ( (pos = strchr(stud_name, '\n')) != NULL)
            {
                *pos = '\0';
            }
            else
            {
                printf("Error! Terminating Program (6)");
                exit(1);
            }

        printf("Please enter the student's grade in Math: ");
        scanf("%f", &Mgrade);


        printf("Please enter the student's grade in Science: ");
        scanf("%f", &Sgrade);


        printf("Please enter the student's grade in English: ");
        scanf("%f", &Egrade);
        getchar();

        //to get random id# or LRN
        srand(time(NULL));
        int idnum = (rand()*999);

            printf("Confirm addition of student?\nName: '");
            fputs(stud_name, stdout);

            printf("'\n|Yes/No| >> ");
            fgets(option, sizeof(option), stdin);

            char no1[] = "n\n", no2[] = "no\n", yes1[] = "y\n", yes2[] = "yes\n";

            // convert input to lowercase to simplify comparison
            for (size_t i = 0; i < sizeof(option); i++)
            {
                option[i] = tolower(option[i]);
            }

            // compare with list of strings
            if (strcmp(option, no1) == 0 || strcmp(option, no2) == 0)         // decline
            {
                printf("Returning to Main menu..\n");
            }
            else if (strcmp(option, yes1) == 0 || strcmp(option, yes2) == 0)  // accept
            {

            int printrec = fprintf(records, "\n%d\t %s\t %.1f\t %.1f\t %.1f\t", idnum, stud_name, Mgrade, Sgrade, Egrade);

                if (printrec < 0)
                {
                    printf("ERROR: There was a problem in adding the student in the system, Terminating program..");
                    exit(1);
                }
                else
                {
                    printf("\nStudent added successfully, returning to Main Menu.... \n\n");
                    fclose(records);
                }
            }
            else
            {
                printf("Invalid Input! Returning to Main menu ↵\n\n");
            }
           }
        }

        else if (select == 2)
        {
             records = fopen("Student-Record.txt", "r");
             if (records == NULL)
             {
                printf("ERROR: There is no existing record. Please add an entry first..");
                continue;
             }

             // throw away the file header
             fgets(line_read, sizeof(line_read) - 1, records);

             // screen header
             printf("-------------------------------------------------------------------------------------------------------------\n");
             printf("Entry #          Id #               Name                    Math Grade       Science Grade     English Grade\n");
             printf("-------------------------------------------------------------------------------------------------------------\n");

             while(feof(records) == 0)
             {
             fgets(line_read, sizeof(line_read) - 1, records);
             sscanf(line_read, "%d %[^\t] %f %f %f %[^\n]", &idnum, studname, &mgrade, &sgrade, &egrade);

             // name adjustments for it to print nicely
             length = strlen(studname);

             if (length >= 8 && length < 16)
             {
                strcpy(stud_name, studname);
                strcat(stud_name, space);
             }
             else if (length > 4 && length < 8)
             {
                strcpy(stud_name, studname);
                strcat(stud_name, space);
                strcat(stud_name, space);
             }
             else
             {
                strcpy(stud_name, studname);
             }
             printf("%02d. \t\t %d\t %s\t      %.1f\t\t %.1f\t\t   %.1f\n", counter,idnum, stud_name, mgrade, sgrade, egrade);
             counter++;
             }
            fclose(records);
        }

        else if (select ==3)
        {
            records = fopen("Student-Record.txt", "r");
            if (records == NULL)
            {
                printf("ERROR: There is no existing record. Please add an entry first..");
                continue;
            }

            fgets(line_read, sizeof(line_read) - 1, records);

            //declare array counter
            while(feof(records) == 0)
            {
               fgets(line_read, sizeof(line_read) - 1, records);
               counter++;
            }
               fclose(records);


            // get the index number
            printf("Select the entry # of the student you want to edit: ");
            scanf("%d", &index);

            // subtracted index by one to the get array index
            index--;

            int id_mem[counter+1];
            char stud_mem[counter + 1][100];
            float mgrade_mem[counter + 1];
            float sgrade_mem[counter + 1];
            float egrade_mem[counter + 1];

            records = fopen("Student-Record.txt", "r");

            //dispose header
            fgets(line_read, sizeof(line_read) - 1, records);

            //scan the file and save them to array
            for (size_t i = 0; feof(records) == 0; i++)
            {
            fgets(line_read, sizeof(line_read) - 1, records);
            sscanf(line_read, "%d %[^\t] %f %f %f %[^\n]", &id_mem[i], stud_mem[i], &mgrade_mem[i], &sgrade_mem[i], &egrade_mem[i]);
            }

            printf("Current selected student: %s\n", stud_mem[index]);
            printf("Please enter new grade for Math: ");
            scanf("%f", &new_math);

            printf("Please enter new grade for Science: ");
            scanf("%f", &new_science);

            printf("Please enter new grade for English: ");
            scanf("%f", &new_english);
            getchar();

            //change grade for the selected student
            mgrade_mem[index] = new_math;
            sgrade_mem[index] = new_science;
            egrade_mem[index] = new_english;

                // rewrite the file with modification
                fclose(records);

                records = fopen("Student-Record.txt", "w");

                // print header again
                fprintf(records, "Id #                  Name            Math Grade            Science Grade            English Grade\n");

                for (size_t i = 0; i < counter - 1; i++)
                {
                    if (i == counter - 2)
                    {
                        fprintf(records, "%d\t %s\t %.1f\t %.1f\t %.1f\t", id_mem[i], stud_mem[i], mgrade_mem[i], sgrade_mem[i], egrade_mem[i]);
                    }
                    else
                    {
                        fprintf(records, "%d\t %s\t %.1f\t %.1f\t %.1f\n", id_mem[i], stud_mem[i], mgrade_mem[i], sgrade_mem[i], egrade_mem[i]);
                    }
                }

                printf("Modification has been recorded, returning to Main menu.... \n\n");
                fclose(records);
        }

        else if(select == 4)
        {
            records = fopen("Student-Record.txt", "r");
            if (records == NULL)
            {
                printf("ERROR: There is no existing record. Please add an entry first..");
                continue;
            }

            fgets(line_read, sizeof(line_read) - 1, records);

            //declare array counter
            while(feof(records) == 0)
            {
              fgets(line_read, sizeof(line_read) - 1, records);
              counter++;
            }
              fclose(records);


            // get the index number
            printf("Select the entry # of the student you want to delete: ");
            scanf("%d", &index);
            getchar();


            // subtracted index by one to get the array index
            index--;

            int id_mem[counter+1];
            char stud_mem[counter + 1][100];
            float mgrade_mem[counter + 1];
            float sgrade_mem[counter + 1];
            float egrade_mem[counter + 1];

            records = fopen("Student-Record.txt", "r");

            //dispose header
            fgets(line_read, sizeof(line_read) - 1, records);

            //scan the file and save them to array
            for (size_t i = 0; feof(records) == 0; i++)
            {
            fgets(line_read, sizeof(line_read) - 1, records);
            sscanf(line_read, "%d %[^\t] %f %f %f %[^\n]", &id_mem[i], stud_mem[i], &mgrade_mem[i], &sgrade_mem[i], &egrade_mem[i]);
            }

            printf("Selected student entry for deletion: '%s'\n", stud_mem[index]);
            printf("Are you sure you want to delete this student entry? \n");
            printf(" |Yes/No| >> ");
            fgets(option, sizeof(option), stdin);

            char no1[] = "n\n", no2[] = "no\n", yes1[] = "y\n", yes2[] = "yes\n";

            // convert input to lowercase to simplify comparison
            for (size_t i = 0; i < sizeof(option); i++)
            {
                option[i] = tolower(option[i]);
            }

            // compare with list of strings
            if (strcmp(option, no1) == 0 || strcmp(option, no2) == 0)         // decline
            {
                printf("Returning to Main menu..\n");
            }
            else if (strcmp(option, yes1) == 0 || strcmp(option, yes2) == 0)  // accept
            {
                // rewrite the file after deletion acceptance
                fclose(records);
                records = fopen("Student-Record.txt", "w");

                // reprinting the header
                fprintf(records, "Id #                  Name            Math Grade            Science Grade            English Grade");

                // print remaining lines
                for (size_t i = 0; i < counter - 1; i++)
                {
                    if (i == index)
                    {
                        continue;
                    }
                    else
                    {
                        fprintf(records, "\n%d\t %s\t %.1f\t %.1f\t %.1f", id_mem[i], stud_mem[i], mgrade_mem[i], sgrade_mem[i], egrade_mem[i]);
                    }
                }

                printf("Student entry has been successfully deleted, returning to Main menu.. \n\n");
                fclose(records);

            }
            else
            {
                printf("Invalid Input! Returning to Main menu..\n\n");
            }

        }

        else
        {
            printf("\nInvalid input! Please enter the correct input from the Main menu.\n");
        }
   }while (1 == 1);
}

