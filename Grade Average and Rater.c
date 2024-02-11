#include<stdio.h>
#include<stdlib.h>


int main()
{

  char name[50];
  int Oral_Comm, Filipino, Pre_Calculus, Biotech, An_Geom, Total;
  float Average;

     printf("Please input your Name: ");
     scanf("%s", &name);

     printf("Please enter your grade in Oral Communication: ");
     scanf("%d", &Oral_Comm);

     printf("Please enter your grade in Filipino: ");
     scanf("%d", &Filipino);

     printf("Please enter your grade in Pre Calculus: ");
     scanf("%d", &Pre_Calculus);

     printf("Please enter your grade in Biotech: ");
     scanf("%d", &Biotech);

     printf("Please enter your grade in Analytical Geometry: ");
     scanf("%d", &An_Geom );

     Total = Oral_Comm + Filipino + Pre_Calculus + Biotech + An_Geom;
     Average = Total / 5;

     printf("\nName: %s\n", name);
     printf("Average: %0.1f\n", Average);

     if(Average >= 80)
     {
         printf("%s got A", name);
     }
     else if(Average >= 60 && Average <= 79)
     {
         printf("%s got B", name);
     }
     else if(Average < 59)
     {
         printf("%s got C", name);
     }

     return 0;
}


