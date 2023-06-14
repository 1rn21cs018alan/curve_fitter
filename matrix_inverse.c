#include <stdio.h>
#include <math.h>
void clear()
{
    printf("\033[2J");
}
void print_matrices(int matA[4][4], int matB[4][4], int size)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d\t", matA[j][i]);
        }
        printf("\t\t");
        for (int j = 0; j < size; j++)
        {
            printf("%d\t", matB[j][i]);
        }
        printf("\n");
    }
}
void input(float mat[4][4], int size, int mode)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (mode)
            {
                if (i == j)
                    mat[i][j] = 1;
                else
                    mat[i][j] = 0;
            }
            else
                scanf("%f", &mat[j][i]);
        }
    }
}
void mod(float matA[4][4], float matB[4][4], int size)
{
    // input: row number to change, row number for reference,multiplier
    int R_ch, R_ref;
    float mult;
    scanf("%d%d%f", &R_ch, &R_ref, &mult);
    for (int i = 0; i < size; i++)
    {
        matA[i][R_ch] += matA[i][R_ref] * mult;
        matB[i][R_ch] += matB[i][R_ref] * mult;
    }
}

float determinant(float[][25], float);
void cofactor(float[][25], float);
void transpose(float[][25], float[][25], float);
int input_matrix()
{
    float a[25][25], k, d;
    int i, j;
    printf("Enter the order of the Matrix : ");
    scanf("%f", &k);
    printf("Enter the elements of %.0fX%.0f Matrix : \n", k, k);
    for (i = 0; i < k; i++)
    {
        for (j = 0; j < k; j++)
        {
            scanf("%f", &a[i][j]);
        }
    }
    d = determinant(a, k);
    if (d == 0)
        printf("\nInverse of Entered Matrix is not possible\n");
    else
        cofactor(a, k);
}

/*For calculating Determinant of the Matrix */
float determinant(float a[25][25], float k)
{
    float s = 1, det = 0, b[25][25];
    int i, j, m, n, c;
    if (k == 1)
    {
        return (a[0][0]);
    }
    else
    {
        det = 0;
        for (c = 0; c < k; c++)
        {
            m = 0;
            n = 0;
            for (i = 0; i < k; i++)
            {
                for (j = 0; j < k; j++)
                {
                    b[i][j] = 0;
                    if (i != 0 && j != c)
                    {
                        b[m][n] = a[i][j];
                        if (n < (k - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            det = det + s * (a[0][c] * determinant(b, k - 1));
            s = -1 * s;
        }
    }

    return (det);
}

void cofactor(float num[25][25], float f)
{
    float b[25][25], fac[25][25];
    int p, q, m, n, i, j;
    for (q = 0; q < f; q++)
    {
        for (p = 0; p < f; p++)
        {
            m = 0;
            n = 0;
            for (i = 0; i < f; i++)
            {
                for (j = 0; j < f; j++)
                {
                    if (i != q && j != p)
                    {
                        b[m][n] = num[i][j];
                        if (n < (f - 2))
                            n++;
                        else
                        {
                            n = 0;
                            m++;
                        }
                    }
                }
            }
            fac[q][p] = pow(-1, q + p) * determinant(b, f - 1);
        }
    }
    transpose(num, fac, f);
}
/*Finding transpose of matrix*/
void transpose(float num[25][25], float fac[25][25], float r)
{
    int i, j;
    float b[25][25], inverse[25][25], d;

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r; j++)
        {
            b[i][j] = fac[j][i];
        }
    }
    d = determinant(num, r);
    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r; j++)
        {
            inverse[i][j] = b[i][j] / d;
        }
    }
    printf("\n\n\nThe inverse of matrix is : \n");

    for (i = 0; i < r; i++)
    {
        for (j = 0; j < r; j++)
        {
            printf("\t%f", inverse[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char const *argv[])
{
    float matA[4][4],matB[4][4];
    input(matA, 4, 0);
    // input(matB, 4, 1);
    // print_matrices(matA, matB, 4);
    input_matrix();
    while (0)
    {
        mod(matA, matB, 4);
        print_matrices(matA, matB, 4);
    }
    return 0;
}
