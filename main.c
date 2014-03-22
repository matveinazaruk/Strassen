#include <stdio.h>
#include <time.h>
#include "strassen_mul.h"

fmpz theSame(const fmpz_mat_t A, const fmpz_mat_t B, fmpz size){
    fmpz i, j;
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            if (*fmpz_mat_entry(A, i, j) != *fmpz_mat_entry(B, i, j)){
                return 0;
            }
        }
    }
    return 1;
}

int main(void)
{
    long i , j ;
    flint_rand_t rand;
    fmpz_mat_t A ;
    fmpz_mat_t B ;
    fmpz_mat_t C, D;
    fmpz start, size = 512;
    flint_printf("Enter matrix size please (power of 2, like 128, 256, 512 ...): ");
    flint_scanf("%d", &size);
    fmpz_mat_init (A, size, size) ;
    fmpz_mat_init (B, size, size) ;
    fmpz_mat_init (C, size, size) ;
    fmpz_mat_init (D, size, size) ;
    fmpz_mat_randbits(A, rand, 4);
    fmpz_mat_randbits(B, rand, 4);

    start = clock();
    commonMultiply(D, A, B);
    flint_printf("\ncommon multiply time: %d\n", clock() - start);
    start = clock();
    //fmpz_mat_print_pretty(D);
    strassenMultiply(C, A, B, size);
    flint_printf("\nstrassen multiply time: %d\n", clock() - start);
    //fmpz_mat_print_pretty(C);

    if (theSame(D, C, size) == 1){
        flint_printf("\nmatrix are the same\n");
    } else {
        flint_printf("\nmatrix are not the same\n");
    }

    flint_randclear(rand);
    fmpz_mat_clear (A) ;
    fmpz_mat_clear (B) ;
    fmpz_mat_clear (C) ;
    fmpz_mat_clear (D) ;
}



