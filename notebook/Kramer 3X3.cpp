/*

 * Name:    Lukas A Scott

 * Date:    12/07/2009

 * Prog:    Program 9

 * Desc:    This program uses Cramer's Rule to find the solution of a

 *     system of three linear equations in three variables.

*/

 

#include <stdio.h>

 

int det3(int a[3][3]);

 

int main(void)

{

    int A[3][3];

    int B[3];

 

    printf("This program uses Cramer's Rule to solve a linear system.\

            Enter each of 3 linear equations as four integers separated by space.\

              For example, x - 2y + 3z = 4 should be entered as 1 -2 3 4");

    printf("\n\nEnter equation 1: ");

    scanf("%i %i %i %i", &A[0][0], &A[0][1], &A[0][2], &B[0]);

    printf("Enter equation 2: ");

    scanf("%i %i %i %i", &A[1][0], &A[1][1], &A[1][2], &B[1]);

    printf("Enter equation 3: ");

    scanf("%i %i %i %i", &A[2][0], &A[2][1], &A[2][2], &B[2]);

 

    /*Finding determinants*/

 

    int detx[3][3] = {{B[0],A[0][1],A[0][2]},{B[1],A[1][1],A[1][2]},

                          {B[2],A[2][1],A[2][2]}};

    int dety[3][3] = {{A[0][0],B[0],A[0][2]},{A[1][0],B[1],A[1][2]},

                          {A[2][0],B[2],A[2][2]}};

    int detz[3][3] = {{A[0][0],A[0][1],B[0]},{A[1][0],A[1][1],B[1]},

                          {A[2][0],A[2][1],B[2]}};

 

    /* Code that determines if the system has a unique solution */

 

      if(det3(A)!=0)

             printf("\nSystem has a unique solution ( %d, %d, %d)",

             det3(detx)/det3(A), det3(dety)/det3(A), det3(detz)/det3(A));

      else

             printf("\nSystem does not have a unique solution because determinant is 0");

 

    return 0;

}

int det3(int a[3][3])

{

    return (a[0][0]*a[1][1]*a[2][2])-(a[0][0]*a[1][2]*a[2][1]),

                +(a[0][1]*a[1][2]*a[2][0])-(a[0][1]*a[1][0]*a[2][2]),

                +(a[0][2]*a[1][0]*a[2][1])-(a[0][2]*a[1][1]*a[2][0]);

}