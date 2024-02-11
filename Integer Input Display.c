#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>

typedef struct node
    {
        int stored;
        struct node *after;
    } LIST;
LIST *L;

void makenull();
void insert(int num);
void del(int num);
void display();

void makenull()
{
    L = NULL;
}

void insert (int num)
{
     LIST *s, *t, *hold;
     s=t=L;
     hold = (LIST*) malloc(sizeof(LIST));
     hold->stored = num;
     while(s!=NULL)
      {
            t=s;
            s=s->after;
      }
      if (s==L) //first element
            L = hold;
      else
             t->after = hold;

             hold->after = s;
}

void del(int num)
{
    LIST *s,*t;
    s=t=L;
    while (s!=NULL && s->stored!=num)
        {
            t=s;
            s = s->after;
        }
    if (s==NULL)
    {
          printf("Error. Number not found.");
          getch();
    }
    else
     {
        if (s==L)
            L=s->after;
        else
            t->after = s->after;
            free(s);
     }
}

void display()
{
    LIST *s;
    int i=1;
    s=L;
    system("cls");
    printf("\n\t\t\t\t\t\t  QUEUE ENTRY LIST\n");
    printf("\t\t\t\t\t_____________________________________\n");
    while(s!=NULL)
        {
         printf("\n\t\t\t\t\t   %d.) %d\n",i++,s->stored);
         s=s->after;
        }
    printf("\t\t\t\t\t_____________________________________\n");
    getch();
}

int menu()
{
    int choice;
    system("cls");
    printf("\n\t\t\t\t\t\t   MAIN MENU\n");
    printf("\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    printf("\t\t\t\t\t   1. Insert\n");
    printf("\t\t\t\t\t   2. Delete\n");
    printf("\t\t\t\t\t   3. Display\n");
    printf("\t\t\t\t\t   4. Exit\n");
    printf("\t\t\t\t\t_________________________________\n");
    printf("\n\t\t\t\t\t Please Select (1-4): ");
    scanf("%d", &choice);
    return (choice);
}

int main ()
{
makenull();
int input;

	while (1)
	{
		system("cls");
        int num;
        input = menu();
		switch (input)
		{
			case 1:
            system("cls");
		    printf("\n\t\t\t\t\t\t    INSERT NUMBER\n");
            printf("\t\t\t\t\t_____________________________________\n");
			printf("\n\t\t\t\t\t  Input number to insert: ");
            scanf("%d", &num);
            printf("\t\t\t\t\t_____________________________________\n");
            insert(num);
				break;

			case 2:
            system("cls");
		    printf("\n\t\t\t\t\t\t    DELETE NUMBER\n");
            printf("\t\t\t\t\t_____________________________________\n");
			printf("\n\t\t\t\t\t  Input number to delete: ");
            scanf("%d", &num);
            printf("\t\t\t\t\t_____________________________________\n");
            del(num);
				break;

			case 3:
				display();
				break;

			case 4:
				exit(0);
				break;

			default:
				printf("\n\t\t\t\t\t Please pick from 1-4 only..\n\t\t\t\t\t ");
				system("pause");
		}
	}

}

