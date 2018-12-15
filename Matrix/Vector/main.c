#include <stdio.h>
#include <time.h>
#include <omp.h>

int main()
{
    int i, j, n, a[19][19], b[19], c[19];

    clock_t start = clock();

    n = 8; //Max 19

    printf("Matrix A\n");

    for (i = 0; i < n; ++i) {
        for (j = 0; j < n; ++j) {
            a[i][j] = 10;
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }

    printf("\nMatrix B\n");

    #pragma omp parallel private(i) shared(b)
    {
        #pragma omp for
        for (i = 0; i < n; ++i) {
            b[i] = 5;
            printf("%d\n", b[i]);
        }
    }

    printf("\nA * B\n");

    #pragma omp parallel private(i) shared(c)
    {
        #pragma omp for
        for (i = 0; i < n; ++i) {
            c[i] = 0;
        }
    }

    #pragma omp parallel private(i,j) shared(n,a,b,c)
    {
        #pragma omp for schedule(dynamic)
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                c[i] += b[j] * a[j][i];
            }
        }
    }


    #pragma omp parallel private(i) shared(c)
    {
        #pragma omp for
        for (i = 0; i < n; ++i) {
            printf("%d\n", c[i]);
        }
    }

    
    return 0;
}