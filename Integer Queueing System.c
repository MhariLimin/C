#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

#define MAX 10


typedef struct queue
{
int input[MAX];
int top;
} QUE;

QUE q;

int menu();
void makenull();
void enqueue(int num);
void dequeue();
void display();
int isFull();
int isEmpty();
int locate(int num);

int main()
{
    int num;
    int ch;
    makenull();


	while (1)
	{
		system("cls");

        ch = menu();
		switch (ch)
		{
		case 1:
		    system("cls");
		    printf("\n\t\t\t\t\t      INSERT NUMBER TO ENQUEUE\n");
            printf("\t\t\t\t\t_____________________________________\n");
			printf("\n\t\t\t\t\t  Input number to enqueue: ");
			scanf("%d", &num);
			//cin.get();
			printf("\t\t\t\t\t_____________________________________\n");
			enqueue(num);
			break;

		case 2:
			dequeue();
            printf("\n\t\t\t\t\t Top entry successfully dequeued!\n\t\t\t\t\t ");
			system("pause");
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

int menu()
{
    int choice;
    system("cls");
    printf("\n\t\t\t\t\t\t   QUEUE MENU\n");
    printf("\t\t\t\t\t~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n");
    printf("\t\t\t\t\t   1. Enqueue\n");
    printf("\t\t\t\t\t   2. Dequeue\n");
    printf("\t\t\t\t\t   3. Display\n");
    printf("\t\t\t\t\t   4. Exit\n");
    printf("\t\t\t\t\t_________________________________\n");
    printf("\n\t\t\t\t\t Please Select (1-4): ");
    scanf("%d", &choice);
    return (choice);
}

void makenull()
{
    q.top = 0;
}
void enqueue(int num)
{
    int s;
	if (isFull())
	{
		printf("Queue Overflow");
		system("pause");
	}
	else
    {
            s = locate(num);
            if(s>=0)
            {
              printf("\n\t\t\t\t\t  Duplicate Queue No. Found.\n\t\t\t\t\t  ");
              system("pause");
            }
        else
        {
            q.input[q.top] = num;
            q.top++;
			printf("\n\t\t\t\t\t  Number successfully queued!\n\t\t\t\t\t  ");
			system("pause");
        }
    }
}

void dequeue()
{
	if (isEmpty())
	{
		printf("Queue is empty");
		system("pause");
	}
	else
	{
		// remove first entry and nudge all the values towards index 0
		for (int i = 0; i < q.top; i++)
		{
			q.input[i] = q.input[i+1];
		}
		q.top--;
	}
}

void display()
{
	system("cls");
	if (isEmpty())
	{
		printf("Queue is empty");
		system("pause");
	}
	else
    {
        printf("\n\t\t\t\t\t\t  QUEUE ENTRY LIST\n");
        printf("\t\t\t\t\t_____________________________________\n");
        for (int i = 0; i < q.top; i++)
        {
            printf("\n\t\t\t\t\t\t  %d.) %d\n", i+1, q.input[i]);
        }
        printf("\t\t\t\t\t_____________________________________\n");
        printf("\n\t\t\t\t\t  ");
        system("pause");
    }
}

int locate(int num) //locates the inputted data them compares it to the list
{

    int i;

    for (i=0;i<=q.top;i++)
    {
        if (q.input[i]==num)
            return i;
    }
    return -1;
}

int isFull()
{
	return (q.top==MAX);
}

int isEmpty()
{
	return (q.top==0);
}

