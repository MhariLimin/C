//header files
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>

//max number student characters
#define MAX 100

typedef struct records //Structure data for student records
{
   int id_num;
   char LASTNAME[MAX];
   char FIRSTNAME[MAX];
   int G1;
   int G2;
   int G3;
   struct records* next;
} REC;

REC *R;

//function preprocessors
void makenull(); //resets the last value of the list
int menu(); //function for menu display and input
void insert(char ln[MAX], char fn[MAX], int idnum, int q1, int q2, int q3);
void update(int idnum); //function for data transfer to structure
int locate(int idnum); //function for student id number
int IDGen(); //locates the inputted data them compares it to the list
void sort();//function for sorting the list by surname
void del(int idnum); //deletes the data of the inputted name of the user
void display(); //display the whole list as well as computing for data average and remarks
void save(); //function for saving the data from the list to the database file
void retrieve(); //function for retrieving past list data from the database file


int main()
{
  //local declarations
  char ln[MAX], fn[MAX];
  int option,q1,q2,q3,i, idnum;
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

          idnum = IDGen();
            if(locate(idnum) > 0)
            {
                printf("Duplicate ID Found.");
                break;
            }
            else
            {
          printf("\n\t\t\t\t\t\t Input surname: ");
          scanf(" %[^\n]s", ln);

          printf("\n\t\t\t\t\t\t Input first name: ");
          scanf(" %[^\n]s", fn);

          printf("\n\t\t\t\t\t\t Input grade 1: ");
          scanf("%d", &q1);

          printf("\n\t\t\t\t\t\t Input grade 2: ");
          scanf("%d", &q2);

          printf("\n\t\t\t\t\t\t Input grade 3: ");
          scanf("%d", &q3);

          printf("\n\t\t\t\t   Grade Data for %s has been recorded successfully", ln);
          printf("\n\t\t\t\t        Your designated ID# in the system is %d\n\t\t\t\t\t     ", idnum);
          system("pause");


          insert(ln, fn, idnum, q1, q2, q3);
          sort(); //call sort function to sort data by surname
            }
          break;

      case 2:
        system ("cls");
          display();//displays the list for user's reference in updating
          printf("\n\n\t\t\t\t\t\t UPDATE STUDENT DATA\n");
          printf("\t\t\t\t\t_____________________________________\n");
              if(R==NULL)
                {
                   printf("\n\t\t\t\t\t\tThe list is empty.\n\t\t\t\t\t    ");
                   system("pause");
                }
              else
                {
                   printf("\n\t\t\t\t Input student ID number you want to update: ");
                   scanf(" %d",&idnum);
                   update(idnum);
                   sort();
                }//copies the whole list except the idnumber entered for updating
          break;

      case 3 :
          system ("cls");
          display();//displays the list for user's reference in deletion
          printf("\n\n\t\t\t\t\t\t DELETE STUDENT DATA\n");
          printf("\t\t\t\t\t_____________________________________\n");
          if(R==NULL)
                {
                   printf("\n\t\t\t\t\t\tThe list is empty.\n\t\t\t\t\t    ");
                   system("pause");
                }
              else
              {
                   printf("\n\t\t\t\t Input student ID number you want to delete: ");
                   scanf(" %d",&idnum);
                   del(idnum);//copies the whole list except the idnumber entered for deletion
              }
          break;

      case 4 : display();
              if(R==NULL)
                {
                   printf("\n\t\t\t\t\t\tThe list is empty.\n\t\t\t\t\t    ");
                }
               getch();
               break;
      case 5 : save(); //save the list in the text file before terminating the program
               printf("\n\n\t\t\t\t\t Thank you for using the program!");
               exit(0);
      default: printf("Number not found! Please pick from 1-5 only!");
               getch();


    }
  }
}

void makenull()
{
    R = NULL;
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
        printf("\n\t\t\t\t\t Please Select (1-5): ");
        scanf("%d", &optn);

    return(optn);
}

void insert(char ln[MAX], char fn[MAX], int idnum, int q1, int q2, int q3)
{
    REC *p, *q, *temp;
    p=q=R;

    temp = (REC*) ((malloc(sizeof(REC))));
    strcpy (temp->LASTNAME, ln);
    strcpy (temp->FIRSTNAME, fn);
    temp->id_num = idnum;
    temp->G1 = q1;
    temp->G2 = q2;
    temp->G3 = q3;

    while (p!=NULL)
        {
           q=p;
           p=p->next;
        }
    if (p==R)
        R=temp;
    else
        q->next = temp;
    temp->next = p;

}
void update(int idnum) //updates the data of the inputted id of the user
{
    REC *p, *q;
    p=q=R;//Linking new nodes
        while(p!=NULL && p->id_num!=idnum){//Loop to find the data the user wants to update
            q=p;
            p=p->next;
        }
        if(p==NULL) //checks if the id number generated can be really found in the list
        {
            printf("ID number not found.\n");
            system("pause");
        }
        else //proceeds to default update function if there is no matching id number in the list
        {
            printf("\n\t\t\t\t Input new surname: ");
            scanf(" %[^\n]s", p->LASTNAME);
            printf("\n\t\t\t\t Input new first name: ");
            scanf(" %[^\n]s", p->FIRSTNAME);
            printf("\n\t\t\t\t Input new Quiz 1 score:  ");
            scanf("%d", &p->G1);
            printf("\n\t\t\t\t Input new Quiz 2 score:  ");
            scanf("%d", &p->G2);
            printf("\n\t\t\t\t Input new Quiz 3 score:  ");
            scanf("%d", &p->G3);

            printf("\n\t\tList was updated successfully..\n");
            system("pause");
        }
    }

int locate(int idnum)
{
    REC *fr, *md, *loc;
    loc=R;
    while(loc!=NULL && loc->id_num!=idnum)//Loop to find if there is a matching id number
        {
            md=loc;
            loc=loc->next;//redirect to the next node
        }
    if(loc==NULL) //checks if the id number generated can be really found in the list
        {
            return (-1);
        }
    else
        {
            return (1);
        }
}

int IDGen() //function for producing a unique student id
{
    int ID;
    int lowest = 1000;
    int highest = 9999;

    srand(time(NULL)); //initialize for the id to be random every run

    ID = (rand() % (highest - lowest + 1)) + lowest; //calculates the random ID to be generated
    return (ID);

}

void sort()
{
    REC *a, *b;
    char templn[MAX], tempfn[MAX];
    int tempid, tempq1, tempq2, tempq3;

    b=R;

    while(b!=NULL) //Loop to reach the end of the list using node b
        {
            a=b->next;
             while(a!=NULL) //Loop to reach the end of the list using node a
              {
                if(strcmp(b->LASTNAME, a->LASTNAME)>0)//compare the strings to check if the data stored in a->LASTNAME is greater than b->LASTNAME
                  {
                    tempid = b->id_num;
                    b->id_num = a->id_num;
                    a->id_num = tempid;

                    strcpy(templn, b->LASTNAME);
                    strcpy(b->LASTNAME, a->LASTNAME);
                    strcpy(a->LASTNAME, templn);

                    strcpy(tempfn, b->FIRSTNAME);
                    strcpy(b->FIRSTNAME, a->FIRSTNAME);
                    strcpy(a->FIRSTNAME, tempfn);

                    tempq1 = b->G1;
                    b->G1 = a->G1;
                    a->G1 = tempq1;

                    tempq2 = b->G2;
                    b->G2 = a->G2;
                    a->G2 = tempq2;

                    tempq3 = b->G3;
                    b->G3 = a->G3;
                    a->G3 = tempq3;
                  }

                a=a->next;//redirect to the next node
              }
            b=b->next;//redirect to the next node
       }
}

void del (int idnum) //deletes the data of the inputted id of the user
{
    REC *p, *q;
    p=q=R;
    while(p!=NULL && p->id_num!=idnum) //Loop to find the data the user wants to delete
        {
          q=p;
          p=p->next;
        }
    if(p==NULL) //checks if the id number generated can be really found in the list
        {
          printf("\n\t\t\t\t Student ID# not found..\n\t\t\t\t ");
          system("pause");
        }
    else
        {
            if(p==R){//If the element is the first element
                R=p->next;
                }
            else{//If the element is not the first element
                q->next = p->next;
                }
            free(p);
            printf("\n\t\t\t   Selected student has been successfully removed from the list..\n\t\t\t   ");
            system("pause");
         }
}

void display() //display the whole list as well as computing for data average and remarks
{
    REC *dis;
    int i=0;
    float ave;

    dis=R;
    system("cls");
    printf("\n\t\t\t\t\t\t    DATABASE LIST\n");
    printf("\t_______________________________________________________________________________________________________________\n\n");
    printf("\t       ID#             NAME OF STUDENT            QUIZ #1    QUIZ #2    QUIZ #3      AVERAGE        REMARKS    \n");
    printf("\t_______________________________________________________________________________________________________________\n");



    while (dis!=NULL)
     {
        ave = (float)(dis->G1+dis->G2+dis->G3)/3; //Computes the aveage of the student
        printf("\n\t %d) TUPM-20-%-11d%s, %s\t%7d    %7d      %5d         %0.2f         %s\n", i+1, dis->id_num, dis->LASTNAME, dis->FIRSTNAME, dis->G1, dis->G2, dis->G3, ave, ave>=75.0 ? "Passed":"Failed");//Displays the content of the linked lists and adding the average and remakrs of the student
        dis = dis->next;//redirect to the next node
        i++;
     }
}

void save(){
    REC *s;
    s=R;
    FILE *fp;
    fp = fopen("List.txt","w+");
    while(s!=NULL)
        {
            fprintf(fp, "%d %s\t%s\t%d %d %d\n",s->id_num, s->LASTNAME, s->FIRSTNAME, s->G1, s->G2, s->G3);
            s = s->next;
        }
    fclose(fp);
}

void retrieve()
{
    REC *s;
    s=R;
    int tempid, tempq1, tempq2, tempq3;
    char templn[MAX], tempfn[MAX];
    FILE *fp;
    fp = fopen("List.txt", "r");
    if(fp==NULL){//checks if file does not exist
        return;
    }
    else //proceeds if it exists
        {
        while(fscanf(fp, "%d %[^\t] %[^\t] %d %d %d\n", &tempid, templn, tempfn, &tempq1, &tempq2, &tempq3)!= EOF) //scans and stores them in local variables
            {
            s = (REC *)malloc(sizeof(struct records));//Allocates memory for the temporary node
            s->id_num = tempid;

                strcpy(s->LASTNAME, templn);
                strcpy(s->FIRSTNAME, tempfn);
                s->G1 = tempq1;
                s->G2 = tempq2;
                s->G3 = tempq3;
                insert(templn, tempfn, tempid, tempq1, tempq2, tempq3);//Calls the insert function to store and record contents in the linked list
                sort(); //call sort function to sort data by surname
                s=s->next;//redirect to the next node

        }

    }
    fclose(fp);
}
