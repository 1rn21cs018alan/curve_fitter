#include <stdio.h>
#include <stdlib.h>
#include<math.h>
struct DataTable
{
    int size;
    float **values;
};
typedef struct DataTable *DT;

DT getTable();
void input_table(DT table);
void print_table(DT table);
void format_print(float val);
void small_print(double val);
void big_print(double val);
void calc(DT table);



void calc(DT table)
{
    for (int i =0;i<table->size;i++)
    {
        float x=table->values[0][i],y=table->values[1][i];
        table->values[2][i]=x*y;
        table->values[3][i]=x*x;
        table->values[4][i]=x*x*y;
        table->values[5][i]=x*x*x;
        table->values[6][i]=x*x*x*x;        
        table->values[0][table->size]+=x;
        table->values[1][table->size]+=y;
        table->values[2][table->size]+=table->values[2][i];
        table->values[3][table->size]+=table->values[3][i];
        table->values[4][table->size]+=table->values[4][i];
        table->values[5][table->size]+=table->values[5][i];
        table->values[6][table->size]+=table->values[6][i];
    }
}


void small_print(double val)
{
    double temp=val;
    int expo=0;
    while(fabs(temp)<1.0)
    {
        expo++;
        temp*=10;
    }
    printf("%.3lfx10^-%d\t",temp,expo);
}

void big_print(double val)
{
    double temp=val;
    int expo=0;
    while(fabs(temp)>=10.0)
    {
        expo++;
        temp/=10;
    }
    printf("%.3lfx10^%d\t",temp,expo);
}


void format_print(float val)
{
    if(val==0)
    {
        printf("%.3lf\t\t",val);
    }
    else if(fabs(val)<0.01)
    {
        small_print(val);
    }
    else if((val > -100.0 ) && ( val< 1000.0 ))
    {
        printf("%.3lf\t\t",val);
    }
    else
    {
        big_print(val);
    }
}

// to create the table
DT getTable()
{
    DT x;
    x = malloc(sizeof(struct DataTable));
    if (x == NULL)
    {
        printf("No Memory\n");
        exit(0);
    }
    return x;
}

// input x and y values into the table
void input_table(DT table)
{
    printf("Enter no of entries:");
    scanf("%d", &(table->size));
    table->values = (float **)malloc(sizeof(float *) * 7);
    for (int i = 0; i < 7; i++)
        table->values[i] = (float *)calloc(1 + table->size, sizeof(float));
    printf("Enter values of x\n");
    for (int i = 0; i < table->size; i++)
        scanf("%f", &(table->values[0][i]));
    printf("Enter values of y\n");
    for (int i = 0; i < table->size; i++)
        scanf("%f", &(table->values[1][i]));
}

void print_table(DT table)
{
    printf("\n\tX\t\tY\t\tXY\t\tX^2\t\t(X^2)Y\t\tX^3\t\tX^4\n");
    for (int j = 0; j < table->size; j++)
    {
        printf("\t");
        for (int i = 0; i < 7; i++)
        {
            format_print(table->values[i][j]);
        }
        printf("\n");
    }
    printf("\nsum\t");
    for (int i = 0; i < 7; i++)
    {
        format_print(table->values[i][table->size]);
    }
}

int main()
{
    DT table;
    table = getTable();
    input_table(table);
    calc(table);
    print_table(table);
}