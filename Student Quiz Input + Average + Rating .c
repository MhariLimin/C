//header files
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

//max number of students
#define MAX 100

typedef struct records //Structure data for student records
{
   char NAME[31];
   int G1;
   int G2;
   int G3;
} REC;
typedef struct list //List of structures
{
   REC entry[MAX];
   int last;
} LIST;

//Global declarations
LIST L;
float ave;

//function preprocessors
void makenull(); //resets the last value of the list
void insert(char n[31], int q1, int q2, int q3); //function for data transfer to structure
int isfull(); //function for checking if the list is full
int isempty(); //function for checking if the list is empty
int pos(char n[31]); //compares the inputted string if it's smaller than the string value in the array
void update (char n[31]); //updates the grade data of the selected string name
char locate(char n[31]); //locates the inputted data them compares it to the list
void del(char n[31]); //deletes the data of the inputted name of the user
float average(int x, int y, int z); //function for defining the process of getting the data average
void display(); //display the whole list as well as computing for data average and remarks
int menu(); //function for menu display and input
void save(); //function for saving the data from the list to the database file
void retrieve(); //function for retrieving past list data from the database file


int main()
{
  //local declarations
  char n[31];
  int option,q1,q2,q3,i;
  makenull(); //resets last value of list
  retrieve(); //populatate the list with the data from the file

  while(1) //infinite loop as long as true
  {
    option = menu(); //recall menu function for menu display
    switch(option) // case for menu input
    {
      case 1 :
          system("cls");
          printf("\n\t\t\t\t\t\t INSERT STUDENT DATA\n");
          printf("\t\t\t\t\t_____________________________________\n");
          printf("\n\t\t\t\t\t\t Input name: ");
          scanf("%s", n);

   /*       if (locate(n) >=0)
          {
              printf("\nDuplicate Record.\n");
              system("Pause");
          }
          else
          {*/

          printf("\n\t\t\t\t\t\t Input grade 1: ");
          scanf("%d", &q1);

          printf("\n\t\t\t\t\t\t Input grade 2: ");
          scanf("%d", &q2);

          printf("\n\t\t\t\t\t\t Input grade 3: ");
          scanf("%d", &q3);


          insert(n, q1, q2, q3); //converts the local variables to structure array variables

          break;

      case 2 :
          system ("cls");
          display();//displays the list for user's reference in deletion
          printf("\n\t\t\t\t\t\t UPDATE STUDENT DATA\n");
          printf("\t\t\t\t\t_____________________________________\n");
          printf("\n\t\t\t\t\t\t Input name: ");
          scanf(" %s",n);
          update(n);//copies the whole list except the name entered and decrements the last value
          save(); //save the list in the database file before terminating the program
          break;

      case 3 :
          system ("cls");
          display();//displays the list for user's reference in deletion
          printf("\n\t\t\t\t\t\t DELETE STUDENT DATA\n");
          printf("\t\t\t\t\t_____________________________________\n");
          printf("\n\t\t\t\t\t\t Input name: ");
          scanf(" %s",n);
          del(n);//copies the whole list except the name entered and decrements the last value
          break;

      case 4 : display();getch();break; //display case function
      case 5 : save(); //save the list in the database file before terminating the program
               printf("\n\n\t\t\t\t\t Thank you for using the program!");
               exit(0);
      default: printf("Number not found! Please pick from 1-4 only!");
               getch();


    }


  }
}


void makenull() //resets the last value of the list
{
    L.last = -1;
}

void insert(char n[31], int q1, int q2, int q3) //function for data transfer to structure
{
    int i,p;
  if (isfull()) //informs the user if the list is already full
  {
    printf("List is full");
    getch();
  }
  else
  {
      if(locate(n)>=0) //locates and inform the user if there is a duplicated name entry
      {
          printf("\nDuplicate Record Found.\n");
          system("pause");
      }
      else
      {
         p = pos(n); //pass the value of the pos function to a local integer variable
      for (i=L.last; i>=p;i--) // loop for sorting the entry alphabetically
      {
          strcpy(L.entry[i+1].NAME, L.entry[i].NAME);
          L.entry[i+1].G1 = L.entry[i].G1;
          L.entry[i+1].G2 = L.entry[i].G2;
          L.entry[i+1].G3 = L.entry[i].G3;
      }
      //assigning of data in the array
      strcpy(L.entry[p].NAME, n); //copy the string data from n to the structure array variable
      L.entry[p].G1 = q1; //copy the integer value of q1,q2,and q3 to their respective structure array variables
      L.entry[p].G2 = q2;
      L.entry[p].G3 = q3;

      L.last++;

  }
}
}

int isfull() //function for checking if the list is full
{
    return(L.last == MAX-1);
}

int isempty()//function for checking if the list is empty
{
    return(L.last == -1);
}

char locate (char n[31]) //locates the inputted data them compares it to the list
{
    for(int i=0;i<=L.last;i++) //loop for locating the input from the list
    {


        if(strcmp(L.entry[i].NAME, n) == 0) //compare if the string inputted by the user is the same as the one on the loop
        {
        return(i);
        }
    }
    return(-1);
}

int pos(char n[31]) //compares the inputted string if it's smaller than the string value in the array
{
    int i;
    for(i=0;i<=L.last;i++) //loop for comparing if the input name is lower or before the array name data
    {
        if(strcmp(L.entry[i].NAME,n)>0)
        {
            return(i);
        }
    }
    return(i);
}

void update (char n[31]) //deletes the data of the inputted name of the user
{
 int i,m;
 int q1,q2,q3;
    if (isempty())//informs the user when the list is empty
    {
       printf("List is empty.");
       getch();
    }
    else
    {
       m = locate(n); //passes the value of locate to the local variable m

       if (m<0)
        {
          printf("Not found.");
          getch();
        }
       else
        {
            printf("Input updated Quiz 1: ");
            scanf("%d", &q1);

            printf("Input updated Quiz 2: ");
            scanf("%d", &q2);

            printf("Input updated Quiz 3: ");
            scanf("%d", &q3);

            i=m;

                L.entry[i].G1 = q1;
                L.entry[i].G2 = q2;
                L.entry[i].G3 = q3;

        }
    }
}


void del (char n[31]) //deletes the data of the inputted name of the user
{
 int i,m;
    if (isempty())//informs the user when the list is empty
    {
       printf("List is empty.");
       getch();
    }
    else
    {
       m = locate(n); //passes the value of locate to the local variable m

       if (m<0)
        {
          printf("Not found.");
          getch();
        }
       else
        {
           for (i=m;i<=L.last;i++) //loop for recopying of the list except for the inputted name
           {
               //copy values and decrements L.last value
                strcpy(L.entry[i].NAME, L.entry[i+1].NAME);
                L.entry[i].G1 = L.entry[i+1].G1;
                L.entry[i].G2 = L.entry[i+1].G2;
                L.entry[i].G3 = L.entry[i+1].G3;
           }
            L.last--; //deletes the last empty element in the structure
        }
    }
}

float average(int x, int y, int z) //function for defining the process of getting the data average
{
    return ((x+y+z)/3.0);
}
void display() //display the whole list as well as computing for data average and remarks
{
    int i;
    system("cls");
    printf("\n\t\t\t\t\t\t DATABASE LIST\n");
    printf("\t\t____________________________________________________________________________________\n\n");
    printf("\t\t  NAME OF STUDENT         QUIZ #1    QUIZ #2    QUIZ #3      AVERAGE        REMARKS    \n");
    printf("\t\t____________________________________________________________________________________\n");
    for (i=0;i<=L.last;i++) //loop for displaying the values of the structure array variables as well as computing individual average
        {

        printf("\n\t\t  %d.) %-5s                 %d         %d         %d         %6.2f         ", i+1,L.entry[i].NAME,L.entry[i].G1,L.entry[i].G2,L.entry[i].G3,ave = average(L.entry[i].G1,L.entry[i].G2,L.entry[i].G3));

           if (ave>=75.0) //conditional statement to compute for the remarks
            {
            printf("Passed\n");
            }
           else
            printf("Failed\n");
        }
}

int menu() //function for menu display and input
{
    int i, optn;
    char *men[] = {"Insert", "Update", "Delete", "Display", "Exit"};
    system ("cls");
    printf("\n\t\t\t\t\t\t STUDENT RECORD\n");
    printf("\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");

    for (i=0;i<5;i++)
        printf("\t\t\t\t\t   %d.) %s\n",i+1,men[i]);//layout of menu display
        printf("\t\t\t\t\t_________________________________\n");
        printf("\n\t\t\t\t\t Please Select (1-4): ");
        scanf("%d", &optn);

    return(optn);
}

void save() //function for saving the data from the list to the database file
{
    FILE *hs;
    int i;
    hs = fopen("Crecord.dbf", "w+");
    if (hs==NULL)
    {
        printf("File Error.\n");
        system("pause");
    }
    else
    {
    for(i=0;i<=L.last;i++)
        {
        fprintf(hs,"%s %d %d %d\n",L.entry[i].NAME,L.entry[i].G1,L.entry[i].G2,L.entry[i].G3); //copies the entries from list to the database file
        }
    fclose(hs);
    }
}

void retrieve() //function for retrieving past list data from the database file
{
    char n[31];
    int q1,q2,q3;

    FILE *hs;
    if((hs = fopen("Crecord.dbf", "r+")) !=NULL) //if file does not exist, creates a new file for storing and retrieving data

        while(!feof(hs))
        {
            fscanf(hs,"%s %d %d %d\n",n, &q1, &q2, &q3);
            insert(n,q1,q2,q3);
        }

    fclose(hs);

}
