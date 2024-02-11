//header files
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#define LP 7
#define TP 3
#define RP 100

//max number of students
#define MAX 100

typedef struct records //Structure for the Voter's data
{
    char NAME[MAX];
    int age;
    int day;
    int month;
    int year;
    int randid;
    char course[MAX];
    char section[MAX];
    char nationality[MAX];

}REG;



typedef struct reg //Structure data for student records
{
   int id;
   char pass[MAX];

} REC;

typedef struct candidates{ // Structure for the Candidate's data
    char CandName[31];
    int PVoteCount;
    int VPVoteCount;
    int SecVoteCount;
    char Pres[MAX];
    char VPres[MAX];
    char Secre[MAX];

}CAND;

typedef struct list //List of structures and for how many candidates there are
{
   REC entry[MAX];
   REG info[MAX];
   CAND cands[MAX];
   int last;
   int PCount;
   int VPCount;
   int SecCount;
} LIST;

//Global declarations
LIST L;

//function preprocessors

//Design & Main Menu:
void gotxy(); //function for accurate placements
void border(char *title, char *subtitle); //function for menu design borders
void coverpage(); //function for the project's cover page
int mainmenu(); //function for menu display and input

//MM functions:
void makenull(); //resets the last value of the list
int insertCard(); //function for detecting the usb for ID verification
void registration(); //function for entering voter's data
int IDGen(); //function for producing a unique Voter ID
void REGinsert(char n[MAX], int a, int d, int m, int y, char c[MAX],char sec[MAX], char nat[MAX], int id, char pw[MAX]); //function for data transfer to structure
void REGsave(int id, char pw[MAX]); //function for saving the data from the list to the database file
void REGretrieve(); //function for retrieving past list data from the database file
int isfull(); //function for checking if the list is full
int isempty(); //function for checking if the list is empty
int pos(char n[MAX]); //compares the inputted string if it's smaller than the string value in the array
char locate(char n[MAX]); //locates the inputted data them compares it to the list

//Voter menu & functions:
int votemenu(); //function for the voting menu
void Voting(char n[MAX], char p[MAX], char l[MAX]); //function for the actual voting process
void VDispCand(); //function for displaying the available candidates
void saveCand(); //function for saving entered candidates
void CandRetrieve(); //function for refilling the candidate file with candidates
int locateCand(char n[MAX], int i); //function for finding the index of the candidate name entered
int locatevoter(); //function for finding the index of the voter name

//admin menu & functions:
void admin(char n[MAX]); //function for the admin control
int adminmenu(); //function for displaying the admin menu
void addCand(char n[MAX]); //admin function for adding candidates
void delCand(char n[MAX]); //admin function for removing candidates
void DispCand(); //admin function for displaying the candidates and their amount of votes
void display(); //display the whole list as well as computing for data average and remarks


int main()
{
  //local declarations for the switch statements
  char n[31], p[31], l[31];
  int option,i,user,pw;
  int VChoice,MChoice;

  coverpage(); //shows the starting cover page of the project
  makenull(); //resets last value of list
  REGretrieve(); //populatate the list with the data from the file
  CandRetrieve(); //populate the list with the data from candidates file

a:
    system("color F0");
    MChoice = mainmenu(); //recall menu function for menu display
    switch(MChoice) // case for menu input
    {
      case 1 :
          insertCard(); //case 1 verifies the card if there is any voter info in there

      if (insertCard()>=0) //if there is a card (usb) in the computer no need for further registration
      {
          printf("\n");
          system("pause");
          printf("\nVoter Information verified!\n ");
          system("pause");
      }
      else //but if not go here and register in order to put info in the card (usb)
      {
          printf("\n");
          system("pause");
          printf("You are not yet registered, please register first..");
          system("pause");
          system("cls");
          registration();
      }

          break;

      case 2 : //straight to registration for more voter ids
          system("cls");
          registration();
          break;

      case 3 : //Exit the program
          printf("\n\n\t\t\t\t\t Thank you for using the program!");
          exit(0);
          break;
      case 295 : //case for admin menu and functions
          system("cls");
          admin(n);
          break;
      default: //default in case user doesn't pick right
          printf("Number not found! Please pick from 1-3 only!");
          getch();
          goto a;


    }




while(1){ //loop while true
    VChoice = votemenu(); //vote menu function for the switch case below

    switch(VChoice){
        case 1: //case for voting
            system("cls");
            border("STUDENT COUNCIL 2021", "   Vote Candidate\n\n\n");
            VDispCand(); //display all the available candidates
            if(locatevoter()>=0) //checks if the voter in question has already voted or not
                    {
                        printf("\nYou can only vote once... Thank you for Voting!\n");
                        system("pause");
                    }
                    else
                    {
                        printf("\nEnter the name of the President you want to vote: ");
                        scanf("%s", n);
                        printf("\nEnter the name of the Vice President you want to vote: ");
                        scanf("%s", p);
                        printf("\nEnter the name of the Secretary you want to vote: ");
                        scanf("%s", l);
                        printf("\nThank you for voting!\n");
                        system("pause");
                        Voting(n, p, l); //enters the names of the candidates the voter chose
                        saveCand(); //saves the candidates in their respective files
                    }
                    break;
        case 2: //case for displaying the candidates
            system("cls");
            border("STUDENT COUNCIL 2021", "  Candidate List\n\n\n");
            VDispCand(); //displays the candidates
            system("pause");
            break;

        case 3: //case for going back to the main menu
            system("cls");
            printf("Thank you for Voting!");
            goto a; //goes back to the top at the menu switch

        default:
            printf("\n Option chosen not included.");
            getch();
            system("cls");

    }

}

}

//Design & Main Menu:
void gotoxy(int a, int b) //function for accurate placements
{
    COORD c;
    c.X=a; //assigning the x coord to a
    c.Y=b; //assigning the y coord to b
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

void border(char *title, char *subtitle) //function for menu design borders
{
    // Left and Right Borders
    for(int i = TP; i < 7; i++)  //for loop terminates when i is less than 7 where i is equal to TP
    {
        gotoxy(LP, i);
        printf("%c", 186);
    }
    for(int i = TP; i < 7; i++)  //for loop terminates when i is less than 7 where i is equal to TP
    {
        gotoxy(RP, i);
        printf("%c", 186);
    }
    // Top and Bottom Borders
    for(int i = LP; i < 100; i++)  //for loop terminates when i is less than 100 where i is equal to LP
    {
        gotoxy(i, 2);
        printf("%c", 205);
    }
    for(int i = LP; i < 100; i++)  //for loop terminates when i is less than 100 where i is equal to LP
    {
        gotoxy(i, 7);
        printf("%c", 196);
    }

    // Corners
    gotoxy(7, 2);
    printf("%c", 201);
    gotoxy(100, 2);
    printf("%c", 187);
    gotoxy(7, 7);
    printf("%c", 211);
    gotoxy(100, 7);
    printf("%c", 189);


    // Texts
    gotoxy((((LP + RP) / 2) - (strlen(title) / 2)), TP + 1);
    for(int i = 0; i < strlen(title); i++)
        {
        for(int j = 0; j < 10000000; j++);
        printf("%c", title[i]);//219
        }
    gotoxy((((LP + RP) / 2) - (strlen(subtitle) / 2)), TP + 2);
    for(int i = 0; i < strlen(subtitle); i++)
        {
        for(int j = 0; j < 10000000; j++);
        printf("%c", subtitle[i]);//219
        }
}

void coverpage() //function for the project's cover page
{
time_t t;

    system ("color 0E");
    gotoxy(39,5);     //assigning coordinates
    printf("Technological University of the Philippines");
    gotoxy(48,6);     //assigning coordinates
    printf("BSCS 2AB First Project");
    gotoxy(53,8);
    printf("Prepared by:");
    gotoxy(50,10);     //assigning coordinates
    printf (" Mhari Allen Limin");
    gotoxy(48,11);     //assigning coordinates
    printf ("Christian Noel Nacario");
    gotoxy(43,21);     //assigning coordinates
    time(&t);
    printf ("Date today: %s", ctime(&t));
    gotoxy(47,22);     //assigning coordinates
    printf("Press any key to continue");
    getch();
}

int mainmenu() //function for menu display and input
{
    int i, optn;
    char *men[] = {"Login", "Register", "Exit"}; //main menu options
    system ("cls");

    border("TECHNOLOGICAL UNIVERSITY OF THE PHILIPPINES", "AUTOMATED VOTING SYSTEM\n\n\n");

    for (i=0;i<3;i++)
        printf("\t\t\t\t\t   %d.) %s\n",i+1,men[i]);//layout of menu display
        printf("\t\t\t\t___________________________________________\n");
        printf("\n\t\t\t\t\t Please Select (1-3): ");
        scanf("%d", &optn);

    return(optn); //return the option chosen
}

//MM Functions
void makenull() //resets the last value of the list
{
    L.last = -1; //sets last to -1
    L.PCount = 0; //sets PCount to 0
    L.VPCount = 0; //sets VPCount to 0
    L.SecCount = 0; //sets SecCount to 0
}

int insertCard() //function for detecting the usb for ID verification
{
    int user,i,s,count;
    char pwrd[MAX];
    FILE *fp;
    do
    {
        system("cls");
        printf("Please insert card...\n");
    }while((fp=fopen("d:\\voter.txt", "r+"))==NULL); //will keep looping until it detects the card (usb) has been plugged in
     {
        fscanf(fp, "%d %s\n", &user, pwrd); //takes the password from the file after the card is detected
        count = 0;
        for(s=0; pwrd[s]; s++)
            {
                if(pwrd[s] != ' ')
                {
                    count ++; //increases count
                }

            }
        printf("\n\nCard Detected! Please wait...\n");
        printf("\n\nValidating your credentials...");
        printf("\nID: %d \n", user);
        printf("PW: ");

        for(i=0; i<count; i++) //hides the password with asterisks
        {
            printf("*");
        }

     }
     printf("\n");
     fclose(fp);



    for(int i=0;i<=L.last;i++)
    {
        if(L.entry[i].id == user && strcmp(L.entry[i].pass, pwrd)==0) //compare if the string inputted by the user is the same as the one on the loop
        {
            return(i);
        }

    }
    return (-1);
}

void registration() //function for entering voter's data
{
    //variables
    char n[MAX];
    int a,d, m, y, user,id, i;
    char pswr;
    char pw[MAX];
    char c[MAX];
    char nat[MAX];
    char sec[MAX];

    i=0;

    //printf("Registration for Voting");
    border("Automated Voting System", "  Registration\n\n\n");

    //voter information the user inputs
    printf("\n\tEnter your surname: ");
    scanf("%s",n);


    printf("\n\tEnter Age: ");
    scanf("%d", &a);

    printf("\n\tEnter Birthday: ");
    printf("\n\t\tDay: ");
    scanf("%d", &d);

    printf("\n\t\tMonth: ");
    scanf("%d", &m);

    printf("\n\t\tYear: ");
    scanf("%d", &y);

    printf("\n\tEnter your course (eg. Civil_Eng): ");
    scanf("%s",c);

    printf("\n\tEnter your section (eg. 1A/2B): ");
    scanf("%s",sec);

    printf("\n\tEnter Nationality: ");
    scanf("%s", nat);



    id = IDGen(); //generates the voter's ID

    printf("\n\tPlease insert your desired password: "); //gets the password the voter enters
    while((pswr = _getch())!=13)
    {
        pw[i] = pswr;
        i++;
        printf("*");
    }

    printf("\n\n\tCongratulations you are now registered in our system! \n\tRedirecting you to Voting Menu...");
    printf("\n");
    system("pause");
    REGinsert(n, a, d, m, y, c, sec, nat, id, pw); //insert all the variables the user input into the structure
    REGsave(id,pw); //saves the specific user ID and PW for future reference
}

int IDGen() //function for producing a unique Voter ID
{
    int ID;
    int lower = 100000;
    int higher = 999999;

    srand(time(NULL)); //initialize for the id to be random every run

    ID = (rand() % (higher - lower + 1)) + lower; //calculates the ID
    printf("\n\tYour Designated ID Number is: \n\t%d", ID);
    return (ID);

}

void REGinsert(char n[MAX], int a, int d, int m, int y, char c[MAX],char sec[MAX], char nat[MAX], int id, char pw[MAX]) //function to input the data of the voter for the ID
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
          strcpy(L.info[i+1].NAME, L.info[i].NAME); //copy the string data from n to the structure array variable
          L.info[i+1].age = L.info[i].age; //copy the age to the structure array variable
          L.info[i+1].day = L.info[i].day; //copy the day to the structure array variable
          L.info[i+1].month = L.info[i].month; //copy the months to the structure array variable
          L.info[i+1].year = L.info[i].year; //copy the months to the structures array variable
          strcpy(L.info[i+1].nationality, L.info[i].nationality); //copy the nationality to the structures array variable
          strcpy(L.info[i+1].course, L.info[i].course); //copy course to the structure array variable
          strcpy(L.info[i+1].section, L.info[i].section); //copy the section to the structure array variable
          L.entry[i+1].id = L.entry[i].id; //copy the voter's id to the structure array variable
          strcpy(L.entry[i+1].pass, L.entry[i].pass); //copy the voter's password to the structure array variable

      }
      //assigning of data in the array
      strcpy(L.info[p].NAME, n); //copy the string data from n to the structure array variable
      L.info[p].age = a; //copy the user entered data into the age element of the structure array variable
      L.info[p].day = d; //copy the user entered data into the day element of the structure array variable
      L.info[p].month = m; //copy the user entered data into the month element of the structure array variable
      L.info[p].year = y; //copy the user entered data into the year element of the structure array variable
      strcpy(L.info[p].nationality, nat); //copy the user entered data into the nationality element of the structure array variable
      strcpy(L.info[p].course, c); //copy the user entered data into the course element of the structure array variable
      strcpy(L.info[p].section, sec); //copy the user entered data into the section element of the structure array variable
      L.entry[p].id = id; //copy the user entered data into the voter's id element of the structure array variable
      strcpy(L.entry[p].pass, pw); //copy the user entered data into the voter's password element of the structure array variable


      L.last++; //increment last to mark another set of info being copied


  }
}
}

void REGsave(int id, char pw[MAX]) //function for saving the data from the list to the database file
{
    FILE *hs;
    int i;
    hs = fopen("voterec.dbf", "w+"); //opens voterec for writing
    if (hs==NULL) //if no file found goes to error
    {
        printf("File Error.\n");
        system("pause");
    }
    else
    {
    for(i=0;i<=L.last;i++) //if there is a file it prints all the entered values earlier to the file
        {
        fprintf(hs,"%s %d %d %d %d %s %s %s %d %s\n", L.info[i].NAME, L.info[i].age, L.info[i].day, L.info[i].month, L.info[i].year, L.info[i].course, L.info[i].section, L.info[i].nationality, L.entry[i].id, L.entry[i].pass); //copies the entries from list to the database file
        }
    fclose(hs);
    }

    hs = fopen("d:\\voter.txt", "w+"); //opens the file in the card (usb) for writing
    if (hs==NULL)
    {
        printf("File Error.\n");
        system("pause");
    }
    else
    {
    fprintf(hs,"%d %s",id, pw); //copies the entries from list to the database file

    fclose(hs);
    }
}

void REGretrieve() //function for retrieving past list data from the database file
{
    char n[MAX], nat[MAX], sec[MAX], c[MAX], pw[MAX];
    int a,d,m,y,id;

    FILE *hs;
    if((hs = fopen("voterec.dbf", "r")) !=NULL) //if file does not exist, creates a new file for storing and retrieving data

        while(fscanf(hs, "%s %d %d %d %d %s %s %s %d %s", n, &a, &d, &m, &y, c, sec, nat, &id, pw)>=1) //while true it scans the values from the files and inserts it into the structure
        {
            REGinsert(n, a, d, m, y, c, sec, nat, id, pw);
        }

    fclose(hs);
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


        if(strcmp(L.info[i].NAME, n) == 0) //compare if the string inputted by the user is the same as the one on the loop
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
        if(strcmp(L.info[i].NAME,n)>0) //returns the index number if they are the same string
        {
            return(i);
        }
    }
    return(i);
}


//voter menu & functions:
int votemenu() //function for menu display and input
{
    int i, choice;

    char *menu[] = {"Vote", "See Candidates", "Logout"}; //options for the voting menu
    system ("cls");
    border("   TECHNOLOGICAL UNIVERSITY OF THE PHILIPPLINES", "    STUDENT COUNCIL VOTING MENU\n\n\n");

    for (i=0;i<3;i++)
        printf("\t\t\t\t\t   %d.) %s\n",i+1,menu[i]);//layout of menu display
        printf("\t\t\t\t\t_________________________________\n");
        printf("\n\t\t\t\t\t Please Select (1-3): ");
        scanf("%d", &choice);

    return(choice); //returns the chosen option from the menu
}

void Voting(char n[MAX], char p[MAX], char l[MAX]){ //function for the actual voting process
    int k, i;
    int TVoting;

        k = locateCand(n, 1); //locates the entered name in the presidential list
        if (k<0){ //if not there then error
            printf("Name not found.");
        }
        else{
            L.cands[k].PVoteCount++; //if the name is there their vote count is incremented
        }

        k = locateCand(p, 2); //locates the entered name in the vice presidential list
        if (k<0){ //if not there then error
            printf("Name not found.");
        }
        else{
            L.cands[k].VPVoteCount++; //if the name is there their vote count is incremented
        }

        k = locateCand(l, 3); //locates the entered name in the secretary list
        if (k<0){ //if not there then error
            printf("Name not found.");
        }
        else{
            L.cands[k].SecVoteCount++; //if the name is there their vote count is incremented
        }

        FILE *fp;
        fp=fopen("d:\\voter.txt", "a"); //opens the voter file in the card to input that the user has voted
        fprintf(fp, " Voted");

        fclose(fp);


    }

void VDispCand(){ //function for displaying the available candidates
    if(isempty()){ //checks if the list is empty
        printf("List is empty!\n");
        printf("Press any button to continue.\n");
        getch();
    }
    else{ //if not shows the same list as the display candidates function but without the amount of votes
        int i;
        printf("\n\t\t LIST OF CANDIDATES\n");
        printf("\n\t\tCandidates for President: ");
            for(i=0; i<L.PCount;i++){
                printf("\n\t\t%d.) %s\t\t\n", i+1, L.cands[i].Pres); //outputs the whole presidents list
            }
        printf("\n\t\tCandidates for Vice President: ");
            for(i=0; i<L.VPCount;i++){
                printf("\n\t\t%d.) %s\t\t\n", i+1, L.cands[i].VPres); //outputs the whole vice presidents list
            }
        printf("\n\t\tCandidates for Secretary: ");
            for(i=0; i<L.SecCount;i++){
                printf("\n\t\t%d.) %s\t\t\n", i+1, L.cands[i].Secre); //outputs the whole vice presidents list
            }
    }
}

void saveCand(){ //function for saving entered candidates
    FILE *fp;
    int i;
    fp = fopen("PCandidates.dbf","w+"); //opens the file for presidential candidates
    for(i = 0; i<L.PCount;i++){
        fprintf(fp, "%s %d\n", L.cands[i].Pres, L.cands[i].PVoteCount); //saves the added presidential candidates to the file
    }
    fclose(fp);

    fp = fopen("VPCandidates.dbf","w+"); //opens the file for vice presidential candidates
    for(i = 0; i<L.VPCount;i++){
        fprintf(fp, "%s %d\n", L.cands[i].VPres, L.cands[i].VPVoteCount); //saves the added vice presidential candidates to the file
    }
    fclose(fp);

    fp = fopen("SecCandidates.dbf","w+"); //opens the file for secretary candidates
    for(i = 0; i<L.SecCount;i++){
        fprintf(fp, "%s %d\n", L.cands[i].Secre, L.cands[i].SecVoteCount); //saves the added secretary candidates to the file
    }
    fclose(fp);

}

void CandRetrieve(){ //function for refilling the candidate file with candidates
    char CN[MAX];
    int VC;

    FILE *hp;
    if((hp = fopen("PCandidates.dbf", "r+")) !=NULL){ //if file does not exist, creates a new file for storing and retrieving data
        while(fscanf(hp, "%s %d", CN, &VC)>=1) //if the file exists it prints all the presidential candidates into the file
        {
            strcpy(L.cands[L.PCount].Pres, CN);
            L.cands[L.PCount].PVoteCount = VC; //copies the current presidential vote count into the file
            L.PCount++; //increments how many presidential candidates there are
        }
    }

    fclose(hp);
     if((hp = fopen("VPCandidates.dbf", "r")) !=NULL){ //if file does not exist, creates a new file for storing and retrieving data
        while(fscanf(hp, "%s %d", CN, &VC)>=1) //if the file exists it prints all the vice presidential candidates into the file
        {
            strcpy(L.cands[L.VPCount].VPres, CN);
            L.cands[L.VPCount].VPVoteCount = VC; //copies the current vice presidential vote count into the file
            L.VPCount++; //increments how many vice presidential candidates there are
        }
    }

    fclose(hp);
     if((hp = fopen("SecCandidates.dbf", "r")) !=NULL){ //if file does not exist, creates a new file for storing and retrieving data
        while(fscanf(hp, "%s %d", CN, &VC)>=1) //if the file exists it prints all the secretary candidates into the file
        {
            strcpy(L.cands[L.SecCount].Secre, CN);
            L.cands[L.SecCount].SecVoteCount = VC; //copies the current secretary vote count into the file
            L.SecCount++; //increments how many secretary candidates there are
        }
    }


    fclose(hp);

}

int locateCand (char n[31], int i ) //function for finding the index of the candidate name entered
{
    int TierChoice;

    TierChoice = i;
    switch(TierChoice){ //switch statement for retrieving the candidates from their respective tiers

     case 1:
        for(int i=0;i<=L.PCount;i++) //loop for locating the president from the list
    {
        if(strcmp(L.cands[i].Pres, n) == 0) //compare if the president inputted by the user is the same as the one on the loop
        {
        return(i); //returns the index if found successfully
        }
    }
        break;

     case 2:
        for(int i=0;i<=L.VPCount;i++) //loop for locating the vice president from the list
    {
        if(strcmp(L.cands[i].VPres, n) == 0) //compare if the vice president inputted by the user is the same as the one on the loop
        {
        return(i); //returns the index if found successfully
        }
    }
        break;

    case 3:
        for(int i=0;i<=L.SecCount;i++) //loop for locating the secretary from the list
    {
        if(strcmp(L.cands[i].Secre, n) == 0) //compare if the secretary inputted by the user is the same as the one on the loop
        {
        return(i); //returns the index if found successfully
        }
    }
        break;
    default:
        printf("This is not supposed to happen what");
        exit(0);
    }
    return(-1);
}

int locatevoter () //locates the inputted data them compares it to the list
{
    //variables used
    int usr;
    char  pword[MAX];
    char status[MAX];

    FILE *fp;
    fp = fopen("d:\\voter.txt", "r"); //opens the file in the card (usb)
    fscanf(fp, "%d %s %s", &usr, pword, status); //gets the username, password, and their voting status


        if(strcmp(status, "Voted") == 0) //compare if the string inputted by the user is the same as the one on the loop
        {
        return(0); //if voted they will no longer be able to access the voting
        }
    return(-1);
}


//admin menu & functions:
void admin(char n[MAX]){ //function for the admin control

    b:
    //variables used
    system("cls");
    system("color 0A");
    char UN[20];
    char PW[MAX];
    char pswd;
    int adminchoice, i=0;

    printf("\n\t\t\t Admin Log-in Panel");
    printf("\n\t\t\t_________________________");
    printf("\n\t\t\t Enter admin username: ");
    scanf("%s", UN); //takes the username of the admin for login

    printf("\n\t\t\t Enter admin password: ");
    while((pswd = _getch())!=13) //takes the password of the admin for login
    {
        PW[i] = pswd;
        i++;
        printf("*"); //hides the password entered by the user
    }

    if (strcmp(UN, "TUPadmin") == 0){

        if(strcmp(PW, "tupmanila") == 0){ //if both strcmp are successfull can access the admin menu

            printf("\n\n\t\t\t Welcome Admin, redirecting you to the admin menu...\n\t\t\t");
            system("pause");

while(1){
            system("color 0A");
            adminchoice = adminmenu();
            switch(adminchoice){
            case 1: //add candidates case
                system("cls");
                system("color B0");
                border("STUDENT COUNCIL 2021", "ADD CANDIDATES\n\n\n");
                printf("\nEnter the name of Candidate you wish to add: ");
                scanf("%s", n);
                addCand(n); //adds the candidates to the list
                saveCand(); //saves the added candidate to the file
                break;
            case 2: //delete candidates case
                system("cls");
                system("color C0");
                border("STUDENT COUNCIL 2021", "DELETE CANDIDATES\n\n\n");
                DispCand(); //displays the all the candidates from all tiers
                printf("\nEnter the name of Candidate you wish to delete: ");
                scanf("%s", n);
                delCand(n); //deletes the candidate from the list
                saveCand(); //saves the deleted candidate to the file
                break;
            case 3: //display candidates case
                system("cls");
                system("color E0");
                border("STUDENT COUNCIL 2021", "DISPLAY VOTES\n\n\n");
                DispCand(); //displays all the candidates in the list
                system("pause");
                break;
            case 4: //display voters case
                system("cls");
                system("color 70");
                border("STUDENT COUNCIL 2021", "DISPLAY VOTERS\n\n\n");
                display(); //displays all the voters in the list
                system("pause");
                break;
            case 5: //exit case
                printf("\nThank you for using the Admin Program :)");
                exit(0); //exits the program
            default: //default in case the number selected isn't from 1-5
            printf("Number not found! Please pick from 1-5 only!");
            getch();

            }

            }
        }
        else{
            printf("\n\n\t\t\t Password entered is invalid\n");
            system("pause");
            goto b; //if wrong password we return to the start of the admin input

        }

    }
    else{
        printf("\n\n\t\t\t Username entered is invalid\n");
        system("pause");
        goto b; //if wrong password we return to the start of the admin input


    }
}

int adminmenu(){ //function for displaying the admin menu
    int i, select;
    char *menu[] = {"Add Candidate", "Remove Candidate", "Display Candidate", "Display Voters", "Exit"}; //options for the admin menu
    system ("cls");
    border("STUDENT COUNCIL 2021", "ADMIN MENU\n\n\n");

    for (i=0;i<5;i++){ //outputs the choices that the admin can choose
        printf("\t\t\t\t         %d.) %s\n",i+1,menu[i]);//layout of menu display
    }
        printf("\t\t\t\t_______________________________________\n");
        printf("\n\t\t\t\t\t Please Select (1-5): ");
        scanf("%d",&select);

    return (select); //returns the chosen menu option
}

void addCand(char n[31]){ //admin function for adding candidates
    int i;
    int choice;
    if(isfull()){ //checks if the candidates list is full
        printf("List is Full");
        getch();
    }
    else{
        printf("What role would you like to add them in? (Pres = 1, VPres = 2, Sec = 3)\n"); //continue if not full
        scanf("%d", &choice);
        if(locateCand(n, choice)>=0){ //locates the candidate chosen in the file to check for duplicates
            printf("\nDuplicate Record Found. \n");
            system("pause");
        }
        else {
            switch(choice){ //switch for where to put the candidate's name in
                case 1:
                    strcpy(L.cands[L.PCount].Pres, n);
                    L.PCount++;
                    break;
                case 2:
                    strcpy(L.cands[L.VPCount].VPres, n);
                    L.VPCount++;
                    break;
                case 3:
                    strcpy(L.cands[L.SecCount].Secre, n);
                    L.SecCount++;
                    break;
                default:
                    printf("Option chosen not included");
                    exit(0);
            }
        }
    }
}

void delCand(char n[MAX]){ //admin function for removing candidates
    int l, i,p;
    if (isempty()){ //checks if there is nothing to remove
        printf("List is Empty.");
        getch();
    }
    else{
        printf("Where would you like to delete? (Pres = 1, VPres = 2, Sec = 3)"); //if not asks the user where they want to delete
        scanf("%d", &p);

        l = locateCand(n, p); //locates the name in that specific part
        getch();
        if (l<0){ //error if the name isn't there
            printf("Not found.");
            getch();
        }
        else{
            switch(p){ //case for which part they removed a candidate
            case 1:
                for (i = l; i < L.PCount; i++){
                strcpy( L.cands[i].Pres,  L.cands[i+1].Pres); //effectively removes the chosen presidential candidate
            }
                L.PCount--; //decrements the count in the presidential list
                break;
            case 2:
                for (i = l; i < L.VPCount; i++){
                strcpy( L.cands[i].VPres,  L.cands[i+1].VPres); //effectively removes the chosen vice presidential candidate
                }
                L.VPCount--; //decrements the count in the vice presidential list
                break;
            case 3:
                for (i = l; i < L.SecCount; i++){
                strcpy( L.cands[i].Secre,  L.cands[i+1].Secre); //effectively removes the chosen secretary candidate
                }
                L.SecCount--; //decrements the count in the secretary list
                break;
            }
        }
    }

}

void DispCand(){ //admin function for displaying the candidates and their amount of votes
    if(isempty()){ //checks if the list to display is empty
        printf("List is empty!\n");
        printf("Press any button to continue.\n");
        getch();
    }
    else{
        int i; //if not shows the same list as the display candidates function, but with the amount of votes they have. ONLY FOR ADMINS.
        printf("\n\t\t LIST OF CANDIDATES\n");
        printf("\n\t\tCandidates for President: ");
        printf("\n\t\tNAME\t\tNo. of Votes\n");
            for(i=0; i<L.PCount;i++){
                printf("\n\t\t%d.) %s\t\t%d", i+1, L.cands[i].Pres, L.cands[i].PVoteCount); //outputs the whole presidents list
            }
        printf("\n\t\tCandidates for Vice President: ");
        printf("\n\t\tNAME\t\tNo. of Votes\n");
            for(i=0; i<L.VPCount;i++){
                printf("\n\t\t%d.) %s\t\t%d", i+1, L.cands[i].VPres, L.cands[i].VPVoteCount); //outputs the whole vice presidents list
            }
        printf("\n\t\tCandidates for Secretary: ");
        printf("\n\t\tNAME\t\tNo. of Votes\n");
            for(i=0; i<L.SecCount;i++){
                printf("\n\t\t%d.) %s\t\t%d", i+1, L.cands[i].Secre, L.cands[i].SecVoteCount); //outputs the whole secretary list
            }
    }
}

void display() //display the whole list as well as computing for data average and remarks
{
    int i;
    system("cls");
    printf("\n\t\t\t\t\t\t   VOTER's INFORMATION DATABASE\n");
    printf("\t\t__________________________________________________________________________________________________\n\n");
    printf("\t\t           ID#           NAME            AGE      BIRTHDAY      COURSE       SECTION      NATIONALITY    \n");
    printf("\t\t__________________________________________________________________________________________________\n");
    for (i=0;i<=L.last;i++) //loop for displaying the values of the structure array variables as well as computing individual average
        {

        printf("\n\t\t  %d.)\t %d\t\t %s\t\t %d\t %d/%d/%d\t %s\t       %s\t   %s\n", i+1, L.entry[i].id, L.info[i].NAME, L.info[i].age, L.info[i].day, L.info[i].month, L.info[i].year, L.info[i].course, L.info[i].section, L.info[i].nationality);

        }
        printf("\nIf display is not displaying as intended, kindly maximize the window, thank you :D\n");

}





