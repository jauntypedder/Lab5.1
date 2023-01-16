#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SIZE 30

int main()
{
  char name[SIZE],surname[SIZE],group[SIZE];
  double x1, x2, y, delta, bin, **A;
  int step,N;

  FILE* input=fopen("input.txt", "r");
    if (input == NULL){
        printf("ERROR: input file was not opened!");
        return 1;
    }
  FILE* output=fopen("output.txt", "w");
    if (output == NULL){
        printf("ERROR: output file was not opened!");
        fclose(input);
        return 2;
    }
  FILE* binary=fopen("binary.bin", "w+b");
    if (binary == NULL){
        printf("ERROR: binary file was not opened!");
        fclose(input);
        fclose(output);
        return 3;
    }
  
  fgets(name,SIZE, input);
  fgets(surname,SIZE, input);
  fgets(group,SIZE, input);
    if (step==0)
    {
        step=((x2-x1)/delta)+1;
    }
    else if (delta==0)
    {
        delta=(x2-x1)/(step-1);
    }
    fclose(input);
    fprintf(output,"\n   N      X          F(X)           ");
    fwrite(&step, sizeof(int), 1, binary);

    for(int i=0; i<step; i++)

    {
     y= ((pow((x1-10),3)*sin((x1+10)/100))-10*x1+12);
     fprintf(output, "\n\t|%d| %.2lf\t|%.2lf\t|",i,x1,y);
     fwrite(&x1, sizeof(double), 1, binary);
     fwrite(&y, sizeof(double), 1, binary);
     x1+=delta;
    }

    fprintf(output,"\n%s %s %s", group, name, surname);
    fclose(output);
    fclose(binary);

    binary = fopen("binary.txt", "r+b");
    printf("  N        X        F(x)    \n\n");
    fread(&N, sizeof(int), 1, binary);

    A=(double**)malloc(3*sizeof(double*));
    for(int i=0; i<3; i++)
    {
        A[i]=(double*)malloc(N*sizeof(double));
    }
  for(int i=0; i<N; i++)
   {
    printf("\n|%d|", i);
    for(int j=1; j<3; j++)
   {
     fread(&bin, sizeof(double), 1, binary);
     A[j][i] = bin;
     printf("\t|%.2lf\t| ", A[j][i]);
    }
 }
  fclose(input);
  fclose(output);
  fclose(binary);
}
