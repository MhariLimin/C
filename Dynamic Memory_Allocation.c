#include<stdio.h>
#include<stdlib.h>

int Activity1(void);
int Activity2(void);
int Activity3(void);

 typedef struct
         {
           char name[50];
           char text[50];
           int num;
           float grade;
         } sys;


int main (void)
{
    do
    {

        int input = 0;

        printf("\nM E N U\n");
        printf("Activity 1\n");
        printf("Acitivity 2\n");
        printf("Acitivty 3\n");
        printf("Exit Program [0]\n");
        printf("Enter your choice: ");
        scanf("%d", &input);

        if(input == 0)
        {
            printf("Thank You for Using This Program!");
            break;
        }

        switch(input)
        {
            case 1:
                Activity1();
                break;

            case 2:
                Activity2();
                break;

            case 3:
                Activity3();
                break;

            default:
                printf("Invalid Input, Please Try Again...");
                break;
        }
    } while (1 == 1);
}

int Activity1 (void)
{
  int limit;

  printf("Enter the limit of text: ");
  scanf("%d", &limit);

  sys *holder;
  holder = malloc(limit*sizeof(char));

  printf("Enter text: ");
  getchar();
  gets(holder->text);

  printf("Inputed text is: ");
  puts(holder->text);

  free(holder);


  return 0;
}
int Activity2(void)
{

sys *holder;
holder = malloc(1*sizeof(sys));


      printf("Enter name: ");
      getchar();
      gets(holder->name);

      printf("Enter roll number: ");
      scanf("%d",&holder->num);

      printf("Enter percentage: ");
      scanf("%f",&holder->grade);

      printf("\nEntered details are:\n");
      printf("Name: %s\nRoll Number: %d \nPercentage: %.2f\n",holder->name,holder->num,holder->grade);
}

int Activity3 (void)
{

   int elements, i, j;

   printf("Enter total number of elements: ");
   scanf("%d", &elements);

   sys *holder;
   holder = malloc(elements*sizeof(sys));


     for(i=0, j=1; i<elements; i++, j++)
      {
        printf("\nEnter detail of student [%d]:\n",j);
        printf("Enter name: ");
        getchar();
        gets((holder+i)->name);

        printf("Enter roll number: ");
        scanf("%d",&(holder+i)->num);

        printf("Enter percentage: ");
        scanf("%f",&(holder+i)->grade);
      }

    printf("\nEntered details are:\n");
        for(i=0, j=1; i<elements; i++,j++)
          {
             printf("Entry #[%d]\nName: %s\nRoll Number: %d \nPercentage: %.2f\n\n", j, (holder+i)->name,(holder+i)->num,(holder+i)->grade);
          }

    return 0;
}

