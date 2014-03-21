#include "strassen_mul.h"

commonMultiply(fmpz_mat_t C, const fmpz_mat_t A, const fmpz_mat_t B){

    fmpz_mat_mul_classical(C, A, B);
}

strassenMultiply(fmpz_mat_t C, const fmpz_mat_t A, const fmpz_mat_t B, fmpz size){
    fmpz h;
    fmpz_mat_t h1, h2, p1, p2, p3, p4, p5, p6, p7;
    fmpz_mat_t a11, a12, a21, a22, b11, b12, b21, b22;
    h = size / 2;
    if (h <= 2){
        commonMultiply(C, A, B);
        return;
    }


    {
        fmpz_mat_init(h1, h, h);
        fmpz_mat_init(h2, h, h);
        fmpz_mat_init(p1, h, h);
        fmpz_mat_init(p2, h, h);
        fmpz_mat_init(p3, h, h);
        fmpz_mat_init(p4, h, h);
        fmpz_mat_init(p5, h, h);
        fmpz_mat_init(p6, h, h);
        fmpz_mat_init(p7, h, h);
        fmpz_mat_init(a11, h, h);
        fmpz_mat_init(a12, h, h);
        fmpz_mat_init(a21, h, h);
        fmpz_mat_init(a22, h, h);
        fmpz_mat_init(b11, h, h);
        fmpz_mat_init(b12, h, h);
        fmpz_mat_init(b21, h, h);
        fmpz_mat_init(b22, h, h);
    }


    copyElements(a11, A, 0, 0, 0, 0, h);
    copyElements(a12, A, 0, 0, 0, h, h);
    copyElements(a21, A, 0, 0, h, 0, h);
    copyElements(a22, A, 0, 0, h, h, h);

    copyElements(b11, B, 0, 0, 0, 0, h);
    copyElements(b12, B, 0, 0, 0, h, h);
    copyElements(b21, B, 0, 0, h, 0, h);
    copyElements(b22, B, 0, 0, h, h, h);

    fmpz_mat_add(h1, a11, a22);
    fmpz_mat_add(h2, b11, b22);
    strassenMultiply(p1, h1, h2, h);
    fmpz_mat_add(h1, a21, a22);
    strassenMultiply(p2, b11, h1, h);
    fmpz_mat_sub(h1, b12, b22);
    strassenMultiply(p3, a11, h1, h);
    fmpz_mat_sub(h1, b21, b11);
    strassenMultiply(p4, a22, h1, h);
    fmpz_mat_add(h1, a11, a12);
    strassenMultiply(p5, h1, b22, h);
    fmpz_mat_add(h1, a21, a11);
    fmpz_mat_add(h2, b11, b12);
    strassenMultiply(p6, h1, h2, h);
    fmpz_mat_add(h1, a12, a22);
    fmpz_mat_sub(h2, b21, b22);
    strassenMultiply(p7, h1, h2, h);


    fmpz_mat_add(h1, p2, p4);
    copyElements(C, h1, h, 0, 0, 0, h);
    fmpz_mat_add(h1, p3, p5);
    copyElements(C, h1, 0, h, 0, 0, h);
    fmpz_mat_add(h1, p1, p4);
    fmpz_mat_add(h1, h1, p7);
    fmpz_mat_sub(h1, h1, p5);
    copyElements(C, h1, 0, 0, 0, 0, h);
    fmpz_mat_sub(h1, p1, p2);
    fmpz_mat_add(h2, p3, p6);
    fmpz_mat_add(h1, h1, h2);
    copyElements(C, h1, h, h, 0, 0, h);


    {
        fmpz_mat_clear(h1);
        fmpz_mat_clear(h2);
        fmpz_mat_clear(p1);
        fmpz_mat_clear(p2);
        fmpz_mat_clear(p3);
        fmpz_mat_clear(p4);
        fmpz_mat_clear(p5);
        fmpz_mat_clear(p6);
        fmpz_mat_clear(p7);
        fmpz_mat_clear(a11);
        fmpz_mat_clear(a12);
        fmpz_mat_clear(a21);
        fmpz_mat_clear(a22);
        fmpz_mat_clear(b11);
        fmpz_mat_clear(b12);
        fmpz_mat_clear(b21);
        fmpz_mat_clear(b22);
    }
}

void copyElements(fmpz_mat_t dest, const fmpz_mat_t source,
              fmpz a, fmpz b, fmpz c, fmpz d, fmpz length){
    fmpz i, j;
    for (i = 0; i < length; i++){
        for (j = 0; j < length; j++){
            fmpz_set(fmpz_mat_entry(dest, a + i, b + j), fmpz_mat_entry(source, c + i, d + j));
        }
    }
}
